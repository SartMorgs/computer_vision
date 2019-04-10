#include <iostream>
#include <stdlib.h>
#include "Imagem.cpp"

using namespace std;

Imagem img;


int main(){
	FILE *ppm_file, *pgm_file, *pg, *pp;
	PIXEL *p;
	u_int pontos[3][30] = {  {81, 76, 80, 83, 72, 90, 86, 82, 83, 81, 79, 98, 82, 84, 85, 92, 83, 89, 76, 77, 82, 83, 78, 86, 91, 96, 82, 65, 69, 88},
                {82, 75, 80, 84, 71, 91, 89, 81, 82, 82, 77, 97, 84, 83, 86, 93, 83, 88, 75, 75, 83, 84, 83, 81, 92, 95, 81, 64, 68, 87},
                {87, 80, 90, 88, 76, 96, 81, 86, 87, 86, 82, 102, 89, 88, 91, 97, 85, 93, 80, 86, 88, 88, 89, 88, 96, 100, 87, 69, 76, 92}};;
	u_int medR, medG, medB;
	int index;

	medR = 83; medG = 82; medB = 87;

	// LEITURA ARQUIVOS PGM E PPM
	p = NULL;
	//img.readPGM(pgm_file, "road.pgm");
	img.readPPM(ppm_file, "road.ppm");
    p = img.getImg();

    // L1-NORM
    //img.normL1(medR, medG, medB, 25);

    // L2-NORM
    //img.normL2(medR, medG, medB, 25);

    // Mahalanobis
    //img.normMahalanobis(pontos[0], pontos[1], pontos[2], 30, 3);

    // K-vizinhos
    img.normKneighbors(pontos[0], pontos[1], pontos[2], 30, 8, 3);

    // THRESHOLD IMAGEM
    //img.thresholdGray(240);
    //img.thresholdRGB(70, 90, 80, 90, 70, 100);

    // ESCRITA ARQUIVOS PGM E PPM
    //img.writePGM(pg, "asfalto.pgm");
    img.writePPM(pp, "asfalto.ppm");

	return 0;
}
