
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
    "@brief This signal is emitted when a different library is selected."
  ),
  "@brief A widget to select a library from the registered ones\n"
  "\n"
  "This class has been introduced in version 0.30.11."
);

#if 0
/**
 *  @brief A layer selection combo box
 *
 *  This combo box allows selecting a (physical) layer from a layout
 */
class LAYUI_PUBLIC LayerSelectionComboBox
  : public QComboBox, public tl::Object
{
Q_OBJECT

public:
  /**
   *  @brief Constructor
   */
  LayerSelectionComboBox (QWidget *parent);

  /**
   *  @brief Destructor
   */
  ~LayerSelectionComboBox ();

  /**
   *  @brief Associate with a layout
   *
   *  Associates this widget with a certain layout object - this one is being
   *  scanned for layers that are presented in this combo box.
   */
  void set_layout (const db::Layout *layout);

  /**
   *  @brief Associate with a view and cellview index
   *
   *  This method can be used instead of set_layout. If this method is used, more
   *  functionality is available, i.e. the ability to create new layers.
   *  If all_layers is set to true, layers are shown which are in the layer list, but
   *  not created as layers yet.
   */
  void set_view (lay::LayoutViewBase *view, int cv_index, bool all_layers = false);

  /**
   *  @brief Sets a flag indicating whether the "new layer" option is available
   */
  void set_new_layer_enabled (bool f);

  /**
   *  @brief Gets a flag indicating whether the "new layer" option is available
   */
  bool is_new_layer_enabled () const;

  /**
   *  @brief Sets a flag indicating whether "no layer" is available as selection
   */
  void set_no_layer_available (bool f);

  /**
   *  @brief Gets a flag indicating whether "no layer" is available as selection
   */
  bool is_no_layer_available () const;

  /**
   *  @brief Set the current layer (index)
   */
  void set_current_layer (const db::LayerProperties &lp);

  /**
   *  @brief Set the current layer (index)
   */
  void set_current_layer (int l);

  /**
   *  @brief Gets a valid indicating whether a layer is selected
   *
   *  This method returns true if "no layer" is selected
   */
  bool is_no_layer_selected () const;

  /**
   *  @brief Gets the cellview index
   *
   *  NOTE: this methods returns -1 if the widget is not
   *  associated with a cellview index.
   */
  int cv_index () const;

  /**
   *  @brief Get the current layer (index)
   *
   *  NOTE: this method returns -1 if no layer is selected or
   *  the current layer does not exist. Use "is_no_layer_selected"
   *  for a value telling whether no layer is selected (true)
   *  or a not-yet-existing layer is selected (false).
   */
  int current_layer () const;

  /**
   *  @brief Get the current layer (index) and makes sure it exists
   *
   *  This method ensures that the layer is created if it does not
   *  exist yet. It returns -1 on "no layer" (if enabled).
   */
  int current_layer_ensure ();

  /**
   *  @brief Get the current layer properties
   *
   *  If "no layer" is selected, this method returns the last properties set
   *  with "set_current_layer". Use "is_no_layer_selected" to get
   *  a value indicating whether the "no layer" entry is selected.
   */
  db::LayerProperties current_layer_props () const;

signals:
  /**
   *  @brief Signal indicating that the user selected a new layer
   *  This signal is emitted if the layer is edited. It is not emitted on programmatic changes.
   */
  void current_layer_changed ();

protected slots:
  void item_selected (int index);

private:
  LayerSelectionComboBoxPrivateData *mp_private;
  tl::DeferredMethod<LayerSelectionComboBox> dm_update_layer_list;
  bool m_ignore_layer_list_changed;

  void on_layer_list_changed (int);
  void update_layer_list ();
  void do_update_layer_list ();
  db::Layout *layout ();
  const db::Layout *layout () const;
};

/**
 *  @brief A cell view selection combo box
 *
 *  This combo box allows selecting a cellview from a lay::LayoutView
 */
class LAYUI_PUBLIC CellViewSelectionComboBox
  : public QComboBox
{
Q_OBJECT

public:
  CellViewSelectionComboBox (QWidget *parent);
  ~CellViewSelectionComboBox ();

  void set_layout_view (const lay::LayoutViewBase *view);
  const lay::LayoutViewBase *layout_view () const;

  void set_current_cv_index (int l);
  int current_cv_index () const;

private:
  CellViewSelectionComboBoxPrivateData *mp_private;
};

/**
 *  @brief Simple color chooser button
 *
 *  This class implements a special button that can replace a
 *  usual push button and supplies a color chooser without the
 *  capability to switch to "auto" color mode.
 */
