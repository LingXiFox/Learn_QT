## [0.1.0] - 2025-12-30
### 新增
- Base64 编码与解码功能。
- Haxi 哈希功能：支持 SHA256 与 FNV1A64（可选启用 MD5）。
- Qt Widgets 图形界面：包含 Base64 与 Haxi 两个分页。
### 说明
- 运行与编译基于 CMake，依赖 Qt Widgets。
- 提供中文翻译资源 `ToolsCpp_zh_CN.ts`。

## [0.1.1] - 2025-12-30
### 新增
- 初步建立中文语言文件（多语言暂未实现）
- 修复哈希编码空字符串的问题，现在哈希编码的输入来自于用户输入
- 修复若干bug
### 说明
- 运行与编译基于 CMake，依赖 Qt Widgets。
- 提供中文翻译资源 `ToolsCpp_zh_CN.ts`。

## [0.2.0] - 2025-12-31
### 新增
- 移除语言配置文件
- 由于新版本openssl不推荐使用MD5加密，当前版本已经禁用MD5,如需启用，请将`mainwindow.cpp`内`item->setEnabled(false);`设置为true
- 为Ncm处理生成框架
### 说明
- 运行与编译基于 CMake，依赖 Qt Widgets。