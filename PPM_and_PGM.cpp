#include <iostream>

typedef struct Pixel{
	int r, g, b, pg;
} PIXEL;

class Imagem{

	private:
		PIXEL **pixels;
		int width, heigth, index, i = 0;
		char type[2];

		char* getType(){
			return type;
		}

		void setType(char *t){
			type = t;
		}

		int getWidth(){
			return width;
		}

		void setWidth(int w){
			width = w;
		}

		int getHeigth(){
			return heigth;
		}

		void setHeigth(int h){
			heigth = h;
		}

		void setPixels(PIXEL **p){
			pixels = p;
		}

		PIXEL getPixels(){
			return pixels;
		}


		// Função de leitura PPM
		void readPPM(FILE *arq){
			PIXEL *pixel;
			int t, w, h;

			fscanf(arq, "%s %d %d\n\n", &t, &w, &h);			// Leitura do cabeçalho
			setType(t);
			setWidth(w);
			setHeigth(h);

			pixel = (PIXEL*) malloc(sizeof(PIXEL)*h*w*3);		// Aloca espaço para um vetor com o tamanho dos pixels no arquivo


			for(int j = 0; j < (h*w); j++){
				index = j / w;
				fscanf(arq, "%d %d %d", &pixel[j].r, &pixel[j].g, &pixel[j].b);
			}

		}

		// Função de leitura PGM
		void readPGM(FILE *arq){
			PIXEL *pixel;
			int t, w, h;

			fscanf(arq, "%s %d %d\n\n" &t, &w, &h);
			setType(t);
			setWidth(w);
			setHeigth(h);

			pixel = (PIXEL*) malloc(sizeof(PIXEL)*h*w);

			for(int j = 0; j < (h*w); j++){
				index = j / w;
				fscanf(arq, "%d", &pixel[j].pg);
			}
		}

		// Função de escrita PPM
		void writePPM(PIXEL *vector, int w, int h){
			int index, x, *color;
			FILE *fp = fopen("first.ppm", "wb");
			color = (int*)malloc(sizeof(int)*3);

			(void)fprintf(fp, "P6\n%d %d\n255\n", w, h);
			for(int i = 0; i < (h*w); i = i+3){
				index = i / w;
				color[0] = vector[i];
				color[1] = vector[i+1];
				color[2] = vector[i+2];
				(void)fwrite(color, 1, 3, fp);
			}

			(void)fclose(fp);
		}

		void writePGM(PIXEL *vector){

		}

		void getTogether(PIXEL *ppm, PIXEL *pgm){
			PIXEL **px;
			int h, w;

			h = getHeigth();
			w = getWidth();

			px = (PIXEL**) malloc(sizeof(PIXEL*)*1);

			for(int j = 0; j < (h*w); j++){
                px[j] = (PIXEL*) malloc(sizeof(PIXEL)*h*w);
			}

			px[0] = ppm;
			px[1] = pgm;

			setPixels(px);
		}
}
