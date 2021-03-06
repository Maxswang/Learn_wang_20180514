#！ /bin/sh
echo "\$#:$#"  # $# 传给脚本的参数个数
echo "\$0:$0"  # $0脚本本身的名字
echo "\$1:$1"  # $1传递给该脚本的第1个参数
echo "\$2:$2"  # $2传递给该shell脚本的第2个参数
echo "\$@:$@"  # $@传给 脚本 的所有参数的列表 
echo "\$*:$*"  # $*以一个单字符串显示所有向脚本传递的参数， 与位置变量不同，参数可超过9个
echo "\$$:$$"  # $$脚本运行的当前进程号
echo "\$?:$?"  # $?命令 执行结果反馈， 0表示成功 其余数字表示 执行不成功
