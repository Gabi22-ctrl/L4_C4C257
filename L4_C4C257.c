#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void encontrar_diagonal_mas_larga(int **matriz, int tamano, int *resultado){
    int contador = 0;
    *resultado = 0;
    // De la esquina inferior izquierda a la diagonal central
    for (int k = tamano-1; k >= 0; k--){ //Controla el paso entre diagonales
        for (int i = k, j = tamano-1; i<tamano; i++, j--){ //Controla el paso entre elementos para cada diagonal
            if (*(*(matriz +i)+j) == 1){ //Accedo a  elemento en cada posicion
                contador++;
                if (contador > *resultado){
                    *resultado = contador;
                }
            }
            else{
                contador = 0;
            }
        }
    }
    for (int k = tamano-2; k>=0; k--){ // La variable k permite el paso entre diagonales mediante el control de la posicion inicial j
        for (int i = 0, j = k; j >= 0; i++, j--){
            if (*(*(matriz + i)+j) == 1){
                contador++;
                if (contador > *resultado){ // Si la cantidad de 1s encontrada es mayor al maximo actual
                    *resultado = contador; //Cambia el maximo actual con el valor de la diagonal
                }
            }
            else {
                contador = 0; // Si se encuentra algo que no es 1, reinicia el contador
            }
        }
    }
}

void reservar_matriz(int ***matriz, int tamano) { //Función que reserva la memoria para la matriz 
    *matriz = malloc(tamano * sizeof(int*)); //Asigno la memoria para las filas, que van a contener punteros
    for (int i = 0; i < tamano; i++) {
        (*matriz)[i] = malloc(tamano * sizeof(int)); //Asigno la memoria de las columnas para cada fila
    }
}

void llenar_matriz(int **matriz, int size){ //Función que llena la matriz con 1s y 0s
    srand(time(NULL)); 
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            (*(*(matriz + i ) + j)) = rand() % 2; //Al acceder a cada posición, se le da un valor a este
        }
    }
}

void imprimir_matriz(int **matriz, int tamano){ //Función que imprime la matriz creada
    printf("La matriz utilizada de tamaño %d x %d es: \n", tamano, tamano);
    for (int i = 0; i < tamano; i++){
        for (int j = 0; j < tamano; j++){
            printf("%d ", *(*(matriz + i ) + j));
        }
        printf("\n");
    }
}

void liberar_espacio(int **matriz, int tamano){
    for (int i = 0; i < tamano; i++){
        free(matriz[i]); //Libero el espacio de cada columa
    }
    free(matriz); //Libero el espacio de la matriz total
}

void redimensionar_matriz(int ***matriz, int *tamano, int nuevo_tamano) {
    // Redimensionar las filas
    srand(time(NULL)); 
    *matriz = realloc(*matriz, nuevo_tamano * sizeof(int*)); 
    for (int i = 0; i < nuevo_tamano; i++) {
        // Redimensionar las columnas de cada fila
        (*matriz)[i] = realloc((*matriz)[i], nuevo_tamano * sizeof(int));
        if (matriz[i] == NULL){
            free(*matriz[i]);
            
    
        }
    }

    //Si la matriz se hace más grande, inicializar las nuevas posiciones con 1s o 0s
    for (int i = *tamano; i < nuevo_tamano; i++) {
        for (int j = 0; j < nuevo_tamano; j++) {
            (*matriz)[i][j] = rand()%2;
        }
    }

    //Si la matriz se hace más pequeña, sólo conservo los valores dentro del rango
    if (nuevo_tamano < *tamano) {
        for (int i = 0; i < nuevo_tamano; i++) {
            for (int j = 0; j < nuevo_tamano; j++) {
                (*matriz)[i][j] = (*matriz)[i][j];
            }
        }
    }

    // Actualizar el tamaño
    *tamano = nuevo_tamano;
}

int main(){
    int **matriz = NULL;
    int TAMANO;
    int diagonal_larga = 0;
    int nuevo_tamano;
    char opcion;

    // Pedir el tamaño inicial de la matriz
    printf("Escriba el tamaño de la matriz cuadrada: \n");
    scanf("%d", &TAMANO);
    
    // Reservar memoria para la matriz
    reservar_matriz(&matriz, TAMANO);
    if (matriz == NULL) {
        printf("No fue posible reservar memoria\n");
        return 1;
    }

    //Llenar la matriz con valores aleatorios
    llenar_matriz(matriz, TAMANO);
    imprimir_matriz(matriz, TAMANO);
    
    //Encontrar la diagonal más larga de 1s
    encontrar_diagonal_mas_larga(matriz, TAMANO, &diagonal_larga);
    printf("La diagonal más larga de 1s consecutivos es: %d \n", diagonal_larga);
    
    //Preguntar al usuario si desea cambiar el tamaño de la matriz
    do {
        printf("¿Desea cambiar el tamaño de la matriz? (s/n): ");
        scanf(" %c", &opcion);
        
        if (opcion == 's' || opcion == 'S') {
            printf("Escriba el nuevo tamaño de la matriz: ");
            scanf("%d", &nuevo_tamano);
        

            if (nuevo_tamano != TAMANO) {
                //Redimensionar la matriz
                redimensionar_matriz(&matriz, &TAMANO, nuevo_tamano);

                //Imprimir la nueva matriz
                imprimir_matriz(matriz, TAMANO);
                encontrar_diagonal_mas_larga(matriz, nuevo_tamano, &diagonal_larga);
                printf("La diagonal más larga de 1s consecutivos es: %d \n", diagonal_larga);
            }
        }
        
        
        
    } while (opcion == 's' || opcion == 'S');
    
    // Liberar espacio al final
    liberar_espacio(matriz, TAMANO);
    
    return 0;
}
