#include <stdio.h>
#include <stdlib.h>

/*Estructura que representa una carta (Valor y Palo)*/
struct Carta
{
    int valor; // Del 1 al 13
    char palo; // ♥ = C, ♦ = D, ♣ = T y ♠ = E
};

/* Baraja (Esta es una pila)*/
struct Baraja{
    struct Carta *carta;
    struct Baraja *siguiente;
};

/* Orden de turnos y jugadores (Esta es una lista simple) */
struct Jugadores
{
	char nombre[50];
    int apuesta;
	struct Jugadores *siguiente;
};

/*Operaciones para la pila (Baraja)*/
int push(struct Baraja **baraja, Carta *carta);
int pop(struct Baraja **baraja);
void mostrarBaraja(struct Baraja *baraja);

/*Operaciones para la lista (Jugadores)*/
int agregar(struct Jugadores **turnos);
int eliminar(struct Jugadores **turnos, char nombre[50]);
void mostrarListaJugadores(struct Jugadores *turnos);


Carta* CrearBaraja(Carta *ArregloBaraja[]);
Carta* Barajar(Carta *ArregloBaraja[]);
void Crear_Barajar_Y_Anadir(struct Baraja **baraja);

int tamano(struct Jugadores *lista){                                     // Paso por valor
                                                                        // Apuntador auxiliar que comienza donde inicia la lista (No es necesario XD trabaja con lista)
    int pos=0;
    while(lista->siguiente!=NULL){                                        // Mientras aux->siguiente sea diferente de nulo (Recorre toda la lista)
        lista=lista->siguiente;                                             // Aumenta el numero de elementos y pasa al siguiente
        pos++;
    }
    pos++;                                                              // Ultimo elemento
    
    return pos;
}

void titulo(){
    // Pagar de 3 a 2 es pagar x1.5 el valor de tu apuesta
    // Pagar 2 a 1 es pagar x1 el valor de tu apuesta
    printf("--------------------------------------------\n");
    printf("|             BLACKJACK ESCOM              |\n");
    printf("|          Blackjack se paga 3 a 2         |\n");
    printf("|  Croupier pide en 16 y se planta en 17   |\n");
    printf("--------------------------------------------\n");
    printf("****           Se paga 2 a 1            ****\n\n");
}


int main(){

    struct Baraja *baraja=NULL;                                         /* Se crea el apuntador de la Baraja (Pila) */
    
	baraja=(struct Baraja*)malloc(sizeof(struct Baraja));               /* Se asigna espacio en memoria */
    
	baraja->siguiente=NULL;                                             /* Se asigna siguiente a NULL por que la pila esta vacia */

    struct Jugadores *orden_turnos=NULL;                                /* Se crea el apuntador de la lista (Orden de turnos) */

    //orden_turnos=(struct Jugadores*)malloc(sizeof(struct Jugadores));   /* Se asigna espacio en memoria */
                                        
    Crear_Barajar_Y_Anadir(&baraja);                                    /* Se Crea, barajan las cartas y se meten a la pila para simular la baraja*/

    printf("%d \n",tamano(orden_turnos));
    agregar(&orden_turnos);
    agregar(&orden_turnos);
    agregar(&orden_turnos);
    printf("%d \n",tamano(orden_turnos));

    printf("1-----\n");
    mostrarListaJugadores(orden_turnos);    
    printf("-----\n");

    titulo();                                                          /* Imprime el bonito titulo */

    return 0;
}

Carta* Barajar(Carta *ArregloBaraja[]){
    Carta *aux;
    aux=(struct Carta*)malloc(sizeof(struct Carta));
    int random;
    for(int j=0;j<rand()%4;j++){
        for(int i = 0; i < 52; i++)
        {
            random = rand()%52;
            aux = ArregloBaraja[i];
            ArregloBaraja[i]=ArregloBaraja[random];
            ArregloBaraja[random]=aux;
        }
    }

    return *ArregloBaraja;
}

void Crear_Barajar_Y_Anadir(struct Baraja **baraja){
    Carta *ArregloBaraja[52];
    
    *ArregloBaraja=CrearBaraja(ArregloBaraja);
    
    *ArregloBaraja=Barajar(ArregloBaraja);
    
    for(int i=0;i<52;i++){
        push(&*baraja, ArregloBaraja[i]);
    }

}

