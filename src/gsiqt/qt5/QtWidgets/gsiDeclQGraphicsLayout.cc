
/*

  KLayout Layout Viewer
  Copyright (C) 2006-2019 Matthias Koefferlein

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
*  @file gsiDeclQGraphicsLayout.cc 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#include <QGraphicsLayout>
#include <QEvent>
#include <QGraphicsItem>
#include <QGraphicsLayoutItem>
#include <QRectF>
#include <QSizeF>
#include <QSizePolicy>
#include "gsiQt.h"
#include "gsiQtWidgetsCommon.h"
#include "gsiDeclQtWidgetsTypeTraits.h"
#include <memory>

// -----------------------------------------------------------------------
// class QGraphicsLayout

// void QGraphicsLayout::activate()


static void _init_f_activate_0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<void > ();
}

static void _call_f_activate_0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  __SUPPRESS_UNUSED_WARNING(ret);
  ((QGraphicsLayout *)cls)->activate ();
}


// int QGraphicsLayout::count()


static void _init_f_count_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<int > ();
}

static void _call_f_count_c0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<int > ((int)((QGraphicsLayout *)cls)->count ());
}


// void QGraphicsLayout::getContentsMargins(double *left, double *top, double *right, double *bottom)


static void _init_f_getContentsMargins_c4704 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("left");
  decl->add_arg<double * > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("top");
  decl->add_arg<double * > (argspec_1);
  static gsi::ArgSpecBase argspec_2 ("right");
  decl->add_arg<double * > (argspec_2);
  static gsi::ArgSpecBase argspec_3 ("bottom");
  decl->add_arg<double * > (argspec_3);
  decl->set_return<void > ();
}

static void _call_f_getContentsMargins_c4704 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  double *arg1 = gsi::arg_reader<double * >() (args, heap);
  double *arg2 = gsi::arg_reader<double * >() (args, heap);
  double *arg3 = gsi::arg_reader<double * >() (args, heap);
  double *arg4 = gsi::arg_reader<double * >() (args, heap);
  __SUPPRESS_UNUSED_WARNING(ret);
  ((QGraphicsLayout *)cls)->getContentsMargins (arg1, arg2, arg3, arg4);
}


// void QGraphicsLayout::invalidate()


static void _init_f_invalidate_0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<void > ();
}

static void _call_f_invalidate_0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  __SUPPRESS_UNUSED_WARNING(ret);
  ((QGraphicsLayout *)cls)->invalidate ();
}


// bool QGraphicsLayout::isActivated()


static void _init_f_isActivated_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<bool > ();
}

static void _call_f_isActivated_c0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<bool > ((bool)((QGraphicsLayout *)cls)->isActivated ());
}


// QGraphicsLayoutItem *QGraphicsLayout::itemAt(int i)


static void _init_f_itemAt_c767 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("i");
  decl->add_arg<int > (argspec_0);
  decl->set_return<QGraphicsLayoutItem * > ();
}

static void _call_f_itemAt_c767 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  int arg1 = gsi::arg_reader<int >() (args, heap);
  ret.write<QGraphicsLayoutItem * > ((QGraphicsLayoutItem *)((QGraphicsLayout *)cls)->itemAt (arg1));
}


// void QGraphicsLayout::removeAt(int index)


static void _init_f_removeAt_767 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("index");
  decl->add_arg<int > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_removeAt_767 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  int arg1 = gsi::arg_reader<int >() (args, heap);
  __SUPPRESS_UNUSED_WARNING(ret);
  ((QGraphicsLayout *)cls)->removeAt (arg1);
}


// void QGraphicsLayout::setContentsMargins(double left, double top, double right, double bottom)


static void _init_f_setContentsMargins_3960 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("left");
  decl->add_arg<double > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("top");
  decl->add_arg<double > (argspec_1);
  static gsi::ArgSpecBase argspec_2 ("right");
  decl->add_arg<double > (argspec_2);
  static gsi::ArgSpecBase argspec_3 ("bottom");
  decl->add_arg<double > (argspec_3);
  decl->set_return<void > ();
}

static void _call_f_setContentsMargins_3960 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  double arg1 = gsi::arg_reader<double >() (args, heap);
  double arg2 = gsi::arg_reader<double >() (args, heap);
  double arg3 = gsi::arg_reader<double >() (args, heap);
  double arg4 = gsi::arg_reader<double >() (args, heap);
  __SUPPRESS_UNUSED_WARNING(ret);
  ((QGraphicsLayout *)cls)->setContentsMargins (arg1, arg2, arg3, arg4);
}


// void QGraphicsLayout::updateGeometry()


static void _init_f_updateGeometry_0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<void > ();
}

static void _call_f_updateGeometry_0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  __SUPPRESS_UNUSED_WARNING(ret);
  ((QGraphicsLayout *)cls)->updateGeometry ();
}


// void QGraphicsLayout::widgetEvent(QEvent *e)


static void _init_f_widgetEvent_1217 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("e");
  decl->add_arg<QEvent * > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_widgetEvent_1217 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  QEvent *arg1 = gsi::arg_reader<QEvent * >() (args, heap);
  __SUPPRESS_UNUSED_WARNING(ret);
  ((QGraphicsLayout *)cls)->widgetEvent (arg1);
}


// static bool QGraphicsLayout::instantInvalidatePropagation()


static void _init_f_instantInvalidatePropagation_0 (qt_gsi::GenericStaticMethod *decl)
{
  decl->set_return<bool > ();
}

static void _call_f_instantInvalidatePropagation_0 (const qt_gsi::GenericStaticMethod * /*decl*/, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<bool > ((bool)QGraphicsLayout::instantInvalidatePropagation ());
}


