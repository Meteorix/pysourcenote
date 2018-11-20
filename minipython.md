MiniPython
===========

自己实现的最小版本python，目前主要用于尝试对象系统。为了简单，基于map实现了PyDictObject，所以用了c++。不过尽量接近cpython的实现，可以一看。后面可能还会扩展，增加gc和更复杂的语法解析。


### Code

[minipython](./minipython)

### Build
```
cd minipython
cmake -G 'Unix Makefiles' -DCMAKE_BUILD_TYPE=Debug .
make
```

### Try it 

```
➜  minipython git:(master) ✗ ./minipython.exe 
***minipython***
>>> a = 1
>>> b = 2
>>> c = a+b
>>> print c
3
>>> x = "hello"
>>> y = "world"
>>> z = x+y
>>> print z
helloworld
>>> __local__
{12416037344: 1
, 12544037731: 2
, 12672038114: 3
, 15360046201: hello
, 15488046584: world
, 15616046971: helloworld
, }
>>> exit
```