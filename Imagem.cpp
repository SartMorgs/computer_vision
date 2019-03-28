#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

typedef unsigned int u_int;
typedef struct pixel{
	int r, g, b, i;
}PIXEL;

class Imagem{
	private:
		int width, heigth;
		char type[2];
		PIXEL *px;
	public:
		// Componente necessários da imagem
		void setWidth(int w);
		int getWidth();
		void setHeigth(int h);
		int getHeigth();
		void setType(char t[]);
		char* getType();
		void setPGM(PIXEL* pgm);
		void setPPM(PIXEL* ppm);
		void setImg(PIXEL* pgm, PIXEL* ppm, PIXEL* img, int w, int h);
		PIXEL* getImg();

		// Funções de leitura e escrita
		void readPGM(FILE* arq, const char* filename);
		void writePGM(FILE* arq, const char* filename);
		void readPPM(FILE* arq, const char* filename);
		void writePPM(FILE* arq, const char* filename);

		// Funções de escala cinza
		void thresholdGray(u_int th);
		void thresholdGray(u_int thlow, u_int thhigh);
		void inverseGray();
		void addGray(unsigned char value);

		// Funções de RGB
		void inverseColor();
		void addColor(unsigned char value);
		void addColor(unsigned char valueR, unsigned char valueG, unsigned char valueB);
		void rgb2Gray();
		void thresholdRGB(u_int thR, u_int thG, u_int thB);
		void thresholdRGB(u_int thRlow, u_int thRhigh, u_int thGlow, u_int thGhigh, u_int thBlow, u_int thBhigh);
};

void Imagem::setWidth(int w){
	width = w;
}

int Imagem::getWidth(){
	return width;
}

void Imagem::setHeigth(int h){
	heigth = h;
}

int Imagem::getHeigth(){
	return heigth;
}

void Imagem::setType(char t[]){
	strcpy(type, t);
}

char* Imagem::getType(){
	return type;
}

void Imagem::setPGM(PIXEL* pgm){

    for(unsigned int k = 0; k < (width*heigth); k++){
        px[k].i = pgm[k].i;
    }
}

void Imagem::setPPM(PIXEL* ppm){
    for(unsigned int k = 0; k < (width*heigth); k++){
        px[k].r = ppm[k].r;
        px[k].g = ppm[k].g;
        px[k].b = ppm[k].b;
    }
}

void Imagem::setImg(PIXEL* pgm, PIXEL* ppm, PIXEL* img, int w, int h){

}

PIXEL* Imagem::getImg(){
    return px;
}

void Imagem::readPGM(FILE* arq, const char* filename){
	int w, h, maxsize;
	char t[2];

	arq = fopen(filename, "r");

	if(arq == NULL) cout<< "Erro na abertura do arquivo" << "\n";
	else{
		fscanf(arq, "%s %d %d %d", &t, &w, &h, &maxsize);

		setType(t);
		setWidth(w);
		setHeigth(h);

		px = (PIXEL*) malloc(sizeof(PIXEL)*w*h);

		for(unsigned int k = 0; k < (w*h); k++){
			fscanf(arq, "%d", &px[k].i);
		}
	}

	fclose(arq);
}


void Imagem::writePGM(FILE* arq, const char* filename){

	arq = fopen(filename, "w");

	if(arq == NULL) cout<< "Erro na abertura do arquivo" << "\n";
	else{
		fprintf(arq, "%s %d %d 255", type, width, heigth);

		for(unsigned int k = 0; k < (width*heigth); k++){
			fprintf(arq, "%d", px[k].i);
		}
	}

	fclose(arq);
}

void Imagem::readPPM(FILE* arq, const char* filename){
	int w, h, maxsize;
	char t[2];

	arq = fopen(filename, "r");

	if(arq == NULL) cout<< "Erro na abertura do arquivo" << "\n";
	else{
		fscanf(arq, "%s %d %d %d", &t, &w, &h, &maxsize);

		setType(t);
		setWidth(w);
		setHeigth(h);


        if(px == NULL){
            px = (PIXEL*) malloc(sizeof(PIXEL)*w*h*3);
        }
        for(unsigned int k = 0; k < (w*h); k++){
            fscanf(arq, "%d %d %d", &px[k].r, &px[k].g, &px[k].b);
        }


	}

	fclose(arq);
}


