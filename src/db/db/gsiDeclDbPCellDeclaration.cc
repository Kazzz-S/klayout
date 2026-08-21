
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



#include "gsiDecl.h"
#include "gsiEnums.h"
#include "dbLayout.h"
#include "dbPCellDeclaration.h"
#include "tlLog.h"

namespace gsi
{

// ---------------------------------------------------------------
//  db::PCellParameterPageBase binding

//  Provide a binding for db::PCellDeclaration for native PCell implementations
Class<db::PCellParametersPageBase> pcell_parameter_page_base_decl ("db", "PCellParametersPageBase",
  gsi::Methods (),
  "@hide.\n"
  "This abstract base class for PCell parameter pages has been introduced in version 0.30.11.\n"
);

DB_PUBLIC Class<db::PCellParametersPageBase> &decl_dbPCellParametersPageBase () { return pcell_parameter_page_base_decl; }

// ---------------------------------------------------------------
//  db::PCellDeclaration binding

static std::vector<db::LayerProperties> get_layer_declarations_native (const db::PCellDeclaration *pd, const db::pcell_parameters_type &parameters)
{
  std::vector<db::PCellLayerDeclaration> lp = pd->db::PCellDeclaration::get_layer_declarations (parameters);
  std::vector<db::LayerProperties> ret;
  for (std::vector<db::PCellLayerDeclaration>::const_iterator l = lp.begin (); l != lp.end (); ++l) {
    ret.push_back (db::LayerProperties (*l));
  }
  return ret;
}

static db::pcell_parameters_type coerce_parameters_native (const db::PCellDeclaration *pd, const db::Layout &layout, const db::pcell_parameters_type &input)
{
  db::pcell_parameters_type param = input;
  pd->db::PCellDeclaration::coerce_parameters (layout, param);
  return param;
}

//  Provide a binding for db::PCellDeclaration for native PCell implementations
Class<db::PCellDeclaration> decl_PCellDeclaration_Native ("db", "PCellDeclaration_Native",
  gsi::method_ext ("get_layers", &get_layer_declarations_native, gsi::arg ("parameters")) +
  gsi::method ("get_parameters", &db::PCellDeclaration::get_parameter_declarations) +
  gsi::method ("produce", &db::PCellDeclaration::produce, gsi::arg ("layout"), gsi::arg ("layers"), gsi::arg ("parameters"), gsi::arg ("cell")) +
  gsi::method ("callback", &db::PCellDeclaration::callback, gsi::arg ("layout"), gsi::arg ("name"), gsi::arg ("states")) +
  gsi::method_ext ("coerce_parameters", &coerce_parameters_native, gsi::arg ("layout"), gsi::arg ("parameters")) +
  gsi::method ("can_create_from_shape", &db::PCellDeclaration::can_create_from_shape, gsi::arg ("layout"), gsi::arg ("shape"), gsi::arg ("layer")) +
  gsi::method ("parameters_from_shape", &db::PCellDeclaration::parameters_from_shape, gsi::arg ("layout"), gsi::arg ("shape"), gsi::arg ("layer")) +
  gsi::method ("transformation_from_shape", &db::PCellDeclaration::transformation_from_shape, gsi::arg ("layout"), gsi::arg ("shape"), gsi::arg ("layer")) +
  gsi::method ("wants_lazy_evaluation", &db::PCellDeclaration::wants_lazy_evaluation) +
  gsi::method ("via_types", &db::PCellDeclaration::via_types) +
  gsi::method ("description", &db::PCellDeclaration::get_description) +
  gsi::method ("display_text", &db::PCellDeclaration::get_display_name, gsi::arg ("parameters")) +
  gsi::method ("cell_name", &db::PCellDeclaration::get_cell_name, gsi::arg ("parameters")) +
  gsi::method ("layout", &db::PCellDeclaration::layout,
    "@brief Gets the Layout object the PCell is registered in or nil if it is not registered yet.\n"
    "This attribute has been added in version 0.27.5."
  ) +
  gsi::method ("id", &db::PCellDeclaration::id,
    "@brief Gets the integer ID of the PCell declaration\n"
    "This ID is used to identify the PCell in the context of a Layout object for example"
  ) +
  gsi::method ("name", &db::PCellDeclaration::name,
    "@brief Gets the name of the PCell\n"
  ),
  "@hide\n@alias PCellDeclaration\n"
);

//  Provide a binding for db::ParameterState for native PCell implementations
Class<db::ParameterState> decl_PCellParameterState ("db", "PCellParameterState",
  gsi::method("value=", &db::ParameterState::set_value, gsi::arg ("v"),
    "@brief Sets the value of the parameter\n"
  ) +
  gsi::method("value", &db::ParameterState::value,
    "@brief Gets the value of the parameter\n"
  ) +
  gsi::method("visible=", &db::ParameterState::set_visible, gsi::arg ("f"),
    "@brief Sets a value indicating whether the parameter is visible in the parameter form\n"
  ) +
  gsi::method("is_visible?", &db::ParameterState::is_visible,
    "@brief Gets a value indicating whether the parameter is visible in the parameter form\n"
  ) +
  gsi::method("enabled=", &db::ParameterState::set_enabled, gsi::arg ("f"),
    "@brief Sets a value indicating whether the parameter is enabled in the parameter form\n"
  ) +
  gsi::method("is_enabled?", &db::ParameterState::is_enabled,
    "@brief Gets a value indicating whether the parameter is enabled in the parameter form\n"
  ) +
  gsi::method("readonly=", &db::ParameterState::set_readonly, gsi::arg ("f"),
    "@brief Sets a value indicating whether the parameter is made read-only (not editable) in the parameter form\n"
  ) +
  gsi::method("is_readonly?", &db::ParameterState::is_readonly,
    "@brief Gets a value indicating whether the parameter is read-only (not editable) in the parameter form\n"
  ) +
  gsi::method("tooltip=", &db::ParameterState::set_tooltip, gsi::arg ("s"),
    "@brief Sets the tool tip text\n"
    "\n"
    "The tool tip is shown when hovering over the parameter label or edit field."
  ) +
  gsi::method("tooltip", &db::ParameterState::tooltip,
    "@brief Gets the tool tip text\n"
  ) +
  gsi::method("icon=", &db::ParameterState::set_icon, gsi::arg ("i"),
    "@brief Sets the icon for the parameter\n"
  ) +
  gsi::method("icon", &db::ParameterState::icon,
    "@brief Gets the icon for the parameter\n"
  ),
  "@brief Provides access to the attributes of a single parameter within \\PCellParameterStates.\n"
  "\n"
  "See \\PCellParameterStates for details about this feature.\n"
  "\n"
  "This class has been introduced in version 0.28."
);

gsi::EnumIn<db::ParameterState, db::ParameterState::Icon> decl_PCellParameterState_Icon ("db", "ParameterStateIcon",
  gsi::enum_const ("NoIcon", db::ParameterState::NoIcon,
    "@brief No icon is shown for the parameter\n"
  ) +
  gsi::enum_const ("InfoIcon", db::ParameterState::InfoIcon,
    "@brief A general 'information' icon is shown\n"
  ) +
  gsi::enum_const ("ErrorIcon", db::ParameterState::ErrorIcon,
    "@brief An icon indicating an error is shown\n"
  ) +
  gsi::enum_const ("WarningIcon", db::ParameterState::WarningIcon,
    "@brief An icon indicating a warning is shown\n"
  ),
  "@brief This enum specifies the icon shown next to the parameter in PCell parameter list.\n"
  "\n"
  "This enum was introduced in version 0.28.\n"
);

//  Inject the NetlistCrossReference::Status declarations into NetlistCrossReference:
gsi::ClassExt<db::ParameterState> inject_PCellParameterState_Icon_in_parent (decl_PCellParameterState_Icon.defs ());

//  Provide a binding for db::ParameterStates for native PCell implementations
Class<db::ParameterStates> decl_PCellParameterStates ("db", "PCellParameterStates",
  gsi::method ("has_parameter?", &db::ParameterStates::has_parameter, gsi::arg ("name"),
    "@brief Gets a value indicating whether a parameter with that name exists\n"
  ) +
  gsi::method ("parameter", static_cast<db::ParameterState & (db::ParameterStates::*) (const std::string &name)> (&db::ParameterStates::parameter), gsi::arg ("name"),
    "@brief Gets the parameter by name\n"
    "\n"
    "This will return a \\PCellParameterState object that can be used to manipulate the "
    "parameter state."
  ) +
  gsi::method ("parameter", static_cast<const db::ParameterState & (db::ParameterStates::*) (const std::string &name) const> (&db::ParameterStates::parameter), gsi::arg ("name"),
    "@brief Gets the parameter by name (const version)\n"
    "\n"
    "This will return a \\PCellParameterState object which cannot be manipulated, but read.\n"
    "\n"
    "The const flavor has been introduced in version 0.30.11."
  ),
  "@brief Provides access to the parameter states inside a 'callback' implementation of a PCell\n"
  "\n"
  "Example: enables or disables a parameter 'n' based on the value:\n"
  "\n"
  "@code\n"
  "n_param = states.parameter(\"n\")\n"
  "n_param.enabled = n_param.value > 1.0\n"
  "@/code\n"
  "\n"
  "This class has been introduced in version 0.28."
);

class PCellDeclarationImpl
  : public db::PCellDeclaration
{
public:
  //  dummy implementation to provide the signature
  virtual std::vector<db::LayerProperties> get_layer_declarations_impl (const db::pcell_parameters_type &) const
  {
    return std::vector<db::LayerProperties> ();
  }

  virtual std::vector<db::PCellLayerDeclaration> get_layer_declarations (const db::pcell_parameters_type &parameters) const
  {
    std::vector<db::LayerProperties> lp;
    if (cb_get_layer_declarations.can_issue ()) {
      lp = cb_get_layer_declarations.issue<PCellDeclarationImpl, std::vector<db::LayerProperties>, const db::pcell_parameters_type &> (&PCellDeclarationImpl::get_layer_declarations_impl, parameters);
    } else {
      lp = PCellDeclarationImpl::get_layer_declarations_impl (parameters);
    }

    std::vector<db::PCellLayerDeclaration> ret;
    for (std::vector<db::LayerProperties>::const_iterator l = lp.begin (); l != lp.end (); ++l) {
      ret.push_back (db::PCellLayerDeclaration (*l));
    }

    return ret;
  }

  std::vector<db::PCellParameterDeclaration> get_parameter_declarations_fb () const
  {
    return db::PCellDeclaration::get_parameter_declarations ();
  }

  virtual std::vector<db::PCellParameterDeclaration> get_parameter_declarations () const
  {
    if (cb_get_parameter_declarations.can_issue ()) {
      return cb_get_parameter_declarations.issue<db::PCellDeclaration, std::vector<db::PCellParameterDeclaration> > (&db::PCellDeclaration::get_parameter_declarations);
    } else {
      return db::PCellDeclaration::get_parameter_declarations ();
    }
  }

  //  dummy implementation to provide the signature
  virtual db::pcell_parameters_type coerce_parameters_impl (const db::Layout & /*layout*/, const db::pcell_parameters_type &input) const
  {
    return input;
  }

  virtual void coerce_parameters (const db::Layout &layout, db::pcell_parameters_type &parameters) const
  {
    db::pcell_parameters_type output;
    if (cb_coerce_parameters.can_issue ()) {
      output = cb_coerce_parameters.issue<PCellDeclarationImpl, db::pcell_parameters_type, const db::Layout &, const db::pcell_parameters_type &> (&PCellDeclarationImpl::coerce_parameters_impl, layout, parameters);
    } else {
      output = PCellDeclarationImpl::coerce_parameters_impl (layout, parameters);
    }
    if (! output.empty ()) {
      parameters = output;
    }
  }

  virtual void callback_fb (const db::Layout &layout, const std::string &name, db::ParameterStates &states) const
  {
    db::PCellDeclaration::callback (layout, name, states);
  }

  virtual void callback (const db::Layout &layout, const std::string &name, db::ParameterStates &states) const
  {
    if (cb_callback.can_issue ()) {
      cb_callback.issue<db::PCellDeclaration, const db::Layout &, const std::string &, db::ParameterStates &> (&db::PCellDeclaration::callback, layout, name, states);
    } else {
      db::PCellDeclaration::callback (layout, name, states);
    }
  }

  void produce_fb (const db::Layout &layout, const std::vector<unsigned int> &layer_ids, const db::pcell_parameters_type &parameters, db::Cell &cell) const
  {
    return db::PCellDeclaration::produce (layout, layer_ids, parameters, cell);
  }

  virtual void produce (const db::Layout &layout, const std::vector<unsigned int> &layer_ids, const db::pcell_parameters_type &parameters, db::Cell &cell) const
  {
    if (cb_produce.can_issue ()) {
      cb_produce.issue<db::PCellDeclaration, const db::Layout &, const std::vector<unsigned int> &, const db::pcell_parameters_type &, db::Cell &> (&db::PCellDeclaration::produce, layout, layer_ids, parameters, cell);
    } else {
      db::PCellDeclaration::produce (layout, layer_ids, parameters, cell);
    }
  }

  bool can_create_from_shape_fb (const db::Layout &layout, const db::Shape &shape, unsigned int layer) const
  {
    return db::PCellDeclaration::can_create_from_shape (layout, shape, layer);
  }

  virtual bool can_create_from_shape (const db::Layout &layout, const db::Shape &shape, unsigned int layer) const
  {
    if (cb_can_create_from_shape.can_issue ()) {
      return cb_can_create_from_shape.issue<db::PCellDeclaration, bool, const db::Layout &, const db::Shape &, unsigned int> (&db::PCellDeclaration::can_create_from_shape, layout, shape, layer);
    } else {
      return db::PCellDeclaration::can_create_from_shape (layout, shape, layer);
    }
  }

  db::pcell_parameters_type parameters_from_shape_fb (const db::Layout &layout, const db::Shape &shape, unsigned int layer) const
  {
    return db::PCellDeclaration::parameters_from_shape (layout, shape, layer);
  }

  virtual db::pcell_parameters_type parameters_from_shape (const db::Layout &layout, const db::Shape &shape, unsigned int layer) const
  {
    if (cb_parameters_from_shape.can_issue ()) {
      return cb_parameters_from_shape.issue<db::PCellDeclaration, db::pcell_parameters_type, const db::Layout &, const db::Shape &, unsigned int> (&db::PCellDeclaration::parameters_from_shape, layout, shape, layer);
    } else {
      return db::PCellDeclaration::parameters_from_shape (layout, shape, layer);
    }
  }

  db::Trans transformation_from_shape_fb (const db::Layout &layout, const db::Shape &shape, unsigned int layer) const
  {
    return db::PCellDeclaration::transformation_from_shape (layout, shape, layer);
  }

  virtual db::Trans transformation_from_shape (const db::Layout &layout, const db::Shape &shape, unsigned int layer) const
  {
    if (cb_transformation_from_shape.can_issue ()) {
      return cb_transformation_from_shape.issue<db::PCellDeclaration, db::Trans, const db::Layout &, const db::Shape &, unsigned int> (&db::PCellDeclaration::transformation_from_shape, layout, shape, layer);
    } else {
      return db::PCellDeclaration::transformation_from_shape (layout, shape, layer);
    }
  }

  bool wants_lazy_evaluation_fb () const
  {
    return db::PCellDeclaration::wants_lazy_evaluation ();
  }

  virtual bool wants_lazy_evaluation () const
  {
    if (cb_wants_lazy_evaluation.can_issue ()) {
      return cb_wants_lazy_evaluation.issue<db::PCellDeclaration, bool> (&db::PCellDeclaration::wants_lazy_evaluation);
    } else {
      return db::PCellDeclaration::wants_lazy_evaluation ();
    }
  }

  std::string get_description_fb () const
  {
    return db::PCellDeclaration::get_description ();
  }

  virtual std::string get_description () const
  {
    if (cb_get_description.can_issue ()) {
      return cb_get_description.issue<db::PCellDeclaration, std::string> (&db::PCellDeclaration::get_description);
    } else {
      return db::PCellDeclaration::get_description ();
    }
  }

  std::vector<db::ViaType> via_types_fb () const
  {
    return db::PCellDeclaration::via_types ();
  }

  virtual std::vector<db::ViaType> via_types () const
  {
    if (cb_via_types.can_issue ()) {
      return cb_via_types.issue<db::PCellDeclaration, std::vector<db::ViaType>> (&db::PCellDeclaration::via_types);
    } else {
      return db::PCellDeclaration::via_types ();
    }
  }

  std::string get_display_name_fb (const db::pcell_parameters_type &parameters) const
  {
    return db::PCellDeclaration::get_display_name (parameters);
  }

  virtual std::string get_display_name (const db::pcell_parameters_type &parameters) const
  {
    if (cb_get_display_name.can_issue ()) {
      return cb_get_display_name.issue<db::PCellDeclaration, std::string, const db::pcell_parameters_type &> (&db::PCellDeclaration::get_display_name, parameters);
    } else {
      return db::PCellDeclaration::get_display_name (parameters);
    }
  }

  std::string get_cell_name_fb (const db::pcell_parameters_type &parameters) const
  {
    return db::PCellDeclaration::get_cell_name (parameters);
  }

  virtual std::string get_cell_name (const db::pcell_parameters_type &parameters) const
  {
    if (cb_get_cell_name.can_issue ()) {
      return cb_get_cell_name.issue<db::PCellDeclaration, std::string, const db::pcell_parameters_type &> (&db::PCellDeclaration::get_cell_name, parameters);
    } else {
      return db::PCellDeclaration::get_cell_name (parameters);
    }
  }

  db::PCellParametersPageBase *create_parameters_page_fb () const
  {
    return db::PCellDeclaration::create_parameters_page ();
  }

  virtual db::PCellParametersPageBase *create_parameters_page () const
  {
    if (cb_create_parameters_page.can_issue ()) {
      return cb_create_parameters_page.issue<db::PCellDeclaration, db::PCellParametersPageBase *> (&db::PCellDeclaration::create_parameters_page);
    } else {
      return db::PCellDeclaration::create_parameters_page ();
    }
  }

  gsi::Callback cb_get_layer_declarations;
  gsi::Callback cb_get_parameter_declarations;
  gsi::Callback cb_produce;
  gsi::Callback cb_create_parameters_page;
  gsi::Callback cb_can_create_from_shape;
  gsi::Callback cb_parameters_from_shape;
  gsi::Callback cb_transformation_from_shape;
  gsi::Callback cb_wants_lazy_evaluation;
  gsi::Callback cb_coerce_parameters;
  gsi::Callback cb_callback;
  gsi::Callback cb_get_display_name;
  gsi::Callback cb_get_cell_name;
  gsi::Callback cb_get_description;
  gsi::Callback cb_via_types;
};

Class<PCellDeclarationImpl> decl_PCellDeclaration (decl_PCellDeclaration_Native, "db", "PCellDeclaration",
  //  fallback implementations to reroute Ruby calls to the base class:
  gsi::method ("get_parameters", &PCellDeclarationImpl::get_parameter_declarations_fb, "@hide") +
  gsi::method ("produce", &PCellDeclarationImpl::produce_fb, "@hide") +
  gsi::method ("create_parameters_page", &PCellDeclarationImpl::create_parameters_page_fb, "@hide") +
  gsi::method ("callback", &PCellDeclarationImpl::callback_fb, "@hide") +
  gsi::method ("can_create_from_shape", &PCellDeclarationImpl::can_create_from_shape_fb, "@hide") +
  gsi::method ("parameters_from_shape", &PCellDeclarationImpl::parameters_from_shape_fb, "@hide") +
  gsi::method ("transformation_from_shape", &PCellDeclarationImpl::transformation_from_shape_fb, "@hide") +
  gsi::method ("display_text", &PCellDeclarationImpl::get_display_name_fb, "@hide") +
  gsi::method ("cell_name", &PCellDeclarationImpl::get_cell_name_fb, "@hide") +
  gsi::method ("wants_lazy_evaluation", &PCellDeclarationImpl::wants_lazy_evaluation_fb, "@hide") +
  gsi::method ("description", &PCellDeclarationImpl::get_description_fb, "@hide") +
  gsi::method ("via_types", &PCellDeclarationImpl::via_types_fb, "@hide") +
  gsi::callback ("get_layers", &PCellDeclarationImpl::get_layer_declarations_impl, &PCellDeclarationImpl::cb_get_layer_declarations, gsi::arg ("parameters"),
    "@brief Returns a list of layer declarations\n"
    "Reimplement this method to return a list of layers this PCell wants to create.\n"
    "The layer declarations are returned as a list of LayerInfo objects which are\n"
    "used as match expressions to look up the layer in the actual layout.\n"
    "\n"
    "This method receives the PCell parameters which allows it to deduce layers\n"
    "from the parameters."
  ) +
  gsi::callback ("get_parameters", &PCellDeclarationImpl::get_parameter_declarations, &PCellDeclarationImpl::cb_get_parameter_declarations,
    "@brief Returns a list of parameter declarations\n"
    "Reimplement this method to return a list of parameters used in that PCell \n"
    "implementation. A parameter declaration is a PCellParameterDeclaration object\n"
    "and defines the parameter name, type, description text and possible choices for\n"
    "the parameter value.\n"
  ) +
  gsi::callback ("coerce_parameters", &PCellDeclarationImpl::coerce_parameters_impl, &PCellDeclarationImpl::cb_coerce_parameters, gsi::arg ("layout"), gsi::arg ("input"),
    "@brief Modifies the parameters to match the requirements\n"
    "@param layout The layout object in which the PCell will be produced\n"
    "@param input The parameters before the modification\n"
    "@return The modified parameters or an empty array, indicating that no modification was done\n"
    "This method can be reimplemented to change the parameter set according to some\n"
    "constraints for example. The reimplementation may modify the parameters in a way\n"
    "that they are usable for the \\produce method.\n"
    "\n"
    "The method receives a reference to the layout so it is able to verify\n"
    "the parameters against layout properties.\n"
    "\n"
    "It can raise an exception to indicate that something is not correct.\n"
  ) +
  gsi::callback ("callback", &PCellDeclarationImpl::callback, &PCellDeclarationImpl::cb_callback, gsi::arg ("layout"), gsi::arg ("name"), gsi::arg ("states"),
    "@brief Indicates a parameter change and allows implementing actions based on the parameter value\n"
    "@param layout The layout object in which the PCell will be produced\n"
    "@param name The name of the parameter which has changed or an empty string if all parameters need to be considered\n"
    "@param states A \\PCellParameterStates object which can be used to manipulate the parameter states\n"
    "This method may be reimplemented to implement parameter-specific actions upon value change or button callbacks. "
    "Whenever the value of a parameter is changed in the PCell parameter form, this method is called with the name of the parameter "
    "in 'name'. The implementation can manipulate values or states (enabled, visible) or parameters using the "
    "\\PCellParameterStates object passed in 'states'.\n"
    "\n"
    "Initially, this method will be called with an empty parameter name to indicate a global change. The implementation "
    "may then consolidate all states. The initial state is build from the 'readonly' (disabled) or 'hidden' (invisible) parameter "
    "declarations.\n"
    "\n"
    "This method is also called when a button-type parameter is present and the button is pressed. In this case the parameter "
    "name is the name of the button.\n"
    "\n"
    "This feature has been introduced in version 0.28."
  ) +
  gsi::callback ("produce", &PCellDeclarationImpl::produce, &PCellDeclarationImpl::cb_produce, gsi::arg ("layout"), gsi::arg ("layer_ids"), gsi::arg ("parameters"), gsi::arg ("cell"),
    "@brief The production callback\n"
    "@param layout The layout object where the cell resides\n"
    "@param layer_ids A list of layer ID's which correspond to the layers declared with get_layers\n"
    "@param parameters A list of parameter values which correspond to the parameters declared with get_parameters\n"
    "@param cell The cell where the layout will be created\n"
    "Reimplement this method to provide the code that implements the PCell.\n"
    "The code is supposed to create the layout in the target cell using the provided \n"
    "parameters and the layers passed in the layer_ids list.\n"
  ) +
  gsi::factory_callback ("create_parameters_page", &PCellDeclarationImpl::create_parameters_page, &PCellDeclarationImpl::cb_create_parameters_page,
    "@brief Creates the PCell parameters page\n"
    "Reimplement this method to provide a PCell parameters page.\n"
    "For more details see the description of the parameters page class.\n"
    "\n"
    "Custom parameter pages have been introduced in version 0.30.11."
  ) +
  gsi::callback ("can_create_from_shape", &PCellDeclarationImpl::can_create_from_shape, &PCellDeclarationImpl::cb_can_create_from_shape, gsi::arg ("layout"), gsi::arg ("shape"), gsi::arg ("layer"),
    "@brief Returns true, if the PCell can be created from the given shape\n"
    "@param layout The layout the shape lives in\n"
    "@param shape The shape from which a PCell shall be created\n"
    "@param layer The layer index (in layout) of the shape\n"
    "KLayout offers a way to convert a shape into a PCell. To test whether the PCell can be created "
    "from a shape, it will call this method. If this method returns true, KLayout will use "
    "\\parameters_from_shape and \\transformation_from_shape to derive the parameters and instance "
    "transformation for the new PCell instance that will replace the shape.\n"
  ) +
  gsi::callback ("parameters_from_shape", &PCellDeclarationImpl::parameters_from_shape, &PCellDeclarationImpl::cb_parameters_from_shape, gsi::arg ("layout"), gsi::arg ("shape"), gsi::arg ("layer"),
    "@brief Gets the parameters for the PCell which can replace the given shape\n"
    "@param layout The layout the shape lives in\n"
    "@param shape The shape from which a PCell shall be created\n"
    "@param layer The layer index (in layout) of the shape\n"
    "KLayout offers a way to convert a shape into a PCell. If \\can_create_from_shape returns true, "
    "it will use this method to derive the parameters for the PCell instance that will replace the shape. "
    "See also \\transformation_from_shape and \\can_create_from_shape."
  ) +
  gsi::callback ("transformation_from_shape", &PCellDeclarationImpl::transformation_from_shape, &PCellDeclarationImpl::cb_transformation_from_shape, gsi::arg ("layout"), gsi::arg ("shape"), gsi::arg ("layer"),
    "@brief Gets the instance transformation for the PCell which can replace the given shape\n"
    "@param layout The layout the shape lives in\n"
    "@param shape The shape from which a PCell shall be created\n"
    "@param layer The layer index (in layout) of the shape\n"
    "KLayout offers a way to convert a shape into a PCell. If \\can_create_from_shape returns true, "
    "it will use this method to derive the transformation for the PCell instance that will replace the shape. "
    "See also \\parameters_from_shape and \\can_create_from_shape."
  ) +
  gsi::callback ("wants_lazy_evaluation", &PCellDeclarationImpl::wants_lazy_evaluation, &PCellDeclarationImpl::cb_wants_lazy_evaluation,
    "@brief Gets a value indicating whether the PCell wants lazy evaluation\n"
    "In lazy evaluation mode, the PCell UI will not immediately update the layout when a parameter is changed. "
    "Instead, the user has to commit the changes in order to have the parameters updated. This is "
    "useful for PCells that take a long time to compute.\n"
    "\n"
    "The default implementation will return 'false' indicating immediate updates.\n"
    "\n"
    "This method has been added in version 0.27.6.\n"
  ) +
  gsi::callback ("description", &PCellDeclarationImpl::get_description, &PCellDeclarationImpl::cb_get_description,
    "@brief Gets the PCell description\n"
    "The description string is a text that gives a human-readable description of the PCell. By default, the "
    "PCell name is used for the description.\n"
    "\n"
    "This method has been added in version 0.30.4.\n"
  ) +
  gsi::callback ("via_types", &PCellDeclarationImpl::via_types, &PCellDeclarationImpl::cb_via_types,
    "@brief Gets the via types the PCell supports - if it is a via PCell\n"
    "If the returned list is non-empty, the PCell may be used as a via PCell. This method is supposed "
    "to deliver a list of via types the PCell supports. If the PCell supports vias, it is expected to "
    "accept the following parameters:\n"
    "\n"
    "@ul\n"
    "@li 'via' (string): the name of the via type requested @/li\n"
    "@li 'w_bottom' (float): the bottom wire width in um or 0 if not specified @/li\n"
    "@li 'h_bottom' (float): the bottom wire height in um or 0 if not specified @/li\n"
    "@li 'w_top' (float): the top wire width in um or 0 if not specified @/li\n"
    "@li 'h_top' (float): the top wire height in um or 0 if not specified @/li\n"
    "@/ul\n"
    "\n"
    "This method has been added in version 0.30.4.\n"
  ) +
  gsi::callback ("display_text", &PCellDeclarationImpl::get_display_name, &PCellDeclarationImpl::cb_get_display_name, gsi::arg ("parameters"),
    "@brief Returns the display text for this PCell given a certain parameter set\n"
    "Reimplement this method to create a distinct display text for a PCell variant with \n"
    "the given parameter set. If this method is not implemented, a default text is created. \n"
  ) +
  gsi::callback ("cell_name", &PCellDeclarationImpl::get_cell_name, &PCellDeclarationImpl::cb_get_cell_name, gsi::arg ("parameters"),
    "@brief Returns a cell name used for the PCell variant\n"
    "Reimplement this method to create a cell name the system uses for the PCell variant. By default that is the PCell name.\n"
    "This feature allows encoding the PCell parameters into the cell name for easier identification of the PCell variant in a cell tree.\n"
    "\n"
    "This feature has been added in version 0.30.5.\n"
  ),
  "@brief A PCell declaration providing the parameters and code to produce the PCell\n"
  "\n"
  "A PCell declaration is basically the recipe of how to create a PCell layout from\n"
  "a parameter set. The declaration includes\n"
  "\n"
  "@ul\n"
    "@li Parameters: names, types, default values @/li\n"
    "@li Layers: the layers the PCell wants to create @/li\n"
    "@li Code: a production callback that is called whenever a PCell is instantiated with a certain parameter set @/li\n"
    "@li Display name: the name that is shown for a given PCell instance @/li\n"
  "@/ul\n"
  "\n"
  "All these declarations are implemented by deriving from the PCellDeclaration class\n"
  "and reimplementing the specific methods. Reimplementing the \\display_name method is \n"
  "optional. The default implementation creates a name from the PCell name plus the \n"
  "parameters.\n"
  "\n"
  "By supplying the information about the layers it wants to create, KLayout is able to\n"
  "call the production callback with a defined set of the layer ID's which are already\n"
  "mapped to valid actual layout layers.\n"
  "\n"
  "This class has been introduced in version 0.22.\n"
);

// ---------------------------------------------------------------
//  db::PCellParameterDeclaration binding

static unsigned int get_type (const db::PCellParameterDeclaration *pd)
{
  return (unsigned int) pd->get_type ();
}

static void set_type (db::PCellParameterDeclaration *pd, unsigned int t)
{
  pd->set_type (db::PCellParameterDeclaration::type (t));
}

static void clear_choices (db::PCellParameterDeclaration *pd)
{
  pd->set_choices (std::vector<tl::Variant> ());
  pd->set_choice_descriptions (std::vector<std::string> ());
}

static void add_choice (db::PCellParameterDeclaration *pd, const std::string &d, const tl::Variant &v)
{
  std::vector<tl::Variant> vv = pd->get_choices ();
  std::vector<std::string> dd = pd->get_choice_descriptions ();
  vv.push_back (v);
  dd.push_back (d);
  pd->set_choice_descriptions (dd);
  pd->set_choices (vv);
}

static unsigned int pd_type_int ()
{
  return (unsigned int) db::PCellParameterDeclaration::t_int;
}

static unsigned int pd_type_double ()
{
  return (unsigned int) db::PCellParameterDeclaration::t_double;
}

static unsigned int pd_type_shape ()
{
  return (unsigned int) db::PCellParameterDeclaration::t_shape;
}

static unsigned int pd_type_string ()
{
  return (unsigned int) db::PCellParameterDeclaration::t_string;
}

static unsigned int pd_type_boolean ()
{
  return (unsigned int) db::PCellParameterDeclaration::t_boolean;
}

static unsigned int pd_type_layer ()
{
  return (unsigned int) db::PCellParameterDeclaration::t_layer;
}

static unsigned int pd_type_list ()
{
  return (unsigned int) db::PCellParameterDeclaration::t_list;
}

static unsigned int pd_type_callback ()
{
  return (unsigned int) db::PCellParameterDeclaration::t_callback;
}

static unsigned int pd_type_none ()
{
  return (unsigned int) db::PCellParameterDeclaration::t_none;
}

db::PCellParameterDeclaration *ctor_pcell_parameter (const std::string &name, unsigned int type, const std::string &description, const tl::Variant &def, const std::string &unit)
{
  db::PCellParameterDeclaration *pd = new db::PCellParameterDeclaration ();
  pd->set_name (name);
  pd->set_type (db::PCellParameterDeclaration::type (type));
  pd->set_description (description);
  pd->set_default (def);
  pd->set_unit (unit);
  return pd;
}

Class<db::PCellParameterDeclaration> decl_PCellParameterDeclaration ("db", "PCellParameterDeclaration",
  gsi::constructor ("new", &ctor_pcell_parameter, gsi::arg ("name"), gsi::arg ("type"), gsi::arg ("description"), gsi::arg ("default", tl::Variant (), "nil"), gsi::arg ("unit", std::string ()),
    "@brief Create a new parameter declaration with the given name, type, default value and unit string\n"
    "@param name The parameter name\n"
    "@param type One of the Type... constants describing the type of the parameter\n"
    "@param description The description text\n"
    "@param default The default (initial) value\n"
    "@param unit The unit string\n"
  ) +
  gsi::method ("name", &db::PCellParameterDeclaration::get_name,
    "@brief Gets the name\n"
  ) +
  gsi::method ("name=", &db::PCellParameterDeclaration::set_name, gsi::arg ("value"),
    "@brief Sets the name\n"
  ) +
  gsi::method ("unit", &db::PCellParameterDeclaration::get_unit,
    "@brief Gets the unit string\n"
  ) +
  gsi::method ("unit=", &db::PCellParameterDeclaration::set_unit, gsi::arg ("unit"),
    "@brief Sets the unit string\n"
    "The unit string is shown right to the edit fields for numeric parameters.\n"
  ) +
  gsi::method_ext ("type", &get_type,
    "@brief Gets the type\n"
    "The type is one of the T... constants."
  ) +
  gsi::method_ext ("type=", &set_type, gsi::arg ("type"),
    "@brief Sets the type\n"
  ) +
  gsi::method ("description", &db::PCellParameterDeclaration::get_description,
    "@brief Gets the description text\n"
  ) +
  gsi::method ("description=", &db::PCellParameterDeclaration::set_description, gsi::arg ("description"),
    "@brief Sets the description\n"
  ) +
  gsi::method ("tooltip", &db::PCellParameterDeclaration::get_tooltip,
    "@brief Gets the tool tip text\n"
    "This attribute has been introduced in version 0.29.3."
  ) +
  gsi::method ("tooltip=", &db::PCellParameterDeclaration::set_tooltip, gsi::arg ("tooltip"),
    "@brief Sets the tool tip text\n"
    "This attribute has been introduced in version 0.29.3."
  ) +
  gsi::method ("hidden?", &db::PCellParameterDeclaration::is_hidden,
    "@brief Returns true, if the parameter is a hidden parameter that should not be shown in the user interface\n"
    "By making a parameter hidden, it is possible to create internal parameters which cannot be\n"
    "edited.\n"
  ) +
  gsi::method ("hidden=", &db::PCellParameterDeclaration::set_hidden, gsi::arg ("flag"),
    "@brief Makes the parameter hidden if this attribute is set to true\n"
  ) +
  gsi::method ("readonly?", &db::PCellParameterDeclaration::is_readonly,
    "@brief Returns true, if the parameter is a read-only parameter\n"
    "By making a parameter read-only, it is shown but cannot be\n"
    "edited.\n"
  ) +
  gsi::method ("readonly=", &db::PCellParameterDeclaration::set_readonly, gsi::arg ("flag"),
    "@brief Makes the parameter read-only if this attribute is set to true\n"
  ) +
  gsi::method_ext ("clear_choices", &clear_choices,
    "@brief Clears the list of choices\n"
  ) +
  gsi::method_ext ("add_choice", &add_choice, gsi::arg ("description"), gsi::arg ("value"),
    "@brief Add a new value to the list of choices\n"
    "This method will add the given value with the given description to the list of\n"
    "choices. If choices are defined, KLayout will show a drop-down box instead of an\n"
    "entry field in the parameter user interface.\n"
  ) +
  gsi::method ("choice_values", &db::PCellParameterDeclaration::get_choices,
    "@brief Returns a list of choice values\n"
  ) +
  gsi::method ("choice_descriptions", &db::PCellParameterDeclaration::get_choice_descriptions,
    "@brief Returns a list of choice descriptions\n"
  ) +
  gsi::method ("min_value", &db::PCellParameterDeclaration::min_value,
    "@brief Gets the minimum value allowed\n"
    "See \\min_value= for a description of this attribute.\n"
    "\n"
    "This attribute has been added in version 0.29."
  ) +
  gsi::method ("min_value=", &db::PCellParameterDeclaration::set_min_value, gsi::arg ("value"),
    "@brief Sets the minimum value allowed\n"
    "The minimum value is a visual feature and limits the allowed values for numerical\n"
    "entry boxes. This applies to parameters of type int or double. The minimum value\n"
    "is not effective if choices are present.\n"
    "\n"
    "The minimum value is not enforced - for example there is no restriction implemented\n"
    "when setting values programmatically.\n"
    "\n"
    "Setting this attribute to \"nil\" (the default) implies \"no limit\".\n"
    "\n"
    "This attribute has been added in version 0.29."
  ) +
  gsi::method ("max_value", &db::PCellParameterDeclaration::max_value,
    "@brief Gets the maximum value allowed\n"
    "See \\max_value= for a description of this attribute.\n"
    "\n"
    "This attribute has been added in version 0.29."
  ) +
  gsi::method ("max_value=", &db::PCellParameterDeclaration::set_max_value, gsi::arg ("value"),
    "@brief Sets the maximum value allowed\n"
    "The maximum value is a visual feature and limits the allowed values for numerical\n"
    "entry boxes. This applies to parameters of type int or double. The maximum value\n"
    "is not effective if choices are present.\n"
    "\n"
    "The maximum value is not enforced - for example there is no restriction implemented\n"
    "when setting values programmatically.\n"
    "\n"
    "Setting this attribute to \"nil\" (the default) implies \"no limit\".\n"
    "\n"
    "This attribute has been added in version 0.29."
  ) +
  gsi::method ("default", &db::PCellParameterDeclaration::get_default,
    "@brief Gets the default value\n"
  ) +
  gsi::method ("default=", &db::PCellParameterDeclaration::set_default, gsi::arg ("value"),
    "@brief Sets the default value\n"
    "If a default value is defined, it will be used to initialize the parameter value\n"
    "when a PCell is created.\n"
  ) +
  gsi::method ("TypeInt", &pd_type_int, "@brief Type code: integer data") +
  gsi::method ("TypeDouble", &pd_type_double, "@brief Type code: floating-point data") +
  gsi::method ("TypeString", &pd_type_string, "@brief Type code: string data") +
  gsi::method ("TypeBoolean", &pd_type_boolean, "@brief Type code: boolean data") +
  gsi::method ("TypeList", &pd_type_list, "@brief Type code: a list of variants") +
  gsi::method ("TypeLayer", &pd_type_layer, "@brief Type code: a layer (a \\LayerInfo object)") +
  gsi::method ("TypeShape", &pd_type_shape, "@brief Type code: a guiding shape (Box, Edge, Point, Polygon or Path)") +
  gsi::method ("TypeCallback", &pd_type_callback, "@brief Type code: a button triggering a callback\n\nThis code has been introduced in version 0.28.") +
  gsi::method ("TypeNone", &pd_type_none, "@brief Type code: unspecific type")
  ,
  "@brief A PCell parameter declaration\n"
  "\n"
  "This class declares a PCell parameter by providing a name, the type and a value \n"
  "and additional \n"
  "information like description, unit string and default value. It is used in the \\PCellDeclaration class to \n"
  "deliver the necessary information.\n"
  "\n"
  "This class has been introduced in version 0.22.\n"
);

}
