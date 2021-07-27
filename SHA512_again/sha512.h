
#define SHA512_DIGEST_BLOCKLEN		128
#define SHA512_DIGEST_VALUELEN		64

typedef struct {
	unsigned long long uChainVar[SHA512_DIGEST_BLOCKLEN / 16];
	unsigned long long	uHighLength;
	unsigned long long uLowLength;
	unsigned char szBuffer[SHA512_DIGEST_BLOCKLEN];
} SHA512_INFO;

void SHA512_Init(SHA512_INFO* info);
void SHA512_Transform(SHA512_INFO* context, unsigned long long* data);
void SHA512_Process(SHA512_INFO* Info, unsigned char *pszMessage, unsigned int uDataLen);
void SHA512_Close(SHA512_INFO* Info, unsigned char* pszDigest);
void SHA512(unsigned char *pszMessage, unsigned int uDataLen, unsigned char *pszDigest);

void SHA512_Transform_op(SHA512_INFO* Info, unsigned long long* ChainVar);
void SHA512_op(SHA512_INFO* Info, unsigned char *pszMessage, unsigned int uDataLen, unsigned char* pszDigest);
void SHA512_Enc_op(unsigned char *pszMessage, unsigned int uDataLen, unsigned char *pszDigest);

void Short_Messages_Test();
void Long_Messages_Test();
void Pseudorandomly_Generated_Messages_Test();
