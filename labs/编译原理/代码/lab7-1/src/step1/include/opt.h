#pragma once

#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Pass.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Support/Casting.h"

#include "llvm/Transforms/InstCombine/InstCombine.h"
#include "llvm/Transforms/Scalar/DCE.h"
#include "llvm/Transforms/Utils/LoopSimplify.h"
#include "llvm/Transforms/Utils.h"
#include "llvm/Transforms/IPO/ConstantMerge.h"



namespace opt {
    using namespace llvm;
    using namespace llvm::sys;

    void Optimize(Module &m);

}