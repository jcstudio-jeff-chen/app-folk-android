#include <jni.h>
#include <string>


float* quantizationTable = new float[256];
float* jcFuncTable = new float[65536];


void initializeQuantizationTable(){
    for(int i = 255; i; i--){
        quantizationTable[i] = (i + 0.5f)/256.0f;
    }
}

void initializeJcFunc(){
    float a, x, p, q, t;
    int indexUpper;
    for(int i = 255; i; i--){
        a = quantizationTable[i];
        indexUpper = i << 8;
        for(int j = 255; j; j--){
            x = quantizationTable[j];
            p = a*a;
            q = (1-a)*(1-a);
            t = 1-2*a;
            jcFuncTable[indexUpper | j] = p*x/(q-t*x);
        }
    }
}



extern "C"
JNIEXPORT jstring JNICALL

Java_com_folk_folk_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
