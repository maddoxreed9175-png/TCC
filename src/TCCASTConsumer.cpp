#include "TCCASTConsumer.h"

#include "ASTWalker.h"

void TCCASTConsumer::HandleTranslationUnit(clang::ASTContext &Context) {
  // Create the object that "walks" through the AST
  ASTWalker Walker(&Context);
  // Start the walk from the root of the tree (the whole file)
  Walker.TraverseDecl(Context.getTranslationUnitDecl());
}
