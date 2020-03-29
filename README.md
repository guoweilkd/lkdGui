# lkdGui

## 1、lkdGui介绍

`lkdGui`是一款为`单色显示屏`制作的图形化界面，lkdGui主要定位于工业控制领域，用于简单漂亮的图形界面设计。它的源代码全部使用c语言编写，符合c99标准。它包含了常用的画图函数如画点、画线、画矩形、文字显示、按钮控件、进度条控件。它使用`窗口`进行统一管理和调度，使得各个应用显示模块之间低耦合，方便应用程序的开发。

### 1.1 目录结构

1. `lkdGui_source`文件夹:它包含了lkdGui的所有源码
    1. `include`文件夹:它包含了Gui所有的`.h`文件。移植时应将此路径加入工程项目。
        1. `lkdGui.h`:此文件里包含所有的Gui函数接口。用户使用Gui函数时应该包含此头文件。
        1. `lkdGuiConfig.h`:此文件用来配置和裁剪Gui.
        1. `lkdGuiTypedef.h`:此文件定义了Gui相关的数据结构，使用者不必看它。
    1. `port`文件夹:它里边包含的是移植相关的文件。
        1. `fontDriver`文件夹:它包含常用的字模库、字库芯片驱动等。使用者可以在这里面加入字体相关的驱动。
        1. `lcdDriverPort`文件夹:它包含常用的液晶驱动。使用者可以在这里面加入液晶相关的驱动。
        1. `lcdDriverPort.c`:Gui的液晶驱动移植接口。用户应该填充里面的相关函数。
        1. `userFontPort.c`:Gui的字体驱动移植接口。用户应该填充里面的相关函数。
        1. `userAppPort.c`:这个输入应用层,里面包含了初始化、窗口管理等函数。永和可以直接在这里面写应用。
    1. `source`文件夹:Gui绘图、窗口管理等相关函数实现源码。

### 1.2 许可证

lkdGui package 遵循 GPLv2 许可，详见 `LICENSE` 文件。

### 1.3 依赖

- None

## 2、如何打开 hello

使用 lkdGui package 需要在 RT-Thread 的包管理器中选择它，具体路径如下：

```
RT-Thread online packages
    peripheral libraries and drivers  --->
        [*] lkdGui a monochrome graphic lirary.  --->
```

然后让 RT-Thread 的包管理器自动更新，或者使用 `pkgs --update` 命令更新包到 BSP 中。

## 3、使用 hello

* 完整的 API 手册可以访问这个[链接](docs/lkdGui使用文档/lkdGui使用文档.md)
* 更多文档位于 [`/docs`](/docs) 下，使用前 **务必查看**

## 4、注意事项


## 5、联系方式 & 感谢

* 维护：guoweilkd
* 主页：https://github.com/guoweilkd/lkdGui