// static void QGraphicsLayout::setInstantInvalidatePropagation(bool enable)


static void _init_f_setInstantInvalidatePropagation_864 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("enable");
  decl->add_arg<bool > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setInstantInvalidatePropagation_864 (const qt_gsi::GenericStaticMethod * /*decl*/, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  bool arg1 = gsi::arg_reader<bool >() (args, heap);
  __SUPPRESS_UNUSED_WARNING(ret);
  QGraphicsLayout::setInstantInvalidatePropagation (arg1);
}


namespace gsi
{

static gsi::Methods methods_QGraphicsLayout () {
  gsi::Methods methods;
  methods += new qt_gsi::GenericMethod ("activate", "@brief Method void QGraphicsLayout::activate()\n", false, &_init_f_activate_0, &_call_f_activate_0);
  methods += new qt_gsi::GenericMethod ("count", "@brief Method int QGraphicsLayout::count()\n", true, &_init_f_count_c0, &_call_f_count_c0);
  methods += new qt_gsi::GenericMethod ("getContentsMargins", "@brief Method void QGraphicsLayout::getContentsMargins(double *left, double *top, double *right, double *bottom)\nThis is a reimplementation of QGraphicsLayoutItem::getContentsMargins", true, &_init_f_getContentsMargins_c4704, &_call_f_getContentsMargins_c4704);
  methods += new qt_gsi::GenericMethod ("invalidate", "@brief Method void QGraphicsLayout::invalidate()\n", false, &_init_f_invalidate_0, &_call_f_invalidate_0);
  methods += new qt_gsi::GenericMethod ("isActivated?", "@brief Method bool QGraphicsLayout::isActivated()\n", true, &_init_f_isActivated_c0, &_call_f_isActivated_c0);
  methods += new qt_gsi::GenericMethod ("itemAt", "@brief Method QGraphicsLayoutItem *QGraphicsLayout::itemAt(int i)\n", true, &_init_f_itemAt_c767, &_call_f_itemAt_c767);
  methods += new qt_gsi::GenericMethod ("removeAt", "@brief Method void QGraphicsLayout::removeAt(int index)\n", false, &_init_f_removeAt_767, &_call_f_removeAt_767);
  methods += new qt_gsi::GenericMethod ("setContentsMargins", "@brief Method void QGraphicsLayout::setContentsMargins(double left, double top, double right, double bottom)\n", false, &_init_f_setContentsMargins_3960, &_call_f_setContentsMargins_3960);
  methods += new qt_gsi::GenericMethod ("updateGeometry", "@brief Method void QGraphicsLayout::updateGeometry()\nThis is a reimplementation of QGraphicsLayoutItem::updateGeometry", false, &_init_f_updateGeometry_0, &_call_f_updateGeometry_0);
  methods += new qt_gsi::GenericMethod ("widgetEvent", "@brief Method void QGraphicsLayout::widgetEvent(QEvent *e)\n", false, &_init_f_widgetEvent_1217, &_call_f_widgetEvent_1217);
  methods += new qt_gsi::GenericStaticMethod (":instantInvalidatePropagation", "@brief Static method bool QGraphicsLayout::instantInvalidatePropagation()\nThis method is static and can be called without an instance.", &_init_f_instantInvalidatePropagation_0, &_call_f_instantInvalidatePropagation_0);
  methods += new qt_gsi::GenericStaticMethod ("setInstantInvalidatePropagation|instantInvalidatePropagation=", "@brief Static method void QGraphicsLayout::setInstantInvalidatePropagation(bool enable)\nThis method is static and can be called without an instance.", &_init_f_setInstantInvalidatePropagation_864, &_call_f_setInstantInvalidatePropagation_864);
  return methods;
}

gsi::Class<QGraphicsLayoutItem> &qtdecl_QGraphicsLayoutItem ();

gsi::Class<QGraphicsLayout> decl_QGraphicsLayout (qtdecl_QGraphicsLayoutItem (), "QtWidgets", "QGraphicsLayout_Native",
  methods_QGraphicsLayout (),
  "@hide\n@alias QGraphicsLayout");

GSI_QTWIDGETS_PUBLIC gsi::Class<QGraphicsLayout> &qtdecl_QGraphicsLayout () { return decl_QGraphicsLayout; }

}


