
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
*  @file gsiDeclQAccessibleTableModelChangeEvent.cc 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#include <QAccessibleTableModelChangeEvent>
#include <QAccessibleInterface>
#include <QObject>
#include "gsiQt.h"
#include "gsiQtGuiCommon.h"
#include <memory>

// -----------------------------------------------------------------------
// class QAccessibleTableModelChangeEvent

// int QAccessibleTableModelChangeEvent::firstColumn()


static void _init_f_firstColumn_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<int > ();
}

static void _call_f_firstColumn_c0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<int > ((int)((QAccessibleTableModelChangeEvent *)cls)->firstColumn ());
}


// int QAccessibleTableModelChangeEvent::firstRow()


static void _init_f_firstRow_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<int > ();
}

static void _call_f_firstRow_c0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<int > ((int)((QAccessibleTableModelChangeEvent *)cls)->firstRow ());
}


// int QAccessibleTableModelChangeEvent::lastColumn()


static void _init_f_lastColumn_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<int > ();
}

static void _call_f_lastColumn_c0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<int > ((int)((QAccessibleTableModelChangeEvent *)cls)->lastColumn ());
}


// int QAccessibleTableModelChangeEvent::lastRow()


static void _init_f_lastRow_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<int > ();
}

static void _call_f_lastRow_c0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<int > ((int)((QAccessibleTableModelChangeEvent *)cls)->lastRow ());
}


// QAccessibleTableModelChangeEvent::ModelChangeType QAccessibleTableModelChangeEvent::modelChangeType()


static void _init_f_modelChangeType_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<qt_gsi::Converter<QAccessibleTableModelChangeEvent::ModelChangeType>::target_type > ();
}

static void _call_f_modelChangeType_c0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<qt_gsi::Converter<QAccessibleTableModelChangeEvent::ModelChangeType>::target_type > ((qt_gsi::Converter<QAccessibleTableModelChangeEvent::ModelChangeType>::target_type)qt_gsi::CppToQtAdaptor<QAccessibleTableModelChangeEvent::ModelChangeType>(((QAccessibleTableModelChangeEvent *)cls)->modelChangeType ()));
}


// void QAccessibleTableModelChangeEvent::setFirstColumn(int col)


static void _init_f_setFirstColumn_767 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("col");
  decl->add_arg<int > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setFirstColumn_767 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  int arg1 = gsi::arg_reader<int >() (args, heap);
  __SUPPRESS_UNUSED_WARNING(ret);
  ((QAccessibleTableModelChangeEvent *)cls)->setFirstColumn (arg1);
}


// void QAccessibleTableModelChangeEvent::setFirstRow(int row)


static void _init_f_setFirstRow_767 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("row");
  decl->add_arg<int > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setFirstRow_767 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  int arg1 = gsi::arg_reader<int >() (args, heap);
  __SUPPRESS_UNUSED_WARNING(ret);
  ((QAccessibleTableModelChangeEvent *)cls)->setFirstRow (arg1);
}


// void QAccessibleTableModelChangeEvent::setLastColumn(int col)


static void _init_f_setLastColumn_767 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("col");
  decl->add_arg<int > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setLastColumn_767 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  int arg1 = gsi::arg_reader<int >() (args, heap);
  __SUPPRESS_UNUSED_WARNING(ret);
  ((QAccessibleTableModelChangeEvent *)cls)->setLastColumn (arg1);
}


// void QAccessibleTableModelChangeEvent::setLastRow(int row)


static void _init_f_setLastRow_767 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("row");
  decl->add_arg<int > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setLastRow_767 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  int arg1 = gsi::arg_reader<int >() (args, heap);
  __SUPPRESS_UNUSED_WARNING(ret);
  ((QAccessibleTableModelChangeEvent *)cls)->setLastRow (arg1);
}


// void QAccessibleTableModelChangeEvent::setModelChangeType(QAccessibleTableModelChangeEvent::ModelChangeType changeType)


static void _init_f_setModelChangeType_5217 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("changeType");
  decl->add_arg<const qt_gsi::Converter<QAccessibleTableModelChangeEvent::ModelChangeType>::target_type & > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setModelChangeType_5217 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  const qt_gsi::Converter<QAccessibleTableModelChangeEvent::ModelChangeType>::target_type & arg1 = gsi::arg_reader<const qt_gsi::Converter<QAccessibleTableModelChangeEvent::ModelChangeType>::target_type & >() (args, heap);
  __SUPPRESS_UNUSED_WARNING(ret);
  ((QAccessibleTableModelChangeEvent *)cls)->setModelChangeType (qt_gsi::QtToCppAdaptor<QAccessibleTableModelChangeEvent::ModelChangeType>(arg1).cref());
}


