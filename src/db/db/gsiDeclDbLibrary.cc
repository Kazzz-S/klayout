
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
#include "dbLibrary.h"
#include "dbLibraryManager.h"
#include "dbFileBasedLibrary.h"
#include "tlLog.h"

namespace gsi
{

// ---------------------------------------------------------------
//  db::Library binding

static db::Library *library_by_name (const std::string &name, const std::string &for_technology)
{
  return db::LibraryManager::instance ().lib_ptr_by_name (name, for_technology);
}

static db::Library *library_by_id (db::lib_id_type id)
{
  return db::LibraryManager::instance ().lib (id);
}

static std::vector<std::string> library_names ()
{
  std::vector<std::string> r;
  for (db::LibraryManager::iterator l = db::LibraryManager::instance ().begin (); l != db::LibraryManager::instance ().end (); ++l) {
    r.push_back (l->first);
  }
  return r;
}

static std::vector<db::lib_id_type> library_ids ()
{
  std::vector<db::lib_id_type> r;
  for (db::LibraryManager::iterator l = db::LibraryManager::instance ().begin (); l != db::LibraryManager::instance ().end (); ++l) {
    r.push_back (l->second);
  }
  return r;
}

static void refresh_all ()
{
  db::LibraryManager::instance ().refresh_all ();
}

static void register_lib (db::Library *lib, const std::string &name)
{
  lib->set_name (name);
  db::LibraryManager::instance ().register_lib (lib);
}

static void unregister_lib (db::Library *lib)
{
  db::LibraryManager::instance ().unregister_lib (lib);
}

static void delete_lib (db::Library *lib)
{
  db::LibraryManager::instance ().delete_lib (lib);
}

static std::string get_technology (db::Library *lib)
{
  const std::set<std::string> &techs = lib->get_technologies ();
  if (techs.empty ()) {
    return std::string ();
  } else {
    return *techs.begin ();
  }
}

static void destroy_lib (db::Library *lib)
{
  if (db::LibraryManager::instance ().lib_ptr_by_name (lib->get_name ()) == lib) {
    delete_lib (lib);
  } else {
    delete lib;
  }
}

namespace {

template <class Base>
class LibraryClass
  : public gsi::Class<Base>
{
public:
  LibraryClass (const char *module, const char *name, const gsi::Methods &methods, const char *description)
    : gsi::Class<Base> (module, name, methods, description)
  { }

  template <class B>
  LibraryClass (const gsi::Class<B> &base, const char *module, const char *name, const gsi::Methods &methods, const char *description)
    : gsi::Class<Base> (base, module, name, methods, description)
  { }

  virtual void destroy (void *p) const
  {
    Base *lib = reinterpret_cast<Base *> (p);
    destroy_lib (lib);
  }
};

class LibraryImpl
  : public db::Library
{
public:
  LibraryImpl () : db::Library ()
  {
    //  .. nothing yet ..
  }

  virtual std::string reload ()
  {
    if (cb_reload.can_issue ()) {
      return cb_reload.issue<db::Library, std::string> (&db::Library::reload);
    } else {
      return db::Library::reload ();
    }
  }

  gsi::Callback cb_reload;
};

}

static LibraryImpl *new_lib ()
{
  return new LibraryImpl ();
}

static db::Library *library_from_file (const std::string &path, const std::string &name, const std::string &for_technology)
{
  //  Check if a library with this specification already is installed and reuse in that case.
  if (! name.empty ()) {

    db::FileBasedLibrary *old_lib = dynamic_cast<db::FileBasedLibrary *> (library_by_name (name, for_technology));
    if (old_lib && old_lib->is_for_path (path)) {
      old_lib->load ();
      return old_lib;
    }

  }

  std::unique_ptr<db::FileBasedLibrary> lib (new db::FileBasedLibrary (path, name));
  lib->set_technology (for_technology);

  std::string n = lib->load ();
  db::Library *ret = lib.get ();
  register_lib (lib.release (), n);

  return ret;
}

static  db::Library *library_from_files (const std::vector<std::string> &paths, const std::string &name, const std::string &for_technology)
{
  if (paths.empty ()) {
    throw tl::Exception (tl::to_string (tr ("At least one path must be given")));
  }

  //  Check if a library with this specification already is installed and reuse in that case.
  if (! name.empty ()) {

    db::FileBasedLibrary *old_lib = dynamic_cast<db::FileBasedLibrary *> (library_by_name (name, for_technology));
    if (old_lib && old_lib->is_for_paths (paths)) {
      old_lib->load ();
      return old_lib;
    }

  }

  std::unique_ptr<db::FileBasedLibrary> lib (new db::FileBasedLibrary (paths.front (), name));
  for (auto i = paths.begin () + 1; i != paths.end (); ++i) {
    lib->merge_with_other_layout (*i);
  }

  lib->set_technology (for_technology);

  std::string n = lib->load ();
  db::Library *ret = lib.get ();
  register_lib (lib.release (), n);

  return ret;
}

/**
 *  @brief A basic implementation of the library
 */

LibraryClass<db::Library> decl_Library ("db", "LibraryBase",
  gsi::method ("library_from_file", &library_from_file, gsi::arg ("path"), gsi::arg ("name", std::string (), "auto"), gsi::arg ("for_technology", std::string (), "none"),
    "@brief Creates a library from a file\n"
    "@param path The path to the file from which to create the library from.\n"
    "@param name The name of the library. If empty, the name will be derived from the GDS LIBNAME or the file name.\n"
    "@return The library object created. It is already registered with the name given or derived from the file.\n"
    "\n"
    "This method will create a \\Library object which is tied to a specific file. This object supports "
    "automatic reloading when the \\Library#refresh method is called.\n"
    "\n"
    "If a file-based library with the same name and path is registered already, this method will not reload again "
    "and return the library that was already registered.\n"
    "\n"
    "This convenience method has been added in version 0.30.8.\n"
  ) +
  gsi::method ("library_from_files", &library_from_files, gsi::arg ("paths"), gsi::arg ("name", std::string (), "auto"), gsi::arg ("for_technology", std::string (), "none"),
    "@brief Creates a library from a set of files\n"
    "@param paths The paths to the files from which to create the library from. At least one file needs to be given.\n"
    "@param name The name of the library. If empty, the name will be derived from the GDS LIBNAME or the file name.\n"
    "@return The library object created. It is already registered with the name given or derived from the file.\n"
    "\n"
    "This method will create a \\Library object which is tied to several files. This object supports "
    "automatic reloading when the \\Library#refresh method is called. The content of the files is merged "
    "into the library. This is useful for example to create one library from a collection of files.\n"
    "\n"
    "This convenience method has been added in version 0.30.8.\n"
  ) +
  gsi::method ("library_by_name", &library_by_name, gsi::arg ("name"), gsi::arg ("for_technology", std::string (), "unspecific"),
    "@brief Gets a library by name\n"
    "Returns the library object for the given name. If the name is not a valid library name, nil is returned.\n"
    "\n"
    "Different libraries can be registered under the same names for different technologies. By specifying a technology, this method\n"
    "will return the first library matching both name and the given technology. It will also return libraries not bound to a specific\n"
    "technology in that case. Without a technology name given ('unspecific'), only libraries not bound to a technology are returned.\n"
    "You can also specify '*' for the technology - in that case, the first library with the given name is returned, regardless whether\n"
    "it is bound to a technology or not.\n"
    "\n"
    "The technology selector has been introduced in version 0.27. The '*' option for the technology has been added in version 0.30.8."
  ) +
  gsi::method ("library_by_id", &library_by_id, gsi::arg ("id"),
    "@brief Gets the library object for the given ID\n"
    "If the ID is not valid, nil is returned.\n"
    "\n"
    "This method has been introduced in version 0.27."
  ) +
  gsi::method ("library_names", &library_names,
    "@brief Returns a list of the names of all libraries registered in the system.\n"
    "\n"
    "NOTE: starting with version 0.27, the name of a library does not need to be unique if libraries are associated with specific technologies. "
    "This method will only return the names and it's not possible not unambiguously derive the library object. It is recommended to use "
    "\\library_ids and \\library_by_id to obtain the library unambiguously."
  ) +
  gsi::method ("library_ids", &library_ids,
    "@brief Returns a list of valid library IDs.\n"
    "See \\library_names for the reasoning behind this method."
    "\n"
    "This method has been introduced in version 0.27."
  ) +
  gsi::method ("refresh_all", &refresh_all,
    "@brief Calls \\refresh on all libraries.\n"
    "\n"
    "This convenience method has been introduced in version 0.30.4."
  ) +
  gsi::method_ext ("register", &register_lib, gsi::arg ("name"),
    "@brief Registers the library with the given name\n"
    "\n"
    "This method can be called in the constructor to register the library after \n"
    "the layout object has been filled with content. If a library with that name\n"
    "already exists for the same technologies, it will be replaced with this library. \n"
    "\n"
    "This method will set the libraries' name.\n"
    "\n"
    "The technology specific behaviour has been introduced in version 0.27."
  ) +
  gsi::method_ext ("unregister", &unregister_lib,
    "@brief Unregisters the library\n"
    "\n"
    "Unregisters the library from the system. This will break all references of cells "
    "using this library and make them 'defunct'.\n"
    "\n"
    "This method has been introduced in version 0.30.5."
  ) +
  gsi::method ("replicate=", &db::Library::set_replicate, gsi::arg ("flag"),
    "@brief Sets a value indicating whether the library produces replicas\n"
    "\n"
    "If this value is true (the default), layout written will include the\n"
    "actual layout of a library cell (replica). With this, it is possible\n"
    "to regenerate the layout without actually having the library at the\n"
    "cost of additional bytes in the file.\n"
    "\n"
    "Setting this flag to false avoids this replication, but a layout\n"
    "cannot be regenerated without having this library.\n"
    "\n"
    "This attribute has been introduced in version 0.30.8."
  ) +
  gsi::method ("replicate", &db::Library::replicate,
    "@brief Gets a value indicating whether the library produces replicas\n"
    "\n"
    "See \\replicate= for a description of this attribute.\n"
    "\n"
    "This attribute has been introduced in version 0.30.8."
  ) +
  gsi::method ("rename", &db::Library::rename, gsi::arg ("name"),
    "@brief Renames the library\n"
    "\n"
    "Re-registers the library under a new name. Note that this method will also change the references "
    "to the library.\n"
    "\n"
    "This method has been introduced in version 0.30.5."
  ) +
  gsi::method_ext ("delete", &delete_lib,
    "@brief Deletes the library\n"
    "\n"
    "This method will delete the library object. Library proxies pointing to this library will become "
    "invalid and the library object cannot be used any more after calling this method.\n"
    "\n"
    "This method has been introduced in version 0.25.\n"
  ) +
  gsi::method ("name", &db::Library::get_name,
    "@brief Returns the libraries' name\n"
    "The name is set when the library is registered. To change it use \\rename.\n"
  ) +
  gsi::method ("id", &db::Library::get_id,
    "@brief Returns the library's ID\n"
    "The ID is set when the library is registered and cannot be changed \n"
  ) +
  gsi::method ("description", &db::Library::get_description,
    "@brief Returns the libraries' description text\n"
  ) +
  gsi::method ("description=", &db::Library::set_description, gsi::arg ("description"),
    "@brief Sets the libraries' description text\n"
  ) +
  gsi::method_ext ("#technology", &get_technology,
    "@brief Returns name of the technology the library is associated with\n"
    "If this attribute is a non-empty string, this library is only offered for "
    "selection if the current layout uses this technology.\n"
    "\n"
    "This attribute has been introduced in version 0.25. In version 0.27 this attribute is deprecated as "
    "a library can now be associated with multiple technologies."
  ) +
  gsi::method ("technology=", &db::Library::set_technology, gsi::arg ("technology"),
    "@brief sets the name of the technology the library is associated with\n"
    "\n"
    "See \\technology for details. "
    "This attribute has been introduced in version 0.25. In version 0.27, a library can be associated with "
    "multiple technologies and this method will revert the selection to a single one. Passing an empty string "
    "is equivalent to \\clear_technologies."
  ) +
  gsi::method ("clear_technologies", &db::Library::clear_technologies,
    "@brief Clears the list of technologies the library is associated with.\n"
    "See also \\add_technology.\n"
    "\n"
    "This method has been introduced in version 0.27"
  ) +
  gsi::method ("add_technology", &db::Library::add_technology, gsi::arg ("tech"),
    "@brief Additionally associates the library with the given technology.\n"
    "See also \\clear_technologies.\n"
    "\n"
    "This method has been introduced in version 0.27"
  ) +
  gsi::method ("is_for_technology", &db::Library::is_for_technology, gsi::arg ("tech"),
    "@brief Returns a value indicating whether the library is associated with the given technology.\n"
    "The method is equivalent to checking whether the \\technologies list is empty.\n"
    "As a special case, you can pass '*' for the 'tech' argument. In that case, this method\n"
    "will return true, if the library is bound to any technology.\n"
    "\n"
    "This method has been introduced in version 0.27. The '*' option for the technology has been added in version 0.30.8."
  ) +
  gsi::method ("for_technologies", &db::Library::for_technologies,
    "@brief Returns a value indicating whether the library is associated with any technology.\n"
    "This method has been introduced in version 0.27"
  ) +
  gsi::method ("technologies", &db::Library::get_technologies,
    "@brief Gets the list of technologies this library is associated with.\n"
    "This method has been introduced in version 0.27"
  ) +
  gsi::method ("layout_const", (const db::Layout &(db::Library::*)() const) &db::Library::layout,
    "@brief The layout object where the cells reside that this library defines (const version)\n"
  ) +
  gsi::method ("layout", (db::Layout &(db::Library::*)()) &db::Library::layout,
    "@brief The layout object where the cells reside that this library defines\n"
  ) +
  gsi::method ("refresh", &db::Library::refresh,
    "@brief Updates all layouts using this library.\n"
    "This method will retire cells or update layouts in the attached clients.\n"
    "It will also recompute the PCells inside the library. "
    "Starting with version 0.30.5, this method will also call 'reload' on all libraries to "
    "refresh cells located in external files.\n"
    "\n"
    "This method has been introduced in version 0.27.8."
  ),
  "@hide"
);

/**
 *  @brief The reimplementation stub
 */

LibraryClass<LibraryImpl> decl_LibraryImpl (decl_Library, "db", "Library",
  gsi::constructor ("new", &new_lib,
    "@brief Creates a new, empty library"
  ) +
  gsi::callback ("reload", &LibraryImpl::reload, &LibraryImpl::cb_reload,
    "@brief Reloads resources for the library.\n"
    "Reimplement this method if you like to reload resources the library was created from - "
    "for example layout files. Make sure you return the new name of the library from this function. "
    "If you do not want to change the name of the library, return the current name (i.e. the value of \\name).\n"
    "\n"
    "@return The new name of the library or the original name if it did not change.\n"
    "\n"
    "This method is called on \\refresh. It was introduced in version 0.30.5.\n"
  ),
  "@brief A Library \n"
  "\n"
  "A library is basically a wrapper around a layout object. The layout object\n"
  "provides cells and potentially PCells that can be imported into other layouts.\n"
  "\n"
  "The library provides a name which is used to identify the library and a description\n"
  "which is used for identifying the library in a user interface. \n"
   "\n"
  "After a library is created and the layout is filled, it must be registered using the register method.\n"
  "\n"
  "This class has been introduced in version 0.22.\n"
);

}
