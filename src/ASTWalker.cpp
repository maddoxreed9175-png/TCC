#include "ASTWalker.h"

#include "clang/Basic/SourceManager.h"

#include <iostream>

using namespace clang;

bool ASTWalker::VisitFunctionDecl(FunctionDecl *FD) {
  // If function has no body, skip it
  if (!FD->hasBody())
    return true;

  // If function is from a header (i.e. <iostream>) skip it
  if (!Context->getSourceManager().isInMainFile(FD->getLocation()))
    return true;

  unsigned Depth = maxLoopDepth(FD->getBody());
  std::cout << FD->getNameAsString() << ": max loop nesting depth = " << Depth
            << "\n";

  return true; // true = keep going, don't stop the traversal
}

unsigned ASTWalker::maxLoopDepth(Stmt *S) {
  if (!S)
    return 0;

  bool IsLoop = isa<ForStmt>(S) || isa<WhileStmt>(S) || isa<DoStmt>(S) ||
                isa<CXXForRangeStmt>(S);

  unsigned DeepestChild = 0;
  for (Stmt *Child : S->children()) {
    unsigned ChildDepth = maxLoopDepth(Child);
    if (ChildDepth > DeepestChild)
      DeepestChild = ChildDepth;
  }

  return IsLoop ? DeepestChild + 1 : DeepestChild;
}
