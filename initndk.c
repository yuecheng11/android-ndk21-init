/************************************************************************
VisualOn Proprietary
Copyright (c) 2016, VisualOn Incorporated. All Rights Reserved

VisualOn, Inc., USA

All data and information contained in or disclosed by this document are
confidential and proprietary information of VisualOn, and all rights
therein are expressly reserved. By accepting this material, the
recipient agrees that this material and the information contained
therein are held in confidence and in trust. The material may only be
used and/or disclosed as authorized in a license agreement controlling
such use and disclosure.
************************************************************************/
/*******************************************************************************
 *      VisualOn Proprietary.
 *      File:   voMediaNdk.h
 *      Author: Klay
 *      2016-02-24 Create file
 *      For libmediandk.so dynamic loading. NDK API from Android Open 
 *      Source Project. Just using SDK21 or higher SDK level
 *******************************************************************************/
#ifndef __Media_Ndk__H
#define __Media_Ndk__H

#include <media/NdkMediaCodec.h>
#include <media/NdkMediaCrypto.h>
//#include "NdkMediaDrm.h"
#include <media/NdkMediaError.h>
#include <media/NdkMediaFormat.h>
//#include "NdkMediaMuxer.h"
#include "voIndex.h"
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <pthread.h>
#include "voLog.h"
//typedef MediaCodec function pointer
typedef AMediaCodec* (*pf_AMediaCodec_createCodecByName)(const char *name);

typedef AMediaCodec* (*pf_AMediaCodec_createDecoderByType)(const char *mime_type);

typedef AMediaCodec* (*pf_AMediaCodec_createEncoderByType)(const char *mime_type);

typedef media_status_t (*pf_AMediaCodec_configure)(AMediaCodec*,
        const AMediaFormat* format,
        ANativeWindow* surface,
        AMediaCrypto *crypto,
        uint32_t flags);

typedef media_status_t (*pf_AMediaCodec_start)(AMediaCodec*);

typedef media_status_t (*pf_AMediaCodec_stop)(AMediaCodec*);

typedef media_status_t (*pf_AMediaCodec_flush)(AMediaCodec*);

typedef media_status_t (*pf_AMediaCodec_delete)(AMediaCodec*);

typedef AMediaFormat* (*pf_AMediaCodec_getOutputFormat)(AMediaCodec*);

typedef ssize_t (*pf_AMediaCodec_dequeueInputBuffer)(AMediaCodec*,
        int64_t timeoutUs);

typedef uint8_t* (*pf_AMediaCodec_getInputBuffer)(AMediaCodec*,
        size_t idx, size_t *out_size);

typedef media_status_t (*pf_AMediaCodec_queueInputBuffer)(AMediaCodec*,
        size_t idx, off_t offset, size_t size, uint64_t time, uint32_t flags);

typedef media_status_t (*pf_AMediaCodec_queueSecureInputBuffer)(AMediaCodec*,
        size_t idx, off_t offset, AMediaCodecCryptoInfo*, uint64_t time, uint32_t flags);

typedef ssize_t (*pf_AMediaCodec_dequeueOutputBuffer)(AMediaCodec*,
        AMediaCodecBufferInfo *info, int64_t timeoutUs);

typedef uint8_t* (*pf_AMediaCodec_getOutputBuffer)(AMediaCodec*,
        size_t idx, size_t *out_size);

typedef media_status_t (*pf_AMediaCodec_releaseOutputBuffer)(AMediaCodec*,
        size_t idx, bool render);

typedef media_status_t (*pf_AMediaCodec_releaseOutputBufferAtTime)(AMediaCodec *mData,
		size_t idx, int64_t timestampNs);

// typedef MediaFormat function pointer
typedef AMediaFormat *(*pf_AMediaFormat_new)();

typedef media_status_t (*pf_AMediaFormat_delete)(AMediaFormat*);

typedef char* (*pf_AMediaFormat_toString)(AMediaFormat*);

typedef void (*pf_AMediaFormat_setString)(AMediaFormat*,
        const char* name, const char* value);

typedef bool (*pf_AMediaFormat_getString)(AMediaFormat*, const char *name, const char **out);

typedef void (*pf_AMediaFormat_setInt32)(AMediaFormat*,
        const char* name, int32_t value);

typedef bool (*pf_AMediaFormat_getInt32)(AMediaFormat*,
        const char *name, int32_t *out);

typedef void (*pf_AMediaFormat_setBuffer)(AMediaFormat*, const char* name, void* data, size_t size);

// typedef AMediaCrypto function pointer
typedef bool (*pf_AMediaCrypto_isCryptoSchemeSupported)(const AMediaUUID uuid);

typedef bool (*pf_AMediaCrypto_requiresSecureDecoderComponent)(const char *mime);

