#pragma once

#include "clang/AST/ASTContext.h"
#include "clang/AST/RecursiveASTVisitor.h"

#include <string>
#include <vector>

struct ForLoop {
  const clang::Stmt *init = nullptr;
  const clang::Expr *cond = nullptr;
  const clang::Expr *inc = nullptr;
};

class ASTWalker : public clang::RecursiveASTVisitor<ASTWalker> {
public:
  // === Constructor === //
  explicit ASTWalker(clang::ASTContext *Context) : Context(Context) {}

  // **NOTE** Whenever you make a function that hooks into the parser, it
  // should return a bool so it knows whether to keep going (true) or stop
  // (false)
  // RecursiveASTVisitor calls this automatically for every FunctionDecl
  // node it walks past in the tree.
  bool VisitFunctionDecl(clang::FunctionDecl *FD);

private:
  // Recursively walks a statement's children looking for ForStmt nodes,
  // putting the init/cond/inc pieces of each one in a ForLoop struct.
  // Returns an empty vector if there are no for loops.
  std::vector<ForLoop> gatherForLoopPieces(clang::Stmt *S);

  // Returns the literal source text a node spans, e.g. "i < n" for a
  // ForStmt's condition
  std::string sourceText(const clang::Stmt *S);

  clang::ASTContext *Context;
};
