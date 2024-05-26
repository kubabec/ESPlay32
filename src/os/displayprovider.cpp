#include "os/displayprovider.hpp"

#ifndef EMULATOR
    // Console code

    DisplayProvider::DisplayProvider(){
        tftDisplay.init();
        tftDisplay.setRotation(1);

        // Initialize screen with BLACK color
        tftDisplay.fillScreen(TFT_BLACK);
    }

    void DisplayProvider::setTextSize(uint8_t s){
        tftDisplay.setTextSize(s);
    }

    void DisplayProvider::setTextFont(uint8_t f){
        tftDisplay.setTextFont(f);
    }

    void DisplayProvider::setTextColor(int c, int b){
        tftDisplay.setTextColor(c, b);
    }
    void DisplayProvider::setTextColor(int c)
    {
        tftDisplay.setTextColor(c);
    }

    void DisplayProvider::fillScreen(uint32_t color){
        //tftDisplay.fillScreen(TFT_BLACK);
        tftDisplay.fillRect(
            currentAppDisplayArea.x,
            currentAppDisplayArea.y,
            currentAppDisplayArea.w,
            currentAppDisplayArea.h,
            color
        );
    }

    int16_t DisplayProvider::drawString(const String& string, int32_t poX, int32_t poY){
        if(!isOverlayMode){
            poY += currentAppDisplayArea.y;
            poX += currentAppDisplayArea.x;
        }
        return tftDisplay.drawString(string, poX, poY);
        return 0;
    }

    void DisplayProvider::drawLine(int32_t xs, int32_t ys, int32_t xe, int32_t ye, uint32_t color){
        tftDisplay.drawLine(
            currentAppDisplayArea.x + xs,
            currentAppDisplayArea.y + ys,
            currentAppDisplayArea.x + xe,
            currentAppDisplayArea.y + ye,
            color
        );
    }

    void DisplayProvider::fillRect(int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color){
        if(!isOverlayMode){
            x += currentAppDisplayArea.x;
            y += currentAppDisplayArea.y;
        }
        tftDisplay.fillRect(x, y, w, h, color);
    }

    void DisplayProvider::fillCircle(int32_t x, int32_t y, int32_t r, uint32_t color)
    {
        if(!isOverlayMode){
            x += currentAppDisplayArea.x;
            y += currentAppDisplayArea.y;
        }
        tftDisplay.fillCircle(x, y, r, color);
    }

    void DisplayProvider::setAppDisplayArea(AppDisplayArea displayArea)
    {
        currentAppDisplayArea = displayArea;
        Serial.println("Display Area: x:" + String(currentAppDisplayArea.x) + ", y:" + String(currentAppDisplayArea.y) + ", w:" + String(currentAppDisplayArea.w) + ", h:" + String(currentAppDisplayArea.h));
    }

    void DisplayProvider::setOverlayMode(bool isOverlay)
    {
        isOverlayMode = isOverlay;
    }


    void DisplayProvider::loadFont(const uint8_t array[])
    {
        tftDisplay.loadFont(array);
    }


#ifndef EMULATOR
        TFT_eSPI* DisplayProvider::tftDirectAccess()
        {
            return &tftDisplay;
        }
#endif


