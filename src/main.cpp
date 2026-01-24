#pragma warning(disable : 4819)
// 解决 VS Code IntelliSense 与 MSVC 头文件版本不兼容的问题 (修复 error STL1000)
#define _ALLOW_COMPILER_AND_STL_VERSION_MISMATCH

#include "math_utils.h" // 引入自定义头文件
#include <iostream>
#include <windows.h> // 引入 Windows API 头文件

int main() {
  // 设置控制台输入输出编码为 UTF-8
  SetConsoleOutputCP(65001);
  SetConsoleCP(65001);

  printMessage(); // 调用自定义函数
  std::cout << "5 + 3 = " << add(5, 3) << std::endl;

  std::cout << "Hello, world!\n";
  std::cout << "请输入一个数字，然后按回车: ";
  int x;
  if (std::cin >> x) {
    std::cout << "你输入的数字是: " << x << "，它的平方是: " << (x * x) << "\n";
  } else {
    std::cout << "未能读取数字225。\n";
  }
  return 0;
}
