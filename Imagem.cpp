#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "vector_oper.cpp"
#include <Imagem.h>

void Imagem::setWidth(u_int w){
	width = w;
}

u_int Imagem::getWidth(){
	return width;
}

void Imagem::setHeight(u_int h){
	height = h;
}

u_int Imagem::getHeight(){
	return height;
}

void Imagem::setType(char t[]){
	strcpy(type, t);
}

char* Imagem::getType(){
	return type;
}

void Imagem::setPGM(PIXEL* pgm){

    for(u_int k = 0; k < n; k++){
        px[k].i = pgm[k].i;
    }
}

void Imagem::setPPM(PIXEL* ppm){
    for(u_int k = 0; k < n; k++){
        px[k].r = ppm[k].r;
        px[k].g = ppm[k].g;
        px[k].b = ppm[k].b;
        px[k].i = (u_int) ((ppm[k].r + ppm[k].g + ppm[k].b) / 3);
    }
}

void Imagem::setPPM(u_int R[], u_int G[], u_int B[]){
    for(u_int k = 0; k < n; k++){
        px[k].r = R[k];
        px[k].g = G[k];
        px[k].b = B[k];
    }
}

void Imagem::setImg(PIXEL* pgm, PIXEL* ppm, PIXEL* img, u_int w, u_int h){

}

PIXEL* Imagem::getImg(){
    return px;
}

u_int* Imagem::getR(){
    u_int *result;

    result = (u_int*) malloc(n*sizeof(u_int));

    for(u_int k = 0; k < n; k++){
        result[k] = px[k].r;
    }

    return result;
}

u_int* Imagem::getG(){
    u_int *result;

    result = (u_int*) malloc(n*sizeof(u_int));

    for(u_int k = 0; k < n; k++){
        result[k] = px[k].g;
    }

    return result;
}

u_int* Imagem::getB(){
    u_int *result;

    result = (u_int*) malloc(n*sizeof(u_int));

    for(u_int k = 0; k < n; k++){
        result[k] = px[k].b;
    }

    return result;
}

void Imagem::readPGM(FILE* arq, const char* filename){
	u_int w, h, maxsize;
	char t[2];

	arq = fopen(filename, "r");

	if(arq == NULL) cout<< "Erro na abertura do arquivo" << "\n";
	else{
		fscanf(arq, "%s %u %u %u", &t, &w, &h, &maxsize);

		setType(t);
		width = w;
		height = h;
		n = w * h;

		px = (PIXEL*) malloc(sizeof(PIXEL)*w*h);

		for(u_int k = 0; k < n; k++){
			fscanf(arq, "%u", &px[k].i);
		}
	}

	fclose(arq);
}

void Imagem::writePGM(FILE* arq, const char* filename){
    u_int maxsize = 255;
	arq = fopen(filename, "w");

	if(arq == NULL) cout<< "Erro na abertura do arquivo" << "\n";
	else{
		fprintf(arq, "P2\n");
		fprintf(arq, "%u %u ", width, height);
		fprintf(arq, "%u\n", maxsize);

		for(u_int k = 0; k < n; k++){
			fprintf(arq, "%u ", px[k].i);
		}
	}

	fclose(arq);
}

void Imagem::readPPM(FILE* arq, const char* filename){
	u_int w, h, maxsize;
	char t[2];

	arq = fopen(filename, "r");

	if(arq == NULL) cout<< "Erro na abertura do arquivo" << "\n";
	else{
		fscanf(arq, "%s %u %u %u", &t, &w, &h, &maxsize);

		setType(t);
		width = w;
		height = h;
		n = w * h;


        if(px == NULL){
            px = (PIXEL*) malloc(sizeof(PIXEL)*n);
        }
        for(u_int k = 0; k < n; k++){
            fscanf(arq, "%u %u %u", &px[k].r, &px[k].g, &px[k].b);
        }


	}

	fclose(arq);
}

void Imagem::writePPM(FILE* arq, const char* filename){
    u_int maxsize = 255;
	arq = fopen(filename, "w");

	if(arq == NULL) cout<< "Erro na abertura do arquivo" << "\n";
	else{
		fprintf(arq, "P3\n");
		fprintf(arq, "%u %u ", width, height);
		fprintf(arq, "%u\n", maxsize);

		for(u_int k = 0; k < n; k++){
			fprintf(arq, "%u %u %u ", px[k].r, px[k].g, px[k].b);
		}
	}

	fclose(arq);
}

void Imagem::thresholdGray(u_int th){
	for(u_int k = 0; k < n; k++){
		if((u_int) px[k].i < th) px[k].i = 255;
		else px[k].i = 0;
	}
}

void Imagem::thresholdGray(u_int thlow, u_int thhigh){

	for(u_int k = 0; k < n; k++){
		if(((u_int) px[k].i > thlow) && ((u_int) px[k].i < thhigh)) px[k].i = 255;
		else px[k].i = 0;
	}
}

void Imagem::inverseGray(){

	for(u_int k = 0; k < n; k++){
		px[k].i = 255 - px[k].i;
	}
}

void Imagem::addGray(unsigned char value){

	for(u_int k = 0; k < n; k++){
		if((int) (px[k].i + value) > 255) px[k].i = 255;
        else px[k].i += value;
	}
}

void Imagem::inverseColor(){
	for(u_int k = 0; k < n; k++){
		px[k].r = 255 - px[k].r;
		px[k].g = 255 - px[k].g;
		px[k].b = 255 - px[k].b;
	}
}

void Imagem::addColor(unsigned char value){
	for(u_int k = 0; k < n; k++){
		if((int) (px[k].r + value) > 255) px[k].r = 255;
        else px[k].r += value;
        if((int) (px[k].g + value) > 255) px[k].g = 255;
        else px[k].g += value;
        if((int) (px[k].b + value) > 255) px[k].b = 255;
        else px[k].b += value;
	}
}

void Imagem::addColor(unsigned char valueR, unsigned char valueG, unsigned char valueB){

	for(u_int k = 0; k < n; k++){
		if((int) (px[k].r + valueR) > 255) px[k].r = 255;
        else px[k].r += valueR;

        if((int) (px[k].g + valueG) > 255) px[k].g = 255;
        else px[k].g += valueG;

        if((int) (px[k].b + valueB) > 255) px[k].b = 255;
        else px[k].b += valueB;
	}
}

void Imagem::rgb2Gray(){
	u_int value;

	for(u_int k = 0; k < n; k++){
		value = ((u_int) px[k].r + px[k].g + px[k].b) / 3;
        px[k].i = value;
	}
}

void Imagem::normL1(u_int refR, u_int refG, u_int refB, u_int th){
    int l1;

    for(u_int k = 0; k < n; k++){
        //index = k / width;
        l1 = abs(((int)px[k].r - (int)refR) + ((int)px[k].g - (int)refG) + ((int)px[k].b - (int)refB));
        if(l1 < th){
            px[k].r = 0;
            px[k].g = 0;
            px[k].b = 0;
        }
        else{
            px[k].r = 255;
            px[k].g = 255;
            px[k].b = 255;
        }
    }
}

