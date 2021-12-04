
/*

  KLayout Layout Viewer
  Copyright (C) 2006-2021 Matthias Koefferlein

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
*  @file gsiDeclQAccessibleHyperlinkInterface.cc 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#include <QAccessibleHyperlinkInterface>
#include "gsiQt.h"
#include "gsiQtGuiCommon.h"
#include <memory>

// -----------------------------------------------------------------------
// class QAccessibleHyperlinkInterface

// QString QAccessibleHyperlinkInterface::anchor()


static void _init_f_anchor_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QString > ();
}

static void _call_f_anchor_c0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<QString > ((QString)((QAccessibleHyperlinkInterface *)cls)->anchor ());
}


// QString QAccessibleHyperlinkInterface::anchorTarget()


static void _init_f_anchorTarget_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QString > ();
}

static void _call_f_anchorTarget_c0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<QString > ((QString)((QAccessibleHyperlinkInterface *)cls)->anchorTarget ());
}


// int QAccessibleHyperlinkInterface::endIndex()


static void _init_f_endIndex_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<int > ();
}

static void _call_f_endIndex_c0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<int > ((int)((QAccessibleHyperlinkInterface *)cls)->endIndex ());
}


// bool QAccessibleHyperlinkInterface::isValid()


static void _init_f_isValid_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<bool > ();
}

static void _call_f_isValid_c0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<bool > ((bool)((QAccessibleHyperlinkInterface *)cls)->isValid ());
}


// int QAccessibleHyperlinkInterface::startIndex()


static void _init_f_startIndex_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<int > ();
}

static void _call_f_startIndex_c0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<int > ((int)((QAccessibleHyperlinkInterface *)cls)->startIndex ());
}


namespace gsi
{

static gsi::Methods methods_QAccessibleHyperlinkInterface () {
  gsi::Methods methods;
  methods += new qt_gsi::GenericMethod ("anchor", "@brief Method QString QAccessibleHyperlinkInterface::anchor()\n", true, &_init_f_anchor_c0, &_call_f_anchor_c0);
  methods += new qt_gsi::GenericMethod ("anchorTarget", "@brief Method QString QAccessibleHyperlinkInterface::anchorTarget()\n", true, &_init_f_anchorTarget_c0, &_call_f_anchorTarget_c0);
  methods += new qt_gsi::GenericMethod ("endIndex", "@brief Method int QAccessibleHyperlinkInterface::endIndex()\n", true, &_init_f_endIndex_c0, &_call_f_endIndex_c0);
  methods += new qt_gsi::GenericMethod ("isValid?", "@brief Method bool QAccessibleHyperlinkInterface::isValid()\n", true, &_init_f_isValid_c0, &_call_f_isValid_c0);
  methods += new qt_gsi::GenericMethod ("startIndex", "@brief Method int QAccessibleHyperlinkInterface::startIndex()\n", true, &_init_f_startIndex_c0, &_call_f_startIndex_c0);
  return methods;
}

gsi::Class<QAccessibleHyperlinkInterface> decl_QAccessibleHyperlinkInterface ("QtGui", "QAccessibleHyperlinkInterface_Native",
  methods_QAccessibleHyperlinkInterface (),
  "@hide\n@alias QAccessibleHyperlinkInterface");

GSI_QTGUI_PUBLIC gsi::Class<QAccessibleHyperlinkInterface> &qtdecl_QAccessibleHyperlinkInterface () { return decl_QAccessibleHyperlinkInterface; }

}


class QAccessibleHyperlinkInterface_Adaptor : public QAccessibleHyperlinkInterface, public qt_gsi::QtObjectBase
{
public:

  virtual ~QAccessibleHyperlinkInterface_Adaptor();

  //  [adaptor ctor] QAccessibleHyperlinkInterface::QAccessibleHyperlinkInterface()
  QAccessibleHyperlinkInterface_Adaptor() : QAccessibleHyperlinkInterface()
  {
    qt_gsi::QtObjectBase::init (this);
  }

  //  [adaptor impl] QString QAccessibleHyperlinkInterface::anchor()
  QString cbs_anchor_c0_0() const
  {
    throw qt_gsi::AbstractMethodCalledException("anchor");
  }

  virtual QString anchor() const
  {
    if (cb_anchor_c0_0.can_issue()) {
      return cb_anchor_c0_0.issue<QAccessibleHyperlinkInterface_Adaptor, QString>(&QAccessibleHyperlinkInterface_Adaptor::cbs_anchor_c0_0);
    } else {
      throw qt_gsi::AbstractMethodCalledException("anchor");
    }
  }

  //  [adaptor impl] QString QAccessibleHyperlinkInterface::anchorTarget()
  QString cbs_anchorTarget_c0_0() const
  {
    throw qt_gsi::AbstractMethodCalledException("anchorTarget");
  }

  virtual QString anchorTarget() const
  {
    if (cb_anchorTarget_c0_0.can_issue()) {
      return cb_anchorTarget_c0_0.issue<QAccessibleHyperlinkInterface_Adaptor, QString>(&QAccessibleHyperlinkInterface_Adaptor::cbs_anchorTarget_c0_0);
    } else {
      throw qt_gsi::AbstractMethodCalledException("anchorTarget");
    }
  }

  //  [adaptor impl] int QAccessibleHyperlinkInterface::endIndex()
  int cbs_endIndex_c0_0() const
  {
    throw qt_gsi::AbstractMethodCalledException("endIndex");
  }

  virtual int endIndex() const
  {
    if (cb_endIndex_c0_0.can_issue()) {
      return cb_endIndex_c0_0.issue<QAccessibleHyperlinkInterface_Adaptor, int>(&QAccessibleHyperlinkInterface_Adaptor::cbs_endIndex_c0_0);
    } else {
      throw qt_gsi::AbstractMethodCalledException("endIndex");
    }
  }

  //  [adaptor impl] bool QAccessibleHyperlinkInterface::isValid()
  bool cbs_isValid_c0_0() const
  {
    throw qt_gsi::AbstractMethodCalledException("isValid");
  }

  virtual bool isValid() const
  {
    if (cb_isValid_c0_0.can_issue()) {
      return cb_isValid_c0_0.issue<QAccessibleHyperlinkInterface_Adaptor, bool>(&QAccessibleHyperlinkInterface_Adaptor::cbs_isValid_c0_0);
    } else {
      throw qt_gsi::AbstractMethodCalledException("isValid");
    }
  }

  //  [adaptor impl] int QAccessibleHyperlinkInterface::startIndex()
  int cbs_startIndex_c0_0() const
  {
    throw qt_gsi::AbstractMethodCalledException("startIndex");
  }

  virtual int startIndex() const
  {
    if (cb_startIndex_c0_0.can_issue()) {
      return cb_startIndex_c0_0.issue<QAccessibleHyperlinkInterface_Adaptor, int>(&QAccessibleHyperlinkInterface_Adaptor::cbs_startIndex_c0_0);
    } else {
      throw qt_gsi::AbstractMethodCalledException("startIndex");
    }
  }

  gsi::Callback cb_anchor_c0_0;
  gsi::Callback cb_anchorTarget_c0_0;
  gsi::Callback cb_endIndex_c0_0;
  gsi::Callback cb_isValid_c0_0;
  gsi::Callback cb_startIndex_c0_0;
};

QAccessibleHyperlinkInterface_Adaptor::~QAccessibleHyperlinkInterface_Adaptor() { }

//  Constructor QAccessibleHyperlinkInterface::QAccessibleHyperlinkInterface() (adaptor class)

static void _init_ctor_QAccessibleHyperlinkInterface_Adaptor_0 (qt_gsi::GenericStaticMethod *decl)
{
  decl->set_return_new<QAccessibleHyperlinkInterface_Adaptor> ();
}

static void _call_ctor_QAccessibleHyperlinkInterface_Adaptor_0 (const qt_gsi::GenericStaticMethod * /*decl*/, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<QAccessibleHyperlinkInterface_Adaptor *> (new QAccessibleHyperlinkInterface_Adaptor ());
}


