1.Compilor project
这是Lua的编译器，会从lua脚本文件生成中间代码。生成编译器名字为luac,在以下目录：
D:\Work\work_code\GameSDK\External\lua\Lua\Bin
这里面有一个测试文件test.lua:
io.write("Hello World.from lua.\n")
向控制台打印一行字符串
在命令行下输入luac，会提示用法。如下编译test.lua：
luac -o test.out  test.lua
声明的文件名字为test.out,注意必须把-o选项放在输入文件的前面
test.out的使用见DataServer的LuaEngine.cpp/LuaEngine/h

2.Interpretor project
这是Lua的解释器，类似于python/cmd.exe...
3.lua project
编译成静态库