void Imagem::normL2(u_int refR, u_int refG, u_int refB, u_int th){
    int l2;

    for(u_int k = 0; k < n; k++){
        //index = k / width;
        l2 = sqrt(((px[k].r - refR)*(px[k].r - refR)) + ((px[k].g - refG)*(px[k].g - refG)) + ((px[k].b - refB)*(px[k].b - refB)));
        if(l2 < th){
            px[k].r = 0;
            px[k].g = 0;
            px[k].b = 0;
        }
        else{
            px[k].r = 255;
            px[k].g = 255;
            px[k].b = 255;
        }
    }
}

void Imagem::normMahalanobis(u_int *vectorR, u_int *vectorG, u_int *vectorB, u_int tam, u_int th){
    u_int index = 0;
    double *mCovariance, *aux;
    double *mCov_inv, dist;
    double mR, mG, mB;

    mCovariance = (double*) malloc(9*sizeof(double));
    aux = (double*)malloc(width*height*3*sizeof(double));

    mR = average(vectorR, tam);
    mG = average(vectorG, tam);
    mB = average(vectorB, tam);


    //Linha 1
    mCovariance[0] = covariance(vectorR, vectorR, tam, mR, mR);
    mCovariance[1] = covariance(vectorR, vectorG, tam, mR, mG);
    mCovariance[2] = covariance(vectorR, vectorB, tam, mR, mB);
    //Linha 2
    mCovariance[3] = covariance(vectorG, vectorR, tam, mG, mR);
    mCovariance[4] = covariance(vectorG, vectorG, tam, mG, mG);
    mCovariance[5] = covariance(vectorG, vectorB, tam, mG, mB);
    //Linha 3
    mCovariance[6] = covariance(vectorB, vectorR, tam, mB, mR);
    mCovariance[7] = covariance(vectorB, vectorG, tam, mB, mG);
    mCovariance[8] = covariance(vectorB, vectorB, tam, mB, mB);

    mCov_inv = inverse(mCovariance);

    for(u_int k = 0; k < (width * height); k++){
        aux[index] = ((px[k].r - mR) * mCov_inv[0]) + ((px[k].g - mG) * mCov_inv[1]) + ((px[k].b - mB) * mCov_inv[2]);
        aux[index + 1] = ((px[k].r - mR) * mCov_inv[3]) + ((px[k].g - mG) * mCov_inv[4]) + ((px[k].b - mB) * mCov_inv[5]);
        aux[index + 2] = ((px[k].r - mR) * mCov_inv[6]) + ((px[k].g - mG) * mCov_inv[7]) + ((px[k].b - mB) * mCov_inv[8]);
        index += 3;

    }


    index = 0;
    for(u_int k = 0; k < (width * height); k++){
        dist = sqrt((aux[index] * (px[k].r - mR)) + (aux[index + 1] * (px[k].g - mG)) + (aux[index + 2] * (px[k].b - mB)));
        index += 3;
        if(dist < (double)th){
            px[k].r = 0;
            px[k].g = 0;
            px[k].b = 0;
        }
        else{
            px[k].r = 255;
            px[k].g = 255;
            px[k].b = 255;
        }
    }
}

void Imagem::normKneighbors(u_int *vectorR, u_int *vectorG, u_int *vectorB, u_int s, u_int numOrb, u_int th){
    u_int sizeSeg;
    double mR, mG, mB;
    double de;
    PIXEL *aux;

    aux = (PIXEL*) malloc(width*height*sizeof(PIXEL));

    for(u_int k = 0; k < (width*height); k++){
        aux[k].r = px[k].r;
        aux[k].g = px[k].g;
        aux[k].b = px[k].b;
    }

    sizeSeg = s / numOrb;


    for(u_int i = 1; i <= numOrb; i++){
        mR = average(vectorR, (i*sizeSeg - sizeSeg), (i*sizeSeg));
        mG = average(vectorG, (i*sizeSeg - sizeSeg), (i*sizeSeg));
        mB = average(vectorB, (i*sizeSeg - sizeSeg), (i*sizeSeg));

        for(u_int k = 0; k < (width*height); k++){
            de = ((px[k].r - mR)*(px[k].r - mR)) + ((px[k].g - mG)*(px[k].g - mG)) + ((px[k].b - mB)*(px[k].b - mB));


            if(sqrt(de) < (double)th){
                aux[k].r = 0;
                aux[k].g = 0;
                aux[k].b = 0;
            }
            else{
                aux[k].r = 255;
                aux[k].g = 255;
                aux[k].b = 255;
            }
        }
    }
    setPPM(aux);
}

double* Imagem::findWeightArray(u_int s){
    u_int cnt_l, cnt_c, cnt_k, cont, k, mx;
    u_int *sampleR, *sampleG, *sampleB;
    int posY, posX;
    double vrR, vrG, vrB, avR, avG, avB;;
    double *w;

    sampleR = (u_int*) malloc(s*s*sizeof(u_int));
    sampleG = (u_int*) malloc(s*s*sizeof(u_int));
    sampleB = (u_int*) malloc(s*s*sizeof(u_int));

    w = (double*) malloc(n*3*sizeof(double));

    cont = 0;

    for(u_int i_line = 0; i_line < height; i_line++){
        for(u_int i_column = 0; i_column < width; i_column++){
            k = i_line*width + i_column;

            // Set 0 para variáveis auxiliares
            cnt_l = 0; cnt_c = 0;
            posY = 0; posX = 0;

            while(1){
                posY = (i_line - (s / 2) + cnt_l);
                posX = (i_column - (s / 2) + cnt_c);

                // trata as bordas superiores
                if(posY < 0){
                    if(posX < 0)
                        cnt_k = (height + posY) * width + (width + posX);
                    else if(posX >= width)
                        cnt_k = (height + posY) * width + (width - posX);
                    else
                        cnt_k = (height + posY) * width + posX;
                }
                // trata as bordas inferiores
                else if(posY >= height){
                    if(posX < 0)
                        cnt_k = (height - posY) * width + (width + posX);
                    else if(posX >= width)
                        cnt_k = (height - posY) * width + (width - posX);
                    else
                        cnt_k = (height - posY) * width + posX;
                }
                // trata as bordas laterais
                else{
                    if(posX < 0)
                        cnt_k = posY * width + (width + posX);
                    else if(posX >= width)
                        cnt_k = posY * width + (width - posX);
                    else
                        cnt_k = posY * width + posX;
                }
                if(cnt_l == (s-1) && cnt_c == (s-1)){
                    sampleR[cnt_l*s + cnt_c] = px[cnt_k].r;
                    sampleG[cnt_l*s + cnt_c] = px[cnt_k].g;
                    sampleB[cnt_l*s + cnt_c] = px[cnt_k].b;
                    break;
                }
                else{
                    sampleR[cnt_l*s + cnt_c] = px[cnt_k].r;
                    sampleG[cnt_l*s + cnt_c] = px[cnt_k].g;
                    sampleB[cnt_l*s + cnt_c] = px[cnt_k].b;
                    cnt_c++;
                }
                if(cnt_c == s){
                    cnt_l++;
                    cnt_c = 0;
                }
            }

            // Média dos pontos
            avR = average(sampleR, s*s); avG = average(sampleG, s*s); avB = average(sampleB, s*s);
            // Variância dos pontos
            vrR = variance(sampleR, s*s, avR); vrG = variance(sampleG, s*s, avG); vrB = variance(sampleB, s*s, avB);

            // Cálculo dos pesos
            w[cont] = vrR;
            w[cont+1] = vrG;
            w[cont+2] = vrB;
            cont += 3;
        }
    }

    mx = maxFind(w, n*3);
    parameterize(w, n*3, mx, 1, 20);
    reverseValue(w, n*3, 20);

    return w;
}

