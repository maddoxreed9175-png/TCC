#include "ASTWalker.h"

#include "clang/Basic/SourceManager.h"
#include "clang/Lex/Lexer.h"

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

  printForLoopPieces(FD->getBody());

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

std::string ASTWalker::sourceText(const Stmt *S) {
  if (!S)
    return "(none)";

  CharSourceRange Range = CharSourceRange::getTokenRange(S->getSourceRange());
  StringRef Text = Lexer::getSourceText(Range, Context->getSourceManager(),
                                         Context->getLangOpts());
  return Text.str();
}

void ASTWalker::printForLoopPieces(Stmt *S) {
  if (!S)
    return;

  if (const ForStmt *FS = dyn_cast<ForStmt>(S)) {
    std::cout << "  for loop:\n";
    std::cout << "    init: " << sourceText(FS->getInit()) << "\n";
    std::cout << "    cond: " << sourceText(FS->getCond()) << "\n";
    std::cout << "    inc:  " << sourceText(FS->getInc()) << "\n";
  }

  for (Stmt *Child : S->children())
    printForLoopPieces(Child);
}