class QGraphicsLayout_Adaptor : public QGraphicsLayout, public qt_gsi::QtObjectBase
{
public:

  virtual ~QGraphicsLayout_Adaptor();

  //  [adaptor ctor] QGraphicsLayout::QGraphicsLayout(QGraphicsLayoutItem *parent)
  QGraphicsLayout_Adaptor() : QGraphicsLayout()
  {
    qt_gsi::QtObjectBase::init (this);
  }

  //  [adaptor ctor] QGraphicsLayout::QGraphicsLayout(QGraphicsLayoutItem *parent)
  QGraphicsLayout_Adaptor(QGraphicsLayoutItem *parent) : QGraphicsLayout(parent)
  {
    qt_gsi::QtObjectBase::init (this);
  }

  //  [expose] void QGraphicsLayout::addChildLayoutItem(QGraphicsLayoutItem *layoutItem)
  void fp_QGraphicsLayout_addChildLayoutItem_2557 (QGraphicsLayoutItem *layoutItem) {
    QGraphicsLayout::addChildLayoutItem(layoutItem);
  }

  //  [expose] void QGraphicsLayout::setGraphicsItem(QGraphicsItem *item)
  void fp_QGraphicsLayout_setGraphicsItem_1919 (QGraphicsItem *item) {
    QGraphicsLayout::setGraphicsItem(item);
  }

  //  [expose] void QGraphicsLayout::setOwnedByLayout(bool ownedByLayout)
  void fp_QGraphicsLayout_setOwnedByLayout_864 (bool ownedByLayout) {
    QGraphicsLayout::setOwnedByLayout(ownedByLayout);
  }

  //  [adaptor impl] int QGraphicsLayout::count()
  int cbs_count_c0_0() const
  {
    throw qt_gsi::AbstractMethodCalledException("count");
  }

  virtual int count() const
  {
    if (cb_count_c0_0.can_issue()) {
      return cb_count_c0_0.issue<QGraphicsLayout_Adaptor, int>(&QGraphicsLayout_Adaptor::cbs_count_c0_0);
    } else {
      throw qt_gsi::AbstractMethodCalledException("count");
    }
  }

  //  [adaptor impl] void QGraphicsLayout::getContentsMargins(double *left, double *top, double *right, double *bottom)
  void cbs_getContentsMargins_c4704_0(double *left, double *top, double *right, double *bottom) const
  {
    QGraphicsLayout::getContentsMargins(left, top, right, bottom);
  }

  virtual void getContentsMargins(double *left, double *top, double *right, double *bottom) const
  {
    if (cb_getContentsMargins_c4704_0.can_issue()) {
      cb_getContentsMargins_c4704_0.issue<QGraphicsLayout_Adaptor, double *, double *, double *, double *>(&QGraphicsLayout_Adaptor::cbs_getContentsMargins_c4704_0, left, top, right, bottom);
    } else {
      QGraphicsLayout::getContentsMargins(left, top, right, bottom);
    }
  }