void Imagem::filter(int kernel[], u_int s, u_int w){
    PIXEL *result;
    u_int k = 0, sumR, sumG, sumB, cnt_l = 0, cnt_c = 0, cnt_k = 0, maxR = 0, maxG = 0, maxB = 0;
    u_int *vectR, *vectG, *vectB;
    int posY, posX;
    bool flag;

    result = (PIXEL*) malloc(n*sizeof(PIXEL));
    vectR = (u_int*) malloc(n*sizeof(u_int));
    vectG = (u_int*) malloc(n*sizeof(u_int));
    vectB = (u_int*) malloc(n*sizeof(u_int));

    for(u_int i_line = 0; i_line < height; i_line++){
        for(u_int i_column = 0; i_column < width; i_column++){
            k = i_line*width + i_column;

            // Set 0 para variáveis auxiliares
            cnt_l = 0; cnt_c = 0;
            sumR = 0; sumG = 0; sumB = 0;
            posY = 0; posX = 0;
            flag = false;

            while(flag != true){
                posY = (i_line - (s / 2) + cnt_l);
                posX = (i_column - (s / 2) + cnt_c);

                // trata as bordas superiores
                if(posY < 0){
                    if(posX < 0)
                        cnt_k = (height + posY) * width + (width + posX);
                    else if(posX >= width)
                        cnt_k = (height + posY) * width + (width - posX);
                    else
                        cnt_k = (height + posY) * width + posX;
                }
                // trata as bordas inferiores
                else if(posY >= height){
                    if(posX < 0)
                        cnt_k = (height - posY) * width + (width + posX);
                    else if(posX >= width)
                        cnt_k = (height - posY) * width + (width - posX);
                    else
                        cnt_k = (height - posY) * width + posX;
                }
                // trata as bordas laterais
                else{
                    if(posX < 0)
                        cnt_k = posY * width + (width + posX);
                    else if(posX >= width)
                        cnt_k = posY * width + (width - posX);
                    else
                        cnt_k = posY * width + posX;
                }
                if(cnt_l == (s-1) && cnt_c == (s-1)){
                    sumR += kernel[cnt_l*s + cnt_c]*px[cnt_k].r;
                    sumG += kernel[cnt_l*s + cnt_c]*px[cnt_k].g;
                    sumB += kernel[cnt_l*s + cnt_c]*px[cnt_k].b;
                    flag = true;
                }
                else{
                    sumR += kernel[cnt_l*s + cnt_c]*px[cnt_k].r;
                    sumG += kernel[cnt_l*s + cnt_c]*px[cnt_k].g;
                    sumB += kernel[cnt_l*s + cnt_c]*px[cnt_k].b;
                    cnt_c++;
                }
                if(cnt_c == s){
                    cnt_l++;
                    cnt_c = 0;
                }
            }
            result[k].r = w*sumR; result[k].g = w*sumG; result[k].b = w*sumB;
        }
    }

    // Normalizando os valores dos pixels entre 0 e 255
    for(u_int k = 0; k < n; k++){
        vectR[k] = result[k].r;
        vectG[k] = result[k].g;
        vectB[k] = result[k].b;
    }
    maxR = maxFind(vectR, n);
    maxG = maxFind(vectG, n);
    maxB = maxFind(vectB, n);
    parameterize(vectR, n, maxR, 255);
    parameterize(vectG, n, maxG, 255);
    parameterize(vectB, n, maxB, 255);

    setPPM(vectR, vectG, vectB);
}

void Imagem::filter(int kernel[], u_int s, double w[]){
    PIXEL *result;
    u_int k = 0, cnt_l = 0, cnt_c = 0, cnt_k = 0, maxR = 0, maxG = 0, maxB = 0, cont = 0, sumR, sumG, sumB;
    double *vectR, *vectG, *vectB;
    int posY, posX;

    result = (PIXEL*) malloc(n*sizeof(PIXEL));
    vectR = (double*) malloc(n*sizeof(double));
    vectG = (double*) malloc(n*sizeof(double));
    vectB = (double*) malloc(n*sizeof(double));


    for(u_int i_line = 0; i_line < height; i_line++){
        for(u_int i_column = 0; i_column < width; i_column++){
            k = i_line*width + i_column;

            // Set 0 para variáveis auxiliares
            cnt_l = 0; cnt_c = 0;
            sumR = 0; sumG = 0; sumB = 0;
            posY = 0; posX = 0;

            while(1){
                posY = (i_line - (s / 2) + cnt_l);
                posX = (i_column - (s / 2) + cnt_c);

                // trata as bordas superiores
                if(posY < 0){
                    if(posX < 0)
                        cnt_k = (height + posY) * width + (width + posX);
                    else if(posX >= width)
                        cnt_k = (height + posY) * width + (width - posX);
                    else
                        cnt_k = (height + posY) * width + posX;
                }
                // trata as bordas inferiores
                else if(posY >= height){
                    if(posX < 0)
                        cnt_k = (height - posY) * width + (width + posX);
                    else if(posX >= width)
                        cnt_k = (height - posY) * width + (width - posX);
                    else
                        cnt_k = (height - posY) * width + posX;
                }
                // trata as bordas laterais
                else{
                    if(posX < 0)
                        cnt_k = posY * width + (width + posX);
                    else if(posX >= width)
                        cnt_k = posY * width + (width - posX);
                    else
                        cnt_k = posY * width + posX;
                }
                if(cnt_l == (s-1) && cnt_c == (s-1)){
                    sumR += kernel[cnt_l*s + cnt_c]*px[cnt_k].r;
                    sumG += kernel[cnt_l*s + cnt_c]*px[cnt_k].g;
                    sumB += kernel[cnt_l*s + cnt_c]*px[cnt_k].b;
                    break;
                }
                else{
                    sumR += kernel[cnt_l*s + cnt_c]*px[cnt_k].r;
                    sumG += kernel[cnt_l*s + cnt_c]*px[cnt_k].g;
                    sumB += kernel[cnt_l*s + cnt_c]*px[cnt_k].b;
                    cnt_c++;
                }
                if(cnt_c == s){
                    cnt_l++;
                    cnt_c = 0;
                }
            }
            vectR[k] = w[cont] * sumR; vectG[k] = w[cont + 1] * sumG; vectB[k] = w[cont + 2] * sumB;
            cont += 3;
        }
    }

    maxG = maxFind(vectG, n);
    maxR = maxFind(vectR, n);
    maxB = maxFind(vectB, n);
    parameterize(vectR, n, maxR, 255);
    parameterize(vectG, n, maxG, 255);
    parameterize(vectB, n, maxB, 255);

    for(u_int j = 0; j < n; j++){
        result[j].r = (u_int) vectR[j];
        result[j].g = (u_int) vectG[j];
        result[j].b = (u_int) vectB[j];
    }

    setPPM(result);
}

