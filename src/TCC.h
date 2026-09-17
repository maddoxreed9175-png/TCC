#pragma once

#include "clang/Frontend/FrontendAction.h"

// Attach to Clang's parsing and direct what gets the AST
class TCC : public clang::ASTFrontendAction {
public:
  // Override CreateASTConsumer to send the AST to TCCASTConsumer
  std::unique_ptr<clang::ASTConsumer>
  CreateASTConsumer(clang::CompilerInstance &CI,
                     clang::StringRef File) override;
};
