# ToolsCpp

一个基于 Qt Widgets 的小型工具集合，支持 Base64 编解码、 Haxi 哈希（支持盐值）和Ncm格式转换。

## 功能介绍

- Base64 编码与解码
- Haxi 哈希：SHA256 与 FNV1A64（可选启用 MD5）
- 基于 Qt Widgets + CMake 构建
- 网易云ncm格式转换

## 环境要求

- CMake 3.16+
- Qt 5 或 Qt 6（Widgets、LinguistTools）
- C++17 编译器
- OpenSSL

## 编译步骤

```bash
cmake -S . -B build
cmake --build build
```

## 使用说明

- Base64：输入文本，选择“Base64编码/解码”，点击按钮输出结果
- Haxi：输入文本，选择哈希类型与盐长度，点击按钮输出结果
- 如需启用 MD5，需要在编译时定义 `HAXI_ALLOW_WEAK_HASHES`

## 运行

macOS/Linux：

```bash
./build/ToolsCpp
```

Windows：

```bash
.\build\ToolsCpp.exe
```

## 项目结构

- `main.cpp`：应用入口与多语言加载逻辑
- `mainwindow.ui`：主窗口布局
- `mainwindow.cpp`：主页面逻辑

## 许可协议

Apache-2.0，详见 `LICENSE`。
Copyright：@LingXiFox
⚠️网易云ncm格式属于加密格式，解除仅限于学习，禁止二次分发售卖