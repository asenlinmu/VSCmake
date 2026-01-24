# C++ CMake 项目模板 (VS Code)

这是一个基于 CMake 和 VS Code 的现代 C++ 项目模板。采用了标准的源文件目录解耦结构，支持跨平台构建。

## 📁 目录结构

```text
VSCmake/
│
├── .vscode/               # VS Code 配置文件 (调试、推荐插件等)
├── src/                   # 源代码目录 (.cpp, .h)
│   ├── main.cpp           # 主程序入口
│   ├── math_utils.cpp     # 示例模块实现
│   └── math_utils.h       # 示例模块头文件
│
├── bin/                   # [自动生成] 编译输出目录 (存放 .exe)
├── build/                 # [自动生成] CMake 构建中间文件
├── CMakeLists.txt         # CMake 构建脚本
└── .gitignore             # Git 忽略配置
```

## 🚀 快速开始

### 1. 环境准备
*   安装 **Visual Studio Code**。
*   安装 C++ 编译器 (Windows 上推荐 **Visual Studio Community** 带 C++ 桌面开发工作负载，或 MinGW)。
*   安装 **CMake** (如果是 Visual Studio 通常已包含)。

### 2. VS Code 插件
打开项目后，VS Code 会提示安装推荐插件 (定义在 `.vscode/extensions.json` 中)，建议全部安装：
*   **C/C++** (Microsoft)
*   **CMake Tools** (Microsoft)

### 3. 编译与运行
本项目完全集成 VS Code 底部状态栏操作：

1.  **选择编译器 (Kit)**：
    *   首次打开时，在底部状态栏左侧选择编译器 (例如 `Visual Studio Community 2022 Release - amd64`)。
    *   如果没弹窗，按 `Ctrl+Shift+P` 输入 `CMake: Select a Kit`。

2.  **构建 (Build)**：
    *   点击底部状态栏的 **⚙️ Build** (齿轮图标)。
    *   或者按下 `F7`。
    *   构建成功后，可执行文件会生成在 `bin/` 目录下。

3.  **运行 (Run)**：
    *   点击底部状态栏的 **▶️ Run** (播放图标)。
    *   或者按下 `Shift + F5`。

4.  **调试 (Debug)**：
    *   点击底部状态栏的 **🐞 Debug** (瓢虫图标)。
    *   或者点击左侧活动栏的“运行与调试”，使用绿色箭头启动。

## ⚠️ 关于中文乱码
本项目已配置为**Windows MSVC 下无乱码模式**：
*   源文件保存为 **UTF-8 (无 BOM)** 格式。
*   `CMakeLists.txt` 中已配置 `/utf-8` 编译参数。
*   如果遇到乱码，请检查右下角文件编码是否正确。

## 📝 开发指南
*   **添加新文件**：直接在 `src/` 目录下创建新的 `.cpp` 或 `.h` 文件，CMake 会自动识别，无需修改配置。
*   **清理构建**：按 `Ctrl+Shift+P` 输入 `CMake: Delete Cache and Reconfigure`。