class LAYUI_PUBLIC SimpleColorButton
  : public QPushButton
{
Q_OBJECT

public:
  SimpleColorButton (QPushButton *&to_replace, const char *name = 0);
  SimpleColorButton (QWidget *parent, const char *name = 0);

  QColor get_color () const;

signals:
  void color_changed (QColor color);

public slots:
  void set_color (QColor color);

private:
  QColor m_color;

  void set_color_internal (QColor color);

private slots:
  virtual void selected ();
};

/**
 *  @brief Color chooser button
 *
 *  This class implements a special button that can replace a
 *  usual push button and supplies a color chooser with the
 *  capability to switch to "auto" color mode.
 */
class LAYUI_PUBLIC ColorButton
  : public QPushButton
{
Q_OBJECT

public:
  ColorButton (QPushButton *&to_replace, const char *name = 0);
  ColorButton (QWidget *parent, const char *name = 0);

  QColor get_color () const;
  static void build_color_menu (QMenu *menu, QObject *receiver, const char *browse_slot, const char *selected_slot);

signals:
  void color_changed (QColor color);

public slots:
  void set_color (QColor color);

private:
  QColor m_color;

  void set_color_internal (QColor color);
  void build_menu ();

protected slots:
  virtual void browse_selected ();
  virtual void menu_selected ();

private slots:
  void menu_about_to_show ();
};

/**
 *  @brief An edit box with a clear button and options menu
 */
class LAYUI_PUBLIC DecoratedLineEdit
  : public QLineEdit
{
Q_OBJECT

public:
  /**
   *  @brief Constructor
   */
  DecoratedLineEdit (QWidget *parent);

  /**
   *  @brief Destructor
   */
  ~DecoratedLineEdit ();

  /**
   *  @brief Sets a value indicating whether the clear button is enabled
   *  The clear button will be on the right side of the edit box. Pressing the button
   *  will clear the text and emit a "textEdited" and "textChanged" event.
   */
  void set_clear_button_enabled (bool en);

  /**
   *  @brief Gets a value indicating whether the clear button is enabled
   */
  bool is_clear_button_enabled () const
  {
    return m_clear_button_enabled;
  }

  /**
   *  @brief Sets a value indicating whether the options button is enabled
   *  The options button appears to the left. Pressing the button will either show
   *  the options menu as set by "setOptionsMenu" or emit the "optionsButtonClicked"
   *  signal.
   */
  void set_options_button_enabled (bool en);

  /**
   *  @brief Gets a value indicating whether the options button is enabled
   */
  bool is_option_button_enabled () const
  {
    return m_options_button_enabled;
  }

  /**
   *  @brief Sets the options menu to be shown when the options button is clicked.
   *  The DecoratedLineEdit object will not take ownership over the menu.
   */
  void set_options_menu (QMenu *menu);

  /**
   *  @brief Gets the options menu
   */
  QMenu *options_menu () const;

  /**
   *  @brief Sets a value indicating whether the widgets accepts ESC keys and sends an esc_pressed signal for this
   */
  void set_escape_signal_enabled (bool f);

  /**
   *  @brief gets a value indicating whether the widgets accepts ESC keys and sends an esc_pressed signal for this
   */
  bool escape_signal_enabled () const
  {
    return m_escape_signal_enabled;
  }

  /**
   *  @brief Sets a value indicating whether the widgets accepts Tab keys and sends an tab_pressed or backtab_pressed signal for this
   */
  void set_tab_signal_enabled (bool f);

  /**
   *  @brief gets a value indicating whether the widgets accepts Tab keys and sends an tab_pressed or backtab_pressed signal for this
   */
  bool tab_signal_enabled () const
  {
    return m_tab_signal_enabled;
  }

  /**
   *  @brief Sets a label in front of the line edit
   */
  void set_label (const std::string &label);

  /**
   *  @brief Gets the label
   */
  const std::string &label () const
  {
    return m_label;
  }

signals:
  void options_button_clicked ();
  void esc_pressed ();
  void tab_pressed ();
  void backtab_pressed ();
  void clear_pressed ();

protected:
  void mousePressEvent (QMouseEvent *event);
  void mouseReleaseEvent (QMouseEvent *event);
  void resizeEvent (QResizeEvent *event);
  void keyPressEvent (QKeyEvent *event);
  bool focusNextPrevChild (bool next);
  bool event (QEvent *event);

private:
  bool m_clear_button_enabled;
  bool m_options_button_enabled;
  bool m_escape_signal_enabled;
  bool m_tab_signal_enabled;
  QLabel *mp_options_label;
  QLabel *mp_clear_label;
  QLabel *mp_front_label;
  QMenu *mp_options_menu;
  int m_default_left_margin, m_default_right_margin;
  std::string m_label;

  void set_margins ();
};
#endif  // @@@
}

#endif