namespace gsi
{

static gsi::Methods methods_QAccessibleTableModelChangeEvent () {
  gsi::Methods methods;
  methods += new qt_gsi::GenericMethod (":firstColumn", "@brief Method int QAccessibleTableModelChangeEvent::firstColumn()\n", true, &_init_f_firstColumn_c0, &_call_f_firstColumn_c0);
  methods += new qt_gsi::GenericMethod (":firstRow", "@brief Method int QAccessibleTableModelChangeEvent::firstRow()\n", true, &_init_f_firstRow_c0, &_call_f_firstRow_c0);
  methods += new qt_gsi::GenericMethod (":lastColumn", "@brief Method int QAccessibleTableModelChangeEvent::lastColumn()\n", true, &_init_f_lastColumn_c0, &_call_f_lastColumn_c0);
  methods += new qt_gsi::GenericMethod (":lastRow", "@brief Method int QAccessibleTableModelChangeEvent::lastRow()\n", true, &_init_f_lastRow_c0, &_call_f_lastRow_c0);
  methods += new qt_gsi::GenericMethod (":modelChangeType", "@brief Method QAccessibleTableModelChangeEvent::ModelChangeType QAccessibleTableModelChangeEvent::modelChangeType()\n", true, &_init_f_modelChangeType_c0, &_call_f_modelChangeType_c0);
  methods += new qt_gsi::GenericMethod ("setFirstColumn|firstColumn=", "@brief Method void QAccessibleTableModelChangeEvent::setFirstColumn(int col)\n", false, &_init_f_setFirstColumn_767, &_call_f_setFirstColumn_767);
  methods += new qt_gsi::GenericMethod ("setFirstRow|firstRow=", "@brief Method void QAccessibleTableModelChangeEvent::setFirstRow(int row)\n", false, &_init_f_setFirstRow_767, &_call_f_setFirstRow_767);
  methods += new qt_gsi::GenericMethod ("setLastColumn|lastColumn=", "@brief Method void QAccessibleTableModelChangeEvent::setLastColumn(int col)\n", false, &_init_f_setLastColumn_767, &_call_f_setLastColumn_767);
  methods += new qt_gsi::GenericMethod ("setLastRow|lastRow=", "@brief Method void QAccessibleTableModelChangeEvent::setLastRow(int row)\n", false, &_init_f_setLastRow_767, &_call_f_setLastRow_767);
  methods += new qt_gsi::GenericMethod ("setModelChangeType|modelChangeType=", "@brief Method void QAccessibleTableModelChangeEvent::setModelChangeType(QAccessibleTableModelChangeEvent::ModelChangeType changeType)\n", false, &_init_f_setModelChangeType_5217, &_call_f_setModelChangeType_5217);
  return methods;
}

gsi::Class<QAccessibleEvent> &qtdecl_QAccessibleEvent ();

gsi::Class<QAccessibleTableModelChangeEvent> decl_QAccessibleTableModelChangeEvent (qtdecl_QAccessibleEvent (), "QtGui", "QAccessibleTableModelChangeEvent_Native",
  methods_QAccessibleTableModelChangeEvent (),
  "@hide\n@alias QAccessibleTableModelChangeEvent");

GSI_QTGUI_PUBLIC gsi::Class<QAccessibleTableModelChangeEvent> &qtdecl_QAccessibleTableModelChangeEvent () { return decl_QAccessibleTableModelChangeEvent; }

}


class QAccessibleTableModelChangeEvent_Adaptor : public QAccessibleTableModelChangeEvent, public qt_gsi::QtObjectBase
{
public:

  virtual ~QAccessibleTableModelChangeEvent_Adaptor();

  //  [adaptor ctor] QAccessibleTableModelChangeEvent::QAccessibleTableModelChangeEvent(QObject *obj, QAccessibleTableModelChangeEvent::ModelChangeType changeType)
  QAccessibleTableModelChangeEvent_Adaptor(QObject *obj, QAccessibleTableModelChangeEvent::ModelChangeType changeType) : QAccessibleTableModelChangeEvent(obj, changeType)
  {
    qt_gsi::QtObjectBase::init (this);
  }

  //  [adaptor ctor] QAccessibleTableModelChangeEvent::QAccessibleTableModelChangeEvent(QAccessibleInterface *iface, QAccessibleTableModelChangeEvent::ModelChangeType changeType)
  QAccessibleTableModelChangeEvent_Adaptor(QAccessibleInterface *iface, QAccessibleTableModelChangeEvent::ModelChangeType changeType) : QAccessibleTableModelChangeEvent(iface, changeType)
  {
    qt_gsi::QtObjectBase::init (this);
  }

  //  [adaptor impl] QAccessibleInterface *QAccessibleTableModelChangeEvent::accessibleInterface()
  QAccessibleInterface * cbs_accessibleInterface_c0_0() const
  {
    return QAccessibleTableModelChangeEvent::accessibleInterface();
  }

