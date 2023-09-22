# QTCourse
一、获取图标（logo）
       推荐常用的网站：

       1）阿里巴巴矢量图标库：https://www.iconfont.cn/

       2）免费logo制作：免费logo在线制作-字体logo-logo设计-U钙网

       得到png或者jpg或者bmp后，进行ico图标转换，网站是：

       比特虫：制作ico图标 | 在线ico图标转换工具 方便制作favicon.ico - 比特虫 - Bitbug.net

二、Qt程序打包
	1.设置qt的安装目录到PC的path中，例如：D:\tools\Qt\6.5.2\mingw_64\bin
	2.把要打包的.exe文件拷贝到单独的文件中，使用Shift+鼠标右键，打开Powershell窗口；
	3.执行windeployqt.exe .\sample6_1.exe ----->这时候可以发布一个绿色版程序
	----------------------- 使用Inno Setup 免费的windows安装程序制作软件 ---------------------------------
	官方下载地址：http://www.jrsoftware.org/isdl.php#stable
	
	点击“Download Sites”可以下载到本地。
	
	可以参考该网址进行打包设置；
	https://subingwen.cn/qt/
	
	