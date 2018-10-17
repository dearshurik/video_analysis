#ifndef CONFIG_H
#define CONFIG_H

#if defined(_WIN32)
    #ifdef CPP_EXPORTS
        #define CPP_API __declspec(dllexport)
    #else
        #define CPP_API __declspec(dllimport)
    #endif
#else
    #if __GNUC__ >= 4
        #define CPP_API __attribute__ ((visibility ("default")))
    #else
        #define CPP_API
    #endif
#endif

#endif // CONFIG_H