void Imagem::edgeRoberts(u_int th){
    u_int k;
    double mx;
    int Gx[4] = {0, 1, -1, 0};
    int Gy[4] = {1, 0, 0, -1};
    int *convX, *convY;
    double *vectG;

    convX = (int*) malloc((width-1)*(height-1)*sizeof(int));
    convY = (int*) malloc((width-1)*(height-1)*sizeof(int));
    vectG = (double*) malloc(n*sizeof(double));

    for(u_int i_line = 0; i_line < height; i_line++){
        for(u_int i_column = 0; i_column < width; i_column++){
            k = i_line*width + i_column;

            // Posições fora da borda inferior e borda direita da matriz
            if(i_line < (height-1) && i_column < (width-1)){
                // Convolução em X e em Y
                convX[k] =  Gx[0]*px[k].i + Gx[1]*px[k + 1].i + Gx[2]*px[k + width].i + Gx[3]*px[k + width + 1].i;
                convY[k] =  Gy[0]*px[k].i + Gy[1]*px[k + 1].i + Gy[2]*px[k + width].i + Gy[3]*px[k + width + 1].i;

                vectG[k] = sqrt( ((double)convX[k]*convX[k]) + ((double)convY[k]*convY[k]) );
            }
            else{
                //printf("k = %d\n", k);
                vectG[k] = 0;
            }
        }
    }

    mx = maxFind(vectG, n);
    parameterize(vectG, n, mx, 255);

    for(u_int j = 0; j < n; j++){
        px[j].i = (u_int) vectG[j];
    }

    thresholdGray(th);
}

void Imagem::edgeSobel(u_int th){
    u_int k, mx;
    int Gx[9] = {   1, 2, 1,
                    0, 0, 0,
                    -1, -2, -1};
    int Gy[9] = {   1, 0, -1,
                    2, 0, -2,
                    1, 0, -1};
    int *convX, *convY;
    u_int *vectGray;

    convX = (int*) malloc(n*sizeof(int));
    convY = (int*) malloc(n*sizeof(int));
    vectGray = (u_int*) malloc(n*sizeof(u_int));

    for(u_int i_line = 0; i_line < height; i_line++){
        for(u_int i_column = 0; i_column < width; i_column++){
            k = i_line*width + i_column;

            // Posições fora das bordas da matriz
            if((i_line < (height-1)) && (i_column < (width-1)) && (i_line > 0) && (i_column > 0)){
                // Convolução em X e em Y
                convX[k] =  Gx[0]*px[k - width - 1].i + Gx[1]*px[k - width].i + Gx[2]*px[k - width + 1].i +
                            Gx[3]*px[k - 1].i + Gx[4]*px[k].i + Gx[5]*px[k + 1].i +
                            Gx[6]*px[k + width - 1].i + Gx[7]*px[k + width].i + Gx[8]*px[k + width + 1].i;
                convY[k] =  Gy[0]*px[k - width - 1].i + Gy[1]*px[k - width].i + Gy[2]*px[k - width + 1].i +
                            Gy[3]*px[k - 1].i + Gy[4]*px[k].i + Gy[5]*px[k + 1].i +
                            Gy[6]*px[k + width - 1].i + Gy[7]*px[k + width].i + Gy[8]*px[k + width + 1].i;
            }
            else{
                if(i_line == 0){
                    if(i_column == 0){
                        convX[k] =  Gx[0]*px[n - 1].i + Gx[1]*px[n - width].i + Gx[2]*px[n - width + 1].i +
                                    Gx[3]*px[width - 1].i + Gx[4]*px[k].i + Gx[5]*px[k + 1].i +
                                    Gx[6]*px[2*width - 1].i + Gx[7]*px[k + width].i + Gx[8]*px[k + width + 1].i;
                        convY[k] =  Gy[0]*px[n - 1].i + Gy[1]*px[n - width].i + Gy[2]*px[n - width + 1].i +
                                    Gy[3]*px[width - 1].i + Gy[4]*px[k].i + Gy[5]*px[k + 1].i +
                                    Gy[6]*px[2*width - 1].i + Gy[7]*px[k + width].i + Gy[8]*px[k + width + 1].i;
                    }
                    else if(i_column == (width - 1)){
                        convX[k] =  Gx[0]*px[n - 2].i + Gx[1]*px[n - 1].i + Gx[2]*px[n - width].i +
                                    Gx[3]*px[k - 1].i + Gx[4]*px[k].i + Gx[5]*px[0].i +
                                    Gx[6]*px[k + width - 1].i + Gx[7]*px[k + width].i + Gx[8]*px[k + 1].i;
                        convY[k] =  Gy[0]*px[n - 2].i + Gy[1]*px[n - 1].i + Gy[2]*px[n - width].i +
                                    Gy[3]*px[k - 1].i + Gy[4]*px[k].i + Gy[5]*px[0].i +
                                    Gy[6]*px[k + width - 1].i + Gy[7]*px[k + width].i + Gy[8]*px[k + 1].i;
                    }
                    else{
                        convX[k] =  Gx[0]*px[n - width + k - 1].i + Gx[1]*px[n - width + k].i + Gx[2]*px[n - width + k + 1].i +
                                    Gx[3]*px[k - 1].i + Gx[4]*px[k].i + Gx[5]*px[k + 1].i +
                                    Gx[6]*px[k + width - 1].i + Gx[7]*px[k + width].i + Gy[8]*px[k + width + 1].i;
                        convY[k] =  Gy[0]*px[n - width + k - 1].i + Gy[1]*px[n - width + k].i + Gy[2]*px[n - width + k + 1].i +
                                    Gy[3]*px[k - 1].i + Gy[4]*px[k].i + Gy[5]*px[k + 1].i +
                                    Gy[6]*px[k + width - 1].i + Gy[7]*px[k + width].i + Gy[8]*px[k + width + 1].i;
                    }
                }
                else if(i_line == (height - 1)){
                    if(i_column == 0){
                        convX[k] =  Gx[0]*px[k - 1].i + Gx[1]*px[k - width].i + Gx[2]*px[k - width + 1].i +
                                    Gx[3]*px[n - 1].i + Gx[4]*px[k].i + Gx[5]*px[k + 1].i +
                                    Gx[6]*px[width - 1].i + Gx[7]*px[0].i + Gx[8]*px[1].i;
                        convY[k] =  Gy[0]*px[k - 1].i + Gy[1]*px[k - width].i + Gy[2]*px[k - width + 1].i +
                                    Gy[3]*px[n - 1].i + Gy[4]*px[k].i + Gy[5]*px[k + 1].i +
                                    Gy[6]*px[width - 1].i + Gy[7]*px[0].i + Gy[8]*px[1].i;
                    }
                    else if(i_column == (width - 1)){
                        convX[k] =  Gx[0]*px[n - width - 2].i + Gx[1]*px[n - width - 1].i + Gx[2]*px[k - width - (k % width)].i +
                                    Gx[3]*px[k - 1].i + Gx[4]*px[k].i + Gx[5]*px[n - width].i +
                                    Gx[6]*px[width - 2].i + Gx[7]*px[width - 1].i + Gx[8]*px[0].i;
                        convY[k] =  Gy[0]*px[n - width - 2].i + Gy[1]*px[n - width - 1].i + Gy[2]*px[k - width - (k % width)].i +
                                    Gy[3]*px[k - 1].i + Gy[4]*px[k].i + Gy[5]*px[n - width].i +
                                    Gy[6]*px[width - 2].i + Gy[7]*px[width - 1].i + Gy[8]*px[0].i;
                    }
                    else{
                        convX[k] =  Gx[0]*px[k - width - 1].i + Gx[1]*px[k - width].i + Gx[2]*px[k - width + 1].i +
                                    Gx[3]*px[k - 1].i + Gx[4]*px[k].i + Gx[5]*px[k + 1].i +
                                    Gx[6]*px[(k % width) - 1].i + Gx[7]*px[(k % width)].i + Gx[8]*px[(k % width) + 1].i;
                        convY[k] =  Gy[0]*px[k - width - 1].i + Gy[1]*px[k - width].i + Gy[2]*px[k - width + 1].i +
                                    Gy[3]*px[k - 1].i + Gy[4]*px[k].i + Gy[5]*px[k + 1].i +
                                    Gy[6]*px[(k % width) - 1].i + Gy[7]*px[(k % width)].i + Gy[8]*px[(k % width) + 1].i;
                    }
                }
                else{
                    if(i_column == 0){
                        convX[k] =  Gx[0]*px[k - 1].i + Gx[1]*px[k - width].i + Gx[2]*px[k - width + 1].i +
                                    Gx[3]*px[k + width - 1].i + Gx[4]*px[k].i + Gx[5]*px[k + 1].i +
                                    Gx[6]*px[k + 2*width - 1].i + Gx[7]*px[k + width].i + Gx[8]*px[k + width + 1].i;
                        convY[k] =  Gy[0]*px[k - 1].i + Gy[1]*px[k - width].i + Gy[2]*px[k - width + 1].i +
                                    Gy[3]*px[k + width - 1].i + Gy[4]*px[k].i + Gy[5]*px[k + 1].i +
                                    Gy[6]*px[k + 2*width - 1].i + Gy[7]*px[k + width].i + Gy[8]*px[k + width + 1].i;
                    }
                    else if(i_column == (width - 1)){
                        convX[k] =  Gx[0]*px[k - width - 1].i + Gx[1]*px[k - width].i + Gx[2]*px[k - width - (k % width)].i +
                                    Gx[3]*px[k - 1].i + Gx[4]*px[k].i + Gx[5]*px[k - (k % width)].i +
                                    Gx[6]*px[k + width - 1].i + Gx[7]*px[k + width].i + Gx[8]*px[k + 1].i;
                        convY[k] =  Gy[0]*px[k - width - 1].i + Gy[1]*px[k - width].i + Gy[2]*px[k - width - (k % width)].i +
                                    Gy[3]*px[k - 1].i + Gy[4]*px[k].i + Gy[5]*px[k - (k % width)].i +
                                    Gy[6]*px[k + width - 1].i + Gy[7]*px[k + width].i + Gy[8]*px[k + 1].i;
                    }
                }
            }
            vectGray[k] = (u_int) abs((float)convX[k]) + abs((float)convY[k]);
            //vectGray[k] = (double)grad;
            //printf("%d   %.4f\n", k, vectGray[k]);
        }
    }

    mx = maxFind(vectGray, n);
    parameterize(vectGray, n, mx, 255);

    for(u_int j = 0; j < n; j++){
        px[j].i = vectGray[j];
    }

    thresholdGray(th);
}

