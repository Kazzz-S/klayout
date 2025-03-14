
/*

  KLayout Layout Viewer
  Copyright (C) 2006-2025 Matthias Koefferlein

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

/**
*  @file gsiDeclQAbstractTextDocumentLayout_PaintContext.cc 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#include <QAbstractTextDocumentLayout>
#include "gsiQt.h"
#include "gsiQtGuiCommon.h"
#include <memory>

// -----------------------------------------------------------------------
// struct QAbstractTextDocumentLayout::PaintContext

//  Constructor QAbstractTextDocumentLayout::PaintContext::PaintContext()


static void _init_ctor_QAbstractTextDocumentLayout_PaintContext_0 (qt_gsi::GenericStaticMethod *decl)
{
  decl->set_return_new<QAbstractTextDocumentLayout::PaintContext> ();
}

static void _call_ctor_QAbstractTextDocumentLayout_PaintContext_0 (const qt_gsi::GenericStaticMethod * /*decl*/, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<QAbstractTextDocumentLayout::PaintContext *> (new QAbstractTextDocumentLayout::PaintContext ());
}



namespace gsi
{

static gsi::Methods methods_QAbstractTextDocumentLayout_PaintContext () {
  gsi::Methods methods;
  methods += new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QAbstractTextDocumentLayout::PaintContext::PaintContext()\nThis method creates an object of class QAbstractTextDocumentLayout::PaintContext.", &_init_ctor_QAbstractTextDocumentLayout_PaintContext_0, &_call_ctor_QAbstractTextDocumentLayout_PaintContext_0);
  return methods;
}

gsi::Class<QAbstractTextDocumentLayout::PaintContext> decl_QAbstractTextDocumentLayout_PaintContext ("QtGui", "QAbstractTextDocumentLayout_PaintContext",
  methods_QAbstractTextDocumentLayout_PaintContext (),
  "@qt\n@brief Binding of QAbstractTextDocumentLayout::PaintContext");

gsi::ClassExt<QAbstractTextDocumentLayout> decl_QAbstractTextDocumentLayout_PaintContext_as_child (decl_QAbstractTextDocumentLayout_PaintContext, "PaintContext");

GSI_QTGUI_PUBLIC gsi::Class<QAbstractTextDocumentLayout::PaintContext> &qtdecl_QAbstractTextDocumentLayout_PaintContext () { return decl_QAbstractTextDocumentLayout_PaintContext; }

}

