#ifndef FILTERCHAIN_H
#define FILTERCHAIN_H

extern "C"{
    #include <libavcodec/avcodec.h>
    #include <libavformat/avformat.h>
    #include <libswscale/swscale.h>
    #include <libavfilter/avfiltergraph.h>
    #include <libavfilter/buffersink.h>
    #include <libavfilter/buffersrc.h>
}

#include <memory>

#include "Decoder.h"
#include "Frame.h"

enum FiltRes
{
    COMPLETE,
    WAIT,
    ERROR
};

class FilterChain {
public:
    FilterChain(Decoder& dec);
    FilterChain(const FilterChain& orig) = delete;
   
    virtual ~FilterChain();
    
    bool add(const char* name, const char* args, void* params = nullptr);
    bool finish();
    
    bool pushFrame(Frame& frame);
    FiltRes popFrame(Frame& frame);

private:
    static void filterGraphFree(AVFilterGraph *fg);

    bool createSrcFilter(Decoder& dec);
    bool createSinkFilter(Decoder& dec);
    
    std::shared_ptr<AVFilterGraph>  filterGraph;
    AVFilterContext*    filterSrc;
    AVFilterContext*    filterSink;
    AVFilterContext*    lastFilter;
};

#endif /* FILTERCHAIN_H */

