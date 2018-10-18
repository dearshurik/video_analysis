
%module(directors="1") videoanalysis

%include "stdint.i"
%include "carrays.i"
%include "arrays_csharp.i"

%apply short OUTPUT[] {short *outSamples}

%{
 #include <Callback.h>
 #include <AudioDec.h>
 #include <VideoDec.h>
 #include <SceneIndex.h> 
%}

%feature("director") AudioCallback;
%feature("director") ImageCallback;

%include <Config.h>
%include <Callback.h>
%include <AudioDec.h>
%include <VideoDec.h>
%include <SceneIndex.h>

