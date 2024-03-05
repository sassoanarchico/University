#pragma once

#include <string>

#include "serialization_context.h"
#include "id_context.h"
#include "blob.h"

namespace mini_core {

class ObjectWriter;

  class Serializer: virtual public IdContext {
public:
  Serializer(SerializationContext* serContext = 0);
  
  /*
   * Set file path for main data file.
   */
  void setFilePath(const std::string& fpath);
  
  /*
   * Set file path for binary object files (BLOBs).
   * Unless an absolute path is specified the path is relative to the main data file directory.
   * to the directory name, if any.
   */
  void setBinaryPath(const std::string& fpath);
  
  /*
   * Set data file format (default is "JSON").
   */
  bool setFormat(const std::string& format);
  
  /* Write an object.
   * Return false if an error occurred during serialization.
   */
  bool writeObject(Serializable& instance);

  bool writeObject(std::string& output, Serializable& instance);

  virtual ~Serializer();
  
protected:
  ObjectWriter* _objectWriter;
};

}
