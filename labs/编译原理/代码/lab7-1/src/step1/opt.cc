//
// Created by asterich on 2023/10/4.
//

#include "include/opt.h"

namespace opt {
    using namespace llvm;
    using namespace llvm::sys;

    void Optimize(Module &m) {
        // Create the analysis managers.
        LoopAnalysisManager LAM;
        FunctionAnalysisManager FAM;
        CGSCCAnalysisManager CGAM;
        ModuleAnalysisManager MAM;

// Create the new pass manager builder.
// Take a look at the PassBuilder constructor parameters for more
// customization, e.g. specifying a TargetMachine or various debugging
// options.
        PassBuilder PB;

// Register all the basic analyses with the managers.
        PB.registerModuleAnalyses(MAM);
        PB.registerFunctionAnalyses(FAM);
        PB.crossRegisterProxies(LAM, FAM, CGAM, MAM);

// Create the pass manager.
// This one corresponds to a typical -O2 optimization pipeline.
        FunctionPassManager FPM;

        FPM.addPass(InstCombinePass());
        FPM.addPass(DCEPass());
        FPM.addPass(LoopSimplifyPass());

        ModulePassManager MPM;

        MPM.addPass(ConstantMergePass());
        MPM.addPass(createModuleToFunctionPassAdaptor(std::move(FPM)));

// Optimize the IR!
        MPM.run(m, MAM);
    }
}