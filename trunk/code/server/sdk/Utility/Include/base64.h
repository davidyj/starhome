//===================================================
//==================base64º”√‹=======================
//===================================================

#ifndef _BASE64_H_
#define _BASE64_H_


int DecodeBase64(const char* pSrc, char* pDst, int nSrcLen);
int EncodeBase64(const char* pSrc, char* pDst, int nSrcLen/*, int nMaxLineLen*/);


#endif