  virtual QAccessibleInterface * accessibleInterface() const
  {
    if (cb_accessibleInterface_c0_0.can_issue()) {
      return cb_accessibleInterface_c0_0.issue<QAccessibleTableModelChangeEvent_Adaptor, QAccessibleInterface *>(&QAccessibleTableModelChangeEvent_Adaptor::cbs_accessibleInterface_c0_0);
    } else {
      return QAccessibleTableModelChangeEvent::accessibleInterface();
    }
  }

  gsi::Callback cb_accessibleInterface_c0_0;
};

QAccessibleTableModelChangeEvent_Adaptor::~QAccessibleTableModelChangeEvent_Adaptor() { }

//  Constructor QAccessibleTableModelChangeEvent::QAccessibleTableModelChangeEvent(QObject *obj, QAccessibleTableModelChangeEvent::ModelChangeType changeType) (adaptor class)

static void _init_ctor_QAccessibleTableModelChangeEvent_Adaptor_6411 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("obj");
  decl->add_arg<QObject * > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("changeType");
  decl->add_arg<const qt_gsi::Converter<QAccessibleTableModelChangeEvent::ModelChangeType>::target_type & > (argspec_1);
  decl->set_return_new<QAccessibleTableModelChangeEvent_Adaptor> ();
}

static void _call_ctor_QAccessibleTableModelChangeEvent_Adaptor_6411 (const qt_gsi::GenericStaticMethod * /*decl*/, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  QObject *arg1 = gsi::arg_reader<QObject * >() (args, heap);
  const qt_gsi::Converter<QAccessibleTableModelChangeEvent::ModelChangeType>::target_type & arg2 = gsi::arg_reader<const qt_gsi::Converter<QAccessibleTableModelChangeEvent::ModelChangeType>::target_type & >() (args, heap);
  ret.write<QAccessibleTableModelChangeEvent_Adaptor *> (new QAccessibleTableModelChangeEvent_Adaptor (arg1, qt_gsi::QtToCppAdaptor<QAccessibleTableModelChangeEvent::ModelChangeType>(arg2).cref()));
}


//  Constructor QAccessibleTableModelChangeEvent::QAccessibleTableModelChangeEvent(QAccessibleInterface *iface, QAccessibleTableModelChangeEvent::ModelChangeType changeType) (adaptor class)

static void _init_ctor_QAccessibleTableModelChangeEvent_Adaptor_7731 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("iface");
  decl->add_arg<QAccessibleInterface * > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("changeType");
  decl->add_arg<const qt_gsi::Converter<QAccessibleTableModelChangeEvent::ModelChangeType>::target_type & > (argspec_1);
  decl->set_return_new<QAccessibleTableModelChangeEvent_Adaptor> ();
}

static void _call_ctor_QAccessibleTableModelChangeEvent_Adaptor_7731 (const qt_gsi::GenericStaticMethod * /*decl*/, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  QAccessibleInterface *arg1 = gsi::arg_reader<QAccessibleInterface * >() (args, heap);
  const qt_gsi::Converter<QAccessibleTableModelChangeEvent::ModelChangeType>::target_type & arg2 = gsi::arg_reader<const qt_gsi::Converter<QAccessibleTableModelChangeEvent::ModelChangeType>::target_type & >() (args, heap);
  ret.write<QAccessibleTableModelChangeEvent_Adaptor *> (new QAccessibleTableModelChangeEvent_Adaptor (arg1, qt_gsi::QtToCppAdaptor<QAccessibleTableModelChangeEvent::ModelChangeType>(arg2).cref()));
}


// QAccessibleInterface *QAccessibleTableModelChangeEvent::accessibleInterface()

static void _init_cbs_accessibleInterface_c0_0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QAccessibleInterface * > ();
}

static void _call_cbs_accessibleInterface_c0_0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<QAccessibleInterface * > ((QAccessibleInterface *)((QAccessibleTableModelChangeEvent_Adaptor *)cls)->cbs_accessibleInterface_c0_0 ());
}

static void _set_callback_cbs_accessibleInterface_c0_0 (void *cls, const gsi::Callback &cb)
{
  ((QAccessibleTableModelChangeEvent_Adaptor *)cls)->cb_accessibleInterface_c0_0 = cb;
}


