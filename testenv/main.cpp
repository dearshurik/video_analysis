#include <cstdlib>

#include <iostream>
#include <Callback.h>
#include <SceneIndex.h>
#include <VideoDec.h>
#include <AudioDec.h>

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

class AudioCb : public AudioCallback
{
public:
    AudioCb() : f(NULL), isFinish(false) 
    {
        f = fopen("out.pcm", "wb");
    }
    
    virtual ~AudioCb() {}
    virtual void putSamples(uint8_t ch, int16_t* samples, size_t size, double timestamp)
    {
        if(ch == 0)
            fwrite(samples, size, sizeof(int16_t), f);
    }
    
    virtual void finishMsg()
    {
        fclose(f);
        isFinish = true;
    }
    
    bool finishGet() { return isFinish; }
    void finishClear() { isFinish = false; }
    
private:
    bool isFinish;
    FILE *f;
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

void runAudio(AudioCb& sc) {
    AudioDec dec("/home/kuznetsov/video/test.mp3", sc);
    dec.setInterval(0, 300);
    dec.run();
}

int main(int argc, char** argv) {
    CustonSceneIdx scIdx;
    AudioCb cb;
    /*runScene(scIdx);
    while(!scIdx.finishGet());*/
    
    /*scIdx.finishClear();
    runVideo(scIdx);
    while(!scIdx.finishGet());*/
    runAudio(cb);
    while(!cb.finishGet());
    return 0;
}
        
