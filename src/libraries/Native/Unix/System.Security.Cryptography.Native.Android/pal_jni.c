// Licensed to the .NET Foundation under one or more agreements.
// The .NET Foundation licenses this file to you under the MIT license.

#include "pal_jni.h"
#include <pthread.h>

JavaVM* gJvm;

// java/io/ByteArrayInputStream
jclass    g_ByteArrayInputStreamClass;
jmethodID g_ByteArrayInputStreamCtor;
jmethodID g_ByteArrayInputStreamReset;

// java/lang/Enum
jclass    g_Enum;
jmethodID g_EnumOrdinal;

// java/lang/Throwable
jclass    g_ThrowableClass;
jmethodID g_ThrowableGetCause;
jmethodID g_ThrowableGetMessage;

// java/security/SecureRandom
jclass    g_randClass;
jmethodID g_randCtor;
jmethodID g_randNextBytesMethod;

// java/security/MessageDigest
jclass    g_mdClass;
jmethodID g_mdGetInstance;
jmethodID g_mdClone;
jmethodID g_mdDigest;
jmethodID g_mdDigestWithInputBytes;
jmethodID g_mdReset;
jmethodID g_mdUpdate;

// javax/crypto/Mac
jclass    g_MacClass;
jmethodID g_MacGetInstance;
jmethodID g_MacClone;
jmethodID g_MacDoFinal;
jmethodID g_MacInit;
jmethodID g_MacReset;
jmethodID g_MacUpdate;

// javax/crypto/spec/SecretKeySpec
jclass    g_sksClass;
jmethodID g_sksCtor;

// javax/crypto/Cipher
jclass    g_cipherClass;
jmethodID g_cipherGetInstanceMethod;
jmethodID g_cipherDoFinalMethod;
jmethodID g_cipherDoFinal2Method;
jmethodID g_cipherUpdateMethod;
jmethodID g_cipherUpdateAADMethod;
jmethodID g_cipherInitMethod;
jmethodID g_cipherInit2Method;
jmethodID g_getBlockSizeMethod;

// javax/crypto/spec/IvParameterSpec
jclass    g_ivPsClass;
jmethodID g_ivPsCtor;

// java/math/BigInteger
jclass    g_bigNumClass;
jmethodID g_bigNumCtor;
jmethodID g_bigNumCtorWithSign;
jmethodID g_toByteArrayMethod;
jmethodID g_valueOfMethod;
jmethodID g_intValueMethod;
jmethodID g_compareToMethod;
jmethodID g_bitLengthMethod;
jmethodID g_sigNumMethod;

// javax/net/ssl/SSLParameters
jclass    g_sslParamsClass;
jmethodID g_sslParamsGetProtocolsMethod;

// javax/net/ssl/SSLContext
jclass    g_sslCtxClass;
jmethodID g_sslCtxGetDefaultMethod;
jmethodID g_sslCtxGetDefaultSslParamsMethod;

// javax/crypto/spec/GCMParameterSpec
jclass    g_GCMParameterSpecClass;
jmethodID g_GCMParameterSpecCtor;

// java/security/interfaces/DSAKey
jclass    g_DSAKeyClass;

// java/security/interfaces/ECKey
jclass    g_ECKeyClass;

// java/security/interfaces/RSAKey
jclass    g_RSAKeyClass;
jmethodID g_RSAKeyGetModulus;

// java/security/interfaces/RSAPublicKey
jclass    g_RSAPublicKeyClass;
jmethodID g_RSAPublicKeyGetPubExpMethod;

// java/security/KeyPair
jclass    g_keyPairClass;
jmethodID g_keyPairCtor;
jmethodID g_keyPairGetPrivateMethod;
jmethodID g_keyPairGetPublicMethod;

// java/security/KeyPairGenerator
jclass    g_keyPairGenClass;
jmethodID g_keyPairGenGetInstanceMethod;
jmethodID g_keyPairGenInitializeWithParamsMethod;
jmethodID g_keyPairGenInitializeMethod;
jmethodID g_keyPairGenGenKeyPairMethod;

// java/security/KeyStore
jclass    g_KeyStoreClass;
jmethodID g_KeyStoreGetInstance;
jmethodID g_KeyStoreAliases;
jmethodID g_KeyStoreContainsAlias;
jmethodID g_KeyStoreDeleteEntry;
jmethodID g_KeyStoreGetCertificate;
jmethodID g_KeyStoreGetEntry;
jmethodID g_KeyStoreLoad;
jmethodID g_KeyStoreSetCertificateEntry;
jmethodID g_KeyStoreSetKeyEntry;

// java/security/KeyStore$PrivateKeyEntry
jclass    g_PrivateKeyEntryClass;
jmethodID g_PrivateKeyEntryGetCertificate;
jmethodID g_PrivateKeyEntryGetPrivateKey;

// java/security/KeyStore$TrustedCertificateEntry
jclass    g_TrustedCertificateEntryClass;
jmethodID g_TrustedCertificateEntryGetTrustedCertificate;

// java/security/Signature
jclass    g_SignatureClass;
jmethodID g_SignatureGetInstance;
jmethodID g_SignatureInitSign;
jmethodID g_SignatureInitVerify;
jmethodID g_SignatureUpdate;
jmethodID g_SignatureSign;
jmethodID g_SignatureVerify;

// java/security/cert/CertificateFactory
jclass    g_CertFactoryClass;
jmethodID g_CertFactoryGetInstance;
jmethodID g_CertFactoryGenerateCertificate;
jmethodID g_CertFactoryGenerateCertificates;
jmethodID g_CertFactoryGenerateCertPathFromList;
jmethodID g_CertFactoryGenerateCertPathFromStream;

// java/security/cert/CertPath
jclass    g_CertPathClass;
jmethodID g_CertPathGetEncoded;
jmethodID g_CertPathGetCertificates;

// java/security/cert/CertPathBuilder
jclass    g_CertPathBuilderClass;
jmethodID g_CertPathBuilderGetInstance;
jmethodID g_CertPathBuilderBuild;

// java/security/cert/CertPathValidator
jclass    g_CertPathValidatorClass;
jmethodID g_CertPathValidatorGetInstance;
jmethodID g_CertPathValidatorValidate;
jmethodID g_CertPathValidatorGetRevocationChecker; // only in API level 24+

// java/security/cert/CertPathValidatorException
jclass    g_CertPathValidatorExceptionClass;
jmethodID g_CertPathValidatorExceptionGetIndex;
jmethodID g_CertPathValidatorExceptionGetReason; // only in API level 24+

// java/security/cert/CertPathValidatorException$BasicReason - only in API level 24+
jclass    g_CertPathExceptionBasicReasonClass;

// java/security/cert/CertStore
jclass    g_CertStoreClass;
jmethodID g_CertStoreGetInstance;

// java/security/cert/CollectionCertStoreParameters
jclass    g_CollectionCertStoreParametersClass;
jmethodID g_CollectionCertStoreParametersCtor;

// java/security/cert/PKIXBuilderParameters
jclass    g_PKIXBuilderParametersClass;
jmethodID g_PKIXBuilderParametersCtor;
jmethodID g_PKIXBuilderParametersAddCertStore;
jmethodID g_PKIXBuilderParametersAddCertPathChecker;
jmethodID g_PKIXBuilderParametersSetDate;
jmethodID g_PKIXBuilderParametersSetRevocationEnabled;
jmethodID g_PKIXBuilderParametersSetTrustAnchors;

// java/security/cert/PKIXCertPathBuilderResult
jclass    g_PKIXCertPathBuilderResultClass;
jmethodID g_PKIXCertPathBuilderResultGetCertPath;
jmethodID g_PKIXCertPathBuilderResultGetTrustAnchor;

