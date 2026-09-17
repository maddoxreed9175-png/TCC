#include "TCC.h"

#include "TCCASTConsumer.h"

std::unique_ptr<clang::ASTConsumer>
TCC::CreateASTConsumer(clang::CompilerInstance &CI, clang::StringRef File) {
  return std::make_unique<TCCASTConsumer>();
}