#else
    // Emulator code

    #include "displayprovider.hpp"

    DisplayProvider::DisplayProvider()
    {
        //sceneData = new QPixmap(480, 320);//(480, 320, QImage::Format_RGB32);
    }

    void DisplayProvider::generateScene()
    {
        sceneData = new QPixmap(480, 320);//(480, 320, QImage::Format_RGB32);
    }



    QPixmap *DisplayProvider::getSceneDataPtr()
    {
        return sceneData;
    }

    void DisplayProvider::setTextSize(uint8_t s){
        //tftDisplay.setTextSize(s);
        fontSize = s;
    }

    void DisplayProvider::setTextFont(uint8_t f){
        //tftDisplay.setTextFont(f);
        fontStyle = f;
    }

    void DisplayProvider::setTextColor(int c, int b){
        //tftDisplay.setTextColor(c, b);
        color = c;
        colorBg = b;
    }
    void DisplayProvider::setTextColor(int c)
    {
        //tftDisplay.setTextColor(c);
        color = c;
    }

    void DisplayProvider::fillScreen(uint32_t color){
        //tftDisplay.fillScreen(TFT_BLACK);
    //    tftDisplay.fillRect(
    //        currentAppDisplayArea.x,
    //        currentAppDisplayArea.y,
    //        currentAppDisplayArea.w,
    //        currentAppDisplayArea.h,
    //        color
    //    );
        QPainter painter(sceneData);

        painter.setRenderHints(QPainter::Antialiasing );

        QPainterPath path;
        path.addRoundedRect(QRectF(currentAppDisplayArea.x,
                                           currentAppDisplayArea.y,
                                           currentAppDisplayArea.w,
                                           currentAppDisplayArea.h), 0, 0);
        QPen pen(QBrush(color), 0);
        painter.setPen(pen);
        painter.fillPath(path, QBrush(color));
        painter.drawPath(path);
    }

    int16_t DisplayProvider::drawString(const String& string, int32_t poX, int32_t poY){
        if(!isOverlayMode){
            poY += currentAppDisplayArea.y;
            poX += currentAppDisplayArea.x;
        }
        //return tftDisplay.drawString(string, poX, poY);
        fillRect(poX, poY, string.length()*fontSize*13, 20*fontSize, colorBg);


        QPainter painter(sceneData);

        painter.setRenderHints(QPainter::Antialiasing );
        QPen pen;
        pen.setColor(color);
        QFont font;
        font.setPointSize(fontSize*20);


        painter.setFont(font);
        painter.setPen(pen);

        painter.drawText(poX, poY+17, string);


    }

    void DisplayProvider::drawLine(int32_t xs, int32_t ys, int32_t xe, int32_t ye, uint32_t color){
    //    tftDisplay.drawLine(
    //        currentAppDisplayArea.x + xs,
    //        currentAppDisplayArea.y + ys,
    //        currentAppDisplayArea.x + xe,
    //        currentAppDisplayArea.y + ye,
    //        color
    //    );

        QPainter painter(sceneData);

        painter.setRenderHints(QPainter::Antialiasing );
        QPen pen;
        pen.setColor(color);
        painter.setPen(pen);

        painter.drawLine(currentAppDisplayArea.x + xs,
                                 currentAppDisplayArea.y + ys,
                                 currentAppDisplayArea.x + xe,
                                 currentAppDisplayArea.y + ye);
    }

    void DisplayProvider::fillRect(int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color){
        if(!isOverlayMode){
            x += currentAppDisplayArea.x;
            y += currentAppDisplayArea.y;
        }
    //    tftDisplay.fillRect(x, y, w, h, color);

        QPainter painter(sceneData);

        painter.setRenderHints(QPainter::Antialiasing );

        QPainterPath path;
        path.addRoundedRect(QRectF(x, y, w, h), 0, 0);
        QPen pen( QBrush(color), 0);
        painter.setPen(pen);
        painter.fillPath(path, QBrush(color));
        painter.drawPath(path);
    }

    void DisplayProvider::fillCircle(int32_t x, int32_t y, int32_t r, uint32_t color)
    {
        if(!isOverlayMode){
            x += currentAppDisplayArea.x;
            y += currentAppDisplayArea.y;
        }
        //tftDisplay.fillCircle(x, y, r, color);
        QPainter painter(sceneData);
        QPen pen;
        QBrush brush;
        brush.setColor(color);
        brush.setStyle(Qt::SolidPattern);
        painter.setBrush(brush);
        painter.setPen(pen);
        //
        painter.setRenderHints(QPainter::Antialiasing );

        painter.drawEllipse(x-r, y-r, 2*r, 2*r);

        painter.end();
    }

    void DisplayProvider::setAppDisplayArea(AppDisplayArea displayArea)
    {
        currentAppDisplayArea = displayArea;
        //Serial.println("Display Area: x:" + String(currentAppDisplayArea.x) + ", y:" + String(currentAppDisplayArea.y) + ", w:" + String(currentAppDisplayArea.w) + ", h:" + String(currentAppDisplayArea.h));
    }

    void DisplayProvider::setOverlayMode(bool isOverlay)
    {
        isOverlayMode = isOverlay;
    }


#endif
