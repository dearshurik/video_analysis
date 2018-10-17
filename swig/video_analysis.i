
%module videoanalysis

%include "stdint.i"

/*
namespace VideoAnalysis {
%newobject AudioDec::AudioDec(const char* AudioCallback& );
%newobject SceneIndex::SceneIndex(const char*, int , int , ImageCallback& );
%newobject VideoDec::VideoDec(const char*, int , int , ImageCallback& );
}
*/


%{
 #include <Callback.h>
 #include <AudioDec.h>
 #include <VideoDec.h>
 #include <SceneIndex.h> 
%}
 
%include <Config.h>
%include <Callback.h>
%include <AudioDec.h>
%include <VideoDec.h>
%include <SceneIndex.h>

