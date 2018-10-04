#include <thread>
#include "SceneIndexImpl.h"
#include <SceneIndex.h>

SceneIndex::SceneIndex(const char* filename, int picW, int picH, ImageCallback& sc) 
    : implPtr(std::make_unique<SceneIndexImpl>(filename, picW, picH, sc))
{
}

SceneIndex::~SceneIndex() {
}

bool SceneIndex::run() {
    std::thread th{[](auto ptr) {
        ptr->run();
    }, std::move(implPtr)};
    th.detach();
}



