 #include<stdio.h>
 #include<stdlib.h>
 #include<cs50.h>
 #include<stdint.h>
 #include<string.h>
 
 
 
int main(int argc, char* argv[])
{
    // TODO
    FILE *file = fopen("card.raw","r");


    if(file==NULL)
    {
        printf("error reading card.raw");
        return(2);
    }



int count=0;

uint8_t sigc[4];

while(count!=50)
{
    
fread(sigc,sizeof(sigc),1,file);
//check for signature
 if(sigc[0]==0xff && sigc[1]== 0xd8 && sigc[2]==0xff && (sigc[3]==0xe0 || sigc[3]==0xe1))
{
    //read 512 bytes untill new sig
   
    uint8_t buffer[512];
    fseek(file,-4,SEEK_CUR);
    
    
    
    //open new jpg
    
    char title[8];
    sprintf(title,"%03d.jpg",count);
    FILE* image = fopen(title,"a");
    //reading and writing data 
    do
    {
        fread(buffer,sizeof(buffer),1,file);
        fread(sigc,sizeof(sigc),1,file);
        fseek(file,-4,SEEK_CUR);
        fwrite(buffer,sizeof(buffer),1,image);
    }while (sigc[0]==0xff && sigc[1]== 0xd8 && sigc[2]==0xff && (sigc[3]==0xe0 || sigc[3]==0xe1));
    count++;
     fclose(image);
        
}

else
{
    
    fseek(file,508,SEEK_CUR);
    
}


}//end of file

fclose(file);
return 0;

}
