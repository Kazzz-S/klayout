
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

#if defined(HAVE_QTBINDINGS)

#include "gsiDecl.h"
#include "edtPCellParametersPageBase.h"
#include "layLayoutViewBase.h"

namespace gsi
{

class PCellParametersPageImpl
  : public edt::PCellParametersPageBase
{
public:
  PCellParametersPageImpl ()
    : edt::PCellParametersPageBase ()
  {
    //  .. nothing yet ..
  }

  void parameter_changed (const std::string &name)
  {
    edt::PCellParametersPageBase::parameter_changed (name);
  }

  virtual tl::Variant get_user_state ()
  {
    if (f_get_user_state.can_issue ()) {
      return f_get_user_state.issue<PCellParametersPageImpl, tl::Variant> (&PCellParametersPageImpl::get_user_state);
    } else {
      return edt::PCellParametersPageBase::get_user_state ();
    }
  }

  virtual void set_user_state (const tl::Variant &user_state)
  {
    if (f_set_user_state.can_issue ()) {
      f_set_user_state.issue<PCellParametersPageImpl, const tl::Variant &> (&PCellParametersPageImpl::set_user_state, user_state);
    } else {
      edt::PCellParametersPageBase::set_user_state (user_state);
    }
  }

  virtual void build_widgets (QFrame *container)
  {
    if (f_build_widgets.can_issue ()) {
      f_build_widgets.issue<PCellParametersPageImpl, QFrame *> (&PCellParametersPageImpl::build_widgets, container);
    } else {
      edt::PCellParametersPageBase::build_widgets (container);
    }
  }

  virtual void commit_values (db::ParameterStates &states)
  {
    if (f_commit_values.can_issue ()) {
      f_commit_values.issue<PCellParametersPageImpl, db::ParameterStates &> (&PCellParametersPageImpl::commit_values, states);
    } else {
      edt::PCellParametersPageBase::commit_values (states);
    }
  }

  virtual void apply_states (const db::ParameterStates &states)
  {
    if (f_apply_states.can_issue ()) {
      f_apply_states.issue<PCellParametersPageImpl, const db::ParameterStates &> (&PCellParametersPageImpl::apply_states, states);
    } else {
      edt::PCellParametersPageBase::apply_states (states);
    }
  }

  virtual void apply_values (const db::ParameterStates &states)
  {
    if (f_apply_values.can_issue ()) {
      f_apply_values.issue<PCellParametersPageImpl, const db::ParameterStates &> (&PCellParametersPageImpl::apply_values, states);
    } else {
      edt::PCellParametersPageBase::apply_values (states);
    }
  }

  gsi::Callback f_get_user_state;
  gsi::Callback f_set_user_state;
  gsi::Callback f_build_widgets;
  gsi::Callback f_commit_values;
  gsi::Callback f_apply_states;
  gsi::Callback f_apply_values;
};

//  borrowed from the db module
extern gsi::Class<db::PCellParametersPageBase> decl_dbPCellParametersPageBase;

gsi::Class<edt::PCellParametersPageBase> decl_PCellParametersPage_Native (decl_dbPCellParametersPageBase, "lay", "PCellParametersPage_Native",
  gsi::method ("dense", &edt::PCellParametersPageBase::dense,
    "@brief Gets a value indicating whether a dense layout is requested.\n"
    "A dense alyout is requested when the page is needed for an embedded PCell parameter page, for\n"
    "example in the editor options page.\n"
    "\n"
    "This flag shall be used in the implementation of the 'build_widgets' method and if set,\n"
    "this method should create a layout with more tightly packed widgets or smaller widget variants.\n"
  ) +
  gsi::method ("show_parameter_names", &edt::PCellParametersPageBase::show_parameter_names,
    "@brief Gets a value indicating whether parameter names are to be shown.\n"
    "This flag correlates with the respective display option.\n"
    "When this option changes, the widget stack is rebuilt.\n"
    "This flag shall be used in the implementation of the 'build_widgets' method and if set,\n"
    "this method should produce labels including the parameter names for visualization.\n"
  ) +
  gsi::method ("view", &edt::PCellParametersPageBase::view,
    "@brief Gets the view object the parameter page is attached to.\n"
  ) +
  gsi::method ("cv_index", &edt::PCellParametersPageBase::cv_index,
    "@brief Gets the cell view index of the Layout object the parameter page is attached to.\n"
  ) +
  gsi::method ("container_widget", &edt::PCellParametersPageBase::container_widget,
    "@brief Gets the container widget that holds the parameter page.\n"
    "The container widget is a QFrame widget that needs to be populated during\n"
    "the execution of the 'build_widgets' method.\n"
    "\n"
    "This widgets is created freshly before 'build_widgets' is called and\n"
    "acts as a container custom PCell parameters page.\n"
    "It is not possible to substitute this widget, but it is possible to\n"
    "create any kind of widget subhierarchy below this page."
  ) +
  gsi::method ("pcell_decl", &edt::PCellParametersPageBase::pcell_decl,
    "@brief Gets the PCellDeclaration object for the PCell that is addressed in this page.\n"
  ) +
  gsi::method ("check_range", &edt::PCellParametersPageBase::check_range, gsi::arg ("value"), gsi::arg ("name"),
    "@brief A utility function to check the a given values against the range given by the PCell parameter declaration.\n"
    "On mismatch, an exception is thrown by this method."
  ),
  "@hide\n"
  "This abstract base class for PCell parameter pages has been introduced in version 0.30.11.\n"
);

gsi::Class<PCellParametersPageImpl> decl_PCellParametersPageImpl (decl_PCellParametersPage_Native, "lay", "PCellParametersPage",
  gsi::callback ("get_user_state", &PCellParametersPageImpl::get_user_state, &PCellParametersPageImpl::f_get_user_state,
    "@brief Provides some user data to be stored along with the page state.\n"
    "The PCell parameters page sometimes persists its state to restore it later, for example, after the "
    "page has been recreated on a configuration change. The state may include things like positions of "
    "scroll bars or splitter pane sizes.\n"
    "\n"
    "This method is called to obtain state values from custom PCell parameter pages.\n"
    "The value is restored with \\set_user_state."
  ) +
  gsi::callback ("set_user_state", &PCellParametersPageImpl::set_user_state, &PCellParametersPageImpl::f_set_user_state, gsi::arg ("user_data"),
    "@brief Restores the PCell parameter page state from some user data.\n"
    "This method is the restore counterpart for \\get_user_state. See documentation there for details."
  ) +
  gsi::callback ("build_widgets", &PCellParametersPageImpl::build_widgets, &PCellParametersPageImpl::f_build_widgets, gsi::arg ("container"),
    "@brief Populates the page widget.\n"
    "This method is supposed to populate the given container widget (a QFrame) with widgets to implement the\n"
    "parameter page user interface. The container widget cannot be substituted and 'build_widgets' is always\n"
    "called with an empty container widget.\n"
    "\n"
    "Use the \\dense method to get a value indicating that a dense layout shall be used for pages suitable\n"
    "for embedding. Use the \\show_parameter_names method to get a value indicating whether to include parameter\n"
    "names in suitable places in the user interface.\n"
    "\n"
    "Use \\pcell_decl to get the \\PCellDeclaration object for the PCell that requested this page. You can\n"
    "use this object to obtain the parameter declarations for the individual PCell parameters. The standard\n"
    "implementation uses these parameters to build a generic widget grid for the PCell parameter editors.\n"
    "\n"
    "The widgets used in the user interface should have event handlers that translate edits into\n"
    "calls of the \\parameter_changed method. This method will implement the necessary actions to trigger\n"
    "callbacks and to update the PCell layout dynamically or to request an update in 'lazy evaluation' mode.\n"
    "\n"
    "The 'build_widgets' method does not need to configure the widgets with values or other dynamic attributes\n"
    "like visibility. The system will call \\apply_values and \\apply_states to refresh values or attributes\n"
    "respectively.\n"
  ) +
  gsi::callback ("commit_values", &PCellParametersPageImpl::commit_values, &PCellParametersPageImpl::f_commit_values, gsi::arg ("states"),
    "@brief Reads the parameter values into the parameter states\n"
    "This method is supposed to fill the parameter values in the \\PCellParameterStates object with the\n"
    "current values of the parameter editors.\n"
    "\n"
    "This method must to change the parameter states or any other attribute in the 'states' object, except\n"
    "the value.\n"
    "\n"
    "The bidirectional counterpart is \\apply_values."
  ) +
  gsi::callback ("apply_values", &PCellParametersPageImpl::apply_values, &PCellParametersPageImpl::f_apply_values, gsi::arg ("states"),
    "@brief Write the parameter values from the parameter states to the edit widgets.\n"
    "This method is supposed to change the edit widgets to reflect the parameter values.\n"
    "\n"
    "A corresponding method to write the parameter attributes like visibility to the edit widgets is \\apply_states.\n"
    "As these steps are called under different conditions, there are two methods for updating values and states\n"
    "respectively. The method for updating the attributes is \\apply_states.\n"
    "\n"
    "The bidirectional counterpart is \\commit_values."
  ) +
  gsi::callback ("apply_states", &PCellParametersPageImpl::apply_states, &PCellParametersPageImpl::f_apply_states, gsi::arg ("states"),
    "@brief Write the parameter attributes from the parameter states to the edit widgets.\n"
    "This method is supposed to change the edit widgets states like visibility or enabled state\n"
    "according to the attributes stored in state PCellParameterStates object.\n"
    "\n"
    "The system will update the actual values by calling the \\apply_values method separately.\n"
  ) +
  gsi::method ("parameter_changed", &PCellParametersPageImpl::parameter_changed, gsi::arg ("name"),
    "@brief Signals a change in a parameter\n"
    "The PCell parameter page implementation shall call this method when a parameter has changed or was edited.\n"
    "Calling this method will trigger the callback function and update the PCell's layout unless lazy evaluation\n"
    "is selected. In that case, the 'Update' button will be shown and the user can choose to update the\n"
    "layout manually.\n"
    "\n"
    "Typically this method is called in a slot attached to the value-representative widget, such as a\n"
    "check box or line edit. Provide the name of the changed parameter through the 'name' argument or\n"
    "use an empty string to signal an unspecific change."
  ),
  "@brief An implementation base class for custom PCell parameter pages\n"
  // @@@
  ""
  ""
  ""
  ""
  ""
  "@brief This class has been introduced in version 0.30.11."
);

}

#endif
