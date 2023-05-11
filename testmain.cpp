您好，这是 Bing。😊

根据网上搜索结果，您可以使用 Python 的 subprocess 模块来运行外部可执行文件，并与之通信。您可以使用 subprocess.Popen 方法来创建一个子进程，并通过 stdin 和 stdout 管道来发送和接收数据。例如，您可以参考以下代码1：

import subprocess

# 创建一个子进程，运行外部可执行文件
p = subprocess.Popen(["C:\\temp\\calc.exe"], stdin=subprocess.PIPE, stdout=subprocess.PIPE)

# 向子进程的标准输入写入一组数据，例如 "1\n2\n"
p.stdin.write(b"1\n2\n")

# 从子进程的标准输出读取一组数据，例如 "3\n"
output = p.stdout.read()

# 打印输出
print(output)
如果您想要实时地与子进程交互，而不是一次性地发送和接收数据，您可以使用 pexpect 模块2，它可以模拟人类的输入和输出行为。例如，您可以参考以下代码2：

import pexpect

# 创建一个子进程，运行外部可执行文件
p = pexpect.spawn("python test.py")

# 等待子进程打印 "Test Program"
p.expect("Test Program")

# 等待子进程打印 "1 First option, 2 Second Option"
p.expect("1 First option, 2 Second Option")

# 向子进程的标准输入写入 "1"
p.sendline("1")

# 等待子进程打印 "Insert second param: "
p.expect("Insert second param: ")

# 向子进程的标准输入写入 "2"
p.sendline("2")

# 从子进程的标准输出读取一组数据，例如 "1 2"
output = p.readline()

# 打印输出
print(output)
希望这些信息对您有帮助。如果您还有其他问题，请随时提出。