
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

#ifndef HDR_edtPCellParametersPageBase
#define HDR_edtPCellParametersPageBase

#include "dbPCellDeclaration.h"
#include "tlDeferredExecution.h"

#include <QFrame>
#include <QPixmap>

class QGroupBox;
class QCheckBox;
class QLabel;
class QToolButton;
class QScrollArea;
class QAction;

namespace lay
{
  class LayoutViewBase;
  class Dispatcher;
}

namespace edt
{

/**
 *  @brief A QScrollArea that displays and allows editing PCell parameters
 */
class PCellParametersPageBase
  : public QFrame, public tl::Object
{
Q_OBJECT

public:
  struct State
  {
    State () : valid (false), h_scroll_position (0), v_scroll_position (0) { }

    bool valid;
    int h_scroll_position;
    int v_scroll_position;
    QString focus_widget;
    tl::Variant user_state;
  };

  /**
   *  @brief Constructor
   *
   *  @param parent The parent widgets
   *  @param dispatcher The dispatcher object for configuration
   *  @param dense A flag indicating that a dense layout shall be used (for embedded pages)
   */
  PCellParametersPageBase (QWidget *parent, lay::Dispatcher *dispatcher, bool dense = false);

  /**
   *  @brief initialization
   *
   *  Use this method to setup when the arguments are not available in the constructor
   *
   *  @param layout The layout in which the PCell instance resides
   *  @param view The layout view from which to take layers for example
   *  @param cv_index The index of the cellview in "view"
   *  @param pcell_decl The PCell declaration
   *  @param parameters The parameter values to show (if empty, the default values are used)
   */
  void setup (lay::LayoutViewBase *view, int cv_index, const db::PCellDeclaration *pcell_decl, const db::pcell_parameters_type &parameters);

  /**
   *  @brief Gets the pages current state
   */
  State get_state ();

  /**
   *  @brief Restores the state
   */
  void set_state (const State &s);

  /**
   *  @brief Gets a value indicating that a dense layout shall be created
   *
   *  Dense layouts are used for embedded parameter pages.
   */
  bool dense () const
  {
    return m_dense;
  }

  /**
   *  @brief Gets a value indicating whether parameter names shall be shown
   *
   *  If the value changes, "build_widgets" is called to rebuild the widgets
   *  with the parameter names shown.
   */
  bool show_parameter_names () const
  {
    return m_show_parameter_names;
  }

  /**
   *  @brief Gets the layout view object the parameter page is attached to
   */
  lay::LayoutViewBase *view () const
  {
    return mp_view;
  }

  /**
   *  @brief Gets the cell view index the parameter page is attached to
   */
  int cv_index () const
  {
    return m_cv_index;
  }

  /**
   *  @brief Gets the container widget where the parameter page lives
   */
  QFrame *container_widget () const
  {
    return mp_main_frame;
  }

  /**
   *  @brief Gets the current parameters
   *
   *  *ok is set to true, if there is no error. In case of an error it's set to false.
   *  The error is indicated in the error label in the editor page.
   *  If ok is null, an exception is thrown.
   */
  std::vector<tl::Variant> get_parameters (bool *ok = 0);

  /**
   *  @brief Gets the current parameters into a ParameterStates object
   *
   *  *ok is set to true, if there is no error. In case of an error it's set to false.
   *  The error is indicated in the error label in the editor page.
   *  If ok is null, an exception is thrown.
   *
   *  The value fields of the ParameterState members is set to the parameter value.
   *  The other attributes are not changed. Parameters not present inside the
   *  ParameterStates object are created with their corresponding name.
   */
  void get_parameters (db::ParameterStates &states, bool *ok = 0);

  /**
   *  @brief Gets the initial parameters
   */
  std::vector<tl::Variant> initial_parameters () const
  {
    return parameter_from_states (m_initial_states);
  }

  /**
   *  @brief Get the PCell declaration pointer
   */
  const db::PCellDeclaration *pcell_decl () const
  {
    return mp_pcell_decl.get ();
  }

  /**
   *  @brief Sets the given parameters as values
   */
  void set_parameters (const  std::vector<tl::Variant> &values);

  /**
   *  @brief Utility: checks the value of the parameter with the given name
   *
   *  In case the value is outside the specified bounds (min and max), an
   *  exception is thrown.
   */
  void check_range (const tl::Variant &value, const std::string &name);

  /**
   *  @brief Mark for later deletion
   */
  void delete_later ();

  /**
   *  @brief Gets the error pixmap
   *
   *  Use this pixmap to indicate "error" state, i.e. in a QLabel.
   */
  static QPixmap error_pixmap ();

  /**
   *  @brief Gets the warning pixmap
   *
   *  Use this pixmap to indicate "warning" state, i.e. in a QLabel.
   */
  static QPixmap warning_pixmap ();

  /**
   *  @brief Gets the info pixmap
   *
   *  Use this pixmap to indicate "info" state, i.e. in a QLabel.
   */
  static QPixmap info_pixmap ();

protected:
  virtual tl::Variant get_user_state ();
  virtual void set_user_state (const tl::Variant &user_state);
  virtual void build_widgets (QFrame *container);
  virtual void commit_values(db::ParameterStates &states);
  virtual void apply_states (const db::ParameterStates &states);
  virtual void apply_values (const db::ParameterStates &states);

  /**
   *  @brief This method needs to be called when a parameter value changed
   *
   *  This will trigger the callbacks and refresh the PCell unless
   *  lazy evaluation is selected.
   */
  void parameter_changed (const std::string &name);

signals:
  void edited ();

public slots:
  void show_parameter_names (bool f);
  void lazy_eval_mode (int);

private slots:
  void update_button_pressed ();
  void lazy_eval_mode_slot ();

private:
  bool m_dense;
  lay::Dispatcher *mp_dispatcher;
  QScrollArea *mp_parameters_area;
  QFrame *mp_main_frame;
  QLabel *mp_error_label;
  QLabel *mp_error_icon;
  QLabel *mp_changed_label;
  QLabel *mp_changed_icon;
  QToolButton *mp_update_button;
  QFrame *mp_error_frame, *mp_update_frame;
  QAction *mp_show_parameter_names_action;
  QAction *mp_auto_lazy_eval_action;
  QAction *mp_always_lazy_eval_action;
  QAction *mp_never_lazy_eval_action;
  tl::weak_ptr<db::PCellDeclaration> mp_pcell_decl;
  lay::LayoutViewBase *mp_view;
  int m_cv_index;
  bool m_show_parameter_names;
  int m_lazy_evaluation;
  tl::DeferredMethod<PCellParametersPageBase> dm_parameter_changed;
  db::ParameterStates m_current_states, m_initial_states;
  db::ParameterStates m_states;

  void init ();
  void do_parameter_changed ();
  bool lazy_evaluation ();
  bool update_current_parameters ();
  void update_widgets_from_states (const db::ParameterStates &states, bool tentatively);
  void get_parameters_internal (db::ParameterStates &states, bool &edit_error);
  void set_parameters_internal (const db::ParameterStates &states, bool tentatively);
  std::vector<tl::Variant> parameter_from_states (const db::ParameterStates &states) const;
  void states_from_parameters (db::ParameterStates &states, const std::vector<tl::Variant> &parameters);
};

}

#endif

#endif
