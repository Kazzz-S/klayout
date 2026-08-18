
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
#include "gsiDeclBasic.h"
#include "dbLibrary.h"
#include "layWidgets.h"
#include "layLayoutViewBase.h"

#include "gsiQt.h"
#include "gsiQtGuiExternals.h"
#include "gsiQtWidgetsExternals.h"

namespace gsi
{

static lay::DitherPatternSelectionButton *new_dither_pattern_selection_button (QWidget *parent)
{
  auto *b = new lay::DitherPatternSelectionButton (parent);
  if (parent) {
    qt_gsi::qt_keep (b);
  }
  return b;
}

Class<lay::DitherPatternSelectionButton> decl_DitherPatternSelectionButton (QT_EXTERNAL_BASE (QPushButton) "lay", "DitherPatternSelectionButton",
  gsi::constructor ("new", &new_dither_pattern_selection_button, gsi::arg ("parent"),
    "@brief Creates a new dither pattern selection button\n"
  ) +
  gsi::method ("view=", &lay::DitherPatternSelectionButton::set_view, gsi::arg ("view"),
    "@brief Associates the button with a view\n"
    "When associated with a view, the button will also display custom pattern available "
    "for this particular view. Without a view, only the standard pattern are available.\n"
  ) +
  gsi::method ("dither_pattern=", &lay::DitherPatternSelectionButton::set_dither_pattern, gsi::arg ("pattern"),
    "@brief Selects a specific pattern by index\n"
    "A negative index corresponds to 'no pattern selected'."
  ) +
  gsi::method ("dither_pattern", &lay::DitherPatternSelectionButton::dither_pattern,
    "@brief Gets the currently selected pattern\n"
    "A negative index corresponds to 'no pattern selected'."
  ) +
  gsi::qt_signal<int> ("dither_pattern_changed(int)", "dither_pattern_changed", gsi::arg("pattern"),
    "@brief This signal is emitted when a different dither pattern is selected."
  ),
  "@brief A widget to select a dither (stipple) pattern\n"
  "\n"
  "This widget can be used to select a dither pattern from the available ones.\n"
  "Pattern are selected by index. If the widget is associated with a view (see \\view=),\n"
  "additional custom pattern may be present are can also be selected. In that case, the\n"
  "dither pattern index becomes view specific.\n"
  "\n"
  "This class has been introduced in version 0.30.11."
);

static lay::LineStyleSelectionButton *new_line_style_selection_button (QWidget *parent)
{
  auto *b = new lay::LineStyleSelectionButton (parent);
  if (parent) {
    qt_gsi::qt_keep (b);
  }
  return b;
}

Class<lay::LineStyleSelectionButton> decl_LineStyleSelectionButton (QT_EXTERNAL_BASE (QPushButton) "lay", "LineStyleSelectionButton",
  gsi::constructor ("new", &new_line_style_selection_button, gsi::arg ("parent"),
    "@brief Creates a new line style selection button\n"
  ) +
  gsi::method ("view=", &lay::LineStyleSelectionButton::set_view, gsi::arg ("view"),
    "@brief Associates the button with a view\n"
    "When associated with a view, the button will also display custom line styles available "
    "for this particular view. Without a view, only the standard styles are available.\n"
  ) +
  gsi::method ("line_style=", &lay::LineStyleSelectionButton::set_line_style, gsi::arg ("style"),
    "@brief Selects a line style by index\n"
    "A negative index corresponds to 'no line style selected'."
  ) +
  gsi::method ("line_style", &lay::LineStyleSelectionButton::line_style,
    "@brief Gets the currently selected line style\n"
    "A negative index corresponds to 'no line style selected'."
  ) +
  gsi::qt_signal<int> ("line_style_changed(int)", "line_style_changed", gsi::arg("pattern"),
    "@brief This signal is emitted when a different dither pattern is selected."
  ),
  "@brief A widget to select a line style (dash pattern)\n"
  "\n"
  "This widget can be used to select a line style from the available ones.\n"
  "Line styles are selected by index. If the widget is associated with a view (see \\view=),\n"
  "additional custom line styles may be present are can also be selected. In that case, the\n"
  "line style index becomes view specific.\n"
  "\n"
  "This class has been introduced in version 0.30.11."
);

static lay::LibrarySelectionComboBox *new_library_selection_combo_box (QWidget *parent)
{
  auto *b = new lay::LibrarySelectionComboBox (parent);
  if (parent) {
    qt_gsi::qt_keep (b);
  }
  return b;
}

static void lib_sel_technology_filter (lay::LibrarySelectionComboBox *ls, const std::string &tech)
{
  if (tech == "*") {
    ls->set_technology_filter (tech, false);
  } else {
    ls->set_technology_filter (tech, true);
  }
}

Class<lay::LibrarySelectionComboBox> decl_LibrarySelectionComboBox (QT_EXTERNAL_BASE (QComboBox) "lay", "LibrarySelectionComboBox",
  gsi::constructor ("new", &new_library_selection_combo_box, gsi::arg ("parent"),
    "@brief Creates a new library selection combo box\n"
  ) +
  gsi::method ("current_library=", &lay::LibrarySelectionComboBox::set_current_library, gsi::arg ("library"),
    "@brief Selects the current library\n"
    "A nil value corresponds to 'no library selected'."
  ) +
  gsi::method ("current_library", &lay::LibrarySelectionComboBox::current_library,
    "@brief Gets the currently selected library\n"
    "A nil value corresponds to 'no library selected'."
  ) +
  gsi::method_ext ("technology=", &lib_sel_technology_filter, gsi::arg ("tech"),
    "@brief Specifies a technology filter.\n"
    "Setting this attribute to a non-empty string filters the libraries and presents "
    "only those registered for the given technology. Setting this attribute to an "
    "empty string, shows all libraries not associated with a technology.\n"
    "\n"
    "Settings this attribute to '*', all libraries are shown."
  ) +
  gsi::qt_signal<db::Library *> ("library_changed(db::Library *)", "library_changed", gsi::arg("library"),
    "@brief This signal is emitted when a different library is selected.\n"
    "The signal is also emitted if the library is changed programmatically.\n"
  ),
  "@brief A widget to select a library from the registered ones\n"
  "\n"
  "This class has been introduced in version 0.30.11."
);

static lay::CellViewSelectionComboBox *new_cell_view_selection_combo_box (QWidget *parent)
{
  auto *b = new lay::CellViewSelectionComboBox (parent);
  if (parent) {
    qt_gsi::qt_keep (b);
  }
  return b;
}

Class<lay::CellViewSelectionComboBox> decl_CellViewSelectionComboBox (QT_EXTERNAL_BASE (QComboBox) "lay", "CellViewSelectionComboBox",
  gsi::constructor ("new", &new_cell_view_selection_combo_box, gsi::arg ("parent"),
    "@brief Creates a new cell view selection combo box\n"
  ) +
  gsi::method ("layout_view=", &lay::CellViewSelectionComboBox::set_layout_view, gsi::arg ("view"),
    "@brief Associates the selection widget with a specific view.\n"
    "The view provides the list of selectable cell views. Hence, only selection widgets that "
    "are associated with a view are useful. Set this attribute to attach the widget to a specific view.\n"
  ) +
  gsi::method ("layout_view", &lay::CellViewSelectionComboBox::layout_view,
    "@brief Gets the view object this widget is associated with.\n"
    "See \\layout_view= for details about this attribute."
  ) +
  gsi::method ("current_cell_view_index=", &lay::CellViewSelectionComboBox::set_current_cv_index, gsi::arg ("cv_index"),
    "@brief Sets the index of the current cell view\n"
    "A negative value corresponds to 'no view selected'.\n"
    "The cell view index addresses a CellView inside the \\LayoutView associated with this "
    "selection widget through \\layout_view=."
  ) +
  gsi::method ("current_cell_view_index", &lay::CellViewSelectionComboBox::current_cv_index,
    "@brief Gets the index of the currently selected cell view\n"
    "See \\current_cell_view= for details of this attribute."
  ) +
  gsi::qt_signal<int> ("current_cv_index_changed(int)", "current_cv_index_changed", gsi::arg("cell_view_index"),
    "@brief This signal is emitted when a different cell view is selected.\n"
    "The signal is also emitted if the cell view is changed programmatically.\n"
  ),
  "@brief A widget to select a cell view from a view\n"
  "\n"
  "To use the widget, first associate it to a view by using \\layout_view=. The widget\n"
  "will show the cell views available inside the layout view and allows selecting one of them.\n"
  "\n"
  "This class has been introduced in version 0.30.11."
);

static lay::LayerSelectionComboBox *new_layerselection_combo_box (QWidget *parent)
{
  auto *b = new lay::LayerSelectionComboBox (parent);
  if (parent) {
    qt_gsi::qt_keep (b);
  }
  return b;
}

Class<lay::LayerSelectionComboBox> decl_LayerSelectionComboBox (QT_EXTERNAL_BASE (QComboBox) "lay", "LayerSelectionComboBox",
  gsi::constructor ("new", &new_layerselection_combo_box, gsi::arg ("parent"),
    "@brief Creates a new layer selection combo box\n"
  ) +
  gsi::method ("set_layout", &lay::LayerSelectionComboBox::set_layout, gsi::arg ("layout"),
    "@brief Attaches the widget to a layout.\n"
    "The widget will display the layers present in the layout and allows selecting one of them.\n"
    "Alternatively, the widget can be associated with a view using \\set_view."
  ) +
  gsi::method ("set_view", &lay::LayerSelectionComboBox::set_view, gsi::arg ("view"), gsi::arg ("cv_index"), gsi::arg ("all_layers", false),
    "@brief Attaches the widget to a layout view.\n"
    "After attaching the widget to a view, the layers present in the layout view for the\n"
    "given cell view are shown in the widget. If 'all_layers' is set to true, also layers are\n"
    "shown which are in the layer list, but not created as layers yet in the underlying \\Layout object.\n"
    "\n"
    "Alternatively, the widget can be attached to a \\Layout object directly using \\set_layout,\n"
    "but in that case, layer colors or styles are not indicated."
  ) +
  gsi::method ("is_new_layer_enabled?", &lay::LayerSelectionComboBox::is_new_layer_enabled,
    "@brief Gets a flag indicating whether the 'new layer' option is available.\n"
    "See \\new_layer_enabled= for details about this attribute.\n"
  ) +
  gsi::method ("new_layer_enabled=", &lay::LayerSelectionComboBox::set_new_layer_enabled, gsi::arg ("enabled"),
    "@brief Sets a flag indicating whether the 'new layer' option is available.\n"
    "With this attribute set to true, the drop-down list provides an entry that allows creating new layers.\n"
  ) +
  gsi::method ("is_optional?", &lay::LayerSelectionComboBox::is_no_layer_available,
    "@brief Sets a flag indicating whether it is possible to choose 'no layer'.\n"
    "See \\optional= for details about this attribute.\n"
  ) +
  gsi::method ("optional=", &lay::LayerSelectionComboBox::set_no_layer_available, gsi::arg ("enabled"),
    "@brief Sets a flag indicating whether it is possible to choose 'no layer'.\n"
    "With this attribute set to true, the drop-down list provides an entry that allows selecting 'nothing'.\n"
  ) +
  gsi::method ("current_layer=", static_cast<void (lay::LayerSelectionComboBox::*) (const db::LayerProperties &)> (&lay::LayerSelectionComboBox::set_current_layer), gsi::arg ("layer_info"),
    "@brief Selects the current layer by layer properties.\n"
    "'no layer' is selected by using an empty \\LayerInfo object."
  ) +
  gsi::method ("current_layer=", static_cast<void (lay::LayerSelectionComboBox::*) (int)> (&lay::LayerSelectionComboBox::set_current_layer), gsi::arg ("layer_index"),
    "@brief Selects the current layer by layer index in the current layout the widget is attached to.\n"
    "'no layer' is selected by using a negative layer index."
  ) +
  gsi::method ("current_layer_index", &lay::LayerSelectionComboBox::current_layer,
    "@brief Gets the index of the currently selected layer.\n"
    "A negative value is returned if the currently selected layer does not exist yet "
    "in the associated \\Layout or 'no layer' is selected. To differentiate, use the "
    "\\is_no_layer_selected attribute - it will return true, if 'no layer' is selected "
    "and false, if the layer is not created yet (also rendering a negative index).\n"
    "\n"
    "In most cases, it will be easier to use \\current_layer_index_ensure, which makes "
    "sure the requested layer is created in the \\Layout object and only returns a "
    "negative index, if 'no layer' is requested."
  ) +
  gsi::method ("current_layer_index_ensure", &lay::LayerSelectionComboBox::current_layer_ensure,
    "@brief Gets the index of the currently selected layer and creates the layer if required.\n"
    "See \\current_layer_index for a discussion of this method."
  ) +
  gsi::method ("is_no_layer_selected", &lay::LayerSelectionComboBox::is_no_layer_selected,
    "@brief Gets a value indicating whether 'no layer' is selected.\n"
    "See \\current_layer_index for a discussion of this method."
  ) +
  gsi::method ("current_layer_info", &lay::LayerSelectionComboBox::current_layer_props,
    "@brief Gets the layer properties of the currently selected layer.\n"
    "This method can be used alternatively to \\current_layer_index or \\current_layer_index_ensure "
    "and will deliver the \\LayerInfo object of the currently selected layer.\n"
    "\n"
    "If 'no layer' is selected, an empty \\LayerInfo object is returned."
  ) +
  gsi::qt_signal ("current_layer_changed()", "current_layer_changed",
    "@brief This signal is emitted when a new layer is selected.\n"
    "The signal is not emitted if the layer is changed programmatically.\n"
  ),
  "@brief A widget to select a layer from a Layout or a cell view inside a LayoutView\n"
  "\n"
  "To use the widget, first associate it to a view by using \\set_layout_view or to a Layout using \\set_layout.\n"
  "The widget will show the layers available and allows selecting one of them.\n"
  "\n"
  "This class has been introduced in version 0.30.11."
);

static lay::SimpleColorButton *new_simple_color_button (QWidget *parent)
{
  auto *b = new lay::SimpleColorButton (parent);
  if (parent) {
    qt_gsi::qt_keep (b);
  }
  return b;
}

Class<lay::SimpleColorButton> decl_SimpleColorButton (QT_EXTERNAL_BASE (QComboBox) "lay", "SimpleColorButton",
  gsi::constructor ("new", &new_simple_color_button, gsi::arg ("parent"),
    "@brief Creates a simple color selection button\n"
  ) +
  gsi::method ("color=", &lay::SimpleColorButton::set_color, gsi::arg ("color"),
    "@brief Selects the current color.\n"
  ) +
  gsi::method ("color", &lay::SimpleColorButton::get_color,
    "@brief Gets the current color.\n"
  ) +
  gsi::qt_signal<QColor> ("color_changed(QColor)", "color_changed", gsi::arg ("color"),
    "@brief This signal is emitted when a new color is selected.\n"
    "The signal is not emitted if the color is changed programmatically.\n"
  ),
  "@brief A widget to select a color\n"
  "\n"
  "Another widget exists (\\ColorButton) which allows selecting 'Auto' color in addition to a plain color\n"
  "and that has a predefined palette.\n"
  "\n"
  "This class has been introduced in version 0.30.11."
);

static lay::ColorButton *new_color_button (QWidget *parent)
{
  auto *b = new lay::ColorButton (parent);
  if (parent) {
    qt_gsi::qt_keep (b);
  }
  return b;
}

Class<lay::ColorButton> decl_ColorButton (QT_EXTERNAL_BASE (QComboBox) "lay", "ColorButton",
  gsi::constructor ("new", &new_color_button, gsi::arg ("parent"),
    "@brief Creates a simple color selection button\n"
  ) +
  gsi::method ("color=", &lay::ColorButton::set_color, gsi::arg ("color"),
    "@brief Selects the current color.\n"
  ) +
  gsi::method ("color", &lay::ColorButton::get_color,
    "@brief Gets the current color.\n"
  ) +
  gsi::qt_signal<QColor> ("color_changed(QColor)", "color_changed", gsi::arg ("color"),
    "@brief This signal is emitted when a new color is selected.\n"
    "The signal is not emitted if the color is changed programmatically.\n"
  ),
  "@brief A widget to select a color\n"
  "\n"
  "This version of the color chooser button has a palette and allows\n"
  "selecting an 'Auto' color (the system is supposed to choose one).\n"
  "The 'Auto' color is represented by an invalid QColor object.\n"
  "\n"
  "This class has been introduced in version 0.30.11."
);

}

#endif