void Imagem::writePPM(FILE* arq, const char* filename){

	arq = fopen(filename, "w");

	if(arq == NULL) cout<< "Erro na abertura do arquivo" << "\n";
	else{
		fprintf(arq, "%s %d %d 255", type, width, heigth);

		for(unsigned int k = 0; k < (width*heigth); k++){
			fprintf(arq, "%d %d %d", px[k].r, px[k].g, px[k].b);
		}
	}

	fclose(arq);
}

void Imagem::thresholdGray(unsigned int th){
	for(unsigned int k = 0; k < (width*heigth); k++){
		if((unsigned int) px[k].i < th) px[k].i = 255;
		else px[k].i = 0;
	}
}

void Imagem::thresholdGray(unsigned int thlow, unsigned int thhigh){

	for(unsigned int k = 0; k < (width*heigth); k++){
		if(((unsigned int) px[k].i > thlow) && ((unsigned int) px[k].i < thhigh)) px[k].i = 255;
		else px[k].i = 0;
	}
}

void Imagem::inverseGray(){

	for(unsigned int k = 0; k < (width*heigth); k++){
		px[k].i = 255 - px[k].i;
	}
}

void Imagem::addGray(unsigned char value){

	for(unsigned int k = 0; k < (width*heigth); k++){
		if((int) (px[k].i + value) > 255) px[k].i = 255;
        else px[k].i += value;
	}
}

void Imagem::inverseColor(){
	for(unsigned int k = 0; k < (width*heigth); k++){
		px[k].r = 255 - px[k].r;
		px[k].g = 255 - px[k].g;
		px[k].b = 255 - px[k].b;
	}
}

void Imagem::addColor(unsigned char value){
	for(unsigned int k = 0; k < (width*heigth); k++){
		if((int) (px[k].r + value) > 255) px[k].r = 255;
        else px[k].r += value;
        if((int) (px[k].g + value) > 255) px[k].g = 255;
        else px[k].g += value;
        if((int) (px[k].b + value) > 255) px[k].b = 255;
        else px[k].b += value;
	}
}

void Imagem::addColor(unsigned char valueR, unsigned char valueG, unsigned char valueB){

	for(unsigned int k = 0; k < (width*heigth); k++){
		if((int) (px[k].r + valueR) > 255) px[k].r = 255;
        else px[k].r += valueR;

        if((int) (px[k].g + valueG) > 255) px[k].g = 255;
        else px[k].g += valueG;

        if((int) (px[k].b + valueB) > 255) px[k].b = 255;
        else px[k].b += valueB;
	}
}

void Imagem::rgb2Gray(){
	unsigned int value;

	for(unsigned int k = 0; k < (width*heigth); k++){
		value = ((unsigned int) px[k].r + px[k].g + px[k].b) / 3;
        px[k].i = value;
	}
}

void Imagem::thresholdRGB(u_int thR, u_int thG, u_int thB){
    for(u_int k = 0; k < (width*heigth); k++){
		if((u_int) px[k].r < thR) px[k].r = 255;
		else px[k].r = 0;
		if((u_int) px[k].g < thG) px[k].g = 255;
		else px[k].g = 0;
		if((u_int) px[k].b < thB) px[k].b = 255;
		else px[k].b = 0;
	}
}

void Imagem::thresholdRGB(u_int thRlow, u_int thRhigh, u_int thGlow, u_int thGhigh, u_int thBlow, u_int thBhigh){
    for(u_int k = 0; k < (width*heigth); k++){
		if(((u_int) px[k].r > thRlow) && ((u_int) px[k].r < thRhigh)) px[k].r = 255;
		else px[k].r = 0;
		if(((u_int) px[k].g > thGlow) && ((u_int) px[k].g < thGhigh)) px[k].g = 255;
		else px[k].g = 0;
		if(((u_int) px[k].b > thBlow) && ((u_int) px[k].b < thBhigh)) px[k].b = 255;
		else px[k].b = 0;
	}
}

