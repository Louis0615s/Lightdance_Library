# compile
```bash
# 編譯 OFController.cpp
g++ -o OFController.o -I./include -c ./src/OFController.cpp

# 編譯 LEDController.cpp
g++ -o LEDController.o -I./include -c ./src/LEDController.cpp

# 編譯 AllMain.cpp，連結 LEDController.o 和 OFController.o，使用 lws2811 库，生成可執行文件 AllMain
g++ ./src/AllMain.cpp LEDController.o OFController.o -lws2811 -o AllMain

# 以超級用戶權限執行 AllMain
sudo ./AllMain

# 更新rpi的library，注意要在Lightdance_Library底下執行
git pull origin main
