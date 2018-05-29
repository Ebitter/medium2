

void BGR2NV21( unsigned char *imgSrc, unsigned char *imgDst, int width, int height )
{
    int w, h;
    int shift = 14, offset1 = 8192, offset2 = 2105344;
    int C0 = 1868, C1 = 9617, C2 = 4899, C3 = 11682, C4 = 9241;

    int r1,r2,g1,g2,b1,b2;

    unsigned char * pRGB1 = imgSrc;
    unsigned char * pRGB2 = imgSrc+width*3;

    unsigned char * pDY1 = imgDst;
    unsigned char * pDY2 = imgDst+width;
    unsigned char * pDUV = imgDst+width*height;

    for ( h = 0; h < height; h += 2 )
    {
        for ( w = 0; w < width; w += 2 )
        {
            b1 = *pRGB1++;
            g1 = *pRGB1++;
            r1 = *pRGB1++;
            *pDY1  = (b1 * C0 + g1 * C1 + r1 * C2 + offset1) >> shift;
            *pDUV++ = ((r1 - *pDY1) * C3 + offset2) >> shift;
            *pDUV++ = ((b1 - *pDY1) * C4 + offset2) >> shift;
            pDY1++;

            b1 = *pRGB1++;
            g1 = *pRGB1++;
            r1 = *pRGB1++;
            *pDY1  = (b1 * C0 + g1 * C1 + r1 * C2 + offset1) >> shift;
            pDY1++;

            b2 = *pRGB2++;
            g2 = *pRGB2++;
            r2 = *pRGB2++;
            *pDY2  = (b2 * C0 + g2 * C1 + r2 * C2 + offset1) >> shift;
            pDY2++;

            b2 = *pRGB2++;
            g2 = *pRGB2++;
            r2 = *pRGB2++;
            *pDY2  = (b2 * C0 + g2 * C1 + r2 * C2 + offset1) >> shift;
            pDY2++;
        }
        pRGB1 += 3*width;
        pRGB2 += 3*width;
        pDY1 += width;
        pDY2 += width;

    }
}
#define MAX(a ,b) ((a > b) ? a : b)
#define MIN(a ,b) ((a < b) ? a : b)
#define CLAP(a) (MAX((MIN(a, 0xff)), 0x00))
void NV212BGR( unsigned char *imgY, unsigned char *imgDst,int width, int height )
{
    int w, h;
    int shift = 14, offset = 8192;
    int C0 = 22987, C1 = -11698, C2 = -5636, C3 = 29049;

    int y1,y2,u1,v1;

    unsigned char * pY1 = imgY;
    unsigned char * pY2 = imgY+width;
    unsigned char * pUV = imgY+width*height;

    unsigned char * pD1 = imgDst;
    unsigned char * pD2 = imgDst+width*3;

    for ( h = 0; h < height; h +=2 )
    {
        for ( w = 0; w < width; w +=2 )
        {
            v1 = *pUV-128;
            pUV++;
            u1 = *pUV-128;
            pUV++;


            y1 = *pY1;
            y2 = *pY2;

            *pD1++ = CLAP(y1+((u1 * C3 + offset) >> shift));
            *pD1++ = CLAP(y1+((u1 * C2 + v1 * C1 + offset) >> shift));
            *pD1++ = CLAP(y1+((v1 * C0 + offset) >> shift));
            *pD2++ = CLAP(y2+((u1 * C3 + offset) >> shift));
            *pD2++ = CLAP(y2+((u1 * C2 + v1 * C1 + offset) >> shift));
            *pD2++ = CLAP(y2+((v1 * C0 + offset) >> shift));

            pY1++;
            pY2++;
            y1 = *pY1;
            y2 = *pY2;

            *pD1++ = CLAP(y1+((u1 * C3 + offset) >> shift));
            *pD1++ = CLAP(y1+((u1 * C2 + v1 * C1 + offset) >> shift));
            *pD1++ = CLAP(y1+((v1 * C0 + offset) >> shift));
            *pD2++ = CLAP(y2+((u1 * C3 + offset) >> shift));
            *pD2++ = CLAP(y2+((u1 * C2 + v1 * C1 + offset) >> shift));
            *pD2++ = CLAP(y2+((v1 * C0 + offset) >> shift));
            pY1++;
            pY2++;

        }
        pY1 += width;
        pY2 += width;
        pD1 += 3*width;
        pD2 += 3*width;

    }
}
