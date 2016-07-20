/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile \n");
        return 1;
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];
    int n= atoi(argv[1]);
    if(n<1 || n>100)
    {
        printf("n=[1,100]");
        return 5;
    }

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    
    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    BITMAPINFOHEADER obi;
    BITMAPFILEHEADER obf;
     obi = bi;
     obf=bf;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || bi.biBitCount != 24 || bi.biCompression != 0) 
    
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    
     
// write outfile's BITMAPFILEHEADER
     
    int opadding = (4-(obi.biWidth * sizeof(RGBTRIPLE)) % 4) %4;
    
    
    

    // write outfile's BITMAPINFOHEADER
   
    
    
    obi.biWidth = bi.biWidth *n;
    obi.biHeight = bi.biHeight *n;
    
    
    obi.biSizeImage = ((obi.biWidth * sizeof(RGBTRIPLE))+opadding)*(abs (obi.biHeight));
    
    obf.bfSize = bf.bfSize +obi.biSizeImage - bi.biSizeImage;   
    
    fwrite(&obf,sizeof(BITMAPFILEHEADER), 1, outptr);
    
    fwrite(&obi,sizeof(BITMAPINFOHEADER), 1, outptr);
    
   
   // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    // iterate over infile's scanlines
    
    for (int i = 0; i < abs (bi.biHeight); i++)
    {  //factor n times 
        for(int a=0;a<n;a++)
        {
        // iterate over pixels in scanline
            for (int j = 0; j <bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;
    
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                //write outfile, resize horizontally
        
               int k = 0;
               for(k=0;k<n;k++)
               {
                   fwrite(&triple,sizeof(RGBTRIPLE),1,outptr);
               }
                 
                   
                
            }
               // skip over padding, if any
        
       
        
        //add padding in outfile
        for(int m=0; m < opadding ; m++ )
        {
            fputc(0x00,outptr);
        }
        
        if(a<n-1)
        {
         fseek(inptr,-bi.biWidth * sizeof(RGBTRIPLE),SEEK_CUR);
        }

        }   
        
    fseek(inptr, padding, SEEK_CUR);
    
       
    
         
         
          
}    

        
    
    

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return (0);

}