  //  [adaptor impl] void QGraphicsLayout::invalidate()
  void cbs_invalidate_0_0()
  {
    QGraphicsLayout::invalidate();
  }

  virtual void invalidate()
  {
    if (cb_invalidate_0_0.can_issue()) {
      cb_invalidate_0_0.issue<QGraphicsLayout_Adaptor>(&QGraphicsLayout_Adaptor::cbs_invalidate_0_0);
    } else {
      QGraphicsLayout::invalidate();
    }
  }

  //  [adaptor impl] QGraphicsLayoutItem *QGraphicsLayout::itemAt(int i)
  QGraphicsLayoutItem * cbs_itemAt_c767_0(int i) const
  {
    __SUPPRESS_UNUSED_WARNING (i);
    throw qt_gsi::AbstractMethodCalledException("itemAt");
  }

  virtual QGraphicsLayoutItem * itemAt(int i) const
  {
    if (cb_itemAt_c767_0.can_issue()) {
      return cb_itemAt_c767_0.issue<QGraphicsLayout_Adaptor, QGraphicsLayoutItem *, int>(&QGraphicsLayout_Adaptor::cbs_itemAt_c767_0, i);
    } else {
      throw qt_gsi::AbstractMethodCalledException("itemAt");
    }
  }

  //  [adaptor impl] void QGraphicsLayout::removeAt(int index)
  void cbs_removeAt_767_0(int index)
  {
    __SUPPRESS_UNUSED_WARNING (index);
    throw qt_gsi::AbstractMethodCalledException("removeAt");
  }

  virtual void removeAt(int index)
  {
    if (cb_removeAt_767_0.can_issue()) {
      cb_removeAt_767_0.issue<QGraphicsLayout_Adaptor, int>(&QGraphicsLayout_Adaptor::cbs_removeAt_767_0, index);
    } else {
      throw qt_gsi::AbstractMethodCalledException("removeAt");
    }
  }

  //  [adaptor impl] void QGraphicsLayout::setGeometry(const QRectF &rect)
  void cbs_setGeometry_1862_0(const QRectF &rect)
  {
    QGraphicsLayout::setGeometry(rect);
  }

  virtual void setGeometry(const QRectF &rect)
  {
    if (cb_setGeometry_1862_0.can_issue()) {
      cb_setGeometry_1862_0.issue<QGraphicsLayout_Adaptor, const QRectF &>(&QGraphicsLayout_Adaptor::cbs_setGeometry_1862_0, rect);
    } else {
      QGraphicsLayout::setGeometry(rect);
    }
  }

  //  [adaptor impl] void QGraphicsLayout::updateGeometry()
  void cbs_updateGeometry_0_0()
  {
    QGraphicsLayout::updateGeometry();
  }

  virtual void updateGeometry()
  {
    if (cb_updateGeometry_0_0.can_issue()) {
      cb_updateGeometry_0_0.issue<QGraphicsLayout_Adaptor>(&QGraphicsLayout_Adaptor::cbs_updateGeometry_0_0);
    } else {
      QGraphicsLayout::updateGeometry();
    }
  }

  //  [adaptor impl] void QGraphicsLayout::widgetEvent(QEvent *e)
  void cbs_widgetEvent_1217_0(QEvent *e)
  {
    QGraphicsLayout::widgetEvent(e);
  }

  virtual void widgetEvent(QEvent *e)
  {
    if (cb_widgetEvent_1217_0.can_issue()) {
      cb_widgetEvent_1217_0.issue<QGraphicsLayout_Adaptor, QEvent *>(&QGraphicsLayout_Adaptor::cbs_widgetEvent_1217_0, e);
    } else {
      QGraphicsLayout::widgetEvent(e);
    }
  }

  //  [adaptor impl] QSizeF QGraphicsLayout::sizeHint(Qt::SizeHint which, const QSizeF &constraint)
  QSizeF cbs_sizeHint_c3330_1(const qt_gsi::Converter<Qt::SizeHint>::target_type & which, const QSizeF &constraint) const
  {
    __SUPPRESS_UNUSED_WARNING (which);
    __SUPPRESS_UNUSED_WARNING (constraint);
    throw qt_gsi::AbstractMethodCalledException("sizeHint");
  }

