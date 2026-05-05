double calcDistancia(double *a, double *b, int dimensao) {
    double soma = 0.0;                    O(1)
    for (int i = 0; i < dimensao; i++) {  O(n)
        soma += pow(a[i] - b[i], 2);      O(1) por iteração
    }
    return sqrt(soma);                    O(1)
}

double calcDistancia(double *a, double *b, int dimensao) {
    double soma = 0.0;                     O(1)
    for (int i = 0; i < dimensao; i++) {   O(n) 
        soma += fabs(a[i] - b[i]);         O(1) por iteração
    }
    return soma;                           O(1)
}

double calcDistancia(double *a, double *b, int dimensao) {
    double dot = 0.0;                      O(1)
    double norm_a = 0.0;                   O(1)
    double norm_b = 0.0;                   O(1)
    for (int i = 0; i < dimensao; i++) {   O(n)
        dot += a[i] * b[i];                O(1) por iteração
        norm_a += a[i] * a[i];             O(1) por iteração
        norm_b += b[i] * b[i];             O(1) por iteração
    }
    
    // Evitar divisão por zero
    if (norm_a == 0 || norm_b == 0) {      O(1)
        return 1.0;                        O(1) 
    }

    double cos_sim = dot / (sqrt(norm_a) * sqrt(norm_b)); O(1)
    return 1.0 - cos_sim;                                 O(1)
}

double calcDistancia(double *a, double *b, int dimensao, double p) {
    double soma = 0.0;                       O(1)
    for (int i = 0; i < dimensao; i++) {     O(n)
        soma += pow(fabs(a[i] - b[i]), p);   O(1) por iteração
    }
    return pow(soma, 1.0 / p);               O(1)
}

double calcDistancia(double *a, double *b, int dimensao) {
    double max = 0.0;                           O(1)
    
    for (int i = 0; i < dimensao; i++) {        O(n) 
        double diferenca = fabs(a[i] - b[i]);   O(1) por iteração
        if (diferenca > max) {                  O(1) por iteração 
            max = diferenca;                    O(1) por iteração
        }
    }
    
    return max;                                 O(1)
}




