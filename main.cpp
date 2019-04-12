#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "Imagem.cpp"

using namespace std;

Imagem img;


int main(){
	FILE *ppm_file, *pgm_file, *pg, *pp;
	PIXEL *p;
	double avR, avG, avB;

    // Carro Brancp
    //u_int rpts[30] = {245, 182, 190, 194, 247, 254, 222, 241, 211, 245, 189, 193, 222, 240, 182, 244, 250, 241, 244, 184, 233, 199, 245, 242, 194, 245, 250, 200, 188, 249};
    //u_int gpts[30] = {244, 190, 198, 198, 250, 255, 234, 241, 218, 243, 196, 202, 227, 243, 190, 243, 241, 244, 244, 195, 238, 206, 245, 241, 194, 245, 255, 207, 196, 252};
    //u_int bpts[30] = {250, 193, 201, 207, 255, 255, 234, 253, 226, 244, 204, 207, 231, 250, 193, 249, 244, 251, 242, 197, 242, 214, 243, 246, 202, 243, 255, 215, 199, 255};

    // Carro Vermelho
    //u_int rpts[30] = {193, 71, 184, 192, 115, 75, 87, 186, 183, 192, 194, 198, 157, 93, 198, 205, 208, 209, 104, 107, 128, 96, 203, 113, 188, 34, 118, 176, 107, 80};
    //u_int gpts[30] = {117, 1, 90, 102, 6, 0, 0, 95, 104, 107, 110, 123, 42, 0, 124, 132, 175, 134, 30, 33, 102, 13, 130, 33, 165, 0, 53, 118, 29, 0};
    //u_int bpts[30] = {147, 11, 127, 137, 35, 11, 17, 130, 135, 140, 144, 154, 83, 19, 151, 162, 192, 165, 57, 58, 115, 43, 160, 60, 181, 16, 77, 140, 55, 25};

    // Ônibus Verde
    u_int rpts[45] = {162, 161, 163, 165, 164, 157, 162, 164, 163, 162, 164, 163, 162, 163, 161, 163, 162, 162, 162, 163, 163, 161, 162, 162, 161, 163, 160, 160, 158, 158, 144, 140, 140, 144, 136, 164, 147, 139, 141, 142, 145, 187, 157, 135, 141};
    u_int gpts[45] = {254, 253, 253, 255, 253, 252, 253, 254, 255, 254, 254, 255, 253, 255, 254, 255, 255, 255, 254, 253, 252, 253, 255, 255, 253, 255, 253, 253, 250, 250, 247, 243, 244, 247, 250, 244, 246, 241, 250, 252, 249, 247, 244};
    u_int bpts[45] = {65, 64, 67, 72, 73, 62, 74, 71, 70, 67, 68, 70, 70, 66, 62, 66, 63, 63, 65, 67, 72, 66, 63, 63, 64, 66, 61, 61, 61, 61, 44, 40, 35, 37, 36, 93, 47, 38, 39, 37, 36, 126, 54, 39, 41};

    // Cálculo da média dos pontos
    avR = average(rpts, 45); avG = average(gpts, 45); avB = average(bpts, 45);

    // L1-Norm
    p = NULL;
	img.readPPM(ppm_file, "Amostra/amostra10.ppm");
    p = img.getImg();
    img.normL1(avR, avG, avB, 15);
    //img.writePPM(pp, "testel1.ppm");
    img.writePPM(pp, "Resultados/amostra_10/result_l1.ppm");

    // L2-Norm
    p = NULL;
	img.readPPM(ppm_file, "Amostra/amostra10.ppm");
    p = img.getImg();
    img.normL2(avR, avG, avB, 50);
    //img.writePPM(pp, "testel2.ppm");
    img.writePPM(pp, "Resultados/amostra_10/result_l2.ppm");

    // Mahalanobis
    p = NULL;
	img.readPPM(ppm_file, "Amostra/amostra9.ppm");
    p = img.getImg();
    img.normMahalanobis(rpts, gpts, bpts, 45, 4);
    //img.writePPM(pp, "testem.ppm");
    img.writePPM(pp, "Resultados/amostra_9/result_m.ppm");


    // KNN
    p = NULL;
	img.readPPM(ppm_file, "Amostra/amostra10.ppm");
    p = img.getImg();
    img.normKneighbors(rpts, gpts, bpts, 45, 30, 35);
    //img.writePPM(pp, "testek.ppm");
    img.writePPM(pp, "Resultados/amostra_10/result_k.ppm");

	return 0;
}
