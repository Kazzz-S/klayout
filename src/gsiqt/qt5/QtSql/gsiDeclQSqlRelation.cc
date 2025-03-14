
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
*  @file gsiDeclQSqlRelation.cc 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#include <QSqlRelation>
#include "gsiQt.h"
#include "gsiQtSqlCommon.h"
#include <memory>

// -----------------------------------------------------------------------
// class QSqlRelation

//  Constructor QSqlRelation::QSqlRelation()


static void _init_ctor_QSqlRelation_0 (qt_gsi::GenericStaticMethod *decl)
{
  decl->set_return_new<QSqlRelation> ();
}

static void _call_ctor_QSqlRelation_0 (const qt_gsi::GenericStaticMethod * /*decl*/, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<QSqlRelation *> (new QSqlRelation ());
}


//  Constructor QSqlRelation::QSqlRelation(const QString &aTableName, const QString &indexCol, const QString &displayCol)


static void _init_ctor_QSqlRelation_5859 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("aTableName");
  decl->add_arg<const QString & > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("indexCol");
  decl->add_arg<const QString & > (argspec_1);
  static gsi::ArgSpecBase argspec_2 ("displayCol");
  decl->add_arg<const QString & > (argspec_2);
  decl->set_return_new<QSqlRelation> ();
}

static void _call_ctor_QSqlRelation_5859 (const qt_gsi::GenericStaticMethod * /*decl*/, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  const QString &arg1 = gsi::arg_reader<const QString & >() (args, heap);
  const QString &arg2 = gsi::arg_reader<const QString & >() (args, heap);
  const QString &arg3 = gsi::arg_reader<const QString & >() (args, heap);
  ret.write<QSqlRelation *> (new QSqlRelation (arg1, arg2, arg3));
}


// QString QSqlRelation::displayColumn()


static void _init_f_displayColumn_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QString > ();
}

static void _call_f_displayColumn_c0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<QString > ((QString)((QSqlRelation *)cls)->displayColumn ());
}


// QString QSqlRelation::indexColumn()


static void _init_f_indexColumn_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QString > ();
}

static void _call_f_indexColumn_c0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<QString > ((QString)((QSqlRelation *)cls)->indexColumn ());
}


// bool QSqlRelation::isValid()


static void _init_f_isValid_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<bool > ();
}

static void _call_f_isValid_c0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<bool > ((bool)((QSqlRelation *)cls)->isValid ());
}


// void QSqlRelation::swap(QSqlRelation &other)


static void _init_f_swap_1833 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("other");
  decl->add_arg<QSqlRelation & > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_swap_1833 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  QSqlRelation &arg1 = gsi::arg_reader<QSqlRelation & >() (args, heap);
  __SUPPRESS_UNUSED_WARNING(ret);
  ((QSqlRelation *)cls)->swap (arg1);
}


// QString QSqlRelation::tableName()


static void _init_f_tableName_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QString > ();
}

static void _call_f_tableName_c0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<QString > ((QString)((QSqlRelation *)cls)->tableName ());
}



namespace gsi
{

static gsi::Methods methods_QSqlRelation () {
  gsi::Methods methods;
  methods += new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QSqlRelation::QSqlRelation()\nThis method creates an object of class QSqlRelation.", &_init_ctor_QSqlRelation_0, &_call_ctor_QSqlRelation_0);
  methods += new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QSqlRelation::QSqlRelation(const QString &aTableName, const QString &indexCol, const QString &displayCol)\nThis method creates an object of class QSqlRelation.", &_init_ctor_QSqlRelation_5859, &_call_ctor_QSqlRelation_5859);
  methods += new qt_gsi::GenericMethod ("displayColumn", "@brief Method QString QSqlRelation::displayColumn()\n", true, &_init_f_displayColumn_c0, &_call_f_displayColumn_c0);
  methods += new qt_gsi::GenericMethod ("indexColumn", "@brief Method QString QSqlRelation::indexColumn()\n", true, &_init_f_indexColumn_c0, &_call_f_indexColumn_c0);
  methods += new qt_gsi::GenericMethod ("isValid?", "@brief Method bool QSqlRelation::isValid()\n", true, &_init_f_isValid_c0, &_call_f_isValid_c0);
  methods += new qt_gsi::GenericMethod ("swap", "@brief Method void QSqlRelation::swap(QSqlRelation &other)\n", false, &_init_f_swap_1833, &_call_f_swap_1833);
  methods += new qt_gsi::GenericMethod ("tableName", "@brief Method QString QSqlRelation::tableName()\n", true, &_init_f_tableName_c0, &_call_f_tableName_c0);
  return methods;
}

gsi::Class<QSqlRelation> decl_QSqlRelation ("QtSql", "QSqlRelation",
  methods_QSqlRelation (),
  "@qt\n@brief Binding of QSqlRelation");


GSI_QTSQL_PUBLIC gsi::Class<QSqlRelation> &qtdecl_QSqlRelation () { return decl_QSqlRelation; }

}

