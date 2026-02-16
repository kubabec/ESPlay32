#include "os/displayprovider.hpp"

#include "os/textures/grass.hpp"


#ifndef EMULATOR
    // Console code

    // Position variables must be global (PNGdec does not handle position coordinates)
    int16_t xpos = 0;
    int16_t ypos = 0;

    
    TFT_eSPI* DisplayProvider::globalPtrTftDisplay;

    int grassW = 40;
    int grassH = 30;

    // TFT_eSPI DisplayProvider::tftDisplay;

    PNG png;

    #define MAX_IMAGE_WIDTH 480 // Sets rendering line buffer lengths, adjust for your images


    void DisplayProvider::pngDraw(PNGDRAW *pDraw) {
        uint16_t lineBuffer[MAX_IMAGE_WIDTH];          // Line buffer for rendering
        uint8_t  maskBuffer[1 + MAX_IMAGE_WIDTH / 8];  // Mask buffer

        png.getLineAsRGB565(pDraw, lineBuffer, PNG_RGB565_BIG_ENDIAN, 0xffffffff);

        if (png.getAlphaMask(pDraw, maskBuffer, 255)) {
            // Note: pushMaskedImage is for pushing to the TFT and will not work pushing into a sprite
            globalPtrTftDisplay->pushMaskedImage(xpos, ypos + pDraw->y, pDraw->iWidth, 1, lineBuffer, maskBuffer);
        }
    }


    void DisplayProvider::displayBallImage(int x, int y)
    {
        xpos = x;
        ypos = y;
        uint16_t pngw = 0, pngh = 0; // To store width and height of image
        int16_t rc = png.openFLASH((uint8_t *)ballPng, sizeof(ballPng), pngDraw);
        
        if (rc == PNG_SUCCESS) {
        //Serial.println("Successfully opened png file");
        pngw = png.getWidth();
        pngh = png.getHeight();
        //Serial.printf("Image metrics: (%d x %d), %d bpp, pixel type: %d\n", pngw, pngh, png.getBpp(), png.getPixelType());
    
        tftDisplay.startWrite();
        uint32_t dt = millis();
        rc = png.decode(NULL, 0);
        tftDisplay.endWrite();
        //Serial.print(millis() - dt); Serial.println("ms");
    //    tft.endWrite();
    
        // png.close(); // Required for files, not needed for FLASH arrays
        }
    }


    void DisplayProvider::displayGrassImage()
    {
        uint16_t pngw = 0, pngh = 0; // To store width and height of image

        while(ypos < 320)
        {

            while(xpos < 480){
                int16_t rc = png.openFLASH((uint8_t *)grass, sizeof(grass), pngDraw);
        
                if (rc == PNG_SUCCESS) {
                //Serial.println("Successfully opened png file");
                pngw = png.getWidth();
                pngh = png.getHeight();
                Serial.printf("Image metrics: (%d x %d), %d bpp, pixel type: %d\n", pngw, pngh, png.getBpp(), png.getPixelType());
            
                tftDisplay.startWrite();
                uint32_t dt = millis();
                rc = png.decode(NULL, 0);
                tftDisplay.endWrite();
                //Serial.print(millis() - dt); Serial.println("ms");
            //    tft.endWrite();
            
                // png.close(); // Required for files, not needed for FLASH arrays
                }

                xpos += grassW;
            }
            xpos = 0;
            ypos += grassH;
            
        }

        xpos = 0;
        ypos = 0;
    }


    DisplayProvider::DisplayProvider(){
        globalPtrTftDisplay = &(this->tftDisplay);
        tftDisplay.init();
        tftDisplay.setRotation(3);

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

    void DisplayProvider::displaySegmentedBg(SegmentedBg& bg) { 

        uint32_t randomColor = random();

        while(bg.isAnySegmentPending()) {
            BgSegmentDetails details = bg.getPendingSegmentDetails();
            xpos = details.x;
            ypos = details.y;
            if(!isOverlayMode){
                xpos += currentAppDisplayArea.x;
                ypos += currentAppDisplayArea.y;
            }
            if(ypos >= 30)
            {
                // /tftDisplay.fillRect(xpos, ypos, 40, 30, randomColor);
                //to do: map texture id to correct array
                int16_t rc = png.openFLASH((uint8_t *)grass, sizeof(grass), pngDraw);


                if (rc == PNG_SUCCESS) {
            
                    tftDisplay.startWrite();
                    uint32_t dt = millis();
                    rc = png.decode(NULL, 0);
                    tftDisplay.endWrite();
            
                // png.close(); // Required for files, not needed for FLASH arrays
                }

            }

            
            bg.goToNextSegment();
        }
        

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
