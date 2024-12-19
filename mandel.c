#include <stdio.h>
#include "fracs.h"


int main()
{
    frac zero = value2frac(0);

    
    const int iXmax = 200;
    const int iYmax = 200;
        
    /*
    const double CxMin=-2;
    const double CxMax= 1;
    const double CyMin=-2.0;
    const double CyMax= 2.0;
    */
    
    frac CxMin = neg(value2frac(2));
    frac CxMax =     value2frac(1);
    frac CyMin = neg(value2frac(2));
    frac CyMax =     value2frac(2);



    
    /*
    double PixelWidth  = (CxMax-CxMin) / iXmax;
    double PixelHeight = (CyMax-CyMin) / iYmax;
    */
    
    frac PixelWidth  = div(add(CxMax, neg(CxMin)), value2frac(iXmax));
    frac PixelHeight = div(add(CyMax, neg(CyMin)), value2frac(iYmax));


    const int maxIter=20;

    FILE* fp = fopen("new.ppm","wb");
    fprintf(fp,"P6\n %d\n %d\n 255\n", iXmax, iYmax);

    for(int iY=0; iY<iYmax; iY++)
    for(int iX=0; iX<iXmax; iX++)
    {   
        /*
        double Cx=CxMin + iX*PixelWidth;
        double Cy=CyMin + iY*PixelHeight;
        */
        frac marX = mul(PixelWidth,  value2frac(iX));
        frac marY = mul(PixelHeight, value2frac(iY));

        frac Cx = add(CxMin, marX);
        frac Cy = add(CyMin, marY);


        /*
        double Zx=0.0;
        double Zy=0.0;
        double Zx2=Zx*Zx;
        double Zy2=Zy*Zy;
        */
        
        frac Zx  = zero;
        frac Zy  = zero;
        frac Zx2 = zero;
        frac Zy2 = zero;



        int iter = 0;
        //for (; iter < maxIter && ((Zx2+Zy2) < 4.0); iter++)
        for (; iter < maxIter && comp(value2frac(4), add(Zx2, Zy2)); iter++)
        {
            Zy = add(mul(mul(Zx, Zy), value2frac(2)), Cy);
            Zx = add(add(Zx2, neg(Zy2)), Cx);
            Zx2 = mul(Zx, Zx);
            Zy2 = mul(Zy, Zy);
            
        }
                
        double gray = ((double)iter / maxIter) * 255.0;

        static unsigned char colors[3];
        colors[0]=(int)gray;
        colors[1]=(int)0;
        colors[2]=(int)gray;

        fwrite(colors, 1, 3, fp);
    }

    fclose(fp);
    return 0;
}
