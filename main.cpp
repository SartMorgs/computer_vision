#include <iostream>
#include <stdio.h>
#include "PPM_and_PGM.cpp"

Imagem img;
FILE *arq_ppm, *arq_pgm;

void read();
void write();

int main(){
    PIXEL **pixels;
    int w, h;

    read();

    img.getTogether();
    w = img.getWidth();
    h = img.getHeigth();
    pixels = img.getPixels();

    for(int j = 0; j < 2; j++){
        for(int i = 0; i < (h*w); i++){
            cout<<pixels[j][i]<<"\t";
        }
        cout<<"\n";
    }

    write();

    return 0;
}

void read(){
    arq_ppm = fopen("apple.ppm", rt);
    arq_pgm = fopen("apple.pgm", rt);

    // PPM
    if(arq_ppm != NULL){
        img.readPPM(arq_ppm);
    }
    else{
        cout<<"Problemas na abertura do arquivo"<< "\n";
    }

    // PGM
    if(arq_pgm != NULL){
        img.readPGM(arq_pgm);
    }
    else{
        cout<<"Problemas na abertura do arquivo"<< "\n";
    }

    // Fecha os arquivos
    fclose(arq_ppm); fclose(arq_pgm);
}

void write(){
    arq_ppm = fopen("apple.ppm", wt);
    arq_pgm = fopen("apple.pgm", wt);

    // PPM
    if(arq_ppm != NULL){
        img.writePPM(arq_ppm);
    }
    else{
        cout<<"Problemas na criacao do arquivo"<< "\n";
    }

    // PGM
    if(arq_pgm != NULL){
        img.writePGM(arq_pgm);
    }
    else{
        cout<<"Problemas na criacao do arquivo"<< "\n";
    }

    // Fecha os arquivos
    fclose(arq_ppm); fclose(arq_pgm);
}