Carta* CrearBaraja(Carta *ArregloBaraja[]){
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

int push(struct Baraja **baraja, Carta *carta)
{
	struct Baraja *nuevo=NULL;

	nuevo=(struct Baraja*)malloc(sizeof(struct Baraja));
	
	if(nuevo==NULL)
	{
		return -1;
	}

	nuevo->carta=carta;
	nuevo->siguiente=*baraja;
	*baraja=nuevo;

	return 0;
}

int pop(struct Baraja **baraja)
{
	struct Baraja *aux=NULL;
	aux=*baraja;

	if(*baraja==NULL)
	{
		return -1;
	}
	else
	{
		*baraja=aux->siguiente;
		free(aux);
	}
	
	return 0;
}

void mostrarBaraja(struct Baraja *baraja)
{
	while(baraja->siguiente!=NULL)
	{
            if( (baraja->carta)->valor <= 10){
                printf("%d%c ",(baraja->carta)->valor,(baraja->carta)->palo);
            }else{
                if((baraja->carta)->valor == 11){
                    printf("J%c ",(baraja->carta)->palo);
                }
                if((baraja->carta)->valor == 12){
                    printf("Q%c ",(baraja->carta)->palo);
                }
                if((baraja->carta)->valor == 13){
                    printf("K%c ",(baraja->carta)->palo);
                }
            }
            baraja=baraja->siguiente;
	}
	printf("\n");
}

int agregar(struct Jugadores **lista)
{
	struct Jugadores *nuevo=NULL;
	nuevo=(struct Jugadores*)malloc(sizeof(struct Jugadores));

    struct Jugadores *actual=NULL;
	actual=(struct Jugadores*)malloc(sizeof(struct Jugadores));
    actual->siguiente=NULL;
    actual=*lista;

    struct Jugadores *siguiente=NULL;
	siguiente=(struct Jugadores*)malloc(sizeof(struct Jugadores));
    siguiente->siguiente=NULL;
    siguiente=*lista;

	if(nuevo==NULL)
	{
		return 0;
	}

    printf("Nombre: ");
    scanf("%s",nuevo->nombre);

    nuevo->apuesta=100;

	if(*lista==NULL){                                        // Si la lista esta vacia
        *lista=nuevo;
    }else{                                                  // Si no esta vacia   
        
        while(siguiente!=NULL){                             // Busco en la lista la posicion en la que va nuevo (entre actual y sig)
            actual=siguiente;
            siguiente=siguiente->siguiente;
        }
                                                            // Si no entra al while o termina, ya encontro la posición en donde va nuevo (entre actual y sig) 
        if(actual==siguiente){                                    // Si actual y sig son iguales entonces nuevo va primero en la lista
            nuevo->siguiente=*lista;                     
            *lista=nuevo;    
        }else{
            actual->siguiente=nuevo;                        // En caso contrario va entre elementos y se inserta despues de actual y antes de siguiente
            nuevo->siguiente=siguiente;
        }
       
    }


	return 0;
}

int eliminar(struct Jugadores **lista,  char nombre[50])
{
	struct Jugadores *actual=NULL;
	struct Jugadores *aux=NULL;
	struct Jugadores *primero=NULL;
	actual=*lista;
	aux=*lista;
	primero=(*lista)->siguiente;

	if((*lista)->nombre==nombre)
	{
		while(aux->siguiente!=*lista)
		{
			aux=aux->siguiente;
		}
		
		aux->siguiente=(*lista)->siguiente;
		free(*lista);
		*lista=aux;
	}
	else
	{
		while(primero!=*lista)
		{
			if(actual->nombre!=nombre)
			{
				actual=actual->siguiente;
			}
		
			if(aux->siguiente!=actual)
			{
				aux=aux->siguiente;
			}

			primero=primero->siguiente;	
		}

		aux->siguiente=actual->siguiente;
		free(actual);
		actual=*lista;
		aux=*lista;
	}	

	return 0;
}

void mostrarListaJugadores(struct Jugadores *lista)
{

    if(lista==NULL){
        printf("Lista vacia\n");
    }else{
        while(lista->siguiente!=NULL){                                                        // Mientras aux->siguiente sea diferente de nulo va a imprimir el elemento
            printf("Nombre: %s Apuesta: %d\n", lista->nombre,lista->apuesta);
            lista=lista->siguiente;                                                             // Imprime y aux avanza al siguente
        }
        printf("Nombre: %s Apuesta: %d\n", lista->nombre,lista->apuesta);                       // Imprime el ultimo elemento de la lista
    }


}	