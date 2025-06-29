  #!/bin/bash

#make clean（清除上一次的评测程序）
cd flex

rm lex.yy.c > /dev/null 2>&1
rm lex.yy.cc > /dev/null 2>&1  

#新建文本，准备存放程序输出结果
touch tokens.txt

#新建文本，准备存放错误信息	         
touch error.txt		

#读取键盘输入到typ中         
read -p '' case
	         
flex -+ sysy.l > error.txt 2>&1	         
#用flex编译源文件，保存错误信息

#检查是否成功生成
if [ ! -f "lex.yy.cc" ];then	         
echo "所需c文件:lex.yy.cc 不存在，编译未成功，请检查源程序的格式。"
echo "下面是错误信息："
cat error.txt
else
#生成最终的可执行程序文件
g++ -o scanner lex.yy.cc        
#执行最终生成的程序
./scanner ../test_cases/case_$case.c 
											
fi