typedef AMediaCrypto* (*pf_AMediaCrypto_new)(const AMediaUUID uuid, const void *initData, size_t initDataSize);

typedef void (*pf_AMediaCrypto_delete)(AMediaCrypto* crypto);

//typedef AMediaCodecCrytoInfo function pointer
typedef AMediaCodecCryptoInfo* (*pf_AMediaCodecCryptoInfo_new)(
                 int numsubsamples,
                 uint8_t key[16],
                 uint8_t iv[16],
                 cryptoinfo_mode_t mode,
                 size_t *clearbytes,
                 size_t *encryptedbytes);

typedef media_status_t (*pf_AMediaCodecCryptoInfo_delete)(AMediaCodecCryptoInfo*);

typedef size_t (*pf_AMediaCodecCryptoInfo_getNumSubSamples)(AMediaCodecCryptoInfo*);

typedef media_status_t (*pf_AMediaCodecCryptoInfo_getKey)(AMediaCodecCryptoInfo*, uint8_t *dst);

typedef media_status_t (*pf_AMediaCodecCryptoInfo_getIV)(AMediaCodecCryptoInfo*, uint8_t *dst);

typedef cryptoinfo_mode_t (*pf_AMediaCodecCryptoInfo_getMode)(AMediaCodecCryptoInfo*);

typedef media_status_t (*pf_AMediaCodecCryptoInfo_getClearBytes)(AMediaCodecCryptoInfo*, size_t *dst);

typedef media_status_t (*pf_AMediaCodecCryptoInfo_getEncryptedBytes)(AMediaCodecCryptoInfo*, size_t *dst);

//define Ndk Media function list
struct NdkMedia
{
    struct {
        pf_AMediaCodec_createCodecByName                  createCodecByName;
        pf_AMediaCodec_createDecoderByType                createDecoderByType;
        pf_AMediaCodec_createEncoderByType                createEncoderByType;
        pf_AMediaCodec_configure                          configure;
        pf_AMediaCodec_start                              start;
        pf_AMediaCodec_stop                               stop;
        pf_AMediaCodec_flush                              flush;
        pf_AMediaCodec_delete                             mdelete;
        pf_AMediaCodec_getOutputFormat                    getOutputFormat;
        pf_AMediaCodec_dequeueInputBuffer                 dequeueInputBuffer;
        pf_AMediaCodec_getInputBuffer                     getInputBuffer;
        pf_AMediaCodec_queueInputBuffer                   queueInputBuffer;
        pf_AMediaCodec_queueSecureInputBuffer             queueSecureInputBuffer;
        pf_AMediaCodec_dequeueOutputBuffer                dequeueOutputBuffer;
        pf_AMediaCodec_getOutputBuffer                    getOutputBuffer;
        pf_AMediaCodec_releaseOutputBuffer                releaseOutputBuffer;
		pf_AMediaCodec_releaseOutputBufferAtTime          releaseOutputBufferAtTime;
    } AMediaCodec;
    struct {
        pf_AMediaFormat_new       mnew;
        pf_AMediaFormat_delete    mdelete;
        pf_AMediaFormat_toString  toString;
        pf_AMediaFormat_setString setString;
        pf_AMediaFormat_getString getString;
        pf_AMediaFormat_setInt32  setInt32;
        pf_AMediaFormat_getInt32  getInt32;
        pf_AMediaFormat_setBuffer setBuffer;
    } AMediaFormat;
    struct {
        pf_AMediaCrypto_isCryptoSchemeSupported        isCryptoSchemeSupported;
        pf_AMediaCrypto_requiresSecureDecoderComponent requiresSecureDecoderComponent;
        pf_AMediaCrypto_delete                         mdelete;
        pf_AMediaCrypto_new                            mnew;   
    } AMediaCrypto;
    struct {
        pf_AMediaCodecCryptoInfo_new                  cryptoinfo_new;
        pf_AMediaCodecCryptoInfo_delete               crytoinfo_delete;
        pf_AMediaCodecCryptoInfo_getNumSubSamples     getNumSubSamples;
        pf_AMediaCodecCryptoInfo_getKey               getKey;
        pf_AMediaCodecCryptoInfo_getIV                getIV;
        pf_AMediaCodecCryptoInfo_getMode              getMode;
        pf_AMediaCodecCryptoInfo_getClearBytes        getClearBytes;
        pf_AMediaCodecCryptoInfo_getEncryptedBytes    getEncryptedBytes;    
    } CryptoInfo;
};
static struct NdkMedia NdkMedia;

//func table
struct members
{
    const char *name;  //method name
    int offset;   //method offset
    bool critical;  //end flag
};