// java/security/cert/PKIXReason - only in API level 24+
jclass    g_PKIXReasonClass;

// java/security/cert/PKIXRevocationChecker - only in API level 24+
jclass    g_PKIXRevocationCheckerClass;
jmethodID g_PKIXRevocationCheckerSetOptions;

// java/security/cert/PKIXRevocationChecker$Option - only in API level 24+
jclass    g_PKIXRevocationCheckerOptionClass;
jfieldID  g_PKIXRevocationCheckerOptionOnlyEndEntity;

// java/security/cert/TrustAnchor
jclass    g_TrustAnchorClass;
jclass    g_TrustAnchorCtor;
jmethodID g_TrustAnchorGetTrustedCert;

// java/security/cert/X509Certificate
jclass    g_X509CertClass;
jmethodID g_X509CertEquals;
jmethodID g_X509CertGetEncoded;
jmethodID g_X509CertGetPublicKey;

// java/security/cert/X509CertSelector
jclass    g_X509CertSelectorClass;
jmethodID g_X509CertSelectorCtor;
jmethodID g_X509CertSelectorSetCertificate;

// java/security/interfaces/RSAPrivateCrtKey
jclass    g_RSAPrivateCrtKeyClass;
jmethodID g_RSAPrivateCrtKeyPubExpField;
jmethodID g_RSAPrivateCrtKeyPrimePField;
jmethodID g_RSAPrivateCrtKeyPrimeQField;
jmethodID g_RSAPrivateCrtKeyPrimeExpPField;
jmethodID g_RSAPrivateCrtKeyPrimeExpQField;
jmethodID g_RSAPrivateCrtKeyCrtCoefField;
jmethodID g_RSAPrivateCrtKeyModulusField;
jmethodID g_RSAPrivateCrtKeyPrivExpField;

// java/security/spec/RSAPrivateCrtKeySpec
jclass    g_RSAPrivateCrtKeySpecClass;
jmethodID g_RSAPrivateCrtKeySpecCtor;

// java/security/spec/RSAPublicKeySpec
jclass    g_RSAPublicCrtKeySpecClass;
jmethodID g_RSAPublicCrtKeySpecCtor;

// java/security/KeyFactory
jclass    g_KeyFactoryClass;
jmethodID g_KeyFactoryGetInstanceMethod;
jmethodID g_KeyFactoryGenPrivateMethod;
jmethodID g_KeyFactoryGenPublicMethod;
jmethodID g_KeyFactoryGetKeySpecMethod;

// java/security/spec/DSAPublicKeySpec
jclass    g_DSAPublicKeySpecClass;
jmethodID g_DSAPublicKeySpecCtor;
jmethodID g_DSAPublicKeySpecGetY;
jmethodID g_DSAPublicKeySpecGetP;
jmethodID g_DSAPublicKeySpecGetQ;
jmethodID g_DSAPublicKeySpecGetG;

// java/security/spec/DSAPrivateKeySpec
jclass    g_DSAPrivateKeySpecClass;
jmethodID g_DSAPrivateKeySpecCtor;
jmethodID g_DSAPrivateKeySpecGetX;

// java/security/spec/ECParameterSpec
jclass    g_ECParameterSpecClass;
jmethodID g_ECParameterSpecCtor;
jmethodID g_ECParameterSpecGetCurve;
jmethodID g_ECParameterSpecGetGenerator;
jmethodID g_ECParameterSpecGetCofactor;
jmethodID g_ECParameterSpecGetOrder;
jmethodID g_ECParameterSpecGetCurveName;

// java/security/spec/ECField
jclass    g_ECFieldClass;
jmethodID g_ECFieldGetFieldSize;

// java/security/spec/ECFieldFp
jclass    g_ECFieldFpClass;
jmethodID g_ECFieldFpCtor;
jmethodID g_ECFieldFpGetP;

// java/security/spec/ECFieldF2m
jclass    g_ECFieldF2mClass;
jmethodID g_ECFieldF2mCtorWithCoefficientBigInteger;
jmethodID g_ECFieldF2mGetReductionPolynomial;

// java/security/spec/ECGenParameterSpecClass
jclass    g_ECGenParameterSpecClass;
jmethodID g_ECGenParameterSpecCtor;

// java/security/spec/ECPoint
jclass    g_ECPointClass;
jmethodID g_ECPointCtor;
jmethodID g_ECPointGetAffineX;
jmethodID g_ECPointGetAffineY;

// java/security/interfaces/ECPrivateKey
jclass    g_ECPrivateKeyClass;
jmethodID g_ECPrivateKeyGetS;

// java/security/spec/ECPrivateKeySpec
jclass    g_ECPrivateKeySpecClass;
jmethodID g_ECPrivateKeySpecCtor;

// java/security/interfaces/ECPublicKey
jclass    g_ECPublicKeyClass;
jmethodID g_ECPublicKeyGetParams;
jmethodID g_ECPublicKeyGetW;

// java/security/spec/ECPublicKeySpec
jclass    g_ECPublicKeySpecClass;
jmethodID g_ECPublicKeySpecCtor;
jmethodID g_ECPublicKeySpecGetParams;

// java/security/spec/EllipticCurve
jclass    g_EllipticCurveClass;
jmethodID g_EllipticCurveCtor;
jmethodID g_EllipticCurveCtorWithSeed;
jmethodID g_EllipticCurveGetA;
jmethodID g_EllipticCurveGetB;
jmethodID g_EllipticCurveGetField;
jmethodID g_EllipticCurveGetSeed;

// java/security/spec/X509EncodedKeySpec
jclass    g_X509EncodedKeySpecClass;
jmethodID g_X509EncodedKeySpecCtor;

// javax/security/auth
jclass    g_DestroyableClass;
jmethodID g_destroy;

// java/util/ArrayList
jclass    g_ArrayListClass;
jmethodID g_ArrayListCtor;
jmethodID g_ArrayListCtorWithCapacity;
jmethodID g_ArrayListCtorWithCollection;
jmethodID g_ArrayListAdd;

// java/util/Collection
jclass    g_CollectionClass;
jmethodID g_CollectionIterator;
jmethodID g_CollectionSize;

// java/util/Date
jclass    g_DateClass;
jmethodID g_DateCtor;

// java/util/Enumeration
jclass    g_Enumeration;
jmethodID g_EnumerationHasMoreElements;
jmethodID g_EnumerationNextElement;

// java/util/HashSet
jclass    g_HashSetClass;
jmethodID g_HashSetCtorWithCapacity;
jmethodID g_HashSetAdd;

// java/util/Iterator
jclass    g_IteratorClass;
jmethodID g_IteratorHasNext;
jmethodID g_IteratorNext;

// java/util/List
jclass    g_ListClass;
jmethodID g_ListGet;

// javax/net/ssl/SSLEngine
jclass    g_SSLEngine;
jmethodID g_SSLEngineSetUseClientModeMethod;
jmethodID g_SSLEngineGetSessionMethod;
jmethodID g_SSLEngineBeginHandshakeMethod;
jmethodID g_SSLEngineWrapMethod;
jmethodID g_SSLEngineUnwrapMethod;
jmethodID g_SSLEngineCloseInboundMethod;
jmethodID g_SSLEngineCloseOutboundMethod;
jmethodID g_SSLEngineGetHandshakeStatusMethod;

// java/nio/ByteBuffer
jclass    g_ByteBuffer;
jmethodID g_ByteBufferAllocateMethod;
jmethodID g_ByteBufferPutMethod;
jmethodID g_ByteBufferPut2Method;
jmethodID g_ByteBufferPut3Method;
jmethodID g_ByteBufferFlipMethod;
jmethodID g_ByteBufferGetMethod;
jmethodID g_ByteBufferPutBufferMethod;
jmethodID g_ByteBufferLimitMethod;
jmethodID g_ByteBufferRemainingMethod;
jmethodID g_ByteBufferCompactMethod;
jmethodID g_ByteBufferPositionMethod;

