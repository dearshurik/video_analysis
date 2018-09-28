#include "FilterChain.h"
#include "Frame.h"

FilterChain::FilterChain(Decoder& dec) 
    : filterGraph(avfilter_graph_alloc(), filterGraphFree)
{
    avfilter_register_all();
    if(!filterGraph)
        return;
     
    createSrcFilter(dec);
    createSinkFilter(dec);
    lastFilter = filterSrc;
}


FilterChain::~FilterChain() {
}

bool FilterChain::createSrcFilter(Decoder& dec) {
    char args[512];
    
    snprintf(args, sizeof(args),
        "video_size=%dx%d:pix_fmt=%d:time_base=%d/%d:pixel_aspect=%d/%d",
        dec->width, dec->height, dec->pix_fmt,
        dec->time_base.num, dec->time_base.den,
        dec->sample_aspect_ratio.num, dec->sample_aspect_ratio.den);
    
    int ret = avfilter_graph_create_filter(&filterSrc, avfilter_get_by_name("buffer"), "in",
                                            args, nullptr, filterGraph.get());
    
    return (ret >= 0);    
}

bool FilterChain::createSinkFilter(Decoder& dec) {
    enum AVPixelFormat pix_fmts[] = { AV_PIX_FMT_GRAY8, AV_PIX_FMT_NONE };
    AVBufferSinkParams *buffersink_params;

    buffersink_params = av_buffersink_params_alloc();
    buffersink_params->pixel_fmts = pix_fmts;
    
    int ret = avfilter_graph_create_filter(&filterSink, avfilter_get_by_name("buffersink"), "out",
                                       NULL, buffersink_params, filterGraph.get());
    av_free(buffersink_params);
    return (ret >= 0);
}

bool FilterChain::add(const char* name, const char* args, void* params) {
    AVFilterContext* flt;
    int ret = avfilter_graph_create_filter(&flt, avfilter_get_by_name(name), NULL,
                                           args, params, filterGraph.get());
    
    if ((ret = avfilter_link(lastFilter, 0, flt, 0)) < 0)
        return false;
    
    lastFilter = flt;
    return true;
}

bool FilterChain::finish() {
    int ret;
    
    if ((ret = avfilter_link(lastFilter, 0, filterSink, 0)) < 0)
        return false;

    if ((ret = avfilter_graph_config(filterGraph.get(), NULL)) < 0)
        return false;    
}

bool FilterChain::pushFrame(Frame& frame) {
    if (av_buffersrc_add_frame_flags(filterSrc, frame, AV_BUFFERSRC_FLAG_KEEP_REF) < 0) 
        return false;
    
    return true; 
}

FiltRes FilterChain::popFrame(Frame& frame) {
    int ret;
    ret = av_buffersink_get_frame(filterSink, frame);
    if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
        return WAIT;
    if (ret < 0)
        return ERROR;

    return COMPLETE;
}

void FilterChain::filterGraphFree(AVFilterGraph *fg) {
    if(fg)
        avfilter_graph_free(&fg);
}


