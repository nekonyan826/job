# import subprocess

# # 创建一个子进程，运行外部可执行文件
# p = subprocess.Popen("./test", stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr = subprocess.PIPE, shell = True)

# # 向子进程的标准输入写入一组数据，例如 "1\n2\n"
# p.stdin.write("3\r\n".encode("GBK"))   
# p.stdin.write("4\r\n".encode("GBK"))  
# # p.stdin.close()
# # 从子进程的标准输出读取一组数据，例如 "3\n"
# output = p.stdout.read()
# print(output)
# # p.stdout.close() 

# p.stdin.write("4\r\n".encode("GBK")) 
# # 打印输出
# output = p.stdout.read()
# print(output)
# p.stdout.close() 


import pexpect

# 创建一个子进程，运行外部可执行文件
p = pexpect.spawn("./test")

# 等待子进程打印 "Test Program"
p.expect("ok")

# 等待子进程打印 "1 First option, 2 Second Option"
# p.expect("1 First option, 2 Second Option")

# 向子进程的标准输入写入 "1"
p.sendline("1 2\n")
output = p.readline()
# 打印输出
print(output)
# 等待子进程打印 "Insert second param: "
p.expect("ok")

# 向子进程的标准输入写入 "2"
p.sendline("2\n")

# 从子进程的标准输出读取一组数据，例如 "1 2"
output = p.readline()

# 打印输出
print(output)