//init func table for standard api and redefine func
static struct members members[] =
{
#define OFF(x) offsetof(struct NdkMedia, AMediaCodec.x)
    { "AMediaCodec_createCodecByName", OFF(createCodecByName), true },
    { "AMediaCodec_createDecoderByType", OFF(createDecoderByType), true},
    { "AMediaCodec_createEncoderByType", OFF(createEncoderByType), true},
    { "AMediaCodec_configure", OFF(configure), true },
    { "AMediaCodec_start", OFF(start), true },
    { "AMediaCodec_stop", OFF(stop), true },
    { "AMediaCodec_flush", OFF(flush), true },
    { "AMediaCodec_delete", OFF(mdelete), true },
    { "AMediaCodec_getOutputFormat", OFF(getOutputFormat), true },
    { "AMediaCodec_dequeueInputBuffer", OFF(dequeueInputBuffer), true },
    { "AMediaCodec_getInputBuffer", OFF(getInputBuffer), true },
    { "AMediaCodec_queueInputBuffer", OFF(queueInputBuffer), true },
    { "AMediaCodec_queueSecureInputBuffer",OFF(queueSecureInputBuffer), true},
    { "AMediaCodec_dequeueOutputBuffer", OFF(dequeueOutputBuffer), true },
    { "AMediaCodec_getOutputBuffer", OFF(getOutputBuffer), true },
    { "AMediaCodec_releaseOutputBuffer", OFF(releaseOutputBuffer), true },
	{ "AMediaCodec_releaseOutputBufferAtTime", OFF(releaseOutputBufferAtTime), true },
#undef OFF
#define OFF(x) offsetof(struct NdkMedia, AMediaFormat.x)
    { "AMediaFormat_new", OFF(mnew), true },
    { "AMediaFormat_delete", OFF(mdelete), true },
    { "AMediaFormat_toString", OFF(toString),true},
    { "AMediaFormat_setString", OFF(setString), true },
    { "AMediaFormat_getString", OFF(getString),true},
    { "AMediaFormat_setInt32", OFF(setInt32), true },
    { "AMediaFormat_getInt32", OFF(getInt32), true },
    { "AMediaFormat_setBuffer", OFF(setBuffer), true},
#undef OFF
#define OFF(x) offsetof(struct NdkMedia, AMediaCrypto.x)
    { "AMediaCrypto_isCryptoSchemeSupported", OFF(isCryptoSchemeSupported), true},
    { "AMediaCrypto_requiresSecureDecoderComponent", OFF(requiresSecureDecoderComponent), true},
    { "AMediaCrypto_delete", OFF(mdelete), true},
    { "AMediaCrypto_new", OFF(mnew), true},
#undef OFF
#define OFF(x) offsetof(struct NdkMedia, CryptoInfo.x)
    { "AMediaCodecCryptoInfo_new", OFF(cryptoinfo_new),true},
    { "AMediaCodecCryptoInfo_delete", OFF(crytoinfo_delete), true},
    { "AMediaCodecCryptoInfo_getNumSubSamples", OFF(getNumSubSamples), true},
    { "AMediaCodecCryptoInfo_getKey", OFF(getKey), true},
    { "AMediaCodecCryptoInfo_getIV", OFF(getIV), true},
    { "AMediaCodecCryptoInfo_getMode", OFF(getMode), true},
    { "AMediaCodecCryptoInfo_getClearBytes", OFF(getClearBytes), true},
    { "AMediaCodecCryptoInfo_getEncryptedBytes", OFF(getEncryptedBytes), true},
#undef OFF
    { NULL, 0, false }
};
#undef OFF

//create symbols, write function-p addr to &NdkMedia.
static bool InitSymbols (void)
{
    static pthread_mutex_t mutex_x= PTHREAD_MUTEX_INITIALIZER;
    static int init_state = -1;
    bool ret;
    pthread_mutex_lock(&mutex_x);

    if (init_state != -1)
        goto m_end;

    init_state = 0;

    void *ndk_handle;
    VOLOGI("Load module lib or lib64");
//this should rely on building.
#ifdef _VOARMV8
    ndk_handle = dlopen("/system/lib64/libmediandk.so", RTLD_NOW);
#else
    ndk_handle = dlopen("/system/lib/libmediandk.so", RTLD_NOW);
#endif
    if (!ndk_handle)
        goto m_end;

    for (int i = 0; members[i].name; i++)
    {
        void *sym = dlsym(ndk_handle, members[i].name);
        if (!sym && members[i].critical)
        {
            dlclose(ndk_handle);
            goto m_end;
        }
        *(void **)((uint8_t*)&NdkMedia + members[i].offset) = sym;
    }

    init_state = 1;
m_end:
    ret = init_state == 1;
    if (!ret){
        VOLOGE("MediaCodec NDK init failed");
        return false;
    } 
    pthread_mutex_unlock(&mutex_x);
    return ret;
}


#endif // __Media_Ndk_WRAP__H

