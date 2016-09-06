#pragma once
/************

ui部分：
1 添加音效（僵尸啃食 子弹 食人花 选择卡片）medium
2 添加音乐 medium
3 鸣谢菜单 easy
4 帮助窗口 easy
5 选项菜单（）
	回到主菜单：	emit signal PlayingInterface::gameReturn() --- signal Mainwindow::gameReturn()&& GameConsole timer close
	重新开始：	emit signal XXX --- signal MainWindow::resetEverything()
6 更改用户名称功能
	PlayingInterface 添加 “xxx的房屋”
游戏逻辑
2 读取存档

特殊
（随机触发）
（胜负判定逻辑重写）
（特殊场景前的开场动画）
1 植物隐形模式
2 无限模式
3 植物无损伤模式

************/