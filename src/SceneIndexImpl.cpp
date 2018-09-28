#include "SceneIndexImpl.h"

SceneIndexImpl::SceneIndexImpl(char* filename)
    : std::make_unique<VideoDecoder>(filename)
{
}

SceneIndexImpl::~SceneIndexImpl() {
}

