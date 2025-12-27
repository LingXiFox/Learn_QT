# Learn_QT

一个用于学习 Qt Widgets 的小型示例应用，提供文本项的添加、展示与删除（删除前有确认对话框）。

## 功能

- 输入文本并添加到列表
- 选中列表项后删除，删除前弹出确认对话框
- 基于 Qt Widgets + CMake 构建
- 预置 Qt 翻译文件示例 `Learn_QT_yue_CN.ts`

## 环境要求

- CMake 3.16+
- Qt 5 或 Qt 6（Widgets、LinguistTools）
- C++17 编译器

## 构建与运行

```bash
cmake -S . -B build
cmake --build build
```

运行：

```bash
./build/Learn_QT
```

Windows 可执行文件：

```bash
.\build\Learn_QT.exe
```

## 项目结构

- `main.cpp`：应用入口与多语言加载逻辑
- `mainwindow.ui`：主窗口布局（输入框、列表、按钮）
- `untitled.ui`：删除确认对话框布局
- `mainwindow.cpp`：按钮交互与删除确认逻辑

## 许可协议

Apache-2.0，详见 `LICENSE`。
Copyright：@LingXiFox