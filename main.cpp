#include <iostream>
#include <stdlib.h>
#include "Imagem.cpp"

using namespace std;

Imagem img;


int main(){
	FILE *ppm_file, *pgm_file, *pg, *pp;
	PIXEL *p;
	int index;

	// LEITURA ARQUIVOS PGM E PPM
	p = NULL;
	//img.readPGM(pgm_file, "road.pgm");
	img.readPPM(ppm_file, "road.ppm");
    p = img.getImg();

    // THRESHOLD IMAGEM
    //img.thresholdGray(240);
    img.thresholdRGB(70, 90, 80, 90, 70, 100);

    // ESCRITA ARQUIVOS PGM E PPM
    //img.writePGM(pg, "asfalto.pgm");
    img.writePPM(pp, "asfalto.ppm");

	return 0;
}