void Imagem::edgeRobinson(u_int th){
    int G[8][9] = { {1, 2, 1, 0, 0, 0, -1, -2, -1},
                    {2, 1, 0, 1, 0, -1, 0, -1, -2},
                    {1, 0, -1, 2, 0, -2, 0, 0, -1},
                    {0, -1, -2, 1, 0, -1, 2, 1, 0},
                    {-1, -2, -1, 0, 0, 0, 1, 2, 1},
                    {-2, -1, 0, -1, 0, 1, 0, 1, 2},
                    {-1, 0, 1, -2, 0, 2, 0, 0, 1},
                    {0, 1, 2, -1, 0, 1, -2, -1, 0}  };
    u_int k;
    int mx;
    int *vectGray, *conv;


    vectGray = (int*) malloc(n*sizeof(int));
    conv = (int*) malloc(8*sizeof(int));

    for(u_int i_line = 0; i_line < height; i_line++){
        for(u_int i_column = 0; i_column < width; i_column++){
            k = i_line*width + i_column;

            // Posições fora das bordas da matriz
            if(i_line < (height-1) && i_column < (width-1) && i_line > 0 && i_column > 0){
                //printf("AQUI 1\n");
                conv[0] =   G[0][0]*px[k - width - 1].i + G[0][1]*px[k - width].i + G[0][2]*px[k - width + 1].i +
                            G[0][3]*px[k - 1].i + G[0][4]*px[k].i + G[0][5]*px[k + 1].i +
                            G[0][6]*px[k + width - 1].i + G[0][7]*px[k + width].i + G[0][8]*px[k + width + 1].i;

                conv[1] =   G[1][0]*px[k - width - 1].i + G[1][1]*px[k - width].i + G[1][2]*px[k - width + 1].i +
                            G[1][3]*px[k - 1].i + G[1][4]*px[k].i + G[1][5]*px[k + 1].i +
                            G[1][6]*px[k + width - 1].i + G[1][7]*px[k + width].i + G[1][8]*px[k + width + 1].i;

                conv[2] =   G[2][0]*px[k - width - 1].i + G[2][1]*px[k - width].i + G[2][2]*px[k - width + 1].i +
                            G[2][3]*px[k - 1].i + G[2][4]*px[k].i + G[2][5]*px[k + 1].i +
                            G[2][6]*px[k + width - 1].i + G[2][7]*px[k + width].i + G[2][8]*px[k + width + 1].i;

                conv[3] =   G[3][0]*px[k - width - 1].i + G[3][1]*px[k - width].i + G[3][2]*px[k - width + 1].i +
                            G[3][3]*px[k - 1].i + G[3][4]*px[k].i + G[3][5]*px[k + 1].i +
                            G[3][6]*px[k + width - 1].i + G[3][7]*px[k + width].i + G[3][8]*px[k + width + 1].i;

                conv[4] =   G[4][0]*px[k - width - 1].i + G[4][1]*px[k - width].i + G[4][2]*px[k - width + 1].i +
                            G[4][3]*px[k - 1].i + G[4][4]*px[k].i + G[4][5]*px[k + 1].i +
                            G[4][6]*px[k + width - 1].i + G[4][7]*px[k + width].i + G[4][8]*px[k + width + 1].i;

                conv[5] =   G[5][0]*px[k - width - 1].i + G[5][1]*px[k - width].i + G[5][2]*px[k - width + 1].i +
                            G[5][3]*px[k - 1].i + G[5][4]*px[k].i + G[5][5]*px[k + 1].i +
                            G[5][6]*px[k + width - 1].i + G[5][7]*px[k + width].i + G[5][8]*px[k + width + 1].i;

                conv[6] =   G[6][0]*px[k - width - 1].i + G[6][1]*px[k - width].i + G[6][2]*px[k - width + 1].i +
                            G[6][3]*px[k - 1].i + G[6][4]*px[k].i + G[6][5]*px[k + 1].i +
                            G[6][6]*px[k + width - 1].i + G[6][7]*px[k + width].i + G[6][8]*px[k + width + 1].i;

                conv[7] =   G[7][0]*px[k - width - 1].i + G[7][1]*px[k - width].i + G[7][2]*px[k - width + 1].i +
                            G[7][3]*px[k - 1].i + G[7][4]*px[k].i + G[7][5]*px[k + 1].i +
                            G[7][6]*px[k + width - 1].i + G[7][7]*px[k + width].i + G[7][8]*px[k + width + 1].i;

            }
            else{
                //printf("AQUI 2\n");
                if(i_line == 0){
                    if(i_column == 0){
                        conv[0] =   G[0][0]*px[n - 1].i + G[0][1]*px[n - width].i + G[0][2]*px[n - width + 1].i +
                                    G[0][3]*px[width - 1].i + G[0][4]*px[k].i + G[0][5]*px[k + 1].i +
                                    G[0][6]*px[2*width - 1].i + G[0][7]*px[k + width].i + G[0][8]*px[k + width + 1].i;

                        conv[1] =   G[1][0]*px[n - 1].i + G[1][1]*px[n - width].i + G[1][2]*px[n - width + 1].i +
                                    G[1][3]*px[width - 1].i + G[1][4]*px[k].i + G[1][5]*px[k + 1].i +
                                    G[1][6]*px[2*width - 1].i + G[1][7]*px[k + width].i + G[1][8]*px[k + width + 1].i;

                        conv[2] =   G[2][0]*px[n - 1].i + G[2][1]*px[n - width].i + G[2][2]*px[n - width + 1].i +
                                    G[2][3]*px[width - 1].i + G[2][4]*px[k].i + G[2][5]*px[k + 1].i +
                                    G[2][6]*px[2*width - 1].i + G[2][7]*px[k + width].i + G[2][8]*px[k + width + 1].i;

                        conv[3] =   G[3][0]*px[n - 1].i + G[3][1]*px[n - width].i + G[3][2]*px[n - width + 1].i +
                                    G[3][3]*px[width - 1].i + G[3][4]*px[k].i + G[3][5]*px[k + 1].i +
                                    G[3][6]*px[2*width - 1].i + G[3][7]*px[k + width].i + G[3][8]*px[k + width + 1].i;

                        conv[4] =   G[4][0]*px[n - 1].i + G[4][1]*px[n - width].i + G[4][2]*px[n - width + 1].i +
                                    G[4][3]*px[width - 1].i + G[4][4]*px[k].i + G[4][5]*px[k + 1].i +
                                    G[4][6]*px[2*width - 1].i + G[4][7]*px[k + width].i + G[4][8]*px[k + width + 1].i;

                        conv[5] =   G[5][0]*px[n - 1].i + G[5][1]*px[n - width].i + G[5][2]*px[n - width + 1].i +
                                    G[5][3]*px[width - 1].i + G[5][4]*px[k].i + G[5][5]*px[k + 1].i +
                                    G[5][6]*px[2*width - 1].i + G[5][7]*px[k + width].i + G[5][8]*px[k + width + 1].i;

                        conv[6] =   G[6][0]*px[n - 1].i + G[6][1]*px[n - width].i + G[6][2]*px[n - width + 1].i +
                                    G[6][3]*px[width - 1].i + G[6][4]*px[k].i + G[6][5]*px[k + 1].i +
                                    G[6][6]*px[2*width - 1].i + G[6][7]*px[k + width].i + G[6][8]*px[k + width + 1].i;

                        conv[7] =   G[7][0]*px[n - 1].i + G[7][1]*px[n - width].i + G[7][2]*px[n - width + 1].i +
                                    G[7][3]*px[width - 1].i + G[7][4]*px[k].i + G[7][5]*px[k + 1].i +
                                    G[7][6]*px[2*width - 1].i + G[7][7]*px[k + width].i + G[7][8]*px[k + width + 1].i;
                    }
                    else if(i_column == (width - 1)){
                        conv[0] =   G[0][0]*px[n - 2].i + G[0][1]*px[n - 1].i + G[0][2]*px[n - width].i +
                                    G[0][3]*px[k - 1].i + G[0][4]*px[k].i + G[0][5]*px[k - (k % width)].i +
                                    G[0][6]*px[k + width - 1].i + G[0][7]*px[k + width].i + G[0][8]*px[k + 1].i;

                        conv[1] =   G[1][0]*px[n - 2].i + G[1][1]*px[n - 1].i + G[1][2]*px[n - width].i +
                                    G[1][3]*px[k - 1].i + G[1][4]*px[k].i + G[1][5]*px[k - (k % width)].i +
                                    G[1][6]*px[k + width - 1].i + G[1][7]*px[k + width].i + G[1][8]*px[k + 1].i;

                        conv[2] =   G[2][0]*px[n - 2].i + G[2][1]*px[n - 1].i + G[2][2]*px[n - width].i +
                                    G[2][3]*px[k - 1].i + G[2][4]*px[k].i + G[2][5]*px[k - (k % width)].i +
                                    G[2][6]*px[k + width - 1].i + G[2][7]*px[k + width].i + G[2][8]*px[k + 1].i;

                        conv[3] =   G[3][0]*px[n - 2].i + G[3][1]*px[n - 1].i + G[3][2]*px[n - width].i +
                                    G[3][3]*px[k - 1].i + G[3][4]*px[k].i + G[3][5]*px[k - (k % width)].i +
                                    G[3][6]*px[k + width - 1].i + G[3][7]*px[k + width].i + G[3][8]*px[k + 1].i;

                        conv[4] =   G[4][0]*px[n - 2].i + G[4][1]*px[n - 1].i + G[4][2]*px[n - width].i +
                                    G[4][3]*px[k - 1].i + G[4][4]*px[k].i + G[4][5]*px[k - (k % width)].i +
                                    G[4][6]*px[k + width - 1].i + G[4][7]*px[k + width].i + G[4][8]*px[k + 1].i;

                        conv[5] =   G[5][0]*px[n - 2].i + G[5][1]*px[n - 1].i + G[5][2]*px[n - width].i +
                                    G[5][3]*px[k - 1].i + G[5][4]*px[k].i + G[5][5]*px[k - (k % width)].i +
                                    G[5][6]*px[k + width - 1].i + G[5][7]*px[k + width].i + G[5][8]*px[k + 1].i;

                        conv[6] =   G[6][0]*px[n - 2].i + G[6][1]*px[n - 1].i + G[6][2]*px[n - width].i +
                                    G[6][3]*px[k - 1].i + G[6][4]*px[k].i + G[6][5]*px[k - (k % width)].i +
                                    G[6][6]*px[k + width - 1].i + G[6][7]*px[k + width].i + G[6][8]*px[k + 1].i;

                        conv[7] =   G[7][0]*px[n - 2].i + G[7][1]*px[n - 1].i + G[7][2]*px[n - width].i +
                                    G[7][3]*px[k - 1].i + G[7][4]*px[k].i + G[7][5]*px[k - (k % width)].i +
                                    G[7][6]*px[k + width - 1].i + G[7][7]*px[k + width].i + G[7][8]*px[k + 1].i;

                    }
                }
                else if(i_line == (height - 1)){
                    if(i_column == 0){
                        conv[0] =   G[0][0]*px[k - 1].i + G[0][1]*px[k - width].i + G[0][2]*px[k - width + 1].i +
                                    G[0][3]*px[n - 1].i + G[0][4]*px[k].i + G[0][5]*px[k + 1].i +
                                    G[0][6]*px[width].i + G[0][7]*px[0].i + G[0][8]*px[1].i;

                        conv[1] =   G[1][0]*px[k - 1].i + G[1][1]*px[k - width].i + G[1][2]*px[k - width + 1].i +
                                    G[1][3]*px[n - 1].i + G[1][4]*px[k].i + G[1][5]*px[k + 1].i +
                                    G[1][6]*px[width].i + G[1][7]*px[0].i + G[1][8]*px[1].i;

                        conv[2] =   G[2][0]*px[k - 1].i + G[2][1]*px[k - width].i + G[2][2]*px[k - width + 1].i +
                                    G[2][3]*px[n - 1].i + G[2][4]*px[k].i + G[2][5]*px[k + 1].i +
                                    G[2][6]*px[width].i + G[2][7]*px[0].i + G[2][8]*px[1].i;

                        conv[3] =   G[3][0]*px[k - 1].i + G[3][1]*px[k - width].i + G[3][2]*px[k - width + 1].i +
                                    G[3][3]*px[n - 1].i + G[3][4]*px[k].i + G[3][5]*px[k + 1].i +
                                    G[3][6]*px[width].i + G[3][7]*px[0].i + G[3][8]*px[1].i;

                        conv[4] =   G[4][0]*px[k - 1].i + G[4][1]*px[k - width].i + G[4][2]*px[k - width + 1].i +
                                    G[4][3]*px[n - 1].i + G[4][4]*px[k].i + G[4][5]*px[k + 1].i +
                                    G[4][6]*px[width].i + G[4][7]*px[0].i + G[4][8]*px[1].i;

                        conv[5] =   G[5][0]*px[k - 1].i + G[5][1]*px[k - width].i + G[5][2]*px[k - width + 1].i +
                                    G[5][3]*px[n - 1].i + G[5][4]*px[k].i + G[5][5]*px[k + 1].i +
                                    G[5][6]*px[width].i + G[5][7]*px[0].i + G[5][8]*px[1].i;

                        conv[6] =   G[6][0]*px[k - 1].i + G[6][1]*px[k - width].i + G[6][2]*px[k - width + 1].i +
                                    G[6][3]*px[n - 1].i + G[6][4]*px[k].i + G[6][5]*px[k + 1].i +
                                    G[6][6]*px[width].i + G[6][7]*px[0].i + G[6][8]*px[1].i;

                        conv[7] =   G[7][0]*px[k - 1].i + G[7][1]*px[k - width].i + G[7][2]*px[k - width + 1].i +
                                    G[7][3]*px[n - 1].i + G[7][4]*px[k].i + G[7][5]*px[k + 1].i +
                                    G[7][6]*px[width].i + G[7][7]*px[0].i + G[7][8]*px[1].i;

                    }
                    else if(i_column == (width - 1)){
                        conv[0] =   G[0][0]*px[n - width - 1].i + G[0][1]*px[n - width].i + G[0][2]*px[k - width - (k % width)].i +
                                    G[0][3]*px[k - 1].i + G[0][4]*px[k].i + G[0][5]*px[k - (k % width)].i +
                                    G[0][6]*px[width - 2].i + G[0][7]*px[width - 1].i + G[0][8]*px[0].i;

                        conv[1] =   G[1][0]*px[n - width - 1].i + G[1][1]*px[n - width].i + G[1][2]*px[k - width - (k % width)].i +
                                    G[1][3]*px[k - 1].i + G[1][4]*px[k].i + G[1][5]*px[k - (k % width)].i +
                                    G[1][6]*px[width - 2].i + G[1][7]*px[width - 1].i + G[1][8]*px[0].i;

                        conv[2] =   G[2][0]*px[n - width - 1].i + G[2][1]*px[n - width].i + G[2][2]*px[k - width - (k % width)].i +
                                    G[2][3]*px[k - 1].i + G[2][4]*px[k].i + G[2][5]*px[k - (k % width)].i +
                                    G[2][6]*px[width - 2].i + G[2][7]*px[width - 1].i + G[2][8]*px[0].i;

                        conv[3] =   G[3][0]*px[n - width - 1].i + G[3][1]*px[n - width].i + G[3][2]*px[k - width - (k % width)].i +
                                    G[3][3]*px[k - 1].i + G[3][4]*px[k].i + G[3][5]*px[k - (k % width)].i +
                                    G[3][6]*px[width - 2].i + G[3][7]*px[width - 1].i + G[3][8]*px[0].i;

                        conv[4] =   G[4][0]*px[n - width - 1].i + G[4][1]*px[n - width].i + G[4][2]*px[k - width - (k % width)].i +
                                    G[4][3]*px[k - 1].i + G[4][4]*px[k].i + G[4][5]*px[k - (k % width)].i +
                                    G[4][6]*px[width - 2].i + G[4][7]*px[width - 1].i + G[4][8]*px[0].i;

                        conv[5] =   G[5][0]*px[n - width - 1].i + G[5][1]*px[n - width].i + G[5][2]*px[k - width - (k % width)].i +
                                    G[5][3]*px[k - 1].i + G[5][4]*px[k].i + G[5][5]*px[k - (k % width)].i +
                                    G[5][6]*px[width - 2].i + G[5][7]*px[width - 1].i + G[5][8]*px[0].i;

                        conv[6] =   G[6][0]*px[n - width - 1].i + G[6][1]*px[n - width].i + G[6][2]*px[k - width - (k % width)].i +
                                    G[6][3]*px[k - 1].i + G[6][4]*px[k].i + G[6][5]*px[k - (k % width)].i +
                                    G[6][6]*px[width - 2].i + G[6][7]*px[width - 1].i + G[6][8]*px[0].i;

                        conv[7] =   G[7][0]*px[n - width - 1].i + G[7][1]*px[n - width].i + G[7][2]*px[k - width - (k % width)].i +
                                    G[7][3]*px[k - 1].i + G[7][4]*px[k].i + G[7][5]*px[k - (k % width)].i +
                                    G[7][6]*px[width - 2].i + G[7][7]*px[width - 1].i + G[7][8]*px[0].i;
                    }
                }
                else{
                    if(i_column == 0){
                        conv[0] =   G[0][0]*px[k - 1].i + G[0][1]*px[k - width].i + G[0][2]*px[k - width + 1].i +
                                    G[0][3]*px[k + width - 1].i + G[0][4]*px[k].i + G[0][5]*px[k + 1].i +
                                    G[0][6]*px[k + 2*width - 1].i + G[0][7]*px[k + width].i + G[0][8]*px[k + width + 1].i;

                        conv[1] =   G[1][0]*px[k - 1].i + G[1][1]*px[k - width].i + G[1][2]*px[k - width + 1].i +
                                    G[1][3]*px[k + width - 1].i + G[1][4]*px[k].i + G[1][5]*px[k + 1].i +
                                    G[1][6]*px[k + 2*width - 1].i + G[1][7]*px[k + width].i + G[1][8]*px[k + width + 1].i;

                        conv[2] =   G[2][0]*px[k - 1].i + G[2][1]*px[k - width].i + G[2][2]*px[k - width + 1].i +
                                    G[2][3]*px[k + width - 1].i + G[2][4]*px[k].i + G[2][5]*px[k + 1].i +
                                    G[2][6]*px[k + 2*width - 1].i + G[2][7]*px[k + width].i + G[2][8]*px[k + width + 1].i;

                        conv[3] =   G[3][0]*px[k - 1].i + G[3][1]*px[k - width].i + G[3][2]*px[k - width + 1].i +
                                    G[3][3]*px[k + width - 1].i + G[3][4]*px[k].i + G[3][5]*px[k + 1].i +
                                    G[3][6]*px[k + 2*width - 1].i + G[3][7]*px[k + width].i + G[3][8]*px[k + width + 1].i;

                        conv[4] =   G[4][0]*px[k - 1].i + G[4][1]*px[k - width].i + G[4][2]*px[k - width + 1].i +
                                    G[4][3]*px[k + width - 1].i + G[4][4]*px[k].i + G[4][5]*px[k + 1].i +
                                    G[4][6]*px[k + 2*width - 1].i + G[4][7]*px[k + width].i + G[4][8]*px[k + width + 1].i;

                        conv[5] =   G[5][0]*px[k - 1].i + G[5][1]*px[k - width].i + G[5][2]*px[k - width + 1].i +
                                    G[5][3]*px[k + width - 1].i + G[5][4]*px[k].i + G[5][5]*px[k + 1].i +
                                    G[5][6]*px[k + 2*width - 1].i + G[5][7]*px[k + width].i + G[5][8]*px[k + width + 1].i;

                        conv[6] =   G[6][0]*px[k - 1].i + G[6][1]*px[k - width].i + G[6][2]*px[k - width + 1].i +
                                    G[6][3]*px[k + width - 1].i + G[6][4]*px[k].i + G[6][5]*px[k + 1].i +
                                    G[6][6]*px[k + 2*width - 1].i + G[6][7]*px[k + width].i + G[6][8]*px[k + width + 1].i;

                        conv[7] =   G[7][0]*px[k - 1].i + G[7][1]*px[k - width].i + G[7][2]*px[k - width + 1].i +
                                    G[7][3]*px[k + width - 1].i + G[7][4]*px[k].i + G[7][5]*px[k + 1].i +
                                    G[7][6]*px[k + 2*width - 1].i + G[7][7]*px[k + width].i + G[7][8]*px[k + width + 1].i;
                    }
                    else if(i_column == (width - 1)){
                        conv[0] =   G[0][0]*px[k - width - 1].i + G[0][1]*px[k - width].i + G[0][2]*px[k - width - (k % width)].i +
                                    G[0][3]*px[k - 1].i + G[0][4]*px[k].i + G[0][5]*px[k - (k % width)].i +
                                    G[0][6]*px[k + width - 1].i + G[0][7]*px[k + width].i + G[0][8]*px[k + 1].i;

                        conv[1] =   G[1][0]*px[k - width - 1].i + G[1][1]*px[k - width].i + G[1][2]*px[k - width - (k % width)].i +
                                    G[1][3]*px[k - 1].i + G[1][4]*px[k].i + G[1][5]*px[k - (k % width)].i +
                                    G[1][6]*px[k + width - 1].i + G[1][7]*px[k + width].i + G[1][8]*px[k + 1].i;

                        conv[2] =   G[2][0]*px[k - width - 1].i + G[2][1]*px[k - width].i + G[2][2]*px[k - width - (k % width)].i +
                                    G[2][3]*px[k - 1].i + G[2][4]*px[k].i + G[2][5]*px[k - (k % width)].i +
                                    G[2][6]*px[k + width - 1].i + G[2][7]*px[k + width].i + G[2][8]*px[k + 1].i;

                        conv[3] =   G[3][0]*px[k - width - 1].i + G[3][1]*px[k - width].i + G[3][2]*px[k - width - (k % width)].i +
                                    G[3][3]*px[k - 1].i + G[3][4]*px[k].i + G[3][5]*px[k - (k % width)].i +
                                    G[3][6]*px[k + width - 1].i + G[3][7]*px[k + width].i + G[3][8]*px[k + 1].i;

                        conv[4] =   G[4][0]*px[k - width - 1].i + G[4][1]*px[k - width].i + G[4][2]*px[k - width - (k % width)].i +
                                    G[4][3]*px[k - 1].i + G[4][4]*px[k].i + G[4][5]*px[k - (k % width)].i +
                                    G[4][6]*px[k + width - 1].i + G[4][7]*px[k + width].i + G[4][8]*px[k + 1].i;

                        conv[5] =   G[5][0]*px[k - width - 1].i + G[5][1]*px[k - width].i + G[5][2]*px[k - width - (k % width)].i +
                                    G[5][3]*px[k - 1].i + G[5][4]*px[k].i + G[5][5]*px[k - (k % width)].i +
                                    G[5][6]*px[k + width - 1].i + G[5][7]*px[k + width].i + G[5][8]*px[k + 1].i;

                        conv[6] =   G[6][0]*px[k - width - 1].i + G[6][1]*px[k - width].i + G[6][2]*px[k - width - (k % width)].i +
                                    G[6][3]*px[k - 1].i + G[6][4]*px[k].i + G[6][5]*px[k - (k % width)].i +
                                    G[6][6]*px[k + width - 1].i + G[6][7]*px[k + width].i + G[6][8]*px[k + 1].i;

                        conv[7] =   G[7][0]*px[k - width - 1].i + G[7][1]*px[k - width].i + G[7][2]*px[k - width - (k % width)].i +
                                    G[7][3]*px[k - 1].i + G[7][4]*px[k].i + G[7][5]*px[k - (k % width)].i +
                                    G[7][6]*px[k + width - 1].i + G[7][7]*px[k + width].i + G[7][8]*px[k + 1].i;

                    }
                }
            }
            vectGray[k] = maxFind(conv, 8);
        }
    }
    mx = maxFind(vectGray, n);
    parameterize(vectGray, n, mx, 255);

    for(u_int j = 0; j < n; j++){
        px[j].i = (u_int) vectGray[j];
    }

    thresholdGray(th);

    free(vectGray);
}
