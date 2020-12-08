#pragma once

#include <string>
#include <vector>

namespace ebc {
class EmbeddedFile {
 public:
  enum class Type {
    Bitcode,
    Exports,
    File,
    LTO,
    Object,
    Xar,
  };

  enum class CommandSource {
    Clang,
    Swift,
  };

  EmbeddedFile(std::string name);
  virtual ~EmbeddedFile() = default;

  std::string GetName() const;
  std::string GetXMLName() const;
  void SetXMLName(std::string name);

  /// Get all commands passed to the compiler to create this embedded file.
  ///
  /// @return A vector of strings with the clang front-end commands.
  const std::vector<std::string>& GetCommands() const;

  /// Set all commands passed to the compiler to create this embedded file.
  ///
  /// @param commands A vector of strings with the clang front-end
  ///                 commands.
  void SetCommands(const std::vector<std::string>& commands, CommandSource source);

  /// Remove the underlying file from the file system.
  void Remove() const;

  Type GetType() const;

  CommandSource GetCommandSource() const;

 protected:
  EmbeddedFile(std::string name, Type type);

 private:
  std::string _name;
  std::string _xml_name;
  Type _type;
  std::vector<std::string> _commands;
  CommandSource _commandSource;
};

inline bool operator==(const EmbeddedFile& lhs, const EmbeddedFile& rhs) {
  return lhs.GetName() == rhs.GetName();
}
}  // namespace ebc
