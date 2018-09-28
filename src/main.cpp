#include <cstdlib>

#include <iostream>
#include "SceneIdx.h"
#include "SceneIndexImpl.h"

const int dst_w = 320;
const int dst_h = 240;

class CustonSceneIdx : public SceneIdx 
{
public:
    CustonSceneIdx() {}
    ~CustonSceneIdx() {}
    virtual void sceneIdx(uint8_t* picData, size_t picSize, int64_t timestamp)
    {
        std::string filename = "scene" + std::to_string(timestamp) + ".bmp";
        FILE *f = fopen(filename.c_str(), "wb");
        fwrite(picData, 1, picSize, f);
        fclose(f);        
    }
};

int main(int argc, char** argv) {
    CustonSceneIdx scIdx;
    SceneIndexImpl scImpl("/home/kuznetsov/video/4308.mp4", dst_w, dst_h, scIdx);
    
    scImpl.makeSceneIdx();
    
    return 0;
}
        