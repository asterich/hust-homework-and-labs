; ModuleID = 'loop_slow.c'
source_filename = "loop_slow.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [14 x i8] c"Result: %lld\0A\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i64 @compute(i64 noundef %0, i64 noundef %1) #0 {
  %3 = alloca i64, align 8
  %4 = alloca i64, align 8
  %5 = alloca i64, align 8
  store i64 %0, i64* %3, align 8
  store i64 %1, i64* %4, align 8
  store i64 0, i64* %5, align 8
  br label %6

6:                                                ; preds = %27, %2
  %7 = load i64, i64* %3, align 8
  %8 = load i64, i64* %4, align 8
  %9 = icmp slt i64 %7, %8
  br i1 %9, label %10, label %28

10:                                               ; preds = %6
  %11 = load i64, i64* %3, align 8
  %12 = srem i64 %11, 2
  %13 = icmp eq i64 %12, 0
  br i1 %13, label %14, label %20

14:                                               ; preds = %10
  %15 = load i64, i64* %3, align 8
  %16 = load i64, i64* %5, align 8
  %17 = add nsw i64 %16, %15
  store i64 %17, i64* %5, align 8
  %18 = load i64, i64* %3, align 8
  %19 = add nsw i64 %18, 2
  store i64 %19, i64* %3, align 8
  br label %27

20:                                               ; preds = %10
  %21 = load i64, i64* %3, align 8
  %22 = mul nsw i64 %21, 2
  %23 = load i64, i64* %5, align 8
  %24 = add nsw i64 %23, %22
  store i64 %24, i64* %5, align 8
  %25 = load i64, i64* %3, align 8
  %26 = add nsw i64 %25, 3
  store i64 %26, i64* %3, align 8
  br label %27

27:                                               ; preds = %20, %14
  br label %6, !llvm.loop !6

28:                                               ; preds = %6
  %29 = load i64, i64* %5, align 8
  ret i64 %29
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i64, align 8
  %3 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  store i64 0, i64* %2, align 8
  store i32 1, i32* %3, align 4
  br label %4

4:                                                ; preds = %9, %0
  %5 = load i32, i32* %3, align 4
  %6 = icmp slt i32 %5, 100
  br i1 %6, label %7, label %12

7:                                                ; preds = %4
  %8 = call i64 @compute(i64 noundef 5, i64 noundef 100000005)
  store i64 %8, i64* %2, align 8
  br label %9

9:                                                ; preds = %7
  %10 = load i32, i32* %3, align 4
  %11 = add nsw i32 %10, 1
  store i32 %11, i32* %3, align 4
  br label %4, !llvm.loop !8

12:                                               ; preds = %4
  %13 = load i64, i64* %2, align 8
  %14 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([14 x i8], [14 x i8]* @.str, i64 0, i64 0), i64 noundef %13)
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
