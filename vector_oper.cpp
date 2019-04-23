#include <iostream>
#include <stdlib.h>
#include <math.h>

typedef unsigned int u_int;

double average(u_int *vec, u_int n){
    int sum = 0;
    double average;

    for(u_int k = 0; k < n; k++){
        sum += vec[k];
    }

    average = ((double)sum / (double)n);
    return average;
}

double average(u_int *vec, u_int b, u_int e){
    int sum = 0;
    double average;

    for(u_int k = b; k < e; k++){
        sum += vec[k];
    }

    average = ((double)sum / (double)(e - b));

    return average;
}

double covariance(u_int vectorX[], u_int vectorY[], u_int n, double averageX, double averageY){
    double covariance, sumCovariance = 0;

    for(u_int k = 0; k < n; k++){
        sumCovariance += ((double)vectorX[k] - averageX)*((double)vectorY[k] - averageY);
    }

    covariance = abs((double)sumCovariance) / (double)(n - 1);

    return covariance;
}

double variance(u_int vec[], u_int n, double average){
    double sum = 0.0, result;

    for(u_int k = 0; k < n; k++){
        sum += ((((double)vec[k]) - average)*(((double)vec[k]) - average));
    }
    result = sum / n;

    return result;
}

double stddv(u_int vec[], u_int n, double average){
    double sum = 0.0, result;

    for(u_int k = 0; k < n; k++){
        sum += (((double)vec[k]) - average);
    }
    result = sum / n;

    return result;

}

double *inverse(double matrix[]){
    double det;
    double *m_inverse;

    m_inverse = (double*) malloc(3*3*sizeof(double));

    det =   (matrix[0] * matrix[4] * matrix[8]) + (matrix[1] * matrix[5] * matrix[6]) + (matrix[2] * matrix[3] * matrix[7]) -
            ((matrix[6] * matrix[4] * matrix[2]) + (matrix[7] * matrix[5] * matrix[0]) + (matrix[8] * matrix[3] * matrix[6]));

    if(det != 0){
        m_inverse[0] = (1 / det) * ((matrix[4] * matrix[8]) - (matrix[7] * matrix[5]));
        m_inverse[1] = - ((1 / det) * ((matrix[3] * matrix[8]) - (matrix[6] * matrix[5])));
        m_inverse[2] = (1 / det) * ((matrix[3] * matrix[7]) - (matrix[6] * matrix[4]));
        m_inverse[3] = - ((1 / det) * ((matrix[1] * matrix[8]) - (matrix[7] * matrix[2])));
        m_inverse[4] = (1 / det) * ((matrix[0] * matrix[8]) - (matrix[6] * matrix[2]));
        m_inverse[5] = - ((1 / det) * ((matrix[0] * matrix[7]) - (matrix[6] * matrix[1])));
        m_inverse[6] = (1 / det) * ((matrix[1] * matrix[5]) - (matrix[4] * matrix[2]));
        m_inverse[7] = - ((1 / det) * ((matrix[0] * matrix[5]) - (matrix[3] * matrix[2])));
        m_inverse[8] = (1 / det) * ((matrix[0] * matrix[4]) - (matrix[3] * matrix[1]));
    }
    else{
        printf("DETERMINANTE 0 \n");
    }


    return m_inverse;
}


u_int maxFind(u_int m[], u_int n){
    u_int result = 0;

    for(u_int k = 0; k < n; k++){
        if(m[k] > result)
            result = m[k];
    }
    //printf("%d\n", result);
    return result;
}

double maxFind(double m[], u_int n){
    double result = 0;

    for(u_int k = 0; k < n; k++){
        if(m[k] > result)
            result = m[k];
    }
    //printf("%d\n", result);
    return result;
}


u_int* parameterize(u_int m[], u_int n, u_int mx, u_int p_e){
    u_int *result;
    result = (u_int*) malloc(n*sizeof(u_int));

    for(u_int k = 0; k < n; k++){
        result[k] = (u_int)((p_e * m[k]) / mx);
    }

    return result;
}

double* parameterize(double m[], u_int n, double mx, u_int p_e){
    double *result;
    result = (double*) malloc(n*sizeof(double));

    for(u_int k = 0; k < n; k++){
        result[k] = (((double)p_e * m[k]) / mx);
        //printf("%.6f\n", result[k]);
    }

    return result;
}

double* parameterize(double m[], u_int n, double mx, u_int p_b, u_int p_e){
    double *result;
    result = (double*) malloc(n*sizeof(double));

    for(u_int k = 0; k < n; k++){
        result[k] = (((double)p_e * (m[k] - (double) p_b)) / (mx - p_b));
        //printf("%.6f\n", result[k]);
    }

    return result;
}

void invertValue(double m[], u_int n, double mx){
    for(u_int k = 0; k < n; k++){
        m[k] = mx - m[k];
    }
}

