
/*

  KLayout Layout Viewer
  Copyright (C) 2006-2026 Matthias Koefferlein

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

*/

#if defined(HAVE_QT)

#include "edtPCellParametersPage.h"
#include "edtPropertiesPageUtils.h"
#include "edtConfig.h"
#include "layWidgets.h"
#include "layQtTools.h"
#include "layLayoutViewBase.h"
#include "layDispatcher.h"
#include "layBusy.h"
#include "tlScriptError.h"

#include <QFrame>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QScrollBar>
#include <QScrollArea>
#include <QToolButton>

namespace
{

class FixedSizeQGroupBox
  : public QGroupBox
{
public:
  FixedSizeQGroupBox (QWidget *parent)
    : QGroupBox (parent)
  {
    //  NOTE: we do vertical resizing explicity on apply_states
    setSizePolicy (QSizePolicy::Preferred, QSizePolicy::Fixed);
  }

  QSize sizeHint () const
  {
    return m_preferred_size;
  }

  void update_size_hint ()
  {
    m_preferred_size = QGroupBox::sizeHint ();
    updateGeometry ();
  }

private:
  QSize m_preferred_size;
};

}

namespace edt
{

static std::string variant_list_to_string (const tl::Variant &value)
{
  if (! value.is_list ()) {
    tl::Variant v = tl::Variant::empty_list ();
    v.push (value);
    return v.to_parsable_string ();
  }

  for (auto i = value.begin (); i != value.end (); ++i) {
    if (! i->is_a_string () || std::string (i->to_string ()).find (",") != std::string::npos) {
      return value.to_parsable_string ();
    }
  }

  //  otherwise we can plainly combine the strings with ","
  std::string res;
  for (auto i = value.begin (); i != value.end (); ++i) {
    if (i != value.begin ()) {
      res += ",";
    }
    res += i->to_string ();
  }
  return res;
}

static void set_value (const db::PCellParameterDeclaration &p, QWidget *widget, const tl::Variant &value)
{
  if (p.get_choices ().empty ()) {

    switch (p.get_type ()) {
      
    case db::PCellParameterDeclaration::t_int:
      {
        QLineEdit *le = dynamic_cast<QLineEdit *> (widget);
        if (le) {
          le->blockSignals (true);
          le->setText (value.cast<int> ().to_qstring ());
          le->blockSignals (false);
        }
      }
      break;

    case db::PCellParameterDeclaration::t_double:
      {
        QLineEdit *le = dynamic_cast<QLineEdit *> (widget);
        if (le) {
          le->blockSignals (true);
          le->setText (value.cast<double> ().to_qstring ());
          le->blockSignals (false);
        }
      }
      break;

    case db::PCellParameterDeclaration::t_string:
      {
        QLineEdit *le = dynamic_cast<QLineEdit *> (widget);
        if (le) {
          le->blockSignals (true);
          le->setText (value.to_qstring ());
          le->blockSignals (false);
        }
      }
      break;

    case db::PCellParameterDeclaration::t_list:
      {
        QLineEdit *le = dynamic_cast<QLineEdit *> (widget);
        if (le) {
          le->blockSignals (true);
          le->setText (tl::to_qstring (variant_list_to_string (value)));
          le->blockSignals (false);
        }
      }
      break;

    case db::PCellParameterDeclaration::t_layer:
      {
        lay::LayerSelectionComboBox *ly = dynamic_cast<lay::LayerSelectionComboBox *> (widget);
        if (ly) {

          db::LayerProperties lp;
          if (value.is_user<db::LayerProperties> ()) {
            lp = value.to_user<db::LayerProperties> ();
          } else if (value.is_nil ()) {
            //  empty LayerProperties
          } else {
            std::string s = value.to_string ();
            tl::Extractor ex (s.c_str ());
            lp.read (ex);
          }

          ly->blockSignals (true);
          ly->set_current_layer (lp);
          ly->blockSignals (false);

        }
      }
      break;

    case db::PCellParameterDeclaration::t_boolean:
      {
        QCheckBox *cbx = dynamic_cast<QCheckBox *> (widget);
        if (cbx) {
          cbx->blockSignals (true);
          cbx->setChecked (value.to_bool ());
          cbx->blockSignals (false);
        }
      }
      break;

    default:
      break;
    }

  } else {

    QComboBox *cb = dynamic_cast<QComboBox *> (widget);
    if (cb) {
      int i = 0;
      for (std::vector<tl::Variant>::const_iterator c = p.get_choices ().begin (); c != p.get_choices ().end (); ++c, ++i) {
        if (*c == value) {
          cb->blockSignals (true);
          cb->setCurrentIndex (i);
          cb->blockSignals (false);
        }
      }
    }

  }
}

PCellParametersPage::PCellParametersPage ()
  : PCellParametersPageBase ()
{
  m_s2s_parameter_changed_slot.triggered.add (this, &PCellParametersPage::parameter_changed_slot);
}

void
PCellParametersPage::build_widgets (QFrame *container)
{
  mp_groups.clear ();
  m_widgets.clear ();
  m_icon_widgets.clear ();
  m_all_widgets.clear ();

  QGridLayout *main_grid = new QGridLayout (container);
  if (dense ()) {
    main_grid->setContentsMargins (4, 4, 4, 4);
    main_grid->setHorizontalSpacing (6);
    main_grid->setVerticalSpacing (2);
  }

  container->setLayout (main_grid);

  QWidget *inner_frame = container;
  QGridLayout *inner_grid = main_grid;

  int main_row = 0;
  int row = 0;
  std::string group_title;

  const std::vector<db::PCellParameterDeclaration> &pcp = pcell_decl ()->parameter_declarations ();
  for (std::vector<db::PCellParameterDeclaration>::const_iterator p = pcp.begin (); p != pcp.end (); ++p) {

    m_all_widgets.push_back (std::vector<QWidget *> ());

    if (p->get_type () == db::PCellParameterDeclaration::t_shape) {
      m_widgets.push_back (0);
      m_icon_widgets.push_back (0);
      continue;
    }

    std::string gt, description;
    size_t tab = p->get_description ().find ("\t");
    if (tab != std::string::npos) {
      gt = std::string (p->get_description (), 0, tab);
      description = std::string (p->get_description (), tab + 1, std::string::npos);
    } else {
      description = p->get_description ();
    }

    if (gt != group_title) {

      if (! gt.empty ()) {

        //  create a new group
        QGroupBox *gb = new FixedSizeQGroupBox (container);
        mp_groups.push_back (gb);
        gb->setTitle (tl::to_qstring (gt));
        main_grid->addWidget (gb, main_row, 0, 1, 3);

        inner_grid = new QGridLayout (gb);
        if (dense ()) {
          inner_grid->setContentsMargins (4, 4, 4, 4);
          inner_grid->setHorizontalSpacing (6);
          inner_grid->setVerticalSpacing (2);
        }
        gb->setLayout (inner_grid);
        inner_frame = gb;

        row = 0;
        ++main_row;

      } else {

        //  back to the main group
        inner_grid = main_grid;
        inner_frame = container;
        row = main_row;

      }

      group_title = gt;

    }

    QLabel *icon_label = new QLabel (QString (), inner_frame);
    inner_grid->addWidget (icon_label, row, 0);
    m_icon_widgets.push_back (icon_label);
    m_all_widgets.back ().push_back (icon_label);

    std::string range;

    if (! p->min_value ().is_nil () || ! p->max_value ().is_nil ()) {
      range = tl::sprintf (
                " [%s, %s]" ,
                p->min_value ().is_nil () ? "-\u221e" /*infinity*/ : p->min_value ().to_string (),
                p->max_value ().is_nil () ? "\u221e"  /*infinity*/ : p->max_value ().to_string ()
              );
    }

    if (p->get_type () != db::PCellParameterDeclaration::t_callback) {

      std::string leader;
      if (show_parameter_names ()) {
        leader = tl::sprintf ("[%s] ", p->get_name ());
      }

      QLabel *l = new QLabel (tl::to_qstring (leader + description + range), inner_frame);
      inner_grid->addWidget (l, row, 1);
      m_all_widgets.back ().push_back (l);

    } else if (show_parameter_names ()) {

      QLabel *l = new QLabel (tl::to_qstring (tl::sprintf ("[%s]", p->get_name ())), inner_frame);
      inner_grid->addWidget (l, row, 1);
      m_all_widgets.back ().push_back (l);

    }

    if (p->get_choices ().empty ()) {

      switch (p->get_type ()) {

      case db::PCellParameterDeclaration::t_int:
      case db::PCellParameterDeclaration::t_double:
        {
          QFrame *f = new QFrame (inner_frame);
          QHBoxLayout *hb = new QHBoxLayout (f);
          hb->setContentsMargins (0, 0, 0, 0);
          f->setLayout (hb);
          f->setFrameShape (QFrame::NoFrame);
          QSizePolicy sp = f->sizePolicy ();
          sp.setHorizontalStretch (1);
          f->setSizePolicy (sp);

          QLineEdit *le = new QLineEdit (f);
          hb->addWidget (le);
          le->setMaximumWidth (150);
          le->setObjectName (tl::to_qstring (p->get_name ()));
          m_widgets.push_back (le);

          if (! p->get_unit ().empty ()) {
            QLabel *ul = new QLabel (f);
            hb->addWidget (ul, 1);
            ul->setText (tl::to_qstring (p->get_unit ()));
          }

          hb->addStretch (1);

          inner_grid->addWidget (f, row, 2);
          m_all_widgets.back ().push_back (f);

          QObject::connect (le, SIGNAL (editingFinished ()), &m_s2s_parameter_changed_slot, SLOT (trigger ()));
        }
        break;

      case db::PCellParameterDeclaration::t_callback:
        {
          QPushButton *pb = new QPushButton (inner_frame);
          pb->setObjectName (tl::to_qstring (p->get_name ()));
          pb->setText (tl::to_qstring (description));
          QSizePolicy sp = pb->sizePolicy ();
          sp.setHorizontalPolicy (QSizePolicy::Fixed);
          sp.setHorizontalStretch (1);
          pb->setSizePolicy (sp);
          m_widgets.push_back (pb);

          inner_grid->addWidget (pb, row, 2);
          m_all_widgets.back ().push_back (pb);

          QObject::connect (pb, SIGNAL (clicked ()), &m_s2s_parameter_changed_slot, SLOT (trigger ()));
        }
        break;

      case db::PCellParameterDeclaration::t_string:
      case db::PCellParameterDeclaration::t_shape:
      case db::PCellParameterDeclaration::t_list:
        {
          QLineEdit *le = new QLineEdit (inner_frame);
          le->setObjectName (tl::to_qstring (p->get_name ()));
          QSizePolicy sp = le->sizePolicy ();
          sp.setHorizontalStretch (1);
          le->setSizePolicy (sp);
          m_widgets.push_back (le);
          inner_grid->addWidget (le, row, 2);
          m_all_widgets.back ().push_back (le);

          QObject::connect (le, SIGNAL (editingFinished ()), &m_s2s_parameter_changed_slot, SLOT (trigger ()));
        }
        break;

      case db::PCellParameterDeclaration::t_layer:
        {
          QFrame *f = new QFrame (inner_frame);
          QHBoxLayout *hb = new QHBoxLayout (f);
          hb->setContentsMargins (0, 0, 0, 0);
          f->setLayout (hb);
          f->setFrameShape (QFrame::NoFrame);
          QSizePolicy sp = f->sizePolicy ();
          sp.setHorizontalStretch (1);
          f->setSizePolicy (sp);

          lay::LayerSelectionComboBox *ly = new lay::LayerSelectionComboBox (f);
          hb->addWidget (ly);
          ly->set_no_layer_available (true);
          ly->set_view (view (), cv_index (), true /*all layers*/);
          ly->setObjectName (tl::to_qstring (p->get_name ()));
          sp = ly->sizePolicy ();
          sp.setHorizontalPolicy (QSizePolicy::Fixed);
          ly->setSizePolicy (sp);
          m_widgets.push_back (ly);

          hb->addStretch (1);

          inner_grid->addWidget (f, row, 2);
          m_all_widgets.back ().push_back (f);

          QObject::connect (ly, SIGNAL (activated (int)), &m_s2s_parameter_changed_slot, SLOT (trigger ()));
        }
        break;

      case db::PCellParameterDeclaration::t_boolean:
        {
          QCheckBox *cbx = new QCheckBox (inner_frame);
          //  this makes the checkbox not stretch over the full width - better when navigating with tab
          QSizePolicy sp = cbx->sizePolicy ();
          sp.setHorizontalStretch (1);
          cbx->setSizePolicy (sp);
          cbx->setObjectName (tl::to_qstring (p->get_name ()));
          m_widgets.push_back (cbx);
          inner_grid->addWidget (cbx, row, 2);
          m_all_widgets.back ().push_back (cbx);

          QObject::connect (cbx, SIGNAL (stateChanged (int)), &m_s2s_parameter_changed_slot, SLOT (trigger ()));
        }
        break;

      default:
        m_widgets.push_back (0);
        break;
      }

    } else {

      QFrame *f = new QFrame (inner_frame);
      QHBoxLayout *hb = new QHBoxLayout (f);
      hb->setContentsMargins (0, 0, 0, 0);
      f->setLayout (hb);
      f->setFrameShape (QFrame::NoFrame);
      QSizePolicy sp = f->sizePolicy ();
      sp.setHorizontalStretch (1);
      f->setSizePolicy (sp);

      QComboBox *cb = new QComboBox (f);
      hb->addWidget (cb);
      cb->setObjectName (tl::to_qstring (p->get_name ()));
      cb->setSizePolicy (QSizePolicy::Fixed, QSizePolicy::Preferred);
      cb->setSizeAdjustPolicy (QComboBox::AdjustToContents);

      int i = 0;
      for (std::vector<tl::Variant>::const_iterator c = p->get_choices ().begin (); c != p->get_choices ().end (); ++c, ++i) {
        if (i < int (p->get_choice_descriptions ().size ())) {
          cb->addItem (tl::to_qstring (p->get_choice_descriptions () [i]));
        } else {
          cb->addItem (tl::to_qstring (c->to_string ()));
        }
      }

      QObject::connect (cb, SIGNAL (activated (int)), &m_s2s_parameter_changed_slot, SLOT (trigger ()));

      m_widgets.push_back (cb);

      hb->addStretch (1);

      inner_grid->addWidget (f, row, 2);
      m_all_widgets.back ().push_back (f);

    }

    ++row;
    if (inner_frame == container) {
      ++main_row;
    }

  }

  //  adds some default buffer space
  main_grid->setRowStretch (main_row, 1);
}

void
PCellParametersPage::parameter_changed_slot (QObject *sender)
{
  if (! pcell_decl ()) {
    return;
  }

  const std::vector<db::PCellParameterDeclaration> &pcp = pcell_decl ()->parameter_declarations ();
  const db::PCellParameterDeclaration *pd = 0;
  for (auto w = m_widgets.begin (); w != m_widgets.end (); ++w) {
    if (*w == sender) {
      pd = &pcp [w - m_widgets.begin ()];
      break;
    }
  }

  parameter_changed (pd ? pd->get_name () : std::string ());
}

void
PCellParametersPage::commit_values (db::ParameterStates &states)
{
  bool edit_error = false;

  int r = 0;
  const std::vector<db::PCellParameterDeclaration> &pcp = pcell_decl ()->parameter_declarations ();
  for (std::vector<db::PCellParameterDeclaration>::const_iterator p = pcp.begin (); p != pcp.end (); ++p, ++r) {

    db::ParameterState &ps = states.parameter (p->get_name ());

    if (! ps.is_visible () || ! ps.is_enabled () || ps.is_readonly () || p->get_type () == db::PCellParameterDeclaration::t_shape) {
      continue;
    }

    if (p->get_choices ().empty ()) {

      switch (p->get_type ()) {

      case db::PCellParameterDeclaration::t_int:
        {
          QLineEdit *le = dynamic_cast<QLineEdit *> (m_widgets [r]);
          if (le) {

            try {

              int v = 0;
              tl::from_string_ext (tl::to_string (le->text ()), v);

              ps.set_value (tl::Variant (v));
              lay::indicate_error (le, (tl::Exception *) 0);

              check_range (tl::Variant (v), p->get_name ());

            } catch (tl::Exception &ex) {

              lay::indicate_error (le, &ex);
              edit_error = true;

            }

          }
        }
        break;

      case db::PCellParameterDeclaration::t_double:
        {
          QLineEdit *le = dynamic_cast<QLineEdit *> (m_widgets [r]);
          if (le) {

            try {

              double v = 0;
              tl::from_string_ext (tl::to_string (le->text ()), v);

              ps.set_value (tl::Variant (v));
              lay::indicate_error (le, (tl::Exception *) 0);

              check_range (tl::Variant (v), p->get_name ());

            } catch (tl::Exception &ex) {

              lay::indicate_error (le, &ex);
              edit_error = true;

            }

          }
        }
        break;

      case db::PCellParameterDeclaration::t_string:
        {
          QLineEdit *le = dynamic_cast<QLineEdit *> (m_widgets [r]);
          if (le) {
            ps.set_value (tl::Variant (tl::to_string (le->text ())));
          }
        }
        break;

      case db::PCellParameterDeclaration::t_list:
        {
          QLineEdit *le = dynamic_cast<QLineEdit *> (m_widgets [r]);
          if (le) {

            std::string s = tl::to_string (le->text ());

            //  try parsing a bracketed expression
            tl::Extractor ex (s.c_str ());
            if (*ex.skip () == '(') {
              tl::Variant v;
              try {
                ex.read (v);
                ps.set_value (v);
                break;
              } catch (...) {
                //  ignore errors
              }
            } else if (ex.at_end ()) {
              ps.set_value (tl::Variant::empty_list ());
              break;
            }

            //  otherwise: plain splitting at comma
            std::vector<std::string> values = tl::split (s, ",");
            ps.set_value (tl::Variant (values.begin (), values.end ()));

          }
        }
        break;

      case db::PCellParameterDeclaration::t_layer:
        {
          lay::LayerSelectionComboBox *ly = dynamic_cast<lay::LayerSelectionComboBox *> (m_widgets [r]);
          if (ly) {
            ps.set_value (tl::Variant (ly->current_layer_props ()));
          }
        }
        break;
      case db::PCellParameterDeclaration::t_boolean:
        {
          QCheckBox *cbx = dynamic_cast<QCheckBox *> (m_widgets [r]);
          if (cbx) {
            ps.set_value (tl::Variant (cbx->isChecked ()));
          }
        }
        break;

      default:
        break;
      }

    } else {

      QComboBox *cb = dynamic_cast<QComboBox*> (m_widgets [r]);
      if (cb && cb->currentIndex () >= 0 && cb->currentIndex () < int (p->get_choices ().size ())) {
        ps.set_value (p->get_choices () [cb->currentIndex ()]);
      }

    }

  }

  if (edit_error) {
    throw tl::Exception (tl::to_string (tr ("There are errors. See the highlighted edit fields for details.")));
  }
}

void
PCellParametersPage::apply_states (const db::ParameterStates &states)
{
  const std::vector<db::PCellParameterDeclaration> &pcp = pcell_decl ()->parameter_declarations ();
  for (std::vector<db::PCellParameterDeclaration>::const_iterator p = pcp.begin (); p != pcp.end (); ++p) {

    size_t i = p - pcp.begin ();
    if (i >= m_widgets.size ()) {
      break;
    }

    const std::string &name = p->get_name ();
    const std::string &static_tooltip = p->get_tooltip ();
    const db::ParameterState &ps = states.parameter (name);

    if (m_widgets [i]) {
      QLineEdit *le = dynamic_cast<QLineEdit *> (m_widgets [i]);
      if (le) {
        le->setEnabled (ps.is_enabled ());
        le->setReadOnly (ps.is_readonly ());
      } else {
        m_widgets [i]->setEnabled (ps.is_enabled () && ! ps.is_readonly ());
      }
    }

    for (auto w = m_all_widgets [i].begin (); w != m_all_widgets [i].end (); ++w) {
      if (*w != m_widgets [i]) {
        (*w)->setEnabled (ps.is_enabled ());
      }
      if (*w != m_icon_widgets [i]) {
        (*w)->setVisible (ps.is_visible ());
      }
      if (ps.tooltip ().empty ()) {
        (*w)->setToolTip (tl::to_qstring (static_tooltip));
      } else {
        (*w)->setToolTip (tl::to_qstring (ps.tooltip ()));
      }
    }

    if (m_icon_widgets [i]) {

      switch (ps.icon ()) {
      case db::ParameterState::NoIcon:
      default:
        m_icon_widgets [i]->setPixmap (QPixmap ());
        m_icon_widgets [i]->hide ();
        break;
      case db::ParameterState::InfoIcon:
        m_icon_widgets [i]->setPixmap (info_pixmap ());
        m_icon_widgets [i]->setVisible (ps.is_visible ());
        break;
      case db::ParameterState::WarningIcon:
        m_icon_widgets [i]->setPixmap (warning_pixmap ());
        m_icon_widgets [i]->setVisible (ps.is_visible ());
        break;
      case db::ParameterState::ErrorIcon:
        m_icon_widgets [i]->setPixmap (error_pixmap ());
        m_icon_widgets [i]->setVisible (ps.is_visible ());
        break;
      }

    }

  }

  //  QGridLayouts are bad in handling nested QFrame (or QGroupBox) with their own layouts,
  //  so we help a little here:
  for (auto g = mp_groups.begin (); g != mp_groups.end (); ++g) {
    FixedSizeQGroupBox *fgb = dynamic_cast<FixedSizeQGroupBox *> (*g);
    if (fgb) {
      fgb->update_size_hint ();
    }
  }

}

void
PCellParametersPage::apply_values (const db::ParameterStates &states)
{
  const std::vector<db::PCellParameterDeclaration> &pcp = pcell_decl ()->parameter_declarations ();
  for (std::vector<db::PCellParameterDeclaration>::const_iterator p = pcp.begin (); p != pcp.end (); ++p) {
    size_t r = p - pcp.begin ();
    if (m_widgets [r]) {
      set_value (*p, m_widgets [r], states.parameter (p->get_name ()).value ());
    }
  }
}

}

#endif
