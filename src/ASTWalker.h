#pragma once

#include "clang/AST/ASTContext.h"
#include "clang/AST/RecursiveASTVisitor.h"

#include <string>

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
  // Recursively walks a statement's children, tracking the deepest chain
  // of for/while/do loops found. Every Stmt (an "if", a loop, a block, an
  // expression...) exposes ->children(), so this one function can walk
  // anything, regardless of what kind of statement it started on.
  unsigned maxLoopDepth(clang::Stmt *S);

  // Recursively walks a statement's children looking for ForStmt nodes,
  // printing the init/cond/inc pieces of each one it finds.
  void printForLoopPieces(clang::Stmt *S);

  // Returns the literal source text a node spans, e.g. "i < n" for a
  // ForStmt's condition
  std::string sourceText(const clang::Stmt *S);

  clang::ASTContext *Context;
};
