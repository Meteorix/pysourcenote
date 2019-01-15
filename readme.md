Python源码学习笔记
=================

> 刘欣 2018.10.30

最近在学习Python源码，参考《Python源码剖析》这本书。记录此学习笔记，分章节不定期更新，欢迎提PR和Issue : )

- [PyObject对象系统](./object.md)
- [GC垃圾回收机制](./gc.md)
- [最小实现minipython](./minipython.md)
- [Python虚拟机](./vm.md)


### Table of Contents

* [Python总体架构](#python%E6%80%BB%E4%BD%93%E6%9E%B6%E6%9E%84)
* [Python源码结构](#python%E6%BA%90%E7%A0%81%E7%BB%93%E6%9E%84)
* [学习环境](#%E5%AD%A6%E4%B9%A0%E7%8E%AF%E5%A2%83)
* [编译python](#%E7%BC%96%E8%AF%91python)
* [vscode调试](#vscode%E8%B0%83%E8%AF%95)
    * [准备工作](#%E5%87%86%E5%A4%87%E5%B7%A5%E4%BD%9C)
    * [lldb attach 配置](#lldb-attach-%E9%85%8D%E7%BD%AE)
    * [lldb launch 配置](#lldb-launch-%E9%85%8D%E7%BD%AE)


### Python总体架构
![image](./img/arch.png)


### Python源码结构

```
cpython
├── Include     Python提供的所有头文件（著名的Python.h)
├── Lib         Python自带的标准库，python写的
├── Modules     标准库，c写的
├── Parser      语法分析部分
├── Objects     所有的内建对象c实现
├── Python      Compiler和Runtime引擎部分，运行核心所在
├── Mac         Mac平台编译部分
├── PCBuild     Window平台编译部分
...  
```


### 学习环境
*   采用python2.7最新github [cpython代码](https://github.com/python/cpython/tree/2.7)
*   macbook 开发环境 gcc编译
*   vscode + lldb做debugger

### 编译python
参考源码/Mac/README，用gcc编译python
```bash
./configure
make
```
编译出来的是在主目录下的`./python.exe`，不用怀疑，是一个在mac下可以启动的二进制

```bash
➜  cpython git:(2.7) ✗ ./python.exe 
Python 2.7.15+ (heads/2.7:64ffee7, Oct 30 2018, 18:02:37) 
[GCC 4.2.1 Compatible Apple LLVM 10.0.0 (clang-1000.11.45.2)] on darwin
Type "help", "copyright", "credits" or "license" for more information.
>>> 
```

通过第一行输出的``Oct 30 2018, 18:02:37``看出来，就是我们刚刚编译好的python了

### vscode调试

有两种方式通过lldb来调试python: `attach`和`launch`

#### 准备工作
1. vscode安装cpp插件：[vscode-cpptools](https://github.com/Microsoft/vscode-cpptools)
2. 在vscode里打开python源码，新建Debug配置，可能需要新建.vscode目录保存配置文件。如图：

![image](./img/debug_config.png)

#### lldb attach 配置
运行编译的python.exe，launch.json配置文件如下，proceeId修改为python.exe的pid：
```json
        {
            "type": "cppdbg",
            "name": "(lldb) attach",
            "program": "${workspaceFolder}/python.exe",
            "request": "attach",
            "processId": "3917",
            "MIMode": "lldb"
        },
```

#### lldb launch 配置
选择launch方式启动，vscode会启动terminal运行python.exe
```json
    "configurations": [
        {
            "name": "(lldb) Launch",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/python.exe",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "externalConsole": true,
            "MIMode": "lldb"
        }
    ]
```

然后可以通过断点的方式很方便地查看调用栈，配合《源码剖析》看非常有帮助。

如下图，可以看出一个简单的 1+2 c栈真tm深啊

![image](./img/1plus2.png)
