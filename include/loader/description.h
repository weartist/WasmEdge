//===-- ssvm/loader/description.h - Desc classes definition------*- C++ -*-===//
//
// Part of the SSVM Project.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the Desc node class and the derived
/// ImportDesc and ExportDesc classes.
///
//===----------------------------------------------------------------------===//
#pragma once

#include "filemgr.h"
#include "type.h"
#include <string>
#include <variant>

namespace AST {

/// Base class of Desc node.
class Desc : public Base {
public:
  /// External type enumeration class
  enum class ExternalType : char {
    Function = 0x00,
    Table = 0x01,
    Memory = 0x02,
    Global = 0x03
  };

protected:
  /// External type of this class.
  ExternalType ExtType;
};

/// Derived import description class.
class ImportDesc : public Desc {
public:
  /// Load binary from file manager.
  ///
  /// Inheritted and overrided from Base.
  /// Read the module name, external name, external type, and corresponding
  /// content.
  ///
  /// \param Mgr the file manager reference.
  ///
  /// \returns ErrCode.
  virtual ErrCode loadBinary(FileMgr &Mgr);

  /// Variant of external type classes.
  using ExtContentType =
      std::variant<std::unique_ptr<unsigned int>, std::unique_ptr<TableType>,
                   std::unique_ptr<MemoryType>, std::unique_ptr<GlobalType>>;

protected:
  /// The node type should be Attr::Desc_Import.
  Attr NodeAttr = Attr::Desc_Import;

private:
  /// \name Data of ImportDesc: Module name, External name, and content node.
  /// @{
  std::string ModName;
  std::string ExtName;
  ExtContentType ExtContent;
  /// @}
};

class ExportDesc : public Desc {
public:
  /// Load binary from file manager.
  ///
  /// Inheritted and overrided from Base.
  /// Read the export name, external type, and corresponding external index.
  ///
  /// \param Mgr the file manager reference.
  ///
  /// \returns ErrCode.
  virtual ErrCode loadBinary(FileMgr &Mgr);

protected:
  /// The node type should be Attr::Desc_Export.
  Attr NodeAttr = Attr::Desc_Export;

private:
  /// \name Data of ExportDesc: External name and external index.
  /// @{
  std::string ExtName;
  unsigned int ExtIdx;
  /// @}
};

} // namespace AST
