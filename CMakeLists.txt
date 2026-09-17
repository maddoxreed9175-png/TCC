cmake_minimum_required(VERSION 3.25)
project(TCC)

# Pulls in whatever Clang/LLVM dev files are installed on this machine
find_package(Clang REQUIRED CONFIG)

add_executable(tcc
    src/main.cpp
    src/ASTWalker.cpp
    src/TCCASTConsumer.cpp
    src/TCC.cpp
)

target_include_directories(tcc PRIVATE
    ${CLANG_INCLUDE_DIRS}
    ${LLVM_INCLUDE_DIRS}
)
target_compile_definitions(tcc PRIVATE ${LLVM_DEFINITIONS})

# If you get an "undefined reference" error, make sure the library containing
# the function/class being called is included below
target_link_libraries(tcc
    PRIVATE
    clangAST
    clangASTMatchers
    clangBasic
    clangFrontend
    clangTooling
)