  virtual QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
  {
    if (cb_sizeHint_c3330_1.can_issue()) {
      return cb_sizeHint_c3330_1.issue<QGraphicsLayout_Adaptor, QSizeF, const qt_gsi::Converter<Qt::SizeHint>::target_type &, const QSizeF &>(&QGraphicsLayout_Adaptor::cbs_sizeHint_c3330_1, qt_gsi::CppToQtAdaptor<Qt::SizeHint>(which), constraint);
    } else {
      throw qt_gsi::AbstractMethodCalledException("sizeHint");
    }
  }

  gsi::Callback cb_count_c0_0;
  gsi::Callback cb_getContentsMargins_c4704_0;
  gsi::Callback cb_invalidate_0_0;
  gsi::Callback cb_itemAt_c767_0;
  gsi::Callback cb_removeAt_767_0;
  gsi::Callback cb_setGeometry_1862_0;
  gsi::Callback cb_updateGeometry_0_0;
  gsi::Callback cb_widgetEvent_1217_0;
  gsi::Callback cb_sizeHint_c3330_1;
};

QGraphicsLayout_Adaptor::~QGraphicsLayout_Adaptor() { }

//  Constructor QGraphicsLayout::QGraphicsLayout(QGraphicsLayoutItem *parent) (adaptor class)

static void _init_ctor_QGraphicsLayout_Adaptor_2557 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("parent", true, "0");
  decl->add_arg<QGraphicsLayoutItem * > (argspec_0);
  decl->set_return_new<QGraphicsLayout_Adaptor> ();
}

static void _call_ctor_QGraphicsLayout_Adaptor_2557 (const qt_gsi::GenericStaticMethod * /*decl*/, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  QGraphicsLayoutItem *arg1 = args ? gsi::arg_reader<QGraphicsLayoutItem * >() (args, heap) : gsi::arg_maker<QGraphicsLayoutItem * >() (0, heap);
  ret.write<QGraphicsLayout_Adaptor *> (new QGraphicsLayout_Adaptor (arg1));
}


// exposed void QGraphicsLayout::addChildLayoutItem(QGraphicsLayoutItem *layoutItem)

static void _init_fp_addChildLayoutItem_2557 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("layoutItem");
  decl->add_arg<QGraphicsLayoutItem * > (argspec_0);
  decl->set_return<void > ();
}

static void _call_fp_addChildLayoutItem_2557 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  QGraphicsLayoutItem *arg1 = gsi::arg_reader<QGraphicsLayoutItem * >() (args, heap);
  __SUPPRESS_UNUSED_WARNING(ret);
  ((QGraphicsLayout_Adaptor *)cls)->fp_QGraphicsLayout_addChildLayoutItem_2557 (arg1);
}


// int QGraphicsLayout::count()

static void _init_cbs_count_c0_0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<int > ();
}

static void _call_cbs_count_c0_0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<int > ((int)((QGraphicsLayout_Adaptor *)cls)->cbs_count_c0_0 ());
}

static void _set_callback_cbs_count_c0_0 (void *cls, const gsi::Callback &cb)
{
  ((QGraphicsLayout_Adaptor *)cls)->cb_count_c0_0 = cb;
}


// void QGraphicsLayout::getContentsMargins(double *left, double *top, double *right, double *bottom)

static void _init_cbs_getContentsMargins_c4704_0 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("left");
  decl->add_arg<double * > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("top");
  decl->add_arg<double * > (argspec_1);
  static gsi::ArgSpecBase argspec_2 ("right");
  decl->add_arg<double * > (argspec_2);
  static gsi::ArgSpecBase argspec_3 ("bottom");
  decl->add_arg<double * > (argspec_3);
  decl->set_return<void > ();
}

static void _call_cbs_getContentsMargins_c4704_0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  double *arg1 = args.read<double * > (heap);
  double *arg2 = args.read<double * > (heap);
  double *arg3 = args.read<double * > (heap);
  double *arg4 = args.read<double * > (heap);
  __SUPPRESS_UNUSED_WARNING(ret);
  ((QGraphicsLayout_Adaptor *)cls)->cbs_getContentsMargins_c4704_0 (arg1, arg2, arg3, arg4);
}

static void _set_callback_cbs_getContentsMargins_c4704_0 (void *cls, const gsi::Callback &cb)
{
  ((QGraphicsLayout_Adaptor *)cls)->cb_getContentsMargins_c4704_0 = cb;
}


// void QGraphicsLayout::invalidate()

