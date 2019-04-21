#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "Imagem.cpp"

using namespace std;

Imagem img;


int main(){
	FILE *ppm_file, *pgm_file, *pg, *pp;
	PIXEL *p, *q;
	int kernel[25] = {  1, 2, 4, 2, 1,
                        2, 4, 8, 4, 2,
                        4, 8, 64, 8, 4,
                        2, 4, 8, 4, 2,
                        1, 2, 4, 2, 1};

	// LEITURA ARQUIVOS PGM E PPM
	p = NULL;
	//img.readPGM(pgm_file, "road.pgm");
	img.readPPM(ppm_file, "Gabarito/gabarito.ppm");
    p = img.getImg();

    img.convolve(kernel, 3);

    // ESCRITA ARQUIVOS PGM E PPM
    //img.writePGM(pg, "asfalto.pgm");
    img.writePPM(pp, "testegabarito.ppm");

	return 0;
}

