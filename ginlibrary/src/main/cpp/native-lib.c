#include "stdio.h"
#include "jni.h"
#include "android/log.h"
#include "stdlib.h"
#include "md5.h"

#define LOG    "-----wang.lichen" // 这个是自定义的LOG的标识
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO,LOG, __VA_ARGS__))

#define SIZE 1024

char* getAscii(char* chs,int len){
//用于接收到的串转换成要用的十六进制串返回主窗口调用
    char hex[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

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


JNIEXPORT jstring JNICALL
Java_com_gin_lib_tools_StrUtils_getMD5(JNIEnv *env, jobject instance, jstring input) {

    char *pass = "helloworld!";//将传进来的字符串拼接上自定义的字符 MD5加密
    const char *before = (*env)->GetStringUTFChars(env, input, 0);
    char *newChar = (char *) calloc(strlen(pass) + strlen(before) + 1, sizeof(char));// calloc ascii
    strcpy(newChar, (*env)->GetStringUTFChars(env, input, 0));
    strcat(newChar, pass);

    LOGI("....newChar.....%s", newChar);

    unsigned char decrypt[16] = {0};
    MD5_CTX md5 = {0};
    MD5Init(&md5);
    MD5Update(&md5, newChar, strlen(newChar));
    MD5Final(&md5, decrypt);

    (*env)->ReleaseStringUTFChars(env, input, newChar);//释放

    int i = 0;
    char szMd5[32] = {0};
    for (i = 0; i < 16; i++) {
        sprintf(szMd5, "%s%02x", szMd5, decrypt[i]);
    }

    jstring result;
    result = (*env)->NewStringUTF(env, szMd5);

    return result;
}

JNIEXPORT jobject JNICALL
Java_com_gin_lib_tools_StrUtils_openFileFromC(JNIEnv *env, jobject instance, jstring path_) {
    const char *path = (*env)->GetStringUTFChars(env, path_, 0);


    (*env)->ReleaseStringUTFChars(env, path_, path);
}

JNIEXPORT jint JNICALL
Java_com_gin_lib_tools_StrUtils_copeFile(JNIEnv *env, jobject instance, jstring oldPath_, jstring newPath_) {
    const char *oldPath = (*env)->GetStringUTFChars(env, oldPath_, 0);
    const char *newPath = (*env)->GetStringUTFChars(env, newPath_, 0);

    LOGI("打开.....%s", oldPath);
    LOGI("写入.....%s", newPath);
    // 打开文件
    FILE *fp_read = fopen(oldPath, "rb");
    FILE *fp_write = fopen(newPath, "wb");

    if (fp_read == NULL) {
        LOGI("打开文件失败.....");
        return 0;
    }

    // 先读取再写入
    int buffer[SIZE]; // 数据缓冲区
    int read_n = 0, write_n; // 每次读取数据的长度


    while ((read_n = fread(buffer, sizeof(int), SIZE, fp_read)) > 0) {
        write_n = fwrite(buffer, sizeof(int), read_n, fp_write);
        if (write_n != read_n) {
            LOGI("打开文件失败.....write error\n");
//            system("pause");
            exit(-1);
        }
    }

    // 关闭流
    fclose(fp_write);
    fclose(fp_read);

    LOGI("-------关闭--读取结束。。。。。。");
    // TODO

    (*env)->ReleaseStringUTFChars(env, oldPath_, oldPath);
    (*env)->ReleaseStringUTFChars(env, newPath_, newPath);
    return 1;
}