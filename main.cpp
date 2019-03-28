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
	img.readPGM(pgm_file, "apple.pgm");
	img.readPPM(ppm_file, "apple.ppm");
    p = img.getImg();

    // ESCRITA ARQUIVOS PGM E PPM
    img.writePGM(pg, "apple_pgm.pgm");
    img.writePPM(pp, "apple_ppm.ppm");

	return 0;
}
