#include "../../../../../../Library/Android/sdk/ndk-bundle/platforms/android-14/arch-mips/usr/include/stdio.h"
#include "../../../../../../Library/Android/sdk/ndk-bundle/platforms/android-14/arch-mips/usr/include/jni.h"
#include "../../../../../../Library/Android/sdk/ndk-bundle/platforms/android-14/arch-mips/usr/include/android/log.h"
#include "../../../../../../Library/Android/sdk/ndk-bundle/platforms/android-14/arch-mips/usr/include/stdlib.h"
#include "md5.h"
#include "../../../../../../Library/Android/sdk/ndk-bundle/platforms/android-14/arch-mips/usr/include/string.h"

#define LOG    "-----wang.lichen" // 这个是自定义的LOG的标识
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO,LOG, __VA_ARGS__))


char* getAscii(char* chs,int len){
//用于接收到的串转换成要用的十六进制串返回主窗口调用
    char hex[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8','9', 'A', 'B', 'C', 'D', 'E', 'F'};

    char *ascii = (char*)calloc ( len * 3 + 1, sizeof(char) );// calloc ascii

    int i = 0;
    while( i < len )
    {
        int b= chs[i] & 0x000000ff;
        ascii[i*2] = hex[b/16] ;
        ascii[i*2+1] = hex[b%16] ;
        ++i;
    }
    return ascii;                    // ascii 返回之前未释放
}

//C字符串转java字符串
jstring strToJstring(JNIEnv* env, const char* pStr)
{
    int        strLen    = strlen(pStr);
    jclass     jstrObj   = (*env)->FindClass(env, "java/lang/String");
    jmethodID  methodId  = (*env)->GetMethodID(env, jstrObj, "<init>", "([BLjava/lang/String;)V");
    jbyteArray byteArray = (*env)->NewByteArray(env, strLen);
    jstring    encode    = (*env)->NewStringUTF(env, "utf-8");
    (*env)->SetByteArrayRegion(env, byteArray, 0, strLen, (jbyte*)pStr);
    return (jstring)(*env)->NewObject(env, jstrObj, methodId, byteArray, encode);
}

jstring stoJstring(JNIEnv* env, const char* pat)
{
    jclass strClass = (*env)->FindClass(env,"Ljava/lang/String;");
    jmethodID ctorID = (*env)->GetMethodID(env,strClass, "<init>", "([BLjava/lang/String;)V");
    jbyteArray bytes = (*env)->NewByteArray(env,strlen(pat));
    (*env)->SetByteArrayRegion(env,bytes, 0, strlen(pat), (jbyte*)pat);
    jstring encoding = (*env)->NewStringUTF(env,"utf-8");
    return (jstring)(*env)->NewObject(strClass, ctorID, bytes, encoding);
}

jstring   CharTojstring(JNIEnv*   env,   char*   str)
{
    jsize   len   =   strlen(str);
    jclass   clsstring   =   (*env)->FindClass(env, "java/lang/String");
    jstring   strencode   =   (*env)->NewStringUTF(env,"utf-8");
    jmethodID   mid   =   (*env)->GetMethodID(env,clsstring,   "<init>",   "([BLjava/lang/String;)V");
    jbyteArray   barr   =   (*env)-> NewByteArray(env,len);

    (*env)-> SetByteArrayRegion(env,barr,0,len,(jbyte*)str);
    return (jstring)(*env)-> NewObject(env,clsstring,mid,barr,strencode);
}




//JNIEXPORT void JNICALL
//Java_com_gin_hellojni_MainActivity_accessJavaRandomNumberMethod(JNIEnv *env, jobject jobj) {
//
//    // 得到jclass
//    jclass jclazz = (*env)->GetObjectClass(env, jobj);
//    // 得到方法ID
//    jmethodID jmtdId = (*env)->GetMethodID(env, jclazz, "getRandomNumber", "(I)I");
//    // 调用方法
//    jint jRandomNum = (*env)->CallIntMethod(env, jobj, jmtdId, 10);
//    // 打印
//    LOGI( "--得到java方法的随机数：%d\n", jRandomNum);
//
//}

//JNIEXPORT jstring JNICALL
//Java_com_gin_hellojni_MainActivity_stringFromJNI(
//        JNIEnv *env,
//        jobject jobj/* this */) {
//
//    int width = 10;
//    int height = 20;
//    LOGI("长和宽分别为 %d ,%d ", width, height);
//
//
//    jstring hello = "Hello from C++";
//
//    return (*env)->NewStringUTF(env, hello);
//}
//
//jstring   CharTojstring2(JNIEnv*   env,   char*   str)
//{
//    jsize   len   =   strlen(str);
//    jclass   clsstring   =   (*env)->FindClass(env, "java/lang/String");
//    jstring   strencode   =   (*env)->NewStringUTF(env,"utf-8");
//    jmethodID   mid   =   (*env)->GetMethodID(env,clsstring,   "<init>",   "([BLjava/lang/String;)V");
//    jbyteArray   barr   =   (*env)-> NewByteArray(env,len);
//    (*env)-> SetByteArrayRegion(env,barr,0,len,(jbyte*)str);
//
//    return (jstring)(*env)-> NewObject(env,clsstring,mid,barr,strencode);
//}

JNIEXPORT jstring JNICALL
Java_com_gin_lib_tools_StrUtils_getMD5(JNIEnv *env, jobject instance, jstring input) {

    char* pass = "helloworld!";//将传进来的字符串拼接上自定义的字符 MD5加密
//    int i;
    char* before = (*env)->GetStringUTFChars(env,input,0);

    unsigned char decrypt[16];
    strcat(before,pass);

//    LOGI("拼接后:%s\n", before);
    MD5_CTX md5;
    MD5Init(&md5);
    MD5Update(&md5,before,strlen(before));

    (*env)->GetStringUTFChars(env, input, before);

    MD5Final(&md5,decrypt);
//    LOGI("加密前:%s\n加密后:", before);
//
//    for(i=0;i<16;i++)
//    {
//        LOGI("%02x",decrypt[i]);
//    }
    char* d =getAscii(decrypt,16);
    jstring result;
    puts(d);
    result=(*env)->NewStringUTF(env,d);
    
    return result;
}