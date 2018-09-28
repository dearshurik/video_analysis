#ifndef SCENEIDX_H
#define SCENEIDX_H

class SceneIdx {
public:
    virtual void sceneIdx(uint8_t* picData, size_t picSize, int64_t timestamp) = 0;
};


#endif /* SCENEIDX_H */

