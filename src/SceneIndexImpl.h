#ifndef SCENEINDEXIMPL_H
#define SCENEINDEXIMPL_H

#include <memory>
#include "SceneIdx.h"

class Decoder;
class FilterChain;
class Converter;

class SceneIndexImpl {
public:
    SceneIndexImpl(char* filename, int picW, int picH, SceneIdx& sc);
    SceneIndexImpl(const SceneIndexImpl& orig) = delete;
    virtual ~SceneIndexImpl();
    
    bool makeSceneIdx();
    
private:
    std::shared_ptr<Decoder>        videoDec;
    std::unique_ptr<FilterChain>    filterChain;
    std::unique_ptr<Converter>      converter;
    SceneIdx&                       scene;
    int                             picW; 
    int                             picH;
};

#endif /* SCENEINDEXIMPL_H */

