#include <stdio.h>
#include <math.h>
#include <string.h>
// #include <process.h>
#include "pgm_rw.cpp"

int main(void){
	static unsigned char av[1000][1000];
  	unsigned char ldata[320];
	char fname[100];        //入力ファイル名
	char fnameout[100]="gaussian5.pgm";
	int i, j, k, l, m, n, sum, h, w, p, q ;
    // int mask3[3][3] = {
    //     {1, 2, 1},
    //     {2, 4, 2},
    //     {1, 2, 1},
    // };
    int mask5[5][5] = {
        {1, 4, 6, 4, 1},
        {4, 16, 24, 16, 4},
        {6, 24, 36, 24, 6},
        {4, 16, 24, 16, 4},
        {1, 4, 6, 4, 1},
    };

	//画像読み込み///////////////////////////////////////////////////////////////////////////////////////

	printf("filename:");
	scanf("%s",&fname);
	readPGM(fname,image_in);

   	h = height, w = width;

	//printf("%3d\n",image_in[0][0]);
	printf("h=%3d\n",h);
	printf("w=%3d\n",w);

	// 平均値画像 /////////////////////////////////////////////////////
   	for(i=0; i<h; i++){
	   	for(j=0; j<w; j++){
			av[i][j]=0;
		}
   	}

   	for(j=1; j<w-1; j++){
   		for(i=1; i<h-1; i++){
	 		sum=0.0;
	   		for(l=-2; l<3; l++){
  	 			for(k=-2; k<3; k++){
	 	 			sum=sum+image_in[i+k][j+l]*mask5[k+2][l+2];
		 		}
		 	}
	 		av[i][j]=sum/256.0;
	 	}
	}
   	writePGM(av,fnameout);


    return 0;
}
