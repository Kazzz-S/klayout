
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
*  @file gsiDeclQCameraFocusZone.cc 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#include <QCameraFocusZone>
#include <QRectF>
#include "gsiQt.h"
#include "gsiQtMultimediaCommon.h"
#include <memory>

// -----------------------------------------------------------------------
// class QCameraFocusZone

//  Constructor QCameraFocusZone::QCameraFocusZone()


static void _init_ctor_QCameraFocusZone_0 (qt_gsi::GenericStaticMethod *decl)
{
  decl->set_return_new<QCameraFocusZone> ();
}

static void _call_ctor_QCameraFocusZone_0 (const qt_gsi::GenericStaticMethod * /*decl*/, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<QCameraFocusZone *> (new QCameraFocusZone ());
}


//  Constructor QCameraFocusZone::QCameraFocusZone(const QRectF &area, QCameraFocusZone::FocusZoneStatus status)


static void _init_ctor_QCameraFocusZone_5464 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("area");
  decl->add_arg<const QRectF & > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("status", true, "QCameraFocusZone::Selected");
  decl->add_arg<const qt_gsi::Converter<QCameraFocusZone::FocusZoneStatus>::target_type & > (argspec_1);
  decl->set_return_new<QCameraFocusZone> ();
}

static void _call_ctor_QCameraFocusZone_5464 (const qt_gsi::GenericStaticMethod * /*decl*/, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  const QRectF &arg1 = gsi::arg_reader<const QRectF & >() (args, heap);
  const qt_gsi::Converter<QCameraFocusZone::FocusZoneStatus>::target_type & arg2 = args ? gsi::arg_reader<const qt_gsi::Converter<QCameraFocusZone::FocusZoneStatus>::target_type & >() (args, heap) : gsi::arg_maker<const qt_gsi::Converter<QCameraFocusZone::FocusZoneStatus>::target_type & >() (qt_gsi::CppToQtReadAdaptor<QCameraFocusZone::FocusZoneStatus>(heap, QCameraFocusZone::Selected), heap);
  ret.write<QCameraFocusZone *> (new QCameraFocusZone (arg1, qt_gsi::QtToCppAdaptor<QCameraFocusZone::FocusZoneStatus>(arg2).cref()));
}


//  Constructor QCameraFocusZone::QCameraFocusZone(const QCameraFocusZone &other)


static void _init_ctor_QCameraFocusZone_2903 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("other");
  decl->add_arg<const QCameraFocusZone & > (argspec_0);
  decl->set_return_new<QCameraFocusZone> ();
}

static void _call_ctor_QCameraFocusZone_2903 (const qt_gsi::GenericStaticMethod * /*decl*/, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  const QCameraFocusZone &arg1 = gsi::arg_reader<const QCameraFocusZone & >() (args, heap);
  ret.write<QCameraFocusZone *> (new QCameraFocusZone (arg1));
}


// QRectF QCameraFocusZone::area()


static void _init_f_area_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QRectF > ();
}

static void _call_f_area_c0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<QRectF > ((QRectF)((QCameraFocusZone *)cls)->area ());
}


// bool QCameraFocusZone::isValid()


static void _init_f_isValid_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<bool > ();
}

static void _call_f_isValid_c0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<bool > ((bool)((QCameraFocusZone *)cls)->isValid ());
}


// bool QCameraFocusZone::operator!=(const QCameraFocusZone &other)


static void _init_f_operator_excl__eq__c2903 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("other");
  decl->add_arg<const QCameraFocusZone & > (argspec_0);
  decl->set_return<bool > ();
}

static void _call_f_operator_excl__eq__c2903 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  const QCameraFocusZone &arg1 = gsi::arg_reader<const QCameraFocusZone & >() (args, heap);
  ret.write<bool > ((bool)((QCameraFocusZone *)cls)->operator!= (arg1));
}


// QCameraFocusZone &QCameraFocusZone::operator=(const QCameraFocusZone &other)


static void _init_f_operator_eq__2903 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("other");
  decl->add_arg<const QCameraFocusZone & > (argspec_0);
  decl->set_return<QCameraFocusZone & > ();
}

static void _call_f_operator_eq__2903 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  const QCameraFocusZone &arg1 = gsi::arg_reader<const QCameraFocusZone & >() (args, heap);
  ret.write<QCameraFocusZone & > ((QCameraFocusZone &)((QCameraFocusZone *)cls)->operator= (arg1));
}


// bool QCameraFocusZone::operator==(const QCameraFocusZone &other)


static void _init_f_operator_eq__eq__c2903 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("other");
  decl->add_arg<const QCameraFocusZone & > (argspec_0);
  decl->set_return<bool > ();
}

static void _call_f_operator_eq__eq__c2903 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  const QCameraFocusZone &arg1 = gsi::arg_reader<const QCameraFocusZone & >() (args, heap);
  ret.write<bool > ((bool)((QCameraFocusZone *)cls)->operator== (arg1));
}


// void QCameraFocusZone::setStatus(QCameraFocusZone::FocusZoneStatus status)


static void _init_f_setStatus_3710 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("status");
  decl->add_arg<const qt_gsi::Converter<QCameraFocusZone::FocusZoneStatus>::target_type & > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setStatus_3710 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  const qt_gsi::Converter<QCameraFocusZone::FocusZoneStatus>::target_type & arg1 = gsi::arg_reader<const qt_gsi::Converter<QCameraFocusZone::FocusZoneStatus>::target_type & >() (args, heap);
  __SUPPRESS_UNUSED_WARNING(ret);
  ((QCameraFocusZone *)cls)->setStatus (qt_gsi::QtToCppAdaptor<QCameraFocusZone::FocusZoneStatus>(arg1).cref());
}


