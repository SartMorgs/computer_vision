#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

typedef unsigned int u_int;
typedef unsigned char u_char;
typedef struct pixel{
	u_int r, g, b, i;
}PIXEL;

class Imagem{
	private:
		u_int width, height, n;
		char type[2];
		PIXEL *px;
	public:

		// Componente necessários da imagem
		void setWidth(u_int w);
		u_int getWidth();
		void setHeight(u_int h);
		u_int getHeight();
		void setType(char t[]);
		char* getType();
		void setPGM(PIXEL* pgm);
		void setPPM(PIXEL* ppm);
		void setPPM(u_int R[], u_int G[], u_int B[]);
		void setImg(PIXEL* pgm, PIXEL* ppm, PIXEL* img, u_int w, u_int h);
		PIXEL* getImg();

		// Funções separar componentes RGB
	    u_int* getR();
	    u_int* getG();
	    u_int* getB();

		// Funções de leitura e escrita
		void readPGM(FILE* arq, const char* filename);
		void writePGM(FILE* arq, const char* filename);
		void readPPM(FILE* arq, const char* filename);
		void writePPM(FILE* arq, const char* filename);

		// Funções de escala cinza
		void thresholdGray(u_int th);
		void thresholdGray(u_int thlow, u_int thhigh);
		void inverseGray();
		void addGray(unsigned char value);

		// Funções de RGB
		void inverseColor();
		void addColor(unsigned char value);
		void addColor(unsigned char valueR, unsigned char valueG, unsigned char valueB);
		void rgb2Gray();

		// Funções distância
		void normL1(u_int refR, u_int refG, u_int refB, u_int th);
		void normL2(u_int refR, u_int refG, u_int refB, u_int th);
		void normMahalanobis(u_int *vectorR, u_int *vectorG, u_int *vectorB, u_int n, u_int th);
		void normKneighbors(u_int *vectorR, u_int *vectorG, u_int *vectorB, u_int s, u_int numOrb, u_int th);

        // Funções de filtro
        double* findWeightArray(u_int s);
		void filter(int kernel[], u_int s, u_int w);          // Kernel com peso fixo (linear)
		void filter(int kernel[], u_int s, double w[]);        // Kernel com peso variável (não-linear)

		// Funções de detecção de borda
		void edgeRoberts(u_int th);
		void edgeSobel(u_int th);
		void edgeRobinson(u_int th);
};
