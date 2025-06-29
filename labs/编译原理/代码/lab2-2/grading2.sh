#!/bin/bash

cd mysolution

chmod +x shell2.sh
./shell2.sh

if [ ! -f "lexer" ];then	         
echo "没有找到词法分析器lexer。"
else


#新建文本，准备存放程序输出结果
touch tokens.txt

#新建文本，准备存放错误信息	         
touch error.txt		

#读取键盘输入到typ中         
read -p '' case
	         

./lexer ../test_cases/case_$case.c > tokens.txt    

#显示程序运行结果
cat tokens.txt											
fi