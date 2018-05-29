#ifndef YUV2BGR_H
#define YUV2BGR_H
extern void BGR2NV21( unsigned char *imgSrc, unsigned char *imgDst, int width, int height );
extern void NV212BGR( unsigned char *imgY, unsigned char *imgDst,int width, int height );

#endif // YUV2BGR_H
