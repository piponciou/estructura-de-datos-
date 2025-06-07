
int cantidadApuestasUsuario(struct Casino *casino, char *userId) {
    int i, suma = 0;
    for (i = 0; i < maxArreglo; i++) {
        if (casino->bets[i] != NULL && strcmp(casino->bets[i]->usuario->userId, userId) == 0) {
            suma++;
        }
    }
    return suma;
}


float promedioMontoPorJuego(struct Casino *casino, char *nombreJuego) {

    int i,totalApuestas = 0;
    float sumaMonto = 0.0;

    for (i = 0; i < maxArreglo; i++)
        {
        if (casino->bets[i] != NULL && strcmp(casino->bets[i]->juego->nombreJuego,nombreJuego) == 0){
            totalApuestas++;
            sumaMonto += casino->bets[i]->montoApostado;
            }
        }

    if (totalApuestas == 0) return 0.0;
    else {
        return sumaMonto/totalApuestas;
    }
}
