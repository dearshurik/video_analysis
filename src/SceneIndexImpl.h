#ifndef SCENEINDEXIMPL_H
#define SCENEINDEXIMPL_H

#include <memory>
#include "Callback.h"

class Decoder;
class FilterChain;
class Converter;

class SceneIndexImpl {
public:
    SceneIndexImpl(const char* filename, int picW, int picH, ImageCallback& sc);
    SceneIndexImpl(const SceneIndexImpl& orig) = delete;
    virtual ~SceneIndexImpl();
    
    bool run();
    
private:
    std::shared_ptr<Decoder>        videoDec;
    std::unique_ptr<FilterChain>    filterChain;
    std::unique_ptr<Converter>      converter;
    ImageCallback&                  scene;
    int                             picW; 
    int                             picH;
};

#endif /* SCENEINDEXIMPL_H */

