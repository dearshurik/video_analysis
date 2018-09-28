#ifndef SCENEINDEXIMPL_H
#define SCENEINDEXIMPL_H

#include <memory>

class VideoDecoder;

class SceneIndexImpl {
public:
    SceneIndexImpl(char* filename);
    SceneIndexImpl(const SceneIndexImpl& orig) = delete;
    virtual ~SceneIndexImpl();
private:
    std::unique_ptr<VideoDecoder> videoDec;

};

#endif /* SCENEINDEXIMPL_H */