// QCameraFocusZone::FocusZoneStatus QCameraFocusZone::status()


static void _init_f_status_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<qt_gsi::Converter<QCameraFocusZone::FocusZoneStatus>::target_type > ();
}

static void _call_f_status_c0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<qt_gsi::Converter<QCameraFocusZone::FocusZoneStatus>::target_type > ((qt_gsi::Converter<QCameraFocusZone::FocusZoneStatus>::target_type)qt_gsi::CppToQtAdaptor<QCameraFocusZone::FocusZoneStatus>(((QCameraFocusZone *)cls)->status ()));
}



namespace gsi
{

static gsi::Methods methods_QCameraFocusZone () {
  gsi::Methods methods;
  methods += new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QCameraFocusZone::QCameraFocusZone()\nThis method creates an object of class QCameraFocusZone.", &_init_ctor_QCameraFocusZone_0, &_call_ctor_QCameraFocusZone_0);
  methods += new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QCameraFocusZone::QCameraFocusZone(const QRectF &area, QCameraFocusZone::FocusZoneStatus status)\nThis method creates an object of class QCameraFocusZone.", &_init_ctor_QCameraFocusZone_5464, &_call_ctor_QCameraFocusZone_5464);
  methods += new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QCameraFocusZone::QCameraFocusZone(const QCameraFocusZone &other)\nThis method creates an object of class QCameraFocusZone.", &_init_ctor_QCameraFocusZone_2903, &_call_ctor_QCameraFocusZone_2903);
  methods += new qt_gsi::GenericMethod ("area", "@brief Method QRectF QCameraFocusZone::area()\n", true, &_init_f_area_c0, &_call_f_area_c0);
  methods += new qt_gsi::GenericMethod ("isValid?", "@brief Method bool QCameraFocusZone::isValid()\n", true, &_init_f_isValid_c0, &_call_f_isValid_c0);
  methods += new qt_gsi::GenericMethod ("!=", "@brief Method bool QCameraFocusZone::operator!=(const QCameraFocusZone &other)\n", true, &_init_f_operator_excl__eq__c2903, &_call_f_operator_excl__eq__c2903);
  methods += new qt_gsi::GenericMethod ("assign", "@brief Method QCameraFocusZone &QCameraFocusZone::operator=(const QCameraFocusZone &other)\n", false, &_init_f_operator_eq__2903, &_call_f_operator_eq__2903);
  methods += new qt_gsi::GenericMethod ("==", "@brief Method bool QCameraFocusZone::operator==(const QCameraFocusZone &other)\n", true, &_init_f_operator_eq__eq__c2903, &_call_f_operator_eq__eq__c2903);
  methods += new qt_gsi::GenericMethod ("setStatus|status=", "@brief Method void QCameraFocusZone::setStatus(QCameraFocusZone::FocusZoneStatus status)\n", false, &_init_f_setStatus_3710, &_call_f_setStatus_3710);
  methods += new qt_gsi::GenericMethod (":status", "@brief Method QCameraFocusZone::FocusZoneStatus QCameraFocusZone::status()\n", true, &_init_f_status_c0, &_call_f_status_c0);
  return methods;
}

gsi::Class<QCameraFocusZone> decl_QCameraFocusZone ("QtMultimedia", "QCameraFocusZone",
  methods_QCameraFocusZone (),
  "@qt\n@brief Binding of QCameraFocusZone");


GSI_QTMULTIMEDIA_PUBLIC gsi::Class<QCameraFocusZone> &qtdecl_QCameraFocusZone () { return decl_QCameraFocusZone; }

}


//  Implementation of the enum wrapper class for QCameraFocusZone::FocusZoneStatus
namespace qt_gsi
{

static gsi::Enum<QCameraFocusZone::FocusZoneStatus> decl_QCameraFocusZone_FocusZoneStatus_Enum ("QtMultimedia", "QCameraFocusZone_FocusZoneStatus",
    gsi::enum_const ("Invalid", QCameraFocusZone::Invalid, "@brief Enum constant QCameraFocusZone::Invalid") +
    gsi::enum_const ("Unused", QCameraFocusZone::Unused, "@brief Enum constant QCameraFocusZone::Unused") +
    gsi::enum_const ("Selected", QCameraFocusZone::Selected, "@brief Enum constant QCameraFocusZone::Selected") +
    gsi::enum_const ("Focused", QCameraFocusZone::Focused, "@brief Enum constant QCameraFocusZone::Focused"),
  "@qt\n@brief This class represents the QCameraFocusZone::FocusZoneStatus enum");

static gsi::QFlagsClass<QCameraFocusZone::FocusZoneStatus > decl_QCameraFocusZone_FocusZoneStatus_Enums ("QtMultimedia", "QCameraFocusZone_QFlags_FocusZoneStatus",
  "@qt\n@brief This class represents the QFlags<QCameraFocusZone::FocusZoneStatus> flag set");

//  Inject the declarations into the parent
static gsi::ClassExt<QCameraFocusZone> inject_QCameraFocusZone_FocusZoneStatus_Enum_in_parent (decl_QCameraFocusZone_FocusZoneStatus_Enum.defs ());
static gsi::ClassExt<QCameraFocusZone> decl_QCameraFocusZone_FocusZoneStatus_Enum_as_child (decl_QCameraFocusZone_FocusZoneStatus_Enum, "FocusZoneStatus");
static gsi::ClassExt<QCameraFocusZone> decl_QCameraFocusZone_FocusZoneStatus_Enums_as_child (decl_QCameraFocusZone_FocusZoneStatus_Enums, "QFlags_FocusZoneStatus");

}

