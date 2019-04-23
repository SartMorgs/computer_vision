#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "Imagem.cpp"

using namespace std;

Imagem img;


int main(){
	FILE *ppm_file, *pgm_file, *pg, *pp;
	PIXEL *p, *q;
	double *w;

	int kernel[9] = {   1, 2, 1,
                        2, 4, 2,
                        1, 2, 1};

	// LEITURA ARQUIVOS PGM E PPM
	p = NULL;
	//img.readPGM(pgm_file, "road.pgm");
	img.readPPM(ppm_file, "Color.ppm");
    p = img.getImg();

    w = img.findWeightArray(3);
    img.convolve(kernel, 3, w);
    //img.inverseColor();

    // ESCRITA ARQUIVOS PGM E PPM
    //img.writePGM(pg, "asfalto.pgm");
    img.writePPM(pp, "teste_nl.ppm");

	return 0;
}

