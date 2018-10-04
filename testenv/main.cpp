#include <cstdlib>

#include <iostream>
#include <Callback.h>
#include <SceneIndex.h>
#include <VideoDec.h>

class CustonSceneIdx : public ImageCallback 
{
public:
    CustonSceneIdx() : isFinish(false), num(0) {}
    ~CustonSceneIdx() {}

    virtual void putImage(uint8_t* picData, size_t picSize, double timestamp)
    {
        std::string filename = "scene" + std::to_string((int)(timestamp*1000)) + ".bmp";
        FILE *f = fopen(filename.c_str(), "wb");
        fwrite(picData, 1, picSize, f);
        fclose(f);        
    }
    
    virtual void finishMsg() {
        isFinish = true;
    }
    
    bool finishGet() { return isFinish; }
    void finishClear() { isFinish = false; }
    
private:
    bool isFinish; 
    int num;
};

void runScene(CustonSceneIdx& sc) {
    SceneIndex scImpl("/home/kuznetsov/video/5926011.mp4", 320, 240, sc);

    scImpl.run();
}

void runVideo(CustonSceneIdx& sc) {
    VideoDec dec("/home/kuznetsov/video/5926011.mp4", 320, 240, sc);
    dec.setInterval(60.04, 0);
    dec.run();
}

int main(int argc, char** argv) {
    CustonSceneIdx scIdx;
    /*runScene(scIdx);
    while(!scIdx.finishGet());*/
    
    scIdx.finishClear();
    runVideo(scIdx);
    while(!scIdx.finishGet());
    return 0;
}
        