static void _init_cbs_invalidate_0_0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<void > ();
}

static void _call_cbs_invalidate_0_0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  __SUPPRESS_UNUSED_WARNING(ret);
  ((QGraphicsLayout_Adaptor *)cls)->cbs_invalidate_0_0 ();
}

static void _set_callback_cbs_invalidate_0_0 (void *cls, const gsi::Callback &cb)
{
  ((QGraphicsLayout_Adaptor *)cls)->cb_invalidate_0_0 = cb;
}


// QGraphicsLayoutItem *QGraphicsLayout::itemAt(int i)

static void _init_cbs_itemAt_c767_0 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("i");
  decl->add_arg<int > (argspec_0);
  decl->set_return<QGraphicsLayoutItem * > ();
}

static void _call_cbs_itemAt_c767_0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  int arg1 = args.read<int > (heap);
  ret.write<QGraphicsLayoutItem * > ((QGraphicsLayoutItem *)((QGraphicsLayout_Adaptor *)cls)->cbs_itemAt_c767_0 (arg1));
}

static void _set_callback_cbs_itemAt_c767_0 (void *cls, const gsi::Callback &cb)
{
  ((QGraphicsLayout_Adaptor *)cls)->cb_itemAt_c767_0 = cb;
}


// void QGraphicsLayout::removeAt(int index)

static void _init_cbs_removeAt_767_0 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("index");
  decl->add_arg<int > (argspec_0);
  decl->set_return<void > ();
}

static void _call_cbs_removeAt_767_0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  int arg1 = args.read<int > (heap);
  __SUPPRESS_UNUSED_WARNING(ret);
  ((QGraphicsLayout_Adaptor *)cls)->cbs_removeAt_767_0 (arg1);
}

static void _set_callback_cbs_removeAt_767_0 (void *cls, const gsi::Callback &cb)
{
  ((QGraphicsLayout_Adaptor *)cls)->cb_removeAt_767_0 = cb;
}


// void QGraphicsLayout::setGeometry(const QRectF &rect)

static void _init_cbs_setGeometry_1862_0 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("rect");
  decl->add_arg<const QRectF & > (argspec_0);
  decl->set_return<void > ();
}

static void _call_cbs_setGeometry_1862_0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  const QRectF &arg1 = args.read<const QRectF & > (heap);
  __SUPPRESS_UNUSED_WARNING(ret);
  ((QGraphicsLayout_Adaptor *)cls)->cbs_setGeometry_1862_0 (arg1);
}

static void _set_callback_cbs_setGeometry_1862_0 (void *cls, const gsi::Callback &cb)
{
  ((QGraphicsLayout_Adaptor *)cls)->cb_setGeometry_1862_0 = cb;
}


// exposed void QGraphicsLayout::setGraphicsItem(QGraphicsItem *item)

static void _init_fp_setGraphicsItem_1919 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("item");
  decl->add_arg<QGraphicsItem * > (argspec_0);
  decl->set_return<void > ();
}

static void _call_fp_setGraphicsItem_1919 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  QGraphicsItem *arg1 = gsi::arg_reader<QGraphicsItem * >() (args, heap);
  __SUPPRESS_UNUSED_WARNING(ret);
  ((QGraphicsLayout_Adaptor *)cls)->fp_QGraphicsLayout_setGraphicsItem_1919 (arg1);
}


// exposed void QGraphicsLayout::setOwnedByLayout(bool ownedByLayout)

static void _init_fp_setOwnedByLayout_864 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("ownedByLayout");
  decl->add_arg<bool > (argspec_0);
  decl->set_return<void > ();
}

static void _call_fp_setOwnedByLayout_864 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  bool arg1 = gsi::arg_reader<bool >() (args, heap);
  __SUPPRESS_UNUSED_WARNING(ret);
  ((QGraphicsLayout_Adaptor *)cls)->fp_QGraphicsLayout_setOwnedByLayout_864 (arg1);
}


// QSizeF QGraphicsLayout::sizeHint(Qt::SizeHint which, const QSizeF &constraint)

static void _init_cbs_sizeHint_c3330_1 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("which");
  decl->add_arg<const qt_gsi::Converter<Qt::SizeHint>::target_type & > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("constraint");
  decl->add_arg<const QSizeF & > (argspec_1);
  decl->set_return<QSizeF > ();
}