// QString QAccessibleHyperlinkInterface::anchor()

static void _init_cbs_anchor_c0_0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QString > ();
}

static void _call_cbs_anchor_c0_0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<QString > ((QString)((QAccessibleHyperlinkInterface_Adaptor *)cls)->cbs_anchor_c0_0 ());
}

static void _set_callback_cbs_anchor_c0_0 (void *cls, const gsi::Callback &cb)
{
  ((QAccessibleHyperlinkInterface_Adaptor *)cls)->cb_anchor_c0_0 = cb;
}


// QString QAccessibleHyperlinkInterface::anchorTarget()

static void _init_cbs_anchorTarget_c0_0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QString > ();
}

static void _call_cbs_anchorTarget_c0_0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<QString > ((QString)((QAccessibleHyperlinkInterface_Adaptor *)cls)->cbs_anchorTarget_c0_0 ());
}

static void _set_callback_cbs_anchorTarget_c0_0 (void *cls, const gsi::Callback &cb)
{
  ((QAccessibleHyperlinkInterface_Adaptor *)cls)->cb_anchorTarget_c0_0 = cb;
}


// int QAccessibleHyperlinkInterface::endIndex()

static void _init_cbs_endIndex_c0_0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<int > ();
}

static void _call_cbs_endIndex_c0_0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<int > ((int)((QAccessibleHyperlinkInterface_Adaptor *)cls)->cbs_endIndex_c0_0 ());
}

