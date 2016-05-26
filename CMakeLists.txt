cmake_minimum_required(VERSION 2.8)
project(decclass)

find_package(LLVM REQUIRED)

add_definitions(
        -std=c++11
        -fno-rtti
        -D__STDC_LIMIT_MACROS
        -D__STDC_CONSTANT_MACROS
)


set(Clang_LIBS
        clangFrontend
        clangSerialization
        clangDriver
        clangParse
        clangSema
        clangAnalysis
        clangAST
        clangBasic
        clangEdit
        clangLex
        clangTooling
        LLVMX86AsmParser # MC, MCParser, Support, X86Desc, X86Info
        LLVMX86Desc # MC, Support, X86AsmPrinter, X86Info
        LLVMX86AsmPrinter # MC, Support, X86Utils
        LLVMX86Info # MC, Support, Target
        LLVMX86Utils # Core, Support
        LLVMipo
        LLVMScalarOpts
        LLVMInstCombine
        LLVMTransformUtils
        LLVMipa
        LLVMAnalysis
        LLVMTarget
        LLVMOption # Support
        LLVMMCParser # MC, Support
        LLVMMC # Object, Support
        LLVMObject # BitReader, Core, Support
        LLVMBitReader # Core, Support
        LLVMCore # Support
        LLVMSupport)

set(HEADER_FILES
        include/CXXField.h
        include/Consumer.h
        include/FieldFinder.h
        include/FieldFinderAction.h
        include/StructExpander.h)

set(SOURCE_FILES
        src/FieldFinder.cpp
        src/StructExpander.cpp
        src/main.cpp)

include_directories(include)
add_executable(decclass ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(decclass ${Clang_LIBS})