// javax/net/ssl/SSLContext
jclass    g_SSLContext;
jmethodID g_SSLContextGetInstanceMethod;
jmethodID g_SSLContextInitMethod;
jmethodID g_SSLContextCreateSSLEngineMethod;

// javax/net/ssl/SSLSession
jclass    g_SSLSession;
jmethodID g_SSLSessionGetApplicationBufferSizeMethod;
jmethodID g_SSLSessionGetPacketBufferSizeMethod;

// javax/net/ssl/SSLEngineResult
jclass    g_SSLEngineResult;
jmethodID g_SSLEngineResultGetStatusMethod;
jmethodID g_SSLEngineResultGetHandshakeStatusMethod;

// javax/net/ssl/TrustManager
jclass    g_TrustManager;

// javax/crypto/KeyAgreement
jclass    g_KeyAgreementClass;
jmethodID g_KeyAgreementGetInstance;
jmethodID g_KeyAgreementInit;
jmethodID g_KeyAgreementDoPhase;
jmethodID g_KeyAgreementGenerateSecret;

jobject ToGRef(JNIEnv *env, jobject lref)
{
    if (lref)
    {
        jobject gref = (*env)->NewGlobalRef(env, lref);
        (*env)->DeleteLocalRef(env, lref);
        return gref;
    }
    return lref;
}

jobject AddGRef(JNIEnv *env, jobject gref)
{
    if (!gref)
        return NULL;
    return (*env)->NewGlobalRef(env, gref);
}

void ReleaseGRef(JNIEnv *env, jobject gref)
{
    if (gref)
        (*env)->DeleteGlobalRef(env, gref);
}

void ReleaseLRef(JNIEnv *env, jobject lref)
{
    if (lref)
        (*env)->DeleteLocalRef(env, lref);
}

static bool TryGetClassGRef(JNIEnv *env, const char* name, jclass* out)
{
    *out = NULL;
    LOG_DEBUG("Finding %s class", name);
    jclass klass = (*env)->FindClass (env, name);
    if (klass == NULL)
        return false;

    *out = ToGRef(env, klass);
    return true;
}

jclass GetClassGRef(JNIEnv *env, const char* name)
{
    jclass klass = NULL;
    if (!TryGetClassGRef(env, name, &klass))
    {
        LOG_ERROR("class %s was not found", name);
    }

    assert(klass);
    return klass;
}

static jclass GetOptionalClassGRef(JNIEnv *env, const char* name)
{
    jclass klass = NULL;
    if (!TryGetClassGRef(env, name, &klass))
    {
        LOG_DEBUG("optional class %s was not found", name);
        // Failing to find an optional class causes an exception state, which we need to clear.
        TryClearJNIExceptions(env);
    }

    return klass;
}

bool CheckJNIExceptions(JNIEnv* env)
{
    if ((*env)->ExceptionCheck(env))
    {
        (*env)->ExceptionDescribe(env);
        (*env)->ExceptionClear(env);
        return true;
    }
    return false;
}

bool TryClearJNIExceptions(JNIEnv* env)
{
    if ((*env)->ExceptionCheck(env))
    {
        (*env)->ExceptionClear(env);
        return true;
    }

    return false;
}

bool TryGetJNIException(JNIEnv* env, jthrowable *ex, bool printException)
{
    if (!(*env)->ExceptionCheck(env))
        return false;

    if (printException)
    {
        (*env)->ExceptionDescribe(env);
    }

    *ex = (*env)->ExceptionOccurred(env);
    (*env)->ExceptionClear(env);
    return true;
}

void AssertOnJNIExceptions(JNIEnv* env)
{
    assert(!CheckJNIExceptions(env));
}

void SaveTo(uint8_t* src, uint8_t** dst, size_t len, bool overwrite)
{
    assert(overwrite || !(*dst));
    if (overwrite)
    {
        free(*dst);
    }
    *dst = (uint8_t*)malloc(len * sizeof(uint8_t));
    memcpy(*dst, src, len);
}

jmethodID GetMethod(JNIEnv *env, bool isStatic, jclass klass, const char* name, const char* sig)
{
    LOG_DEBUG("Finding %s method", name);
    jmethodID mid = isStatic ? (*env)->GetStaticMethodID(env, klass, name, sig) : (*env)->GetMethodID(env, klass, name, sig);
    if (!mid) {
        LOG_ERROR("method %s %s was not found", name, sig);
        assert(mid);
    }
    return mid;
}

jmethodID GetOptionalMethod(JNIEnv *env, bool isStatic, jclass klass, const char* name, const char* sig)
{
    LOG_DEBUG("Finding %s method", name);
    jmethodID mid = isStatic ? (*env)->GetStaticMethodID(env, klass, name, sig) : (*env)->GetMethodID(env, klass, name, sig);
    if (!mid) {
        LOG_INFO("optional method %s %s was not found", name, sig);
        // Failing to find an optional method causes an exception state, which we need to clear.
        TryClearJNIExceptions(env);
    }
    return mid;
}

jfieldID GetField(JNIEnv *env, bool isStatic, jclass klass, const char* name, const char* sig)
{
    LOG_DEBUG("Finding %s field", name);
    jfieldID fid = isStatic ? (*env)->GetStaticFieldID(env, klass, name, sig) : (*env)->GetFieldID(env, klass, name, sig);
    if (!fid) {
        LOG_ERROR("field %s %s was not found", name, sig);
        assert(fid);
    }
    return fid;
}

static void DetatchThreadFromJNI(void* unused)
{
    LOG_DEBUG("Detaching thread from JNI");
    (void)unused;
    (*gJvm)->DetachCurrentThread(gJvm);
}

static pthread_key_t threadLocalEnvKey;
static pthread_once_t threadLocalEnvInitKey = PTHREAD_ONCE_INIT;

static void
make_key()
{
    (void) pthread_key_create(&threadLocalEnvKey, &DetatchThreadFromJNI);
}

JNIEnv* GetJNIEnv()
{
    JNIEnv *env;
    (*gJvm)->GetEnv(gJvm, (void**)&env, JNI_VERSION_1_6);
    if (env)
        return env;
    jint ret = (*gJvm)->AttachCurrentThreadAsDaemon(gJvm, &env, NULL);

    (void) pthread_once(&threadLocalEnvInitKey, make_key);
    LOG_DEBUG("Registering JNI thread detach. env ptr %p. Key: %ld", (void*)env, (long)threadLocalEnvKey);
    pthread_setspecific(threadLocalEnvKey, env);

    assert(ret == JNI_OK && "Unable to attach thread to JVM");
    (void)ret;
    return env;
}

int GetEnumAsInt(JNIEnv *env, jobject enumObj)
{
    int value = (*env)->CallIntMethod(env, enumObj, g_EnumOrdinal);
    (*env)->DeleteLocalRef(env, enumObj);
    return value;
}

JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *vm, void *reserved)
{
    (void)reserved;
    LOG_INFO("JNI_OnLoad in pal_jni.c");
    gJvm = vm;

    JNIEnv* env = GetJNIEnv();

    // cache some classes and methods while we're in the thread-safe JNI_OnLoad
    g_ByteArrayInputStreamClass =   GetClassGRef(env, "java/io/ByteArrayInputStream");
    g_ByteArrayInputStreamCtor =    GetMethod(env, false, g_ByteArrayInputStreamClass, "<init>", "([B)V");
    g_ByteArrayInputStreamReset =    GetMethod(env, false, g_ByteArrayInputStreamClass, "reset", "()V");

    g_Enum =                    GetClassGRef(env, "java/lang/Enum");
    g_EnumOrdinal =             GetMethod(env, false, g_Enum, "ordinal", "()I");

    g_ThrowableClass =      GetClassGRef(env, "java/lang/Throwable");
    g_ThrowableGetCause =   GetMethod(env, false, g_ThrowableClass, "getCause", "()Ljava/lang/Throwable;");
    g_ThrowableGetMessage = GetMethod(env, false, g_ThrowableClass, "getMessage", "()Ljava/lang/String;");

    g_randClass =               GetClassGRef(env, "java/security/SecureRandom");
    g_randCtor =                GetMethod(env, false, g_randClass, "<init>", "()V");
    g_randNextBytesMethod =     GetMethod(env, false, g_randClass, "nextBytes", "([B)V");

    g_mdClass =                 GetClassGRef(env, "java/security/MessageDigest");
    g_mdGetInstance =           GetMethod(env, true,  g_mdClass, "getInstance", "(Ljava/lang/String;)Ljava/security/MessageDigest;");
    g_mdClone =                 GetMethod(env, false, g_mdClass, "clone", "()Ljava/lang/Object;");
    g_mdDigest =                GetMethod(env, false, g_mdClass, "digest", "()[B");
    g_mdDigestWithInputBytes =  GetMethod(env, false, g_mdClass, "digest", "([B)[B");
    g_mdReset =                 GetMethod(env, false, g_mdClass, "reset", "()V");
    g_mdUpdate =                GetMethod(env, false, g_mdClass, "update", "([B)V");

    g_MacClass =          GetClassGRef(env, "javax/crypto/Mac");
    g_MacGetInstance =    GetMethod(env, true,  g_MacClass, "getInstance", "(Ljava/lang/String;)Ljavax/crypto/Mac;");
    g_MacClone =          GetMethod(env, false, g_MacClass, "clone", "()Ljava/lang/Object;");
    g_MacDoFinal =        GetMethod(env, false, g_MacClass, "doFinal", "()[B");
    g_MacUpdate =         GetMethod(env, false, g_MacClass, "update", "([B)V");
    g_MacInit =           GetMethod(env, false, g_MacClass, "init", "(Ljava/security/Key;)V");
    g_MacReset =          GetMethod(env, false, g_MacClass, "reset", "()V");

    g_sksClass =                GetClassGRef(env, "javax/crypto/spec/SecretKeySpec");
    g_sksCtor =                 GetMethod(env, false, g_sksClass, "<init>", "([BLjava/lang/String;)V");

    g_cipherClass =             GetClassGRef(env, "javax/crypto/Cipher");
    g_cipherGetInstanceMethod = GetMethod(env, true,  g_cipherClass, "getInstance", "(Ljava/lang/String;)Ljavax/crypto/Cipher;");
    g_getBlockSizeMethod =      GetMethod(env, false, g_cipherClass, "getBlockSize", "()I");
    g_cipherDoFinalMethod =     GetMethod(env, false, g_cipherClass, "doFinal", "()[B");
    g_cipherDoFinal2Method =    GetMethod(env, false, g_cipherClass, "doFinal", "([B)[B");
    g_cipherUpdateMethod =      GetMethod(env, false, g_cipherClass, "update", "([B)[B");
    g_cipherUpdateAADMethod =   GetMethod(env, false, g_cipherClass, "updateAAD", "([B)V");
    g_cipherInitMethod =        GetMethod(env, false, g_cipherClass, "init", "(ILjava/security/Key;Ljava/security/spec/AlgorithmParameterSpec;)V");
    g_cipherInit2Method =       GetMethod(env, false, g_cipherClass, "init", "(ILjava/security/Key;)V");

    g_ivPsClass =               GetClassGRef(env, "javax/crypto/spec/IvParameterSpec");
    g_ivPsCtor =                GetMethod(env, false, g_ivPsClass, "<init>", "([B)V");

    g_GCMParameterSpecClass =   GetClassGRef(env, "javax/crypto/spec/GCMParameterSpec");
    g_GCMParameterSpecCtor =    GetMethod(env, false, g_GCMParameterSpecClass, "<init>", "(I[B)V");

    g_bigNumClass =             GetClassGRef(env, "java/math/BigInteger");
    g_bigNumCtor =              GetMethod(env, false, g_bigNumClass, "<init>", "([B)V");
    g_bigNumCtorWithSign =      GetMethod(env, false, g_bigNumClass, "<init>", "(I[B)V");
    g_toByteArrayMethod =       GetMethod(env, false, g_bigNumClass, "toByteArray", "()[B");
    g_valueOfMethod =           GetMethod(env, true, g_bigNumClass, "valueOf", "(J)Ljava/math/BigInteger;");
    g_intValueMethod =          GetMethod(env, false, g_bigNumClass, "intValue", "()I");
    g_compareToMethod =         GetMethod(env, false, g_bigNumClass, "compareTo", "(Ljava/math/BigInteger;)I");
    g_bitLengthMethod =         GetMethod(env, false, g_bigNumClass, "bitLength", "()I");
    g_sigNumMethod =            GetMethod(env, false, g_bigNumClass, "signum", "()I");

    g_sslParamsClass =              GetClassGRef(env, "javax/net/ssl/SSLParameters");
    g_sslParamsGetProtocolsMethod = GetMethod(env, false,  g_sslParamsClass, "getProtocols", "()[Ljava/lang/String;");

    g_sslCtxClass =                     GetClassGRef(env, "javax/net/ssl/SSLContext");
    g_sslCtxGetDefaultMethod =          GetMethod(env, true,  g_sslCtxClass, "getDefault", "()Ljavax/net/ssl/SSLContext;");
    g_sslCtxGetDefaultSslParamsMethod = GetMethod(env, false, g_sslCtxClass, "getDefaultSSLParameters", "()Ljavax/net/ssl/SSLParameters;");

    g_CertFactoryClass =                        GetClassGRef(env, "java/security/cert/CertificateFactory");
    g_CertFactoryGetInstance =                  GetMethod(env, true, g_CertFactoryClass, "getInstance", "(Ljava/lang/String;)Ljava/security/cert/CertificateFactory;");
    g_CertFactoryGenerateCertificate =          GetMethod(env, false, g_CertFactoryClass, "generateCertificate", "(Ljava/io/InputStream;)Ljava/security/cert/Certificate;");
    g_CertFactoryGenerateCertificates =         GetMethod(env, false, g_CertFactoryClass, "generateCertificates", "(Ljava/io/InputStream;)Ljava/util/Collection;");
    g_CertFactoryGenerateCertPathFromList =     GetMethod(env, false, g_CertFactoryClass, "generateCertPath", "(Ljava/util/List;)Ljava/security/cert/CertPath;");
    g_CertFactoryGenerateCertPathFromStream =   GetMethod(env, false, g_CertFactoryClass, "generateCertPath", "(Ljava/io/InputStream;Ljava/lang/String;)Ljava/security/cert/CertPath;");

    g_CertPathClass =           GetClassGRef(env, "java/security/cert/CertPath");
    g_CertPathGetEncoded =      GetMethod(env, false, g_CertPathClass, "getEncoded", "(Ljava/lang/String;)[B");
    g_CertPathGetCertificates = GetMethod(env, false, g_CertPathClass, "getCertificates", "()Ljava/util/List;");

    g_CertPathBuilderClass =        GetClassGRef(env, "java/security/cert/CertPathBuilder");
    g_CertPathBuilderGetInstance =  GetMethod(env, true, g_CertPathBuilderClass, "getInstance", "(Ljava/lang/String;)Ljava/security/cert/CertPathBuilder;");
    g_CertPathBuilderBuild =        GetMethod(env, false, g_CertPathBuilderClass, "build", "(Ljava/security/cert/CertPathParameters;)Ljava/security/cert/CertPathBuilderResult;");

    g_CertPathValidatorClass =                  GetClassGRef(env, "java/security/cert/CertPathValidator");
    g_CertPathValidatorGetInstance =            GetMethod(env, true, g_CertPathValidatorClass, "getInstance", "(Ljava/lang/String;)Ljava/security/cert/CertPathValidator;");
    g_CertPathValidatorValidate =               GetMethod(env, false, g_CertPathValidatorClass, "validate", "(Ljava/security/cert/CertPath;Ljava/security/cert/CertPathParameters;)Ljava/security/cert/CertPathValidatorResult;");
    g_CertPathValidatorGetRevocationChecker =   GetOptionalMethod(env, false, g_CertPathValidatorClass, "getRevocationChecker", "()Ljava/security/cert/CertPathChecker;");

    g_CertPathValidatorExceptionClass =     GetClassGRef(env, "java/security/cert/CertPathValidatorException");
    g_CertPathValidatorExceptionGetIndex =  GetMethod(env, false, g_CertPathValidatorExceptionClass, "getIndex", "()I");
    g_CertPathValidatorExceptionGetReason = GetOptionalMethod(env, false, g_CertPathValidatorExceptionClass, "getReason", "()Ljava/security/cert/CertPathValidatorException$Reason;");

    g_CertPathExceptionBasicReasonClass =   GetOptionalClassGRef(env, "java/security/cert/CertPathValidatorException$BasicReason");

    g_CertStoreClass =          GetClassGRef(env, "java/security/cert/CertStore");
    g_CertStoreGetInstance =    GetMethod(env, true, g_CertStoreClass, "getInstance", "(Ljava/lang/String;Ljava/security/cert/CertStoreParameters;)Ljava/security/cert/CertStore;");

    g_CollectionCertStoreParametersClass =  GetClassGRef(env, "java/security/cert/CollectionCertStoreParameters");
    g_CollectionCertStoreParametersCtor =   GetMethod(env, false, g_CollectionCertStoreParametersClass, "<init>", "(Ljava/util/Collection;)V");

    g_PKIXBuilderParametersClass =                  GetClassGRef(env, "java/security/cert/PKIXBuilderParameters");
    g_PKIXBuilderParametersCtor =                   GetMethod(env, false, g_PKIXBuilderParametersClass, "<init>", "(Ljava/security/KeyStore;Ljava/security/cert/CertSelector;)V");
    g_PKIXBuilderParametersAddCertStore =           GetMethod(env, false, g_PKIXBuilderParametersClass, "addCertStore", "(Ljava/security/cert/CertStore;)V");
    g_PKIXBuilderParametersAddCertPathChecker =     GetMethod(env, false, g_PKIXBuilderParametersClass, "addCertPathChecker", "(Ljava/security/cert/PKIXCertPathChecker;)V");
    g_PKIXBuilderParametersSetDate =                GetMethod(env, false, g_PKIXBuilderParametersClass, "setDate", "(Ljava/util/Date;)V");
    g_PKIXBuilderParametersSetRevocationEnabled =   GetMethod(env, false, g_PKIXBuilderParametersClass, "setRevocationEnabled", "(Z)V");
    g_PKIXBuilderParametersSetTrustAnchors =        GetMethod(env, false, g_PKIXBuilderParametersClass, "setTrustAnchors", "(Ljava/util/Set;)V");

    g_PKIXCertPathBuilderResultClass =          GetClassGRef(env, "java/security/cert/PKIXCertPathBuilderResult");
    g_PKIXCertPathBuilderResultGetCertPath =    GetMethod(env, false, g_PKIXCertPathBuilderResultClass, "getCertPath", "()Ljava/security/cert/CertPath;");
    g_PKIXCertPathBuilderResultGetTrustAnchor = GetMethod(env, false, g_PKIXCertPathBuilderResultClass, "getTrustAnchor", "()Ljava/security/cert/TrustAnchor;");

    g_PKIXReasonClass =   GetOptionalClassGRef(env, "java/security/cert/PKIXReason");

    if (g_CertPathValidatorGetRevocationChecker != NULL)
    {
        g_PKIXRevocationCheckerClass =                  GetClassGRef(env, "java/security/cert/PKIXRevocationChecker");
        g_PKIXRevocationCheckerSetOptions =             GetMethod(env, false, g_PKIXRevocationCheckerClass, "setOptions", "(Ljava/util/Set;)V");

        g_PKIXRevocationCheckerOptionClass =            GetClassGRef(env, "java/security/cert/PKIXRevocationChecker$Option");
        g_PKIXRevocationCheckerOptionOnlyEndEntity =    GetField(env, true, g_PKIXRevocationCheckerOptionClass, "ONLY_END_ENTITY", "Ljava/security/cert/PKIXRevocationChecker$Option;");
    }

    g_TrustAnchorClass =            GetClassGRef(env, "java/security/cert/TrustAnchor");
    g_TrustAnchorCtor =             GetMethod(env, false, g_TrustAnchorClass, "<init>", "(Ljava/security/cert/X509Certificate;[B)V");
    g_TrustAnchorGetTrustedCert =   GetMethod(env, false, g_TrustAnchorClass, "getTrustedCert", "()Ljava/security/cert/X509Certificate;");

    g_X509CertClass =           GetClassGRef(env, "java/security/cert/X509Certificate");
    g_X509CertEquals =          GetMethod(env, false, g_X509CertClass, "equals", "(Ljava/lang/Object;)Z");
    g_X509CertGetEncoded =      GetMethod(env, false, g_X509CertClass, "getEncoded", "()[B");
    g_X509CertGetPublicKey =    GetMethod(env, false, g_X509CertClass, "getPublicKey", "()Ljava/security/PublicKey;");

    g_X509CertSelectorClass =           GetClassGRef(env, "java/security/cert/X509CertSelector");
    g_X509CertSelectorCtor =            GetMethod(env, false, g_X509CertSelectorClass, "<init>", "()V");
    g_X509CertSelectorSetCertificate =  GetMethod(env, false, g_X509CertSelectorClass, "setCertificate", "(Ljava/security/cert/X509Certificate;)V");

    g_DSAKeyClass = GetClassGRef(env, "java/security/interfaces/DSAKey");

    g_ECKeyClass =  GetClassGRef(env, "java/security/interfaces/ECKey");

    g_RSAKeyClass =                    GetClassGRef(env, "java/security/interfaces/RSAKey");
    g_RSAKeyGetModulus =               GetMethod(env, false, g_RSAKeyClass, "getModulus", "()Ljava/math/BigInteger;");

    g_RSAPublicKeyClass =              GetClassGRef(env, "java/security/interfaces/RSAPublicKey");
    g_RSAPublicKeyGetPubExpMethod =    GetMethod(env, false, g_RSAPublicKeyClass, "getPublicExponent", "()Ljava/math/BigInteger;");

    g_keyPairClass =                   GetClassGRef(env, "java/security/KeyPair");
    g_keyPairCtor =                    GetMethod(env, false, g_keyPairClass, "<init>", "(Ljava/security/PublicKey;Ljava/security/PrivateKey;)V");
    g_keyPairGetPrivateMethod =        GetMethod(env, false, g_keyPairClass, "getPrivate", "()Ljava/security/PrivateKey;");
    g_keyPairGetPublicMethod =         GetMethod(env, false, g_keyPairClass, "getPublic", "()Ljava/security/PublicKey;");

    g_keyPairGenClass =                      GetClassGRef(env, "java/security/KeyPairGenerator");
    g_keyPairGenGetInstanceMethod =          GetMethod(env, true,  g_keyPairGenClass, "getInstance", "(Ljava/lang/String;)Ljava/security/KeyPairGenerator;");
    g_keyPairGenInitializeMethod =           GetMethod(env, false, g_keyPairGenClass, "initialize", "(I)V");
    g_keyPairGenInitializeWithParamsMethod = GetMethod(env, false, g_keyPairGenClass, "initialize", "(Ljava/security/spec/AlgorithmParameterSpec;)V");
    g_keyPairGenGenKeyPairMethod =           GetMethod(env, false, g_keyPairGenClass, "genKeyPair", "()Ljava/security/KeyPair;");

    g_KeyStoreClass =               GetClassGRef(env, "java/security/KeyStore");
    g_KeyStoreGetInstance =         GetMethod(env, true, g_KeyStoreClass, "getInstance", "(Ljava/lang/String;)Ljava/security/KeyStore;");
    g_KeyStoreAliases =             GetMethod(env, false, g_KeyStoreClass, "aliases", "()Ljava/util/Enumeration;");
    g_KeyStoreContainsAlias =       GetMethod(env, false, g_KeyStoreClass, "containsAlias", "(Ljava/lang/String;)Z");
    g_KeyStoreDeleteEntry =         GetMethod(env, false, g_KeyStoreClass, "deleteEntry", "(Ljava/lang/String;)V");
    g_KeyStoreGetCertificate =      GetMethod(env, false, g_KeyStoreClass, "getCertificate", "(Ljava/lang/String;)Ljava/security/cert/Certificate;");
    g_KeyStoreGetEntry =            GetMethod(env, false, g_KeyStoreClass, "getEntry", "(Ljava/lang/String;Ljava/security/KeyStore$ProtectionParameter;)Ljava/security/KeyStore$Entry;");
    g_KeyStoreLoad =                GetMethod(env, false, g_KeyStoreClass, "load", "(Ljava/io/InputStream;[C)V");
    g_KeyStoreSetCertificateEntry = GetMethod(env, false, g_KeyStoreClass, "setCertificateEntry", "(Ljava/lang/String;Ljava/security/cert/Certificate;)V");
    g_KeyStoreSetKeyEntry =         GetMethod(env, false, g_KeyStoreClass, "setKeyEntry", "(Ljava/lang/String;Ljava/security/Key;[C[Ljava/security/cert/Certificate;)V");

    g_PrivateKeyEntryClass =            GetClassGRef(env, "java/security/KeyStore$PrivateKeyEntry");
    g_PrivateKeyEntryGetCertificate =   GetMethod(env, false, g_PrivateKeyEntryClass, "getCertificate", "()Ljava/security/cert/Certificate;");
    g_PrivateKeyEntryGetPrivateKey =    GetMethod(env, false, g_PrivateKeyEntryClass, "getPrivateKey", "()Ljava/security/PrivateKey;");

    g_TrustedCertificateEntryClass =                    GetClassGRef(env, "java/security/KeyStore$TrustedCertificateEntry");
    g_TrustedCertificateEntryGetTrustedCertificate =    GetMethod(env, false, g_TrustedCertificateEntryClass, "getTrustedCertificate", "()Ljava/security/cert/Certificate;");

    g_SignatureClass =                 GetClassGRef(env, "java/security/Signature");
    g_SignatureGetInstance =           GetMethod(env, true, g_SignatureClass, "getInstance", "(Ljava/lang/String;)Ljava/security/Signature;");
    g_SignatureInitSign =              GetMethod(env, false, g_SignatureClass, "initSign", "(Ljava/security/PrivateKey;)V");
    g_SignatureInitVerify =            GetMethod(env, false, g_SignatureClass, "initVerify", "(Ljava/security/PublicKey;)V");
    g_SignatureUpdate =                GetMethod(env, false, g_SignatureClass, "update", "([B)V");
    g_SignatureSign =                  GetMethod(env, false, g_SignatureClass, "sign", "()[B");
    g_SignatureVerify =                GetMethod(env, false, g_SignatureClass, "verify", "([B)Z");

    g_RSAPrivateCrtKeyClass =          GetClassGRef(env, "java/security/interfaces/RSAPrivateCrtKey");
    g_RSAPrivateCrtKeyPubExpField =    GetMethod(env, false, g_RSAPrivateCrtKeyClass, "getPublicExponent", "()Ljava/math/BigInteger;");
    g_RSAPrivateCrtKeyPrimePField =    GetMethod(env, false, g_RSAPrivateCrtKeyClass, "getPrimeP", "()Ljava/math/BigInteger;");
    g_RSAPrivateCrtKeyPrimeQField =    GetMethod(env, false, g_RSAPrivateCrtKeyClass, "getPrimeQ", "()Ljava/math/BigInteger;");
    g_RSAPrivateCrtKeyPrimeExpPField = GetMethod(env, false, g_RSAPrivateCrtKeyClass, "getPrimeExponentP", "()Ljava/math/BigInteger;");
    g_RSAPrivateCrtKeyPrimeExpQField = GetMethod(env, false, g_RSAPrivateCrtKeyClass, "getPrimeExponentQ", "()Ljava/math/BigInteger;");
    g_RSAPrivateCrtKeyCrtCoefField =   GetMethod(env, false, g_RSAPrivateCrtKeyClass, "getCrtCoefficient", "()Ljava/math/BigInteger;");
    g_RSAPrivateCrtKeyModulusField =   GetMethod(env, false, g_RSAPrivateCrtKeyClass, "getModulus", "()Ljava/math/BigInteger;");
    g_RSAPrivateCrtKeyPrivExpField =   GetMethod(env, false, g_RSAPrivateCrtKeyClass, "getPrivateExponent", "()Ljava/math/BigInteger;");

    g_RSAPrivateCrtKeySpecClass =      GetClassGRef(env, "java/security/spec/RSAPrivateCrtKeySpec");
    g_RSAPrivateCrtKeySpecCtor =       GetMethod(env, false, g_RSAPrivateCrtKeySpecClass, "<init>", "(Ljava/math/BigInteger;Ljava/math/BigInteger;Ljava/math/BigInteger;Ljava/math/BigInteger;Ljava/math/BigInteger;Ljava/math/BigInteger;Ljava/math/BigInteger;Ljava/math/BigInteger;)V");

    g_RSAPublicCrtKeySpecClass =       GetClassGRef(env, "java/security/spec/RSAPublicKeySpec");
    g_RSAPublicCrtKeySpecCtor =        GetMethod(env, false, g_RSAPublicCrtKeySpecClass, "<init>", "(Ljava/math/BigInteger;Ljava/math/BigInteger;)V");

    g_KeyFactoryClass =                GetClassGRef(env, "java/security/KeyFactory");
    g_KeyFactoryGetInstanceMethod =    GetMethod(env, true, g_KeyFactoryClass, "getInstance", "(Ljava/lang/String;)Ljava/security/KeyFactory;");
    g_KeyFactoryGenPrivateMethod =     GetMethod(env, false, g_KeyFactoryClass, "generatePrivate", "(Ljava/security/spec/KeySpec;)Ljava/security/PrivateKey;");
    g_KeyFactoryGenPublicMethod =      GetMethod(env, false, g_KeyFactoryClass, "generatePublic", "(Ljava/security/spec/KeySpec;)Ljava/security/PublicKey;");
    g_KeyFactoryGetKeySpecMethod =     GetMethod(env, false, g_KeyFactoryClass, "getKeySpec", "(Ljava/security/Key;Ljava/lang/Class;)Ljava/security/spec/KeySpec;");

    g_DSAPublicKeySpecClass =              GetClassGRef(env, "java/security/spec/DSAPublicKeySpec");
    g_DSAPublicKeySpecCtor =               GetMethod(env, false, g_DSAPublicKeySpecClass, "<init>", "(Ljava/math/BigInteger;Ljava/math/BigInteger;Ljava/math/BigInteger;Ljava/math/BigInteger;)V");
    g_DSAPublicKeySpecGetY =               GetMethod(env, false, g_DSAPublicKeySpecClass, "getY", "()Ljava/math/BigInteger;");
    g_DSAPublicKeySpecGetP =               GetMethod(env, false, g_DSAPublicKeySpecClass, "getP", "()Ljava/math/BigInteger;");
    g_DSAPublicKeySpecGetQ =               GetMethod(env, false, g_DSAPublicKeySpecClass, "getQ", "()Ljava/math/BigInteger;");
    g_DSAPublicKeySpecGetG =               GetMethod(env, false, g_DSAPublicKeySpecClass, "getG", "()Ljava/math/BigInteger;");

    g_DSAPrivateKeySpecClass =             GetClassGRef(env, "java/security/spec/DSAPrivateKeySpec");
    g_DSAPrivateKeySpecGetX =              GetMethod(env, false, g_DSAPrivateKeySpecClass, "getX", "()Ljava/math/BigInteger;");
    g_DSAPrivateKeySpecCtor =              GetMethod(env, false, g_DSAPrivateKeySpecClass, "<init>", "(Ljava/math/BigInteger;Ljava/math/BigInteger;Ljava/math/BigInteger;Ljava/math/BigInteger;)V");

    g_ECGenParameterSpecClass =        GetClassGRef(env, "java/security/spec/ECGenParameterSpec");
    g_ECGenParameterSpecCtor =         GetMethod(env, false, g_ECGenParameterSpecClass, "<init>", "(Ljava/lang/String;)V");

    g_ECFieldClass =                   GetClassGRef(env, "java/security/spec/ECField");
    g_ECFieldGetFieldSize =            GetMethod(env, false, g_ECFieldClass, "getFieldSize", "()I");

    g_ECFieldFpClass =                 GetClassGRef(env, "java/security/spec/ECFieldFp");
    g_ECFieldFpCtor =                  GetMethod(env, false, g_ECFieldFpClass, "<init>", "(Ljava/math/BigInteger;)V");
    g_ECFieldFpGetP =                  GetMethod(env, false, g_ECFieldFpClass, "getP", "()Ljava/math/BigInteger;");

    g_ECFieldF2mClass =                         GetClassGRef(env, "java/security/spec/ECFieldF2m");
    g_ECFieldF2mCtorWithCoefficientBigInteger = GetMethod(env, false, g_ECFieldF2mClass, "<init>", "(ILjava/math/BigInteger;)V");
    g_ECFieldF2mGetReductionPolynomial =        GetMethod(env, false, g_ECFieldF2mClass, "getReductionPolynomial", "()Ljava/math/BigInteger;");

    g_ECParameterSpecClass =           GetClassGRef(env, "java/security/spec/ECParameterSpec");
    g_ECParameterSpecCtor =            GetMethod(env, false, g_ECParameterSpecClass, "<init>", "(Ljava/security/spec/EllipticCurve;Ljava/security/spec/ECPoint;Ljava/math/BigInteger;I)V");
    g_ECParameterSpecGetCurve =        GetMethod(env, false, g_ECParameterSpecClass, "getCurve", "()Ljava/security/spec/EllipticCurve;");
    g_ECParameterSpecGetGenerator =    GetMethod(env, false, g_ECParameterSpecClass, "getGenerator", "()Ljava/security/spec/ECPoint;");
    g_ECParameterSpecGetCofactor =     GetMethod(env, false, g_ECParameterSpecClass, "getCofactor", "()I");
    g_ECParameterSpecGetOrder =        GetMethod(env, false, g_ECParameterSpecClass, "getOrder", "()Ljava/math/BigInteger;");
    g_ECParameterSpecGetCurveName =    GetOptionalMethod(env, false, g_ECParameterSpecClass, "getCurveName", "()Ljava/lang/String;");

    g_ECPointClass =                   GetClassGRef(env, "java/security/spec/ECPoint");
    g_ECPointCtor =                    GetMethod(env, false, g_ECPointClass, "<init>", "(Ljava/math/BigInteger;Ljava/math/BigInteger;)V");
    g_ECPointGetAffineX =              GetMethod(env, false, g_ECPointClass, "getAffineX", "()Ljava/math/BigInteger;");
    g_ECPointGetAffineY =              GetMethod(env, false, g_ECPointClass, "getAffineY", "()Ljava/math/BigInteger;");

    g_ECPrivateKeyClass =              GetClassGRef(env, "java/security/interfaces/ECPrivateKey");
    g_ECPrivateKeyGetS =               GetMethod(env, false, g_ECPrivateKeyClass, "getS", "()Ljava/math/BigInteger;");

    g_ECPrivateKeySpecClass =          GetClassGRef(env, "java/security/spec/ECPrivateKeySpec");
    g_ECPrivateKeySpecCtor =           GetMethod(env, false, g_ECPrivateKeySpecClass, "<init>", "(Ljava/math/BigInteger;Ljava/security/spec/ECParameterSpec;)V");

    g_ECPublicKeyClass =               GetClassGRef(env, "java/security/interfaces/ECPublicKey");
    g_ECPublicKeyGetParams =           GetMethod(env, false, g_ECPublicKeyClass, "getParams", "()Ljava/security/spec/ECParameterSpec;");
    g_ECPublicKeyGetW =                GetMethod(env, false, g_ECPublicKeyClass, "getW", "()Ljava/security/spec/ECPoint;");

    g_ECPublicKeySpecClass =           GetClassGRef(env, "java/security/spec/ECPublicKeySpec");
    g_ECPublicKeySpecCtor =            GetMethod(env, false, g_ECPublicKeySpecClass, "<init>", "(Ljava/security/spec/ECPoint;Ljava/security/spec/ECParameterSpec;)V");
    g_ECPublicKeySpecGetParams =       GetMethod(env, false, g_ECPublicKeySpecClass, "getParams", "()Ljava/security/spec/ECParameterSpec;");

    g_EllipticCurveClass =             GetClassGRef(env, "java/security/spec/EllipticCurve");
    g_EllipticCurveCtor =              GetMethod(env, false, g_EllipticCurveClass, "<init>", "(Ljava/security/spec/ECField;Ljava/math/BigInteger;Ljava/math/BigInteger;)V");
    g_EllipticCurveCtorWithSeed =      GetMethod(env, false, g_EllipticCurveClass, "<init>", "(Ljava/security/spec/ECField;Ljava/math/BigInteger;Ljava/math/BigInteger;[B)V");
    g_EllipticCurveGetA =              GetMethod(env, false, g_EllipticCurveClass, "getA", "()Ljava/math/BigInteger;");
    g_EllipticCurveGetB =              GetMethod(env, false, g_EllipticCurveClass, "getB", "()Ljava/math/BigInteger;");
    g_EllipticCurveGetField =          GetMethod(env, false, g_EllipticCurveClass, "getField", "()Ljava/security/spec/ECField;");
    g_EllipticCurveGetSeed =           GetMethod(env, false, g_EllipticCurveClass, "getSeed", "()[B");

    g_X509EncodedKeySpecClass =        GetClassGRef(env, "java/security/spec/X509EncodedKeySpec");
    g_X509EncodedKeySpecCtor =         GetMethod(env, false, g_X509EncodedKeySpecClass, "<init>", "([B)V");

    g_DestroyableClass =               GetClassGRef(env, "javax/security/auth/Destroyable");
    g_destroy =                        GetMethod(env, false, g_DestroyableClass, "destroy", "()V");

    g_ArrayListClass =              GetClassGRef(env, "java/util/ArrayList");
    g_ArrayListCtor =               GetMethod(env, false, g_ArrayListClass, "<init>", "()V");
    g_ArrayListCtorWithCapacity =   GetMethod(env, false, g_ArrayListClass, "<init>", "(I)V");
    g_ArrayListCtorWithCollection = GetMethod(env, false, g_ArrayListClass, "<init>", "(Ljava/util/Collection;)V");
    g_ArrayListAdd =                GetMethod(env, false, g_ArrayListClass, "add", "(Ljava/lang/Object;)Z");

    g_CollectionClass =     GetClassGRef(env, "java/util/Collection");
    g_CollectionIterator =  GetMethod(env, false, g_CollectionClass, "iterator", "()Ljava/util/Iterator;");
    g_CollectionSize =      GetMethod(env, false, g_CollectionClass, "size", "()I");

    g_DateClass =   GetClassGRef(env, "java/util/Date");
    g_DateCtor =    GetMethod(env, false, g_DateClass, "<init>", "(J)V");

    g_Enumeration =                 GetClassGRef(env, "java/util/Enumeration");
    g_EnumerationHasMoreElements =  GetMethod(env, false, g_Enumeration, "hasMoreElements", "()Z");
    g_EnumerationNextElement =      GetMethod(env, false, g_Enumeration, "nextElement", "()Ljava/lang/Object;");

    g_HashSetClass =            GetClassGRef(env, "java/util/HashSet");
    g_HashSetCtorWithCapacity = GetMethod(env, false, g_HashSetClass, "<init>", "(I)V");
    g_HashSetAdd =              GetMethod(env, false, g_HashSetClass, "add", "(Ljava/lang/Object;)Z");

    g_IteratorClass =   GetClassGRef(env, "java/util/Iterator");
    g_IteratorHasNext = GetMethod(env, false, g_IteratorClass, "hasNext", "()Z");
    g_IteratorNext =    GetMethod(env, false, g_IteratorClass, "next", "()Ljava/lang/Object;");

    g_ListClass =   GetClassGRef(env, "java/util/List");
    g_ListGet =     GetMethod(env, false, g_ListClass, "get", "(I)Ljava/lang/Object;");

    g_SSLEngine =                         GetClassGRef(env, "javax/net/ssl/SSLEngine");
    g_SSLEngineSetUseClientModeMethod =   GetMethod(env, false, g_SSLEngine, "setUseClientMode", "(Z)V");
    g_SSLEngineGetSessionMethod =         GetMethod(env, false, g_SSLEngine, "getSession", "()Ljavax/net/ssl/SSLSession;");
    g_SSLEngineBeginHandshakeMethod =     GetMethod(env, false, g_SSLEngine, "beginHandshake", "()V");
    g_SSLEngineWrapMethod =               GetMethod(env, false, g_SSLEngine, "wrap", "(Ljava/nio/ByteBuffer;Ljava/nio/ByteBuffer;)Ljavax/net/ssl/SSLEngineResult;");
    g_SSLEngineUnwrapMethod =             GetMethod(env, false, g_SSLEngine, "unwrap", "(Ljava/nio/ByteBuffer;Ljava/nio/ByteBuffer;)Ljavax/net/ssl/SSLEngineResult;");
    g_SSLEngineGetHandshakeStatusMethod = GetMethod(env, false, g_SSLEngine, "getHandshakeStatus", "()Ljavax/net/ssl/SSLEngineResult$HandshakeStatus;");
    g_SSLEngineCloseInboundMethod =       GetMethod(env, false, g_SSLEngine, "closeInbound", "()V");
    g_SSLEngineCloseOutboundMethod =      GetMethod(env, false, g_SSLEngine, "closeOutbound", "()V");

    g_ByteBuffer =                        GetClassGRef(env, "java/nio/ByteBuffer");
    g_ByteBufferAllocateMethod =          GetMethod(env, true,  g_ByteBuffer, "allocate", "(I)Ljava/nio/ByteBuffer;");
    g_ByteBufferPutMethod =               GetMethod(env, false, g_ByteBuffer, "put", "(Ljava/nio/ByteBuffer;)Ljava/nio/ByteBuffer;");
    g_ByteBufferPut2Method =              GetMethod(env, false, g_ByteBuffer, "put", "([B)Ljava/nio/ByteBuffer;");
    g_ByteBufferPut3Method =              GetMethod(env, false, g_ByteBuffer, "put", "([BII)Ljava/nio/ByteBuffer;");
    g_ByteBufferFlipMethod =              GetMethod(env, false, g_ByteBuffer, "flip", "()Ljava/nio/Buffer;");
    g_ByteBufferLimitMethod =             GetMethod(env, false, g_ByteBuffer, "limit", "()I");
    g_ByteBufferGetMethod =               GetMethod(env, false, g_ByteBuffer, "get", "([B)Ljava/nio/ByteBuffer;");
    g_ByteBufferPutBufferMethod =         GetMethod(env, false, g_ByteBuffer, "put", "(Ljava/nio/ByteBuffer;)Ljava/nio/ByteBuffer;");
    g_ByteBufferRemainingMethod =         GetMethod(env, false, g_ByteBuffer, "remaining", "()I");
    g_ByteBufferCompactMethod =           GetMethod(env, false, g_ByteBuffer, "compact", "()Ljava/nio/ByteBuffer;");
    g_ByteBufferPositionMethod =          GetMethod(env, false, g_ByteBuffer, "position", "()I");

    g_SSLContext =                        GetClassGRef(env, "javax/net/ssl/SSLContext");
    g_SSLContextGetInstanceMethod =       GetMethod(env, true,  g_SSLContext, "getInstance", "(Ljava/lang/String;)Ljavax/net/ssl/SSLContext;");
    g_SSLContextInitMethod =              GetMethod(env, false, g_SSLContext, "init", "([Ljavax/net/ssl/KeyManager;[Ljavax/net/ssl/TrustManager;Ljava/security/SecureRandom;)V");
    g_SSLContextCreateSSLEngineMethod =   GetMethod(env, false, g_SSLContext, "createSSLEngine", "()Ljavax/net/ssl/SSLEngine;");

    g_SSLSession =                               GetClassGRef(env, "javax/net/ssl/SSLSession");
    g_SSLSessionGetApplicationBufferSizeMethod = GetMethod(env, false, g_SSLSession, "getApplicationBufferSize", "()I");
    g_SSLSessionGetPacketBufferSizeMethod =      GetMethod(env, false, g_SSLSession, "getPacketBufferSize", "()I");

    g_SSLEngineResult =                          GetClassGRef(env, "javax/net/ssl/SSLEngineResult");
    g_SSLEngineResultGetStatusMethod =           GetMethod(env, false, g_SSLEngineResult, "getStatus", "()Ljavax/net/ssl/SSLEngineResult$Status;");
    g_SSLEngineResultGetHandshakeStatusMethod =  GetMethod(env, false, g_SSLEngineResult, "getHandshakeStatus", "()Ljavax/net/ssl/SSLEngineResult$HandshakeStatus;");

    g_TrustManager =                             GetClassGRef(env, "javax/net/ssl/TrustManager");

    g_KeyAgreementClass          = GetClassGRef(env, "javax/crypto/KeyAgreement");
    g_KeyAgreementGetInstance    = GetMethod(env, true, g_KeyAgreementClass, "getInstance", "(Ljava/lang/String;)Ljavax/crypto/KeyAgreement;");
    g_KeyAgreementInit           = GetMethod(env, false, g_KeyAgreementClass, "init", "(Ljava/security/Key;)V");
    g_KeyAgreementDoPhase        = GetMethod(env, false, g_KeyAgreementClass, "doPhase", "(Ljava/security/Key;Z)Ljava/security/Key;");
    g_KeyAgreementGenerateSecret = GetMethod(env, false, g_KeyAgreementClass, "generateSecret", "()[B");

    return JNI_VERSION_1_6;
}