static void _set_callback_cbs_endIndex_c0_0 (void *cls, const gsi::Callback &cb)
{
  ((QAccessibleHyperlinkInterface_Adaptor *)cls)->cb_endIndex_c0_0 = cb;
}


// bool QAccessibleHyperlinkInterface::isValid()

static void _init_cbs_isValid_c0_0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<bool > ();
}

static void _call_cbs_isValid_c0_0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<bool > ((bool)((QAccessibleHyperlinkInterface_Adaptor *)cls)->cbs_isValid_c0_0 ());
}

static void _set_callback_cbs_isValid_c0_0 (void *cls, const gsi::Callback &cb)
{
  ((QAccessibleHyperlinkInterface_Adaptor *)cls)->cb_isValid_c0_0 = cb;
}


// int QAccessibleHyperlinkInterface::startIndex()

static void _init_cbs_startIndex_c0_0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<int > ();
}

static void _call_cbs_startIndex_c0_0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<int > ((int)((QAccessibleHyperlinkInterface_Adaptor *)cls)->cbs_startIndex_c0_0 ());
}

static void _set_callback_cbs_startIndex_c0_0 (void *cls, const gsi::Callback &cb)
{
  ((QAccessibleHyperlinkInterface_Adaptor *)cls)->cb_startIndex_c0_0 = cb;
}


namespace gsi
{

gsi::Class<QAccessibleHyperlinkInterface> &qtdecl_QAccessibleHyperlinkInterface ();

static gsi::Methods methods_QAccessibleHyperlinkInterface_Adaptor () {
  gsi::Methods methods;
  methods += new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QAccessibleHyperlinkInterface::QAccessibleHyperlinkInterface()\nThis method creates an object of class QAccessibleHyperlinkInterface.", &_init_ctor_QAccessibleHyperlinkInterface_Adaptor_0, &_call_ctor_QAccessibleHyperlinkInterface_Adaptor_0);
  methods += new qt_gsi::GenericMethod ("anchor", "@brief Virtual method QString QAccessibleHyperlinkInterface::anchor()\nThis method can be reimplemented in a derived class.", true, &_init_cbs_anchor_c0_0, &_call_cbs_anchor_c0_0);
  methods += new qt_gsi::GenericMethod ("anchor", "@hide", true, &_init_cbs_anchor_c0_0, &_call_cbs_anchor_c0_0, &_set_callback_cbs_anchor_c0_0);
  methods += new qt_gsi::GenericMethod ("anchorTarget", "@brief Virtual method QString QAccessibleHyperlinkInterface::anchorTarget()\nThis method can be reimplemented in a derived class.", true, &_init_cbs_anchorTarget_c0_0, &_call_cbs_anchorTarget_c0_0);
  methods += new qt_gsi::GenericMethod ("anchorTarget", "@hide", true, &_init_cbs_anchorTarget_c0_0, &_call_cbs_anchorTarget_c0_0, &_set_callback_cbs_anchorTarget_c0_0);
  methods += new qt_gsi::GenericMethod ("endIndex", "@brief Virtual method int QAccessibleHyperlinkInterface::endIndex()\nThis method can be reimplemented in a derived class.", true, &_init_cbs_endIndex_c0_0, &_call_cbs_endIndex_c0_0);
  methods += new qt_gsi::GenericMethod ("endIndex", "@hide", true, &_init_cbs_endIndex_c0_0, &_call_cbs_endIndex_c0_0, &_set_callback_cbs_endIndex_c0_0);
  methods += new qt_gsi::GenericMethod ("isValid", "@brief Virtual method bool QAccessibleHyperlinkInterface::isValid()\nThis method can be reimplemented in a derived class.", true, &_init_cbs_isValid_c0_0, &_call_cbs_isValid_c0_0);
  methods += new qt_gsi::GenericMethod ("isValid", "@hide", true, &_init_cbs_isValid_c0_0, &_call_cbs_isValid_c0_0, &_set_callback_cbs_isValid_c0_0);
  methods += new qt_gsi::GenericMethod ("startIndex", "@brief Virtual method int QAccessibleHyperlinkInterface::startIndex()\nThis method can be reimplemented in a derived class.", true, &_init_cbs_startIndex_c0_0, &_call_cbs_startIndex_c0_0);
  methods += new qt_gsi::GenericMethod ("startIndex", "@hide", true, &_init_cbs_startIndex_c0_0, &_call_cbs_startIndex_c0_0, &_set_callback_cbs_startIndex_c0_0);
  return methods;
}

gsi::Class<QAccessibleHyperlinkInterface_Adaptor> decl_QAccessibleHyperlinkInterface_Adaptor (qtdecl_QAccessibleHyperlinkInterface (), "QtGui", "QAccessibleHyperlinkInterface",
  methods_QAccessibleHyperlinkInterface_Adaptor (),
  "@qt\n@brief Binding of QAccessibleHyperlinkInterface");

}