namespace gsi
{

gsi::Class<QAccessibleTableModelChangeEvent> &qtdecl_QAccessibleTableModelChangeEvent ();

static gsi::Methods methods_QAccessibleTableModelChangeEvent_Adaptor () {
  gsi::Methods methods;
  methods += new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QAccessibleTableModelChangeEvent::QAccessibleTableModelChangeEvent(QObject *obj, QAccessibleTableModelChangeEvent::ModelChangeType changeType)\nThis method creates an object of class QAccessibleTableModelChangeEvent.", &_init_ctor_QAccessibleTableModelChangeEvent_Adaptor_6411, &_call_ctor_QAccessibleTableModelChangeEvent_Adaptor_6411);
  methods += new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QAccessibleTableModelChangeEvent::QAccessibleTableModelChangeEvent(QAccessibleInterface *iface, QAccessibleTableModelChangeEvent::ModelChangeType changeType)\nThis method creates an object of class QAccessibleTableModelChangeEvent.", &_init_ctor_QAccessibleTableModelChangeEvent_Adaptor_7731, &_call_ctor_QAccessibleTableModelChangeEvent_Adaptor_7731);
  methods += new qt_gsi::GenericMethod ("accessibleInterface", "@brief Virtual method QAccessibleInterface *QAccessibleTableModelChangeEvent::accessibleInterface()\nThis method can be reimplemented in a derived class.", true, &_init_cbs_accessibleInterface_c0_0, &_call_cbs_accessibleInterface_c0_0);
  methods += new qt_gsi::GenericMethod ("accessibleInterface", "@hide", true, &_init_cbs_accessibleInterface_c0_0, &_call_cbs_accessibleInterface_c0_0, &_set_callback_cbs_accessibleInterface_c0_0);
  return methods;
}

gsi::Class<QAccessibleTableModelChangeEvent_Adaptor> decl_QAccessibleTableModelChangeEvent_Adaptor (qtdecl_QAccessibleTableModelChangeEvent (), "QtGui", "QAccessibleTableModelChangeEvent",
  methods_QAccessibleTableModelChangeEvent_Adaptor (),
  "@qt\n@brief Binding of QAccessibleTableModelChangeEvent");

}


//  Implementation of the enum wrapper class for QAccessibleTableModelChangeEvent::ModelChangeType
namespace qt_gsi
{

static gsi::Enum<QAccessibleTableModelChangeEvent::ModelChangeType> decl_QAccessibleTableModelChangeEvent_ModelChangeType_Enum ("QtGui", "QAccessibleTableModelChangeEvent_ModelChangeType",
    gsi::enum_const ("ModelReset", QAccessibleTableModelChangeEvent::ModelReset, "@brief Enum constant QAccessibleTableModelChangeEvent::ModelReset") +
    gsi::enum_const ("DataChanged", QAccessibleTableModelChangeEvent::DataChanged, "@brief Enum constant QAccessibleTableModelChangeEvent::DataChanged") +
    gsi::enum_const ("RowsInserted", QAccessibleTableModelChangeEvent::RowsInserted, "@brief Enum constant QAccessibleTableModelChangeEvent::RowsInserted") +
    gsi::enum_const ("ColumnsInserted", QAccessibleTableModelChangeEvent::ColumnsInserted, "@brief Enum constant QAccessibleTableModelChangeEvent::ColumnsInserted") +
    gsi::enum_const ("RowsRemoved", QAccessibleTableModelChangeEvent::RowsRemoved, "@brief Enum constant QAccessibleTableModelChangeEvent::RowsRemoved") +
    gsi::enum_const ("ColumnsRemoved", QAccessibleTableModelChangeEvent::ColumnsRemoved, "@brief Enum constant QAccessibleTableModelChangeEvent::ColumnsRemoved"),
  "@qt\n@brief This class represents the QAccessibleTableModelChangeEvent::ModelChangeType enum");

static gsi::QFlagsClass<QAccessibleTableModelChangeEvent::ModelChangeType > decl_QAccessibleTableModelChangeEvent_ModelChangeType_Enums ("QtGui", "QAccessibleTableModelChangeEvent_QFlags_ModelChangeType",
  "@qt\n@brief This class represents the QFlags<QAccessibleTableModelChangeEvent::ModelChangeType> flag set");

//  Inject the declarations into the parent
static gsi::ClassExt<QAccessibleTableModelChangeEvent> inject_QAccessibleTableModelChangeEvent_ModelChangeType_Enum_in_parent (decl_QAccessibleTableModelChangeEvent_ModelChangeType_Enum.defs ());
static gsi::ClassExt<QAccessibleTableModelChangeEvent> decl_QAccessibleTableModelChangeEvent_ModelChangeType_Enum_as_child (decl_QAccessibleTableModelChangeEvent_ModelChangeType_Enum, "ModelChangeType");
static gsi::ClassExt<QAccessibleTableModelChangeEvent> decl_QAccessibleTableModelChangeEvent_ModelChangeType_Enums_as_child (decl_QAccessibleTableModelChangeEvent_ModelChangeType_Enums, "QFlags_ModelChangeType");

}

