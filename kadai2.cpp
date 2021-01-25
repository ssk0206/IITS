#include <stdio.h>
#include <math.h>
#include <string.h>
#include <iostream>
// #include <process.h>
#include "pgm_rw.cpp"
int k[10][5][5] = {
    {
        {-13, 2, 7, 2, -10},
        {2, 17, 22, 17, 2},
        {7, 22, 27, 22, 7},
        {2, 17, 22, 17, 2},
        {-13, 2, 7, 2, -10},
    },
    {
        {31, -44, 0, 44, -31},
        {-5, -62, 0, 62, 5},
        {-17,-68, 0, 68, 17},
        {-5, -62, 0, 62, 5},
        {31, -44, 0, 44, -31},
    },
    {
        {-31, 5, 17, 5, -31},
        {44, 62, 68, 62, 44},
        {0,  0,  0,  0,  0},
        {-44,-62,-68,-62,-44},
        {31, -5, -17, -5, 31},
    },
    {
        {2, -1, -2, -1, 2},
        {2, -1, -2, -1, 2},
        {2, -1, -2, -1, 2},
        {2, -1, -2, -1, 2},
        {2, -1, -2, -1, 2},
    },
    {
        {-4, -2, 0, 2, 4},
        {-2, -1, 0, 1, 2},
        {0, 0, 0, 0, 0},
        {2, 1, 0, -1, -2},
        {4, 2, 0, -2, -4},
    },
    {
        {2, 2, 2, 2, 2},
        {-1, -1, -1, -1, -1},
        {-2, -2, -2, -2, -2},
        {-1, -1, -1, -1, -1},
        {2, 2, 2, 2, 2},
    },
    {
        {-1, 2, 0, 2, 1},
        {-1, 2, 0, 2, 1},
        {-1, 2, 0, 2, 1},
        {-1, 2, 0, 2, 1},
        {-1, 2, 0, 2, 1},
    },
    {
        {4, -2, -4, -2, 4},
        {2, -1, -2, -1, 2},
        {0, 0, 0, 0, 0},
        {-2, 1, 2, 1, -2},
        {-4, 2, 4, 2, -4},
    },
    {
        {-4, -2, 0, 2, 4},
        {2, 1, 0, -1, -2},
        {4, 2, 0, -2, -4},
        {2, 1, 0, -1, -2},
        {-4, -2, 0, 2, 4},
    },
    {
        {1, 1, 1, 1, 1},
        {-2, -2, -2, -2, -2},
        {0, 0, 0, 0, 0},
        {2, 2, 2, 2, 2},
        {-1, -1, -1, -1, -1},
    }
};

int size = 512;

int biCubic(double x, double y, unsigned char (*image)[1000]) {
    double original_x = x*256.0/size;
    double original_y = y*256.0/size;
    double dx = original_x - floor(original_x);
    double dy = original_y - floor(original_y);

    double weight[10] = {
        1, dx, dy, dx*dx, dx*dy, dy*dy, dx*dx*dx, dx*dx*dy, dx*dy*dy, dy*dy*dy
    };

    double denominator[10] = {
        175, 420, 420, 70, 100, 70, 60, 140, 140, 60
    };

    double pixel = 0;
    for (int i = 0; i < 10; i++) { // mask 10
        double sum;
        for (int h = -2; h < 3; h++) {
            for (int w = -2; w < 3; w++) {
                sum += image_in[(int)original_x+w][(int)original_y+h] * k[i][h+2][w+2];
            }
        }
        sum = sum * weight[i] / denominator[i];
        pixel += sum;
    }
    if (pixel == 0) {
        std::cout << pixel << std::endl;
    }
    return (int)pixel;
}

int main(void){
	static unsigned char av[1000][1000];
  	unsigned char ldata[320];
	char fname[100];        //入力ファイル名
	char fnameout[100]="pow2_bicubic_3.pgm";
	int i, j, k, l, m, n, sum, h, w, p, q ;

	//画像読み込み///////////////////////////////////////////////////////////////////////////////////////
	printf("filename:");
	scanf("%s",&fname);
	readPGM(fname,image_in);

   	h = height, w = width;

	//printf("%3d\n",image_in[0][0]);
	printf("h=%3d\n",h);
	printf("w=%3d\n",w);

	// 平均値画像 /////////////////////////////////////////////////////
    //
   	for(i=0; i<size; i++){
	   	for(j=0; j<size; j++){
			av[i][j]=0;
		}
   	}

   	for(j=1; j<size-1; j++){
   		for(i=1; i<size-1; i++){
            av[i][j] = biCubic(i, j, image_in);
	 	}
	}
   	writePGM(av,fnameout);


    return 0;
}
