#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

struct Carta
{
    int valor;
    char palo;
};

struct Baraja{
    struct Carta* Carta;
    struct Baraja* siguiente;
};

void imprimir(Carta* ArregloBaraja[]){
    for(int i=0;i<52;i++){
        char kqj;
        if( (ArregloBaraja[i])->valor <= 10){
            printf("%d%c ",(ArregloBaraja[i])->valor,(ArregloBaraja[i])->palo);
        }else{
            if((ArregloBaraja[i])->valor == 11){
                printf("J%c ",(ArregloBaraja[i])->palo);
            }
            if((ArregloBaraja[i])->valor == 12){
                printf("Q%c ",(ArregloBaraja[i])->palo);
            }
            if((ArregloBaraja[i])->valor == 13){
                printf("K%c ",(ArregloBaraja[i])->palo);
            }
        }
        if(i % 13 == 12){
            printf("\n");
        }
    }
}

Carta* CrearBaraja(Carta* ArregloBaraja[]);

int main(){

    Carta* ArregloBaraja[52];
    /* Llenar baraja */
    *ArregloBaraja=CrearBaraja(ArregloBaraja);
    
    //imprimir(ArregloBaraja);
    printf("--------------------------------------------\n");
    printf("|             BLACKJACK ESCOM              |\n");
    printf("|          Blackjack se paga 3 a 2         |\n");
    printf("|  Croupier pide en 16 y se planta en 17   |\n");
    printf("--------------------------------------------\n");
    printf("****           Se paga 2 a 1            ****\n\n");

    return 0;
}


Carta* CrearBaraja(Carta* ArregloBaraja[]){
    int indice=0;
    for(int i=0;i<4;i++){
            for(int j=0;j<13;j++){
                /* Crea la carta */
                struct Carta *carta=NULL;
                carta=(struct Carta*)malloc(sizeof(struct Carta));
                /* Asigna el valor a la carta */ 
                carta->valor = j + 1;

                /* Asigna el palo a la carta */
                switch (i)
                {
                case 0:
                    carta->palo = 'C';
                    break;
                case 1:
                    carta->palo = 'D';
                    break;
                case 2:
                    carta->palo = 'T';
                    break;
                case 3:
                    carta->palo = 'E';
                    break;
                default:
                    break;
                }
                ArregloBaraja[indice]=carta;
                indice++;
            }        
        }
        return *ArregloBaraja;
}