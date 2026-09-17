#pragma once

#include "clang/AST/ASTConsumer.h"
#include "clang/AST/ASTContext.h"

// Waits for Clang to generate the AST then reads (consumes) it
class TCCASTConsumer : public clang::ASTConsumer {
public:
  // HandleTranslationUnit runs once the entire file has been parsed and
  // turned into an AST.
  void HandleTranslationUnit(clang::ASTContext &Context) override;
};
