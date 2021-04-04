#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "Imagem.cpp"

using namespace std;

Imagem img;

int main(){
	FILE *ppm_file, *pgm_file, *pg, *pp;
	//PIXEL *p, *q;
	double *w;

	// LEITURA ARQUIVOS PGM E PPM
	//p = NULL;
	img.readPGM(pgm_file, "almofada.pgm");
	//img.readPPM(ppm_file, "star.ppm");
    //p = img.getImg();

    //img.edgeRoberts(30);
    img.edgeSobel(20);
    //img.edgeRobinson(70);
    //img.inverseColor();

    // ESCRITA ARQUIVOS PGM E PPM
    //img.writePGM(pg, "asfalto.pgm");
    img.writePGM(pg, "teste_result.pgm");

	return 0;
}

