; ModuleID = 'dse_slow.c'
source_filename = "dse_slow.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [14 x i8] c"Result: %lld\0A\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i64 @compute(i64 noundef %0) #0 {
  %2 = alloca i64, align 8
  %3 = alloca i64, align 8
  %4 = alloca i64, align 8
  %5 = alloca i64, align 8
  %6 = alloca i64, align 8
  %7 = alloca i64, align 8
  store i64 %0, i64* %2, align 8
  store i64 0, i64* %3, align 8
  store i64 0, i64* %4, align 8
  br label %8

8:                                                ; preds = %23, %1
  %9 = load i64, i64* %4, align 8
  %10 = load i64, i64* %2, align 8
  %11 = icmp slt i64 %9, %10
  br i1 %11, label %12, label %26

12:                                               ; preds = %8
  %13 = load i64, i64* %4, align 8
  %14 = mul nsw i64 %13, 2
  store i64 %14, i64* %5, align 8
  %15 = load i64, i64* %5, align 8
  %16 = add nsw i64 %15, 1
  store i64 %16, i64* %6, align 8
  %17 = load i64, i64* %5, align 8
  %18 = load i64, i64* %6, align 8
  %19 = add nsw i64 %17, %18
  store i64 %19, i64* %7, align 8
  %20 = load i64, i64* %7, align 8
  %21 = load i64, i64* %3, align 8
  %22 = add nsw i64 %21, %20
  store i64 %22, i64* %3, align 8
  br label %23

23:                                               ; preds = %12
  %24 = load i64, i64* %4, align 8
  %25 = add nsw i64 %24, 1
  store i64 %25, i64* %4, align 8
  br label %8, !llvm.loop !6

26:                                               ; preds = %8
  %27 = load i64, i64* %3, align 8
  ret i64 %27
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i64, align 8
  %3 = alloca i64, align 8
  %4 = alloca i64, align 8
  store i32 0, i32* %1, align 4
  store i64 100000000, i64* %2, align 8
  store i64 0, i64* %3, align 8
  store i64 1, i64* %4, align 8
  br label %5

5:                                                ; preds = %11, %0
  %6 = load i64, i64* %4, align 8
  %7 = icmp slt i64 %6, 100
  br i1 %7, label %8, label %14

8:                                                ; preds = %5
  %9 = load i64, i64* %2, align 8
  %10 = call i64 @compute(i64 noundef %9)
  store i64 %10, i64* %3, align 8
  br label %11

11:                                               ; preds = %8
  %12 = load i64, i64* %4, align 8
  %13 = add nsw i64 %12, 1
  store i64 %13, i64* %4, align 8
  br label %5, !llvm.loop !8

14:                                               ; preds = %5
  %15 = load i64, i64* %3, align 8
  %16 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([14 x i8], [14 x i8]* @.str, i64 0, i64 0), i64 noundef %15)
  ret i32 0
}

declare i32 @printf(i8* noundef, ...) #1

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 1}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"Ubuntu clang version 14.0.0-1ubuntu1.1"}
!6 = distinct !{!6, !7}
!7 = !{!"llvm.loop.mustprogress"}
!8 = distinct !{!8, !7}
