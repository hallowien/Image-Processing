#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 512

void convulation(); //konvülasyon hesaplamalarý
void readpgm(); //pgm dosyasýnýn okunmasý
void edgeDetection(double); //threshold deðerine göre edge detection yapýlmasý ve resmin son hali

FILE *fp, *gxfile, *gyfile, *outfile;

int image[SIZE][SIZE];
double temp[SIZE][SIZE], max;

int outimagex[SIZE][SIZE];
int outimagey[SIZE][SIZE];


//filtreler 
int filterx[3][3] = {{-1,0,1},
				   {-2,0,2},
				   {-1,0,1}};
				   
int filtery[3][3] = {{1,2,1},
				    {0,0,0},
				    {-1,-2,-1}};

int main() {
	
    int i,j,x,k,y;

    //input dosyasýnýn açýlmasý
    fp = fopen("lena.pgm", "rb");
    
    readpgm();
	convulation();
	
    //output dosyalarýnýn açýlmasý
    gxfile = fopen("Gx.pgm", "wb");
    gyfile = fopen("Gy.pgm", "wb");
    outfile = fopen("output.pgm", "wb");
	
	//headerlar        
    fprintf(gxfile,"P5\n512 512\n255\n");
    fprintf(gyfile,"P5\n512 512\n255\n");
    fprintf(outfile,"P5\n512 512\n255\n");
    
    
    //gx ve gy filtrelerinin uygulanýp dosyalara yazýlmasý 
    for (x = 0; x < SIZE; x++) {
        for (y = 0; y < SIZE; y++) {
            fprintf(gxfile,"%c",(char)sqrt((double)(outimagex[x][y]*outimagex[x][y])));
            fprintf(gyfile,"%c",(char)sqrt((double)(outimagey[x][y]*outimagey[x][y])));
        }
    }
    
    //max deðerin bulunmasý
        max = 0;
        for (i=k;i<SIZE-k;i++) {
            for (j=k;j<SIZE-k;j++) {
                temp[i][j] = sqrt((double)((outimagex[i][j]*outimagex[i][j]) + (outimagey[i][j]*outimagey[i][j])));
                if (temp[i][j] > max) max = temp[i][j];
            }
        }
        
    //normalizasyon ve bir threshold deðeri ile kenarlarýn belirginleþtirilmesi  
        for (i=0;i<SIZE;i++) {
            for (j=0;j<SIZE;j++) {
                temp[i][j] = (temp[i][j]/max) * 255;
                edgeDetection(temp[i][j]);
            }
        }  
        
    return 0;
}

//threshold deðerinin üstündeki deðerlerin siyah, altýndaki deðerlerin beyaza eþitlenmesi 
void edgeDetection(double value) {
	
	int threshold = 50;   
    if ((int)value >= threshold) {
        fprintf(outfile, "%c", (char)((int)255));
    } else {
        fprintf(outfile, "%c", (char)((int)0));
    }
}

//filtrelerin uygulanmasý
void convulation(){
	
    int i,j,x,y,first,second,k=1;

        for (i=k; i<SIZE-k; i++) {
            for (j=k; j<SIZE-k; j++) {
            	
                first = 0;
                second = 0;
                
                for (x=-k; x<=k; x++) {
                    for (y=-k; y<=k; y++) {
                        first += image[i+x][j+y] * filterx[x+k][y+k];
                        second += image[i+x][j+y] * filtery[x+k][y+k];
                    }
                }
                outimagex[i][j] = first;
                outimagey[i][j] = second;
            }
        }
}

//pgm dosyasýnýn okunup matrise yazýlmasý
void readpgm(){
	
	int i, j;
	
	//input headerý okunmasý 
    char string[10];
    for (i = 0; i < 3; i++) {
        fgets(string, 10, fp);
    }
    
    for (i=0;i<SIZE;i++) {
        for (j=0;j<SIZE;j++) {
                image[i][j] = getc(fp);

        }
    }
}




