# C++ 简单示例 (MSVC)

这是一个简单的 C++ 程序。

## 如何运行

检测到您的系统已安装 **Visual Studio 2022 Community**。您可以直接使用配置好的任务来运行。

### 方法 1: 使用 VS Code 任务 (推荐)

1. 按 `Ctrl + Shift + B` (或 **终端** -> **运行生成任务**) 来编译程序。
2. 在终端中运行 `./main.exe`，或者
3. 按 `Ctrl + Shift + P` 输入 "Run Task" 选择 "Run Application"。

### 方法 2: 手动命令行 (Developer Command Prompt)

1. 打开 "Developer Command Prompt for VS 2022"。
2. 导航到此文件夹:
   ```cmd
   cd c:\Users\MECHREVO\Desktop\VSC
   ```
3. 编译:
   ```cmd
   cl /EHsc /utf-8 main.cpp
   ```
4. 运行:
   ```cmd
   main.exe
   ```

程序会输出问候语并提示输入一个数字，然后显示该数字的平方。