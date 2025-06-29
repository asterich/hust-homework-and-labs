#!/bin/bash

apt install bc &> /dev/null

cd src/step1
# if [ -f "codegen" ]; then
#    rm codegen 2>&1 >/dev/null
# fi
touch err.txt
make codegen > err.txt 2>&1 >/dev/null
if [ $? == 0 ]; then 
  chmod +x codegen
  cd ../../llvm_ir
  
  read -p '' case

  irfile=$case
  target=${case/".ll"/".bin"}
  infile=${case/".ll"/".in"}
  asmfile=${case/".ll"/".s"}

  ../src/step1/codegen $irfile
  if [ -f $asmfile ]; then
      # qemu-arm -L /usr/arm-linux-gnueabihf/ -B 0x10000000 "$filename" < "$filename.in" > "$filename.out" 2>/dev/null 
      # arm-linux-gnueabihf-gcc $asmfile ../lib/libsysy.a -o $target -static
      #clang -target riscv64-unknown-elf -march=rv64i2p0 $asmfile ../lib/sylib.c -o $target -fuse-ld=lld
      clang $asmfile -o $target -O0
      # If InFile exists, Redirect and Compare
      if [ $? == 0 ]; then 
          if [ -f $infile ]; then
	            threshold=30.0
              # 使用time命令计时
              output=$( (time ./$target < $infile) 2>&1 )

              # 提取“real”时间
              real_time=$(echo "$output" | grep real | awk '{print $2}' | sed 's/.*m//g' | sed 's/[^0-9.]//g')

              echo $real_time

              # 判断时间是否超过阈值
              if (( $(echo "$real_time > $threshold" |bc -l) )); then
                  echo "运行超时，最大时间限制： $threshold"
              else
                  echo "符合时间限制"
              fi
          else
              threshold=30.0
	            # 使用time命令计时
              output=$( (time  ./$target) 2>&1 )

              # 提取“real”时间
              real_time=$(echo "$output" | grep real | awk '{print $2}' | sed 's/.*m//g' | sed 's/[^0-9.]//g')

              echo $real_time

              # 判断时间是否超过阈值
              if (( $(echo "$real_time > $threshold" |bc -l) )); then
                  echo "运行超时，最大时间限制： $threshold"
              else 
                  echo "符合时间限制"
              fi
          fi
      else
          echo "汇编编译失败！！"
      fi
  else 
    echo "Codegen未生成汇编代码！"
  fi   
else  
    echo "Codegen未编译成功，请排查程序错误！以下是提示信息："
    cat err.txt
fi

