; ModuleID = 'instcombine.c'
source_filename = "instcombine.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @foo() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  store i32 600, i32* %1, align 4
  store i32 400, i32* %2, align 4
  store i32 300, i32* %3, align 4
  %5 = load i32, i32* %1, align 4
  %6 = add nsw i32 200, %5
  %7 = load i32, i32* %2, align 4
  %8 = add nsw i32 %6, %7
  %9 = add nsw i32 %8, 200
  store i32 %9, i32* %4, align 4
  %10 = load i32, i32* %4, align 4
  ret i32 %10
}

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  %3 = call i32 @foo()
  store i32 %3, i32* %2, align 4
  %4 = load i32, i32* %2, align 4
  ret i32 %4
}

attributes #0 = { noinline nounwind uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2}
!llvm.ident = !{!3}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"uwtable", i32 1}
!2 = !{i32 7, !"frame-pointer", i32 2}
!3 = !{!"clang version 13.0.0 (https://github.com/llvm/llvm-project/ 24c8eaec9467b2aaf70b0db33a4e4dd415139a50)"}