static void _call_cbs_sizeHint_c3330_1 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  const qt_gsi::Converter<Qt::SizeHint>::target_type & arg1 = args.read<const qt_gsi::Converter<Qt::SizeHint>::target_type & > (heap);
  const QSizeF &arg2 = args.read<const QSizeF & > (heap);
  ret.write<QSizeF > ((QSizeF)((QGraphicsLayout_Adaptor *)cls)->cbs_sizeHint_c3330_1 (arg1, arg2));
}

static void _set_callback_cbs_sizeHint_c3330_1 (void *cls, const gsi::Callback &cb)
{
  ((QGraphicsLayout_Adaptor *)cls)->cb_sizeHint_c3330_1 = cb;
}


// void QGraphicsLayout::updateGeometry()

static void _init_cbs_updateGeometry_0_0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<void > ();
}

static void _call_cbs_updateGeometry_0_0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  __SUPPRESS_UNUSED_WARNING(ret);
  ((QGraphicsLayout_Adaptor *)cls)->cbs_updateGeometry_0_0 ();
}

static void _set_callback_cbs_updateGeometry_0_0 (void *cls, const gsi::Callback &cb)
{
  ((QGraphicsLayout_Adaptor *)cls)->cb_updateGeometry_0_0 = cb;
}


// void QGraphicsLayout::widgetEvent(QEvent *e)

static void _init_cbs_widgetEvent_1217_0 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("e");
  decl->add_arg<QEvent * > (argspec_0);
  decl->set_return<void > ();
}

static void _call_cbs_widgetEvent_1217_0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  QEvent *arg1 = args.read<QEvent * > (heap);
  __SUPPRESS_UNUSED_WARNING(ret);
  ((QGraphicsLayout_Adaptor *)cls)->cbs_widgetEvent_1217_0 (arg1);
}

static void _set_callback_cbs_widgetEvent_1217_0 (void *cls, const gsi::Callback &cb)
{
  ((QGraphicsLayout_Adaptor *)cls)->cb_widgetEvent_1217_0 = cb;
}


