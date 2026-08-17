
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

#include "edtPCellParametersPageBase.h"
#include "edtConfig.h"
#include "layLayoutViewBase.h"
#include "layDispatcher.h"
#include "layBusy.h"
#include "tlScriptError.h"

#include <QFrame>
#include <QLabel>
#include <QGridLayout>
#include <QScrollBar>
#include <QScrollArea>
#include <QToolButton>

namespace edt
{

PCellParametersPageBase::PCellParametersPageBase ()
  : m_parameter_changed_enabled (false),
    m_dense (false),
    mp_dispatcher (0),
    m_show_parameter_names (false),
    m_lazy_evaluation (-1),
    dm_parameter_changed (this, &PCellParametersPageBase::do_parameter_changed),
    dm_delete_me (this, &PCellParametersPageBase::do_delete_me),
    m_s2s_lazy_eval_mode_slotm1 (-1),
    m_s2s_lazy_eval_mode_slot0 (0),
    m_s2s_lazy_eval_mode_slot1 (1)
{
  mp_page_widget = new QFrame (0);
  mp_page_widget->setFrameShape (QFrame::NoFrame);

  m_s2s_update_button_pressed.triggered.add (this, &PCellParametersPageBase::update_button_pressed_slot);
  m_s2s_lazy_eval_mode_slotm1.triggered.add (this, &PCellParametersPageBase::lazy_eval_mode);
  m_s2s_lazy_eval_mode_slot0.triggered.add (this, &PCellParametersPageBase::lazy_eval_mode);
  m_s2s_lazy_eval_mode_slot1.triggered.add (this, &PCellParametersPageBase::lazy_eval_mode);
  m_s2s_show_parameter_names_slot.triggered.add (this, &PCellParametersPageBase::show_parameter_names_slot);
}

PCellParametersPageBase::~PCellParametersPageBase ()
{
  if (mp_page_widget) {
    delete mp_page_widget.data ();
  }
}

void
PCellParametersPageBase::do_delete_me ()
{
  delete this;
}

void
PCellParametersPageBase::set_parent (QWidget *p)
{
  tl_assert (mp_page_widget->parent () == 0);
  tl_assert (p != 0);
  mp_page_widget->setParent (p);
  init ();
}

void
PCellParametersPageBase::set_dense (bool d)
{
  tl_assert (mp_page_widget->parent () == 0);
  m_dense = d;
}

tl::Variant
PCellParametersPageBase::get_user_state ()
{
  return tl::Variant ();
}

void
PCellParametersPageBase::set_user_state (const tl::Variant & /*user_state*/)
{
  //  .. nothing yet ..
}

void
PCellParametersPageBase::init ()
{
  tl_assert (mp_page_widget);

  QPalette palette;
  QFont font;

  mp_pcell_decl.reset (0);
  mp_view = 0;
  m_cv_index = 0;
  mp_parameters_area = 0;

  QGridLayout *frame_layout = new QGridLayout (mp_page_widget.data ());
  //  spacing and margin for tool windows
  frame_layout->setContentsMargins (0, 0, 0, 0);
  frame_layout->setHorizontalSpacing (0);
  frame_layout->setVerticalSpacing (0);
  mp_page_widget->setLayout (frame_layout);

  mp_update_frame = new QFrame (mp_page_widget.data ());
  mp_update_frame->setFrameShape (QFrame::NoFrame);
  frame_layout->addWidget (mp_update_frame, 0, 0, 1, 1);

  QGridLayout *update_frame_layout = new QGridLayout (mp_update_frame);
  mp_update_frame->setLayout (update_frame_layout);
  if (m_dense) {
    update_frame_layout->setContentsMargins (4, 4, 4, 4);
    update_frame_layout->setHorizontalSpacing (6);
    update_frame_layout->setVerticalSpacing (2);
  }

  mp_changed_icon = new QLabel (mp_update_frame);
  mp_changed_icon->setPixmap (QPixmap (":/warn_16px@2x.png"));
  update_frame_layout->addWidget (mp_changed_icon, 0, 0, 1, 1);

  mp_update_button = new QToolButton (mp_update_frame);
  mp_update_button->setText (tr ("Update"));
  QObject::connect (mp_update_button, SIGNAL (clicked()), &m_s2s_update_button_pressed, SLOT (trigger ()));
  update_frame_layout->addWidget (mp_update_button, 0, 1, 1, 1);

  mp_changed_label = new QLabel (mp_update_frame);
  mp_changed_label->setText (tr ("Update needed"));
  update_frame_layout->addWidget (mp_changed_label, 0, 2, 1, 1);

  update_frame_layout->setColumnStretch (2, 1);

  mp_error_frame = new QFrame (mp_page_widget.data ());
  mp_error_frame->setFrameShape (QFrame::NoFrame);
  frame_layout->addWidget (mp_error_frame, 1, 0, 1, 1);

  QGridLayout *error_frame_layout = new QGridLayout (mp_error_frame);
  mp_error_frame->setLayout (error_frame_layout);
  if (m_dense) {
    error_frame_layout->setContentsMargins (4, 4, 4, 4);
    error_frame_layout->setHorizontalSpacing (6);
    error_frame_layout->setVerticalSpacing (2);
  }

  mp_error_icon = new QLabel (mp_error_frame);
  mp_error_icon->setPixmap (QPixmap (":/warn_16px@2x.png"));
  error_frame_layout->addWidget (mp_error_icon, 1, 0, 1, 1);

  mp_error_label = new QLabel (mp_error_frame);
  mp_error_label->setWordWrap (true);
  palette = mp_error_label->palette ();
  palette.setColor (QPalette::WindowText, Qt::red);
  mp_error_label->setPalette (palette);
  font = mp_error_label->font ();
  font.setBold (true);
  mp_error_label->setFont (font);
  error_frame_layout->addWidget (mp_error_label, 1, 1, 1, 2);

  error_frame_layout->setColumnStretch (2, 1);

  QFrame *options_frame = new QFrame (mp_page_widget.data ());
  options_frame->setFrameShape (QFrame::NoFrame);
  frame_layout->addWidget (options_frame, 3, 0, 1, 1);

  QHBoxLayout *options_frame_layout = new QHBoxLayout (options_frame);
  options_frame->setLayout (options_frame_layout);
  if (m_dense) {
    options_frame_layout->setContentsMargins (4, 4, 4, 4);
  }

  QToolButton *dot_menu_button = new QToolButton (options_frame);
  dot_menu_button->setText (tr ("Options "));
  dot_menu_button->setAutoRaise (true);
  dot_menu_button->setPopupMode (QToolButton::InstantPopup);
  dot_menu_button->setToolButtonStyle (Qt::ToolButtonTextOnly);
  options_frame_layout->addWidget (dot_menu_button);
  options_frame_layout->addStretch ();

  QMenu *dot_menu = new QMenu (dot_menu_button);
  dot_menu_button->setMenu (dot_menu);
  mp_show_parameter_names_action = new QAction (dot_menu);
  dot_menu->addAction (mp_show_parameter_names_action);
  mp_show_parameter_names_action->setText (tr ("Show parameter names"));
  mp_show_parameter_names_action->setCheckable (true);
  QObject::connect (mp_show_parameter_names_action, SIGNAL (triggered (bool)), &m_s2s_show_parameter_names_slot, SLOT (trigger (bool)));

  QMenu *lazy_eval_menu = new QMenu (dot_menu);
  lazy_eval_menu->setTitle (tr ("Lazy PCell evaluation"));
  dot_menu->addMenu (lazy_eval_menu);

  mp_auto_lazy_eval_action = new QAction (lazy_eval_menu);
  lazy_eval_menu->addAction (mp_auto_lazy_eval_action);
  mp_auto_lazy_eval_action->setText (tr ("As requested by PCell"));
  mp_auto_lazy_eval_action->setCheckable (true);
  QObject::connect (mp_auto_lazy_eval_action, SIGNAL (triggered ()), &m_s2s_lazy_eval_mode_slotm1, SLOT (trigger ()));

  mp_always_lazy_eval_action = new QAction (lazy_eval_menu);
  lazy_eval_menu->addAction (mp_always_lazy_eval_action);
  mp_always_lazy_eval_action->setText (tr ("Always"));
  mp_always_lazy_eval_action->setCheckable (true);
  QObject::connect (mp_always_lazy_eval_action, SIGNAL (triggered ()), &m_s2s_lazy_eval_mode_slot1, SLOT (trigger ()));

  mp_never_lazy_eval_action = new QAction (lazy_eval_menu);
  lazy_eval_menu->addAction (mp_never_lazy_eval_action);
  mp_never_lazy_eval_action->setText (tr ("Never"));
  mp_never_lazy_eval_action->setCheckable (true);
  QObject::connect (mp_never_lazy_eval_action, SIGNAL (triggered ()), &m_s2s_lazy_eval_mode_slot0, SLOT (trigger ()));
}

void
PCellParametersPageBase::build_widgets (QFrame * /*container*/)
{
  //  .. nothing yet ..
}

bool
PCellParametersPageBase::lazy_evaluation ()
{
  if (m_lazy_evaluation < 0) {
    return mp_pcell_decl.get () && mp_pcell_decl->wants_lazy_evaluation ();
  } else {
    return m_lazy_evaluation > 0;
  }
}

void
PCellParametersPageBase::lazy_eval_mode (int mode)
{
  if (mode == m_lazy_evaluation) {
    return;
  }

  m_lazy_evaluation = mode;

  if (mp_dispatcher) {
    mp_dispatcher->config_set (cfg_edit_pcell_lazy_eval_mode, m_lazy_evaluation);
  }

  setup (mp_view, mp_dispatcher, m_cv_index, mp_pcell_decl.get (), get_parameters ());
}

void
PCellParametersPageBase::show_parameter_names_slot (bool f)
{
  if (m_show_parameter_names == f) {
    return;
  }

  m_show_parameter_names = f;

  if (mp_dispatcher) {
    mp_dispatcher->config_set (cfg_edit_pcell_show_parameter_names, m_show_parameter_names);
  }

  setup (mp_view, mp_dispatcher, m_cv_index, mp_pcell_decl.get (), get_parameters ());
}

void
PCellParametersPageBase::setup (lay::LayoutViewBase *view, lay::Dispatcher *dispatcher, int cv_index, const db::PCellDeclaration *pcell_decl, const db::pcell_parameters_type &parameters)
{
  tl_assert (mp_page_widget && mp_page_widget->parent () != 0);

  if (mp_dispatcher != dispatcher) {

    mp_dispatcher = dispatcher;

    mp_dispatcher->config_get (cfg_edit_pcell_show_parameter_names, m_show_parameter_names);
    mp_dispatcher->config_get (cfg_edit_pcell_lazy_eval_mode, m_lazy_evaluation);

  }

  mp_show_parameter_names_action->setChecked (m_show_parameter_names);

  mp_auto_lazy_eval_action->setChecked (m_lazy_evaluation < 0);
  mp_always_lazy_eval_action->setChecked (m_lazy_evaluation > 0);
  mp_never_lazy_eval_action->setChecked (m_lazy_evaluation == 0);

  mp_pcell_decl.reset (const_cast<db::PCellDeclaration *> (pcell_decl));  //  no const weak_ptr ...
  mp_view = view;
  m_cv_index = cv_index;
  m_states = db::ParameterStates ();
  m_initial_states = db::ParameterStates ();

  const std::vector<db::PCellParameterDeclaration> &pcp = pcell_decl->parameter_declarations ();

  //  initialize states
  for (std::vector<db::PCellParameterDeclaration>::const_iterator p = pcp.begin (); p != pcp.end (); ++p) {

    size_t i = p - pcp.begin ();

    tl::Variant value;
    if (i < parameters.size ()) {
      value = parameters [i];
    } else {
      value = p->get_default ();
    }

    db::ParameterState &ps = m_states.parameter (p->get_name ());
    ps.set_value (value);
    ps.set_readonly (p->is_readonly ());
    ps.set_visible (! p->is_hidden ());

  }

  if (mp_parameters_area) {
    delete mp_parameters_area;
  }

  mp_parameters_area = new QScrollArea (mp_page_widget.data ());
  mp_parameters_area->setFrameShape (QFrame::NoFrame);
  mp_parameters_area->setWidgetResizable (true);
  QGridLayout *frame_layout = dynamic_cast<QGridLayout *> (mp_page_widget->layout ());
  frame_layout->addWidget (mp_parameters_area, 2, 0, 1, 1);
  frame_layout->setRowStretch (2, 1);

  mp_main_frame = new QFrame (mp_parameters_area);
  mp_main_frame->setFrameShape (QFrame::NoFrame);

  if (! mp_pcell_decl) {

    QGridLayout *main_grid = new QGridLayout (mp_main_frame);
    mp_main_frame->setLayout (main_grid);
    if (m_dense) {
      main_grid->setContentsMargins (4, 4, 4, 4);
      main_grid->setHorizontalSpacing (6);
      main_grid->setVerticalSpacing (2);
    }

    mp_parameters_area->setWidget (mp_main_frame);
    update_current_parameters ();

    return;

  }

  //  block parameter change events during setup
  m_parameter_changed_enabled = false;

  try {

    //  populate the main frame with widgets
    build_widgets (mp_main_frame);

    //  initial callback

    if (mp_pcell_decl->layout ()) {
      mp_pcell_decl->callback (*mp_pcell_decl->layout (), std::string (), m_states);
    }

  } catch (tl::Exception &ex) {
    //  potentially caused by script errors in callback implementation
    tl::error << ex.msg ();
  } catch (std::runtime_error &ex) {
    tl::error << ex.what ();
  } catch (...) {
    //  ignore other errors
  }

  m_parameter_changed_enabled = true;

  m_initial_states = m_states;
  mp_error_frame->hide ();

  update_widgets_from_states (m_states, lazy_evaluation ());

  mp_parameters_area->setWidget (mp_main_frame);
  mp_main_frame->show ();

  update_current_parameters ();
}

PCellParametersPageBase::State
PCellParametersPageBase::get_state ()
{
  State s;
  if (! mp_page_widget) {
    return s;
  }

  s.valid = true;
  s.v_scroll_position = mp_parameters_area->verticalScrollBar ()->value ();
  s.h_scroll_position = mp_parameters_area->horizontalScrollBar ()->value ();

  if (mp_page_widget->focusWidget ()) {
    s.focus_widget = mp_page_widget->focusWidget ()->objectName ();
  }

  s.user_state = get_user_state ();

  return s;
}

void
PCellParametersPageBase::set_state (const State &s)
{
  if (s.valid && mp_page_widget) {

    mp_parameters_area->verticalScrollBar ()->setValue (s.v_scroll_position);
    mp_parameters_area->horizontalScrollBar ()->setValue (s.h_scroll_position);

    if (! s.focus_widget.isEmpty ()) {
      QWidget *c = mp_page_widget->findChild<QWidget *> (s.focus_widget);
      if (c) {
        c->setFocus ();
      }
    }

    set_user_state (s.user_state);

  }
}

void
PCellParametersPageBase::parameter_changed (const std::string &name)
{
  if (! mp_pcell_decl) {
    return;
  }
  if (! mp_view->cellview (m_cv_index).is_valid ()) {
    return;
  }
  if (lay::BusySection::is_busy ()) {
    //  ignore events for example during debugger execution
    return;
  }

  if (! m_parameter_changed_enabled) {
    return;
  }
  //  prevent recursive calls
  m_parameter_changed_enabled = false;

  db::ParameterStates states = m_states;

  bool edit_error = true;
  try {
    //  Silent and without coerce - this will be done later in do_parameter_changed().
    //  This is just about providing the inputs for the callback.
    commit_values (states);
    edit_error = false;
  } catch (...) {
    //  Ignore errors here
  }

  if (! edit_error) {

    try {

      //  Note: checking for is_busy prevents callbacks during debugger execution
      if (mp_pcell_decl->layout ()) {
        mp_pcell_decl->callback (*mp_pcell_decl->layout (), name, states);
      }
      m_states = states;

    } catch (tl::Exception &ex) {
      //  potentially caused by script errors in callback implementation
      tl::error << ex.msg ();
    } catch (std::runtime_error &ex) {
      tl::error << ex.what ();
    } catch (...) {
      //  ignore other errors
    }

  }

  m_parameter_changed_enabled = true;

  dm_parameter_changed ();
}

void
PCellParametersPageBase::delete_later ()
{
  if (mp_page_widget) {
    mp_page_widget->hide ();
  }

  dm_parameter_changed.cancel ();
  dm_delete_me ();
}

void
PCellParametersPageBase::do_parameter_changed ()
{
  bool ok = true;
  db::ParameterStates states = m_states;
  get_parameters (states, &ok);   //  includes coerce
  if (ok) {
    update_widgets_from_states (states, lazy_evaluation ());
    if (! lazy_evaluation ()) {
      edited ();
    }
  }
}

void
PCellParametersPageBase::update_button_pressed_slot ()
{
  if (update_current_parameters ()) {
    edited ();
  }
}

bool
PCellParametersPageBase::update_current_parameters ()
{
  bool ok = true;
  db::ParameterStates states = m_states;
  get_parameters (states, &ok);   //  includes coerce
  if (ok) {
    m_current_states = states;
    mp_update_frame->hide ();
  }

  return ok;
}

void
PCellParametersPageBase::commit_values (db::ParameterStates & /*states*/)
{
  //  .. nothing yet ..
}

void
PCellParametersPageBase::get_parameters (db::ParameterStates &states, bool *ok)
{
  try {

    if (! mp_pcell_decl) {
      throw tl::Exception (tl::to_string (tr ("PCell no longer valid.")));
    }

    mp_error_frame->hide ();

    commit_values (states);

    //  coerces the parameters and writes the changed values back
    if (mp_view->cellview (m_cv_index).is_valid ()) {

      auto parameters = parameter_from_states (states);
      auto before_coerce = parameters;
      if (mp_pcell_decl->layout ()) {
        mp_pcell_decl->coerce_parameters (*mp_pcell_decl->layout (), parameters);
      }

      if (parameters != before_coerce) {
        states_from_parameters (states, parameters);
        set_parameters_internal (states, lazy_evaluation ());
      }

    }

    if (ok) {
      *ok = true;
    }

  } catch (tl::ScriptError &ex) {

    if (ok) {
      mp_error_label->setText (tl::to_qstring (ex.basic_msg ()));
      mp_error_label->setToolTip (tl::to_qstring (ex.msg ()));
      mp_error_frame->show ();
      *ok = false;
    } else {
      throw;
    }

  } catch (tl::Exception &ex) {

    if (ok) {
      mp_error_label->setText (tl::to_qstring (ex.msg ()));
      mp_error_frame->show ();
      *ok = false;
    } else {
      throw;
    }

  }
}

std::vector<tl::Variant>
PCellParametersPageBase::get_parameters (bool *ok)
{
  db::ParameterStates states = m_states;
  get_parameters (states, ok);

  return parameter_from_states (states);
}

void
PCellParametersPageBase::set_parameters (const std::vector<tl::Variant> &parameters)
{
  if (! mp_pcell_decl) {
    return;
  }

  states_from_parameters (m_states, parameters);

  try {
    if (mp_view->cellview (m_cv_index).is_valid () && mp_pcell_decl->layout ()) {
      mp_pcell_decl->callback (*mp_pcell_decl->layout (), std::string (), m_states);
    }
  } catch (tl::Exception &ex) {
    //  potentially caused by script errors in callback implementation
    tl::error << ex.msg ();
  } catch (std::runtime_error &ex) {
    tl::error << ex.what ();
  } catch (...) {
    //  ignore other errors
  }

  m_initial_states = m_states;
  mp_error_frame->hide ();

  update_widgets_from_states (m_states, false);
}

void
PCellParametersPageBase::update_widgets_from_states (const db::ParameterStates &states, bool tentatively)
{
  if (! mp_pcell_decl) {
    return;
  }

  set_parameters_internal (states, tentatively);

  bool en = m_parameter_changed_enabled;
  m_parameter_changed_enabled = false;
  try {
    apply_states (states);
  } catch (tl::Exception &ex) {
    //  potentially caused by script errors in callback implementation
    tl::error << ex.msg ();
  } catch (std::runtime_error &ex) {
    tl::error << ex.what ();
  } catch (...) {
    //  ignore other errors
  }
  m_parameter_changed_enabled = en;
}

void
PCellParametersPageBase::apply_states (const db::ParameterStates & /*states*/)
{
  //  .. nothing yet ..
}

void
PCellParametersPageBase::apply_values (const db::ParameterStates & /*states*/)
{
  //  .. nothing yet ..
}

void
PCellParametersPageBase::set_parameters_internal (const db::ParameterStates &states, bool tentatively)
{
  if (! mp_pcell_decl) {
    return;
  }

  bool en = m_parameter_changed_enabled;
  m_parameter_changed_enabled = false;
  try {
    apply_values (states);
  } catch (tl::Exception &ex) {
    //  potentially caused by script errors in callback implementation
    tl::error << ex.msg ();
  } catch (std::runtime_error &ex) {
    tl::error << ex.what ();
  } catch (...) {
    //  ignore other errors
  }
  m_parameter_changed_enabled = en;

  bool update_needed = false;

  if (! tentatively) {
    m_current_states = states;
  } else {
    update_needed = ! m_current_states.values_are_equal (states);
  }

  mp_update_frame->setVisible (update_needed);
}

std::vector<tl::Variant>
PCellParametersPageBase::parameter_from_states (const db::ParameterStates &states) const
{
  std::vector<tl::Variant> parameters;
  if (mp_pcell_decl) {

    const std::vector<db::PCellParameterDeclaration> &pcp = mp_pcell_decl->parameter_declarations ();
    for (auto p = pcp.begin (); p != pcp.end (); ++p) {
      if (! states.has_parameter (p->get_name ())) {
        parameters.push_back (p->get_default ());
      } else {
        parameters.push_back (states.parameter (p->get_name ()).value ());
      }
    }

  }

  return parameters;
}

void
PCellParametersPageBase::states_from_parameters (db::ParameterStates &states, const std::vector<tl::Variant> &parameters)
{
  if (! mp_pcell_decl) {
    return;
  }

  size_t r = 0;
  const std::vector<db::PCellParameterDeclaration> &pcp = mp_pcell_decl->parameter_declarations ();
  for (std::vector<db::PCellParameterDeclaration>::const_iterator p = pcp.begin (); p != pcp.end (); ++p, ++r) {
    db::ParameterState &ps = states.parameter (p->get_name ());
    if (r < parameters.size ()) {
      ps.set_value (parameters [r]);
    } else {
      ps.set_value (p->get_default ());
    }
  }
}

void
PCellParametersPageBase::check_range (const tl::Variant &value, const std::string &name)
{
  if (! mp_pcell_decl) {
    return;
  }

  const db::PCellParameterDeclaration *pd = mp_pcell_decl->parameter_by_name (name);
  if (! pd) {
    return;
  }

  if (! pd->min_value ().is_nil () && value < pd->min_value ()) {
    throw tl::Exception (tl::sprintf (tl::to_string (tr ("The value is lower than the minimum allowed value: given value is %s, minimum value is %s")), value.to_string (), pd->min_value ().to_string ()));
  }

  if (! pd->max_value ().is_nil () && ! (value < pd->max_value () || value == pd->max_value ())) {
    throw tl::Exception (tl::sprintf (tl::to_string (tr ("The value is higher than the maximum allowed value: given value is %s, maximum value is %s")), value.to_string (), pd->max_value ().to_string ()));
  }
}

QPixmap
PCellParametersPageBase::error_pixmap ()
{
  return QPixmap (":/error_16px@2x.png");
}

QPixmap
PCellParametersPageBase::warning_pixmap ()
{
  return QPixmap (":/warn_16px@2x.png");
}

QPixmap
PCellParametersPageBase::info_pixmap ()
{
  return QPixmap (":/info_16px@2x.png");
}

}

#endif
