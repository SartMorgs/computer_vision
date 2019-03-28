#include <iostream>
#include <stdlib.h>
#include "Imagem.cpp"

using namespace std;

Imagem img;


int main(){
	FILE *ppm_file, *pgm_file;
	PIXEL *p;
	int index;

	p = NULL;

    cout<< "INICIO DO PROGRAMA!" << "\n";

	//img.readPGM(pgm_file, "apple.pgm");
	img.readPPM(ppm_file, "apple.ppm");

	p = img.getImg();

	if(p == NULL) cout << "VAZIO!" << "\n";

	cout << "TAMANHO DA IMAGEM: " << img.getHeigth() << " x " << img.getWidth() << "\n";
/*
	cout << "IMAGEM PGM:" << "\n";
	index = 0;
	for(unsigned int k = 0; k < (img.getWidth()*img.getHeigth()); k++){
		cout << p[k].i << "\t";
		if((k / img.getWidth()) > index){
			cout << "\n";
			index = k / img.getWidth();
		}
	}
*/
	cout << "IMAGEM PPM:" << "\n";
	index = 0;
	for(unsigned int k = 0; k < (img.getWidth()*img.getHeigth()); k++){
		cout << p[k].r << "  " << p[k].g << " " << p[k].b << " " << "\t";
		if((k / img.getWidth()) > index){
			cout << "\n";
			index++;
		}
	}
	return 0;
}
