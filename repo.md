# b1957_pre

## Repo简介

Restaurant Layout Advisor是一个C++控制台应用程序，用于计算餐厅的最优桌椅布局。程序根据给定的房间尺寸，自动计算可以放置多少张桌子，并生成可视化的文本布局图。

**主要功能：**
- 根据房间尺寸和家具参数计算最优表格布局
- 支持自定义表格尺寸、椅子尺寸和间距
- 文本图形化显示布局（使用ASCII字符）
- 计算总座位容量

**技术栈：**
- C++ (C++17标准)
- Visual Studio项目
- 控制台应用程序

**项目结构：**
- `RestaurantLayoutAdvisor.cpp`: 主程序文件，包含布局计算和显示逻辑
- `RestaurantLayoutAdvisor.sln`: Visual Studio解决方案文件
- `RestaurantLayoutAdvisor.vcxproj`: Visual Studio项目文件

**核心算法：**
- `calculateTableLayout()`: 计算表格布局，考虑间距和pillar位置
- `printLayout()`: 将布局渲染为文本图形
- `overlapsWithPillar()`: 检查表格位置是否与pillar重叠

## 题目Prompt

Make all tables 4x4 with 4 chairs and add 8x8 pillar in center of room

## PR链接

https://github.com/ncepudlgc/b1957_pre/pull/1
