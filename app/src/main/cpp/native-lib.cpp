#include <jni.h>
#include <string>


float* quantizationTable = new float[256];
float* jcFuncTable = new float[65536];
float* jcFuncTable2 = new float[65536];


void initializeQuantizationTable(){
    for(int i = 0; !(i >> 8); i++){
        quantizationTable[i] = (i + 0.5f)/256.0f;
    }
}

void initializeJcFunc(){
    float a, x, p, q, t;
    int indexUpper;
    for(int i = 0; !(i >> 8); i++){
        indexUpper = i << 8;
        a = quantizationTable[i];
        p = a*a;
        q = (1-a)*(1-a);
        t = 1-2*a;
        for(int j = 0; !(j >> 8); j++){
            x = quantizationTable[j];
            jcFuncTable[indexUpper | j] = p*x/(q-t*x);
        }
    }
}

void initializeJcFunc2(){
    float a, x, p, p1, p2, q, t;
    int indexUpper;
    for(int i = 0; !(i >> 8); i++){
        indexUpper = i << 8;
        a = quantizationTable[i];
        p = a*a;
        q = (1-a)*(1-a);
        t = 1-2*a;
        p1 = p+t;
        p2 = p-t;
        for(int j = 0; !(j >> 7); j++){
            x = quantizationTable[j];
            jcFuncTable2[indexUpper | j] = p1*x/(q+t*(2*x-1));
        }
        for(int j = 128; !(j >> 8); j++){
            x = quantizationTable[j];
            jcFuncTable2[indexUpper | j] = (p2*x+t)/(q-t*(2*x-1));
        }
    }
}

extern "C"
JNIEXPORT void JNICALL

Java_com_folk_folk_AppDelegate_initialize(
        JNIEnv *env,
        jobject /* this */) {
    initializeQuantizationTable();
    initializeJcFunc();
    initializeJcFunc2();
}
