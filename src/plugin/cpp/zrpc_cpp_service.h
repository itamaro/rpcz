// Copyright 2011, Nadav Samet.
// All rights reserved.
//
// Author: thesamet@gmail.com <Nadav Samet>

#ifndef ZRPC_CPP_SERVICE_H
#define ZRPC_CPP_SERVICE_H

#include <map>
#include <string>
#include <google/protobuf/stubs/common.h>
#include <google/protobuf/descriptor.h>

namespace google {
namespace protobuf {
  namespace io {
    class Printer;             // printer.h
  }
}
}

namespace zrpc {
namespace plugin {
namespace cpp {

class ServiceGenerator {
 public:
  // See generator.cc for the meaning of dllexport_decl.
  explicit ServiceGenerator(
      const google::protobuf::ServiceDescriptor* descriptor,
      const std::string& dllexport_decl);
  ~ServiceGenerator();

  // Header stuff.

  // Generate the class definitions for the service's interface and the
  // stub implementation.
  void GenerateDeclarations(google::protobuf::io::Printer* printer);

  // Source file stuff.

  // Generate code that initializes the global variable storing the service's
  // descriptor.
  void GenerateDescriptorInitializer(google::protobuf::io::Printer* printer,
                                     int index);

  // Generate implementations of everything declared by GenerateDeclarations().
  void GenerateImplementation(google::protobuf::io::Printer* printer);

 private:
  enum RequestOrResponse { REQUEST, RESPONSE };
  enum VirtualOrNon { VIRTUAL, NON_VIRTUAL };

  // Header stuff.

  // Generate the service abstract interface.
  void GenerateInterface(google::protobuf::io::Printer* printer);

  // Generate the stub class definition.
  void GenerateStubDefinition(google::protobuf::io::Printer* printer);

  // Prints signatures for all methods in the
  void GenerateMethodSignatures(VirtualOrNon virtual_or_non,
                                google::protobuf::io::Printer* printer);

  // Source file stuff.

  // Generate the default implementations of the service methods, which
  // produce a "not implemented" error.
  void GenerateNotImplementedMethods(google::protobuf::io::Printer* printer);

  // Generate the CallMethod() method of the service.
  void GenerateCallMethod(google::protobuf::io::Printer* printer);

  // Generate the Get{Request,Response}Prototype() methods.
  void GenerateGetPrototype(RequestOrResponse which,
                            google::protobuf::io::Printer* printer);

  // Generate the stub's implementations of the service methods.
  void GenerateStubMethods(google::protobuf::io::Printer* printer);

  const google::protobuf::ServiceDescriptor* descriptor_;
  std::map<std::string, std::string> vars_;

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(ServiceGenerator);
};

}  // namespace cpp
}  // namespace plugin
}  // namespace zrpc
#endif  // ZRPC_CPP_SERVICE_H
