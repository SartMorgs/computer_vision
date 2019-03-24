#include <iostream>
#include <stdlib.h>

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
		void setImg(PIXEL* p);
		PIXEL* getImg();

		// Funções de leitura e escrita
		void readPGM(FILE* arq, const* char filename);
		void writePGM(FILE* arq, const* char filename);
		void readPPM(FILE* arq, const* char filename);
		void writePPM(FILE* arq, const* char filename);

		// Funções de escala cinza
		void thresholdGray(unsigned int th);
		void thresholdGray(unsigned int thlow, unsigned int thhigh);
		void inverseGray();
		void addGray(unsigned char value);

		// Funções de RGB
		void inverseColor();
		void addColor(unsigned char value);
		void addColor(unsigned char valueR, unsigned char valueG, unsigned char value);
		void rgb2Gray();
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
	type = t;
}

char* Imagem::getType(){
	return type;
}

void Imagem::setImg(PIXEL* pgm, PIXEL* pgm, int w, int h){
	
}

PIXEL* Imagem::getImg(){
	return px;
}

void Imagem::readPGM(FILE* arq, const* char filename){
	int w, h, maxsize;
	char t[2];
	PIXEL *pxl;

	arq = fopen(filename, "r");

	if(arq == NULL) cout<< "Erro na abertura do arquivo" << "\n";
	else{
		fscanf(arq, "%s %d %d %d", &t, &w, &h, &maxsize);

		setType(t);
		setWidth(w);
		setHeigth(h);

		pxl = (PIXEL*) malloc(sizeof(PIXEL)*w*h);

		for(unsigned int k = 0; k < (w*h); k++){
			fscanf(arq, "%d", &pxl[k].i);
		}
	}

	fclose(arq);
}


void Imagem::writePGM(FILE* arq, const* char filename){
	int w, h;
	char t[2];
	PIXEL *pxl;

	pxl = getImg();
	w = getWidth();
	h = getHeigth();
	t = getType();

	arq = fopen(filename, "w");

	if(arq == NULL) cout<< "Erro na abertura do arquivo" << "\n";
	else{
		fprintf(arq, "%s %d %d 255", t, w, h);

		for(unsigned int k = 0; k < (w*h); k++){
			fprintf(arq, "%d", pxl[k].i);
		}
	}

	fclose(arq);
}

void Imagem::readPPM(FILE* arq, const* char filename){
	int w, h, maxsize;
	char t[2];
	PIXEL *pxl;

	arq = fopen(filename, "r");

	if(arq == NULL) cout<< "Erro na abertura do arquivo" << "\n";
	else{
		fscanf(arq, "%s %d %d %d", &t, &w, &h, &maxsize);

		setType(t);
		setWidth(w);
		setHeigth(h);

		pxl = (PIXEL*) malloc(sizeof(PIXEL)*w*h*3);

		for(unsigned int k = 0; k < (w*h); k++){
			fscanf(arq, "%d %d %d", &pxl[k].r, &pxl[k].g, &pxl[k].b);
		}
	}

	fclose(arq);
}


void Imagem::writePPM(FILE* arq, const* char filename){
	int w, h;
	char t[2];
	PIXEL *pxl;

	pxl = getImg();
	w = getWidth();
	h = getHeigth();
	t = getType();

	arq = fopen(filename, "w");

	if(arq == NULL) cout<< "Erro na abertura do arquivo" << "\n";
	else{
		fprintf(arq, "%s %d %d 255", t, w, h);

		for(unsigned int k = 0; k < (w*h); k++){
			fprintf(arq, "%d %d %d", pxl[k].r, pxl[k].g, pxl[k].b);
		}
	}

	fclose(arq);
}

void thresholdGray(unsigned int th){
	int w, h;
	PIXEL *pxl;

	pxl = getImg();
	w = getWidth();
	h = getHeigth();

	for(unsigned int k = 0; k < (w*h); k++){
		if((unsigned int) pxl[k].i < th) pxl[k].i = 255;
		else pxl[k].i = 0;
	}
}

void thresholdGray(unsigned int thlow, unsigned int thhigh){
	int w, h;
	PIXEL *pxl;

	pxl = getImg();
	w = getWidth();
	h = getHeigth();

	for(unsigned int k = 0; k < (w*h); k++){
		if(((unsigned int) pxl[k].i > thlow) && ((unsigned int) pxl[k].i < thhigh)) pxl[k].i = 255;
		else pxl[k].i = 0;
	}
}

void inverseGray(){
	int w, h;
	PIXEL *pxl;

	pxl = getImg();
	w = getWidth();
	h = getHeigth();

	for(unsigned int k = 0; k < (w*h); k++){
		pxl[k].i = 255 - pxl[k].i;
	}
}

void addGray(unsigned char value){
	int w, h;
	PIXEL *pxl;

	pxl = getImg();
	w = getWidth();
	h = getHeigth();

	for(unsigned int k = 0; k < (w*h); k++){
		if((int) (pxl[k].i + value) > 255) pxl[k].i = 255;
        else pxl[k].i += value;
	}	
}

void inverseColor(){
	int w, h;
	PIXEL *pxl;

	pxl = getImg();
	w = getWidth();
	h = getHeigth();

	for(unsigned int k = 0; k < (w*h); k++){
		pxl[k].r = 255 - pxl[k].r;
		pxl[k].g = 255 - pxl[k].g;
		pxl[k].b = 255 - pxl[k].b;
	}
}

void addColor(unsigned char value){
	int w, h;
	PIXEL *pxl;

	pxl = getImg();
	w = getWidth();
	h = getHeigth();

	for(unsigned int k = 0; k < (w*h); k++){
		if((int) (pxl[k].r + value) > 255) pxl[k].r = 255;
        else pxl[k].r += value;
        if((int) (pxl[k].g + value) > 255) pxl[k].g = 255;
        else pxl[k].g += value;
        if((int) (pxl[k].b + value) > 255) pxl[k].b = 255;
        else pxl[k].b += value;
	}
}

void addColor(unsigned char valueR, unsigned char valueG, unsigned char value){
	int w, h;
	PIXEL *pxl;

	pxl = getImg();
	w = getWidth();
	h = getHeigth();

	for(unsigned int k = 0; k < (w*h); k++){
		if((int) (pxl[k].r + valueR) > 255) pxl[k].r = 255;
        else pxl[k].r += valueR;

        if((int) (pxl[k].g + valueG) > 255) pxl[k].g = 255;
        else pxl[k].g += valueG;

        if((int) (pxl[k].b + valueB) > 255) pxl[k].b = 255;
        else pxl[k].b += valueB;
	}
}

void rgb2Gray(){
	int w, h;
	PIXEL *pxl;
	unsigned int value

	pxl = getImg();
	w = getWidth();
	h = getHeigth();

	for(unsigned int k = 0; k < (w*h); k++){
		value = ((unsigned int) pxl[k].r + pxl[k].g + pxl[k].b) / 3;
        pxl[k].i = value;
	}
}