namespace gsi
{

gsi::Class<QGraphicsLayout> &qtdecl_QGraphicsLayout ();

static gsi::Methods methods_QGraphicsLayout_Adaptor () {
  gsi::Methods methods;
  methods += new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QGraphicsLayout::QGraphicsLayout(QGraphicsLayoutItem *parent)\nThis method creates an object of class QGraphicsLayout.", &_init_ctor_QGraphicsLayout_Adaptor_2557, &_call_ctor_QGraphicsLayout_Adaptor_2557);
  methods += new qt_gsi::GenericMethod ("*addChildLayoutItem", "@brief Method void QGraphicsLayout::addChildLayoutItem(QGraphicsLayoutItem *layoutItem)\nThis method is protected and can only be called from inside a derived class.", false, &_init_fp_addChildLayoutItem_2557, &_call_fp_addChildLayoutItem_2557);
  methods += new qt_gsi::GenericMethod ("count", "@hide", true, &_init_cbs_count_c0_0, &_call_cbs_count_c0_0);
  methods += new qt_gsi::GenericMethod ("count", "@brief Virtual method int QGraphicsLayout::count()\nThis method can be reimplemented in a derived class.", true, &_init_cbs_count_c0_0, &_call_cbs_count_c0_0, &_set_callback_cbs_count_c0_0);
  methods += new qt_gsi::GenericMethod ("getContentsMargins", "@hide", true, &_init_cbs_getContentsMargins_c4704_0, &_call_cbs_getContentsMargins_c4704_0);
  methods += new qt_gsi::GenericMethod ("getContentsMargins", "@brief Virtual method void QGraphicsLayout::getContentsMargins(double *left, double *top, double *right, double *bottom)\nThis method can be reimplemented in a derived class.", true, &_init_cbs_getContentsMargins_c4704_0, &_call_cbs_getContentsMargins_c4704_0, &_set_callback_cbs_getContentsMargins_c4704_0);
  methods += new qt_gsi::GenericMethod ("invalidate", "@hide", false, &_init_cbs_invalidate_0_0, &_call_cbs_invalidate_0_0);
  methods += new qt_gsi::GenericMethod ("invalidate", "@brief Virtual method void QGraphicsLayout::invalidate()\nThis method can be reimplemented in a derived class.", false, &_init_cbs_invalidate_0_0, &_call_cbs_invalidate_0_0, &_set_callback_cbs_invalidate_0_0);
  methods += new qt_gsi::GenericMethod ("itemAt", "@hide", true, &_init_cbs_itemAt_c767_0, &_call_cbs_itemAt_c767_0);
  methods += new qt_gsi::GenericMethod ("itemAt", "@brief Virtual method QGraphicsLayoutItem *QGraphicsLayout::itemAt(int i)\nThis method can be reimplemented in a derived class.", true, &_init_cbs_itemAt_c767_0, &_call_cbs_itemAt_c767_0, &_set_callback_cbs_itemAt_c767_0);
  methods += new qt_gsi::GenericMethod ("removeAt", "@hide", false, &_init_cbs_removeAt_767_0, &_call_cbs_removeAt_767_0);
  methods += new qt_gsi::GenericMethod ("removeAt", "@brief Virtual method void QGraphicsLayout::removeAt(int index)\nThis method can be reimplemented in a derived class.", false, &_init_cbs_removeAt_767_0, &_call_cbs_removeAt_767_0, &_set_callback_cbs_removeAt_767_0);
  methods += new qt_gsi::GenericMethod ("setGeometry", "@hide", false, &_init_cbs_setGeometry_1862_0, &_call_cbs_setGeometry_1862_0);
  methods += new qt_gsi::GenericMethod ("setGeometry", "@brief Virtual method void QGraphicsLayout::setGeometry(const QRectF &rect)\nThis method can be reimplemented in a derived class.", false, &_init_cbs_setGeometry_1862_0, &_call_cbs_setGeometry_1862_0, &_set_callback_cbs_setGeometry_1862_0);
  methods += new qt_gsi::GenericMethod ("*setGraphicsItem", "@brief Method void QGraphicsLayout::setGraphicsItem(QGraphicsItem *item)\nThis method is protected and can only be called from inside a derived class.", false, &_init_fp_setGraphicsItem_1919, &_call_fp_setGraphicsItem_1919);
  methods += new qt_gsi::GenericMethod ("*setOwnedByLayout", "@brief Method void QGraphicsLayout::setOwnedByLayout(bool ownedByLayout)\nThis method is protected and can only be called from inside a derived class.", false, &_init_fp_setOwnedByLayout_864, &_call_fp_setOwnedByLayout_864);
  methods += new qt_gsi::GenericMethod ("*sizeHint", "@hide", true, &_init_cbs_sizeHint_c3330_1, &_call_cbs_sizeHint_c3330_1);
  methods += new qt_gsi::GenericMethod ("*sizeHint", "@brief Virtual method QSizeF QGraphicsLayout::sizeHint(Qt::SizeHint which, const QSizeF &constraint)\nThis method can be reimplemented in a derived class.", true, &_init_cbs_sizeHint_c3330_1, &_call_cbs_sizeHint_c3330_1, &_set_callback_cbs_sizeHint_c3330_1);
  methods += new qt_gsi::GenericMethod ("updateGeometry", "@hide", false, &_init_cbs_updateGeometry_0_0, &_call_cbs_updateGeometry_0_0);
  methods += new qt_gsi::GenericMethod ("updateGeometry", "@brief Virtual method void QGraphicsLayout::updateGeometry()\nThis method can be reimplemented in a derived class.", false, &_init_cbs_updateGeometry_0_0, &_call_cbs_updateGeometry_0_0, &_set_callback_cbs_updateGeometry_0_0);
  methods += new qt_gsi::GenericMethod ("widgetEvent", "@hide", false, &_init_cbs_widgetEvent_1217_0, &_call_cbs_widgetEvent_1217_0);
  methods += new qt_gsi::GenericMethod ("widgetEvent", "@brief Virtual method void QGraphicsLayout::widgetEvent(QEvent *e)\nThis method can be reimplemented in a derived class.", false, &_init_cbs_widgetEvent_1217_0, &_call_cbs_widgetEvent_1217_0, &_set_callback_cbs_widgetEvent_1217_0);
  return methods;
}

gsi::Class<QGraphicsLayout_Adaptor> decl_QGraphicsLayout_Adaptor (qtdecl_QGraphicsLayout (), "QtWidgets", "QGraphicsLayout",
  methods_QGraphicsLayout_Adaptor (),
  "@qt\n@brief Binding of QGraphicsLayout");

}
