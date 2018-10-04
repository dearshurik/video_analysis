#ifndef SCENEINDEX_H
#define SCENEINDEX_H

#include <memory>
#include "Callback.h"

class SceneIndexImpl;

class SceneIndex {
public:
	// Create scene detect object 
	// filename - media file name
	// picW, picH - output picture whidth and height
	// sc - callback object
    SceneIndex(const char* filename, int picW, int picH, ImageCallback& sc);
    SceneIndex(const SceneIndex& orig) = delete;
    virtual ~SceneIndex();
    
	// Run scene detector in self thread
    bool run();
private:
    std::unique_ptr<SceneIndexImpl> implPtr;
};

#endif /* SCENEINDEX_H */

