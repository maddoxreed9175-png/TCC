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

  // === CODE === //
  std::vector<ForLoop> Loops = gatherForLoopPieces(FD->getBody());
  std::cout << FD->getNameAsString() << ": " << Loops.size()
            << " for loop(s)\n";

  std::cout << "First Loop:" << sourceText(Loops[0].init)
            << sourceText(Loops[0].cond) << sourceText(Loops[0].inc)
            << std::endl;
  ForLoop loop = Loops[0];

  // === Initializer === //
  // int i = ?
  if (const auto *declStmt = dyn_cast_or_null<DeclStmt>(loop.init)) {
    for (const Decl *decl : declStmt->decls()) {
      if (const auto *varDecl = dyn_cast<VarDecl>(decl)) {
        std::string Name = varDecl->getNameAsString();
        if (const Expr *initExpr = varDecl->getInit()) {
          if (const auto *literal =
                  dyn_cast<IntegerLiteral>(initExpr->IgnoreParenImpCasts())) {
            int64_t Value = literal->getValue().getSExtValue();
            std::cout << "Init value: " << Value << std::endl;
          }
        }
      }
    }
  } else if (const auto *assignment = dyn_cast_or_null<BinaryOperator>(loop.init)) {
      if (assignment->getOpcode() == BO_Assign) {
          const Expr *leftSide = assignment->getLHS()->IgnoreParenImpCasts();
          const Expr *rightSide = assignment->getRHS()->IgnoreParenImpCasts();

          if (const auto *variableRef = dyn_cast<DeclRefExpr>(leftSide)) {
              std::string name = variableRef->getDecl()->getNameAsString(); // "i"
          }
          if (const auto* literal = dyn_cast<IntegerLiteral>(rightSide)) {
              int64_t value = literal->getValue().getSExtValue();
          }
      }
  }

  // Conditional
  if (const auto *BO = dyn_cast_or_null<BinaryOperator>(loop.cond)) {
    StringRef Op = BO->getOpcodeStr(); // "<"
    const Expr *LHS = BO->getLHS()->IgnoreParenImpCasts();
    const Expr *RHS = BO->getRHS()->IgnoreParenImpCasts();
    if (const auto *DR = dyn_cast<DeclRefExpr>(LHS)) {
      std::string Var = DR->getDecl()->getNameAsString(); // "i"
      std::cout << "Cond Value: " << Var << std::endl;
    }
  }

  // Actor
  if (const auto *UO =
          dyn_cast_or_null<UnaryOperator>(loop.inc)) { // i++ / ++i / i--
    UO->getOpcode();  // UO_PostInc, UO_PreInc, UO_PostDec, UO_PreDec
    UO->getSubExpr(); // the "i"
    std::cout << "Inc Value: " << UO->getOpcode() << std::endl;
  } else if (const auto *BO = dyn_cast_or_null<BinaryOperator>(loop.inc)) {
    BO->getOpcode(); // BO_AddAssign for i += 2, BO_DivAssign for n /= 2,
                     // BO_Assign for i = i * 2
  }

  return true; // true = keep going, don't stop the traversal
}

std::vector<ForLoop> ASTWalker::gatherForLoopPieces(Stmt *S) {
  std::vector<ForLoop> Loops;
  if (!S)
    return Loops;

  if (const ForStmt *FS = dyn_cast<ForStmt>(S))
    Loops.push_back({FS->getInit(), FS->getCond(), FS->getInc()});

  for (Stmt *Child : S->children()) {
    std::vector<ForLoop> ChildLoops = gatherForLoopPieces(Child);
    Loops.insert(Loops.end(), ChildLoops.begin(), ChildLoops.end());
  }

  return Loops;
}

std::string ASTWalker::sourceText(const Stmt *S) {
  if (!S)
    return "(none)";
  CharSourceRange Range = CharSourceRange::getTokenRange(S->getSourceRange());
  return Lexer::getSourceText(Range, Context->getSourceManager(),
                              Context->getLangOpts())
      .str();
}
