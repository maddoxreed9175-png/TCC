#include "TCC.h"

#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "llvm/Support/CommandLine.h"

using namespace clang;

// Groups custom flags under the --help flag
static llvm::cl::OptionCategory ToolCategory("tcc options");

int main(int argc, const char **argv) {
  // Parses the arguments the user passed
  auto ExpectedParser =
      tooling::CommonOptionsParser::create(argc, argv, ToolCategory);
  if (!ExpectedParser) {
    llvm::errs() << ExpectedParser.takeError();
    return 1;
  }

  // Unwrap parsed arguments
  tooling::CommonOptionsParser &OptionsParser = ExpectedParser.get();

  // Gets parsed compilation and source files and puts them in a tool
  tooling::ClangTool Tool(OptionsParser.getCompilations(),
                          OptionsParser.getSourcePathList());

  // For every source file, parse, and then give the AST to TCC
  return Tool.run(tooling::newFrontendActionFactory<TCC>().get());
}
