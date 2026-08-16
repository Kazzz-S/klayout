
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

#ifndef HDR_edtPCellParametersPage
#define HDR_edtPCellParametersPage

#include "edtPCellParametersPageBase.h"

namespace edt
{

/**
 *  @brief A QScrollArea that displays and allows editing PCell parameters
 */
class PCellParametersPage
  : public PCellParametersPageBase
{
public:
  /**
   *  @brief Constructor
   */
  PCellParametersPage ();

protected:
  virtual void build_widgets (QFrame *container);
  virtual void commit_values(db::ParameterStates &states);
  virtual void apply_states (const db::ParameterStates &states);
  virtual void apply_values (const db::ParameterStates &states);

private:
  void parameter_changed_slot (QObject *sender);

private:
  std::vector<QGroupBox *> mp_groups;
  std::vector<QWidget *> m_widgets;
  std::vector<QLabel *> m_icon_widgets;
  std::vector<std::vector<QWidget *> > m_all_widgets;
  SignalToEventAddSender m_s2s_parameter_changed_slot;
};

}

#endif

#endif
