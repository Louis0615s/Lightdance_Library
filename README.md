# compile
```bash

0| directory tree

# directory tree of /Lightdance_Library/Lightdance-PCA

Lightdance_Lightdance/Lightdance-PCA
├── inc
│   ├── Config.h
│   ├── LEDController.h
│   ├── OFController.h
│   ├── clk.h
│   ├── dma.h
│   ├── gpio.h
│   ├── mailbox.h
│   ├── pcm.h
│   ├── pwm.h
│   ├── rpihw.h
│   └── ws2811.h
├── LEDController.o
├── OFController.o
├── out
├── src
│   ├── AllMain.cpp
│   ├── LEDController.cpp
│   ├── LightOff.cpp
│   └── OFController.cpp
└── tree.txt

== For Users ==
1| how to use this code

Only modify the following two files:
a. /inc/Config.h
  Adjust hardware properties including:
  i. number of PCA (which controls OF)
  ii. number of LED on LED-strip
  iii. brightness of OF and LED
  iV. gamma correction of OF and LED
b. /src/AllMain.cpp
  Adjust how OF and LED work including:
  i. color (RGB)
  ii. brightness (0~255)
  iii. time

== For Developers ==
2| compile & execution

# 編譯 OFController.cpp
g++ -o OFController.o -I./include -c ./src/OFController.cpp

# 編譯 LEDController.cpp
g++ -o LEDController.o -I./include -c ./src/LEDController.cpp

# 編譯 AllMain.cpp，連結 LEDController.o 和 OFController.o，使用 lws2811 库，生成可執行文件 AllMain
g++ ./src/AllMain.cpp LEDController.o OFController.o -lws2811 -o AllMain

# 以超級用戶權限執行 AllMain
sudo ./AllMain

3| git version control

# 更新rpi的library，注意要在Lightdance_Library底下執行
git pull origin main

# 將rpi的更新push至github，注意要在Lightdance_Library底下執行 
git add .
git commit -m "<commit message>"
git push

