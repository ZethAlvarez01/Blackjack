#include <stdio.h>
#include <stdlib.h>

/*Estructura que representa una carta (Valor y Palo)*/
struct Carta
{
    int valor; // Del 1 al 13
    char palo; // ♥ = C, ♦ = D, ♣ = T y ♠ = E
};

/* Pila (Esta es una pila)*/
struct Pila{
    struct Carta *carta;
    struct Pila *siguiente;
};

/*Cartas repartidas por jugador*/
struct ListaCartas
{
	Carta* carta;
	ListaCartas *siguiente;
};

/* Orden de turnos y Jugadores (Esta es una lista simple) */
struct Lista
{
	char nombre[50];
    int apuesta;
    int estado;                 // 0 = In Game 1 = Game Over
    Carta* lista_de_cartas[10];
	Lista *siguiente;
};


/*Operaciones para la pila*/
int push(struct Pila **Pila, Carta *carta);
Pila* pop(struct Pila **Pila);
void mostrarPila(struct Pila *Pila);

/*Operaciones para la Lista*/
void pushLista(Lista* &);
void popLista(Lista* &,char []);
void mostrarLista(Lista*,int);
int tamanoLista(Lista*);
void pushCrupier(Lista* &);

Carta* CrearPila(Carta *ArregloPila[]);
Carta* Pilar(Carta *ArregloPila[]);
void Crear_Pilar_Y_Anadir(struct Pila **Pila);


int tamano(struct Lista *lista){                                     // Paso por valor
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

void anadirjugadores(Lista* &orden_turnos){
    system("cls");

    titulo();

    printf("Anadir jugadores\n");
    int stop=1;
    do{
        printf("Anade el nombre del nuevo jugador\n");
        pushLista(orden_turnos);
        printf("Anadir mas jugadores? [1/YES][0/No]\n");
        scanf("%d",&stop);
    }while(stop!=0);
}

int main(){

    struct Pila *Pila=NULL;                                         /* Se crea el apuntador de la Pila (Pila) */
	Pila=(struct Pila*)malloc(sizeof(struct Pila));               /* Se asigna espacio en memoria */
	Pila->siguiente=NULL;                                             /* Se asigna siguiente a NULL por que la pila esta vacia */

    Lista *orden_turnos=NULL;                                /* Se crea el apuntador de la lista (Orden de turnos) */
    orden_turnos=(struct Lista*)malloc(sizeof(struct Lista));   /* Se asigna espacio en memoria */

    Crear_Pilar_Y_Anadir(&Pila);   

    system("cls");

    titulo(); 

    anadirjugadores(orden_turnos);

    int control=0;
    do{
        system("cls");
        titulo();
        printf("Comienza el juego!\nLista de jugadores: \n");
        mostrarLista(orden_turnos,1);
        printf("\nEmpezar o anadir otro jugador? [0 Empezar][1 Anadir jugador]\n");
        int op=0;
        scanf("%d",&op);
        switch (op)
        {
        case 0:
            control=1;
            break;
        case 1:
            anadirjugadores(orden_turnos);
            break;
        default:
            break;
        }

    }while(control==0);

    pushCrupier(orden_turnos);

    /*Comienza el juego
        Fases del turno
        1° Se hacen apuestas
        2° Se reparten las cartas a todos
        3° Inician jugadores
            - Separa
            - Dobla
            - Pide o planta
        4° Juega el crupier
        5° Se pagan apuestas
    */

   /* 1° Se hacen apuestas */
    system("cls");
    titulo();
    printf("\nHagan sus apuestas\n");
    mostrarLista(orden_turnos,0);
    Lista *aux2=orden_turnos;
    int apuestas[tamanoLista(orden_turnos)-1];
    int pos=0;

    
    while(aux2->siguiente!=NULL){
        printf("\n%s tienes para apostar: %d creditos\n",aux2->nombre,aux2->apuesta);
        int flg=1;
        do{
                
                printf("Cuanto quieres apostar?\n");
                int apu_actual=0;
                scanf("%d",&apu_actual);
                if(apu_actual > aux2->apuesta){
                    printf("\nNo puedes apostar mas de lo que tienes.\n");
                    flg=1;
                }else{
                    flg=0;
                    apuestas[pos]=apu_actual;
                    aux2->apuesta=aux2->apuesta-apu_actual;
                    pos++;
                }
        }while(flg!=0);
        
        aux2=aux2->siguiente;
    }

    for(int i=0;i<tamanoLista(orden_turnos)-1;i++){
        printf("%d ",apuestas[i]);
    }

    /* 2° Se reparten las cartas a todos */
    system("cls");
    titulo();
    printf("\nReparticion de cartas\n");
    printf("Las cartas se repartieron asi de la siguete forma.\n\n");
    //mostrarPila(Pila);   

    Lista* aux5=orden_turnos;
    ListaCartas* mano;
    while(aux5->siguiente!=NULL){
        mano=NULL;
        struct Pila* carta=pop(&Pila);
        aux5->lista_de_cartas[0]=carta->carta;
        carta=pop(&Pila);
        aux5->lista_de_cartas[1]=carta->carta;
        aux5=aux5->siguiente;
    }
    mano = NULL;
    struct Pila* carta=pop(&Pila);                      // Saco una carta del mazo y la guarda en un arreglo (siempre son 2 cartas por jugador)
    aux5->lista_de_cartas[0]=carta->carta;
    carta=pop(&Pila);
    aux5->lista_de_cartas[1]=carta->carta;

    Lista* aux6=orden_turnos;
     while(aux6->siguiente!=NULL){
         printf("La mano de %s es: \n",aux6->nombre);
         Carta* mano=aux6->lista_de_cartas[0];
         printf("%d%c ",mano->valor,mano->palo);
         mano=aux6->lista_de_cartas[1];
         printf("%d%c \n\n",mano->valor,mano->palo);
         aux6=aux6->siguiente;
     }
     printf("La mano del %s es: \n",aux6->nombre);
     Carta* mano2=aux6->lista_de_cartas[0];
     printf("%d%c ",mano2->valor,mano2->palo);
     mano2=aux6->lista_de_cartas[1];
     printf("%d%c \n\n",mano2->valor,mano2->palo);
     char contin;
     printf("Presiona una tecla...\n");
     fflush(stdin);
     scanf("%c",&contin);

     Lista* aux7=orden_turnos;
     int jug_act=0;
     int cartas_mano=2;
     int opcion=0;
     int parar = 1;
     int suma=0;

     while(aux7->siguiente!=NULL){

        system("cls");
        titulo();
        printf("\nComienza el juego\n\n ");

         printf("Es turno de %s\n",aux7->nombre);
         printf(" Mano actual\n");
         for(int i=0;i<cartas_mano;i++){
             printf(" %d%c",aux7->lista_de_cartas[i]->valor,aux7->lista_de_cartas[i]->palo);
         }
         printf("\n\n Que quieres hacer?\n\n 1 Doblar apuesta\n 2 Pedir carta\n 3 Plantarse\n\n Opcion: ");
         opcion=0;
         parar=1;
         fflush(stdin);
         scanf("%d",&opcion);
         
         switch (opcion){
            case 1:
                    system("cls");
                    titulo();
                    printf("\nComienza el juego %s\n\n ",aux7->nombre);

                if(apuestas[jug_act]>aux7->apuesta){
                    printf("\nNo tienes creditos suficientes\n\n Creditos actuales: %d",aux7->apuesta);
                }else{
                    printf("\nHas doblado tu apuesta inicial, solo recibiras una carta mas.\n");
                    aux7->apuesta=aux7->apuesta-apuestas[jug_act];
                    apuestas[jug_act]=apuestas[jug_act]+apuestas[jug_act];
                    printf(" Creditos restantes: %d\n Nueva apuesta: %d\n\n",aux7->apuesta,apuestas[jug_act]);
                    struct Pila* carta=pop(&Pila);  
                    aux7->lista_de_cartas[cartas_mano]=carta->carta;
                    cartas_mano++; 
                    printf("Tu nueva mano es: \n",aux7->nombre);
                    suma=0;
                    for(int i=0;i<cartas_mano;i++){
                        int valor=aux7->lista_de_cartas[i]->valor;
                        if(valor>=10){
                            valor=10;
                        }
                        suma=suma+valor;
                        printf(" %d%c",aux7->lista_de_cartas[i]->valor,aux7->lista_de_cartas[i]->palo);
                    }
                    if(suma>21){
                        aux7->estado=1;
                        printf("\n\n  Game Over!  ");
                    }
                        printf("\n\nPresiona una tecla...\n");
                        fflush(stdin);
                        scanf("%c",&contin);
                    

                    
                    jug_act++;
                    cartas_mano=2;
                    suma=0;

                }
                break;
            case 2:
                system("cls");
                titulo();
                printf("\nComienza el juego %s\n\n ",aux7->nombre);
                
                printf("Pide las cartas que quieras\n");
                while(parar!=0){
                    struct Pila* carta=pop(&Pila);  
                    aux7->lista_de_cartas[cartas_mano]=carta->carta;
                    cartas_mano++; 
                    printf("Tu nueva mano es: \n",aux7->nombre);
                    suma=0;
                    for(int i=0;i<cartas_mano;i++){
                        int valor=aux7->lista_de_cartas[i]->valor;
                        if(valor>=10){
                            valor=10;
                        }
                        suma=suma+valor;
                        printf(" %d%c",aux7->lista_de_cartas[i]->valor,aux7->lista_de_cartas[i]->palo);
                    }

                    if(suma>21){
                        aux7->estado=1;
                        printf("\n\n  Game Over!  ");
                        parar=0;
                    }else{
                        printf("\n\nPedir otra? [1/Si] [0/Plantarse]\n");
                        fflush(stdin);
                        scanf("%d",&parar);
                    }
                }

                printf("\n\nPresiona una tecla...\n");
                fflush(stdin);
                scanf("%c",&contin);
                jug_act++;
                cartas_mano=2;
                parar=1;
                suma=0;
                break;
            case 3:
                system("cls");
                titulo();
                printf("\nTe has plantado %s\n\n ",aux7->nombre);
                    printf(" Tu mano es\n");
                    suma=0;
                    for(int i=0;i<cartas_mano;i++){
                        int valor=aux7->lista_de_cartas[i]->valor;
                        if(valor>=10){
                            valor=10;
                        }
                        suma=suma+valor;
                        printf(" %d%c",aux7->lista_de_cartas[i]->valor,aux7->lista_de_cartas[i]->palo);
                    }

                    if(suma>21){
                        aux7->estado=1;
                        printf("\n\n  Game Over!  ");
                    }
                        printf("\n\nPresiona una tecla...\n");
                        fflush(stdin);
                        scanf("%c",&contin);
                    

                    jug_act++;
                    cartas_mano=2;
                    suma=0;
                break;
            default:
                break;
         }
         aux7=aux7->siguiente;
     }

    system("cls");
    titulo();
    printf("\n \n\n ");
     printf(" Es turno del %s \n",aux7->nombre);
     printf(" Su mano es\n");
     cartas_mano=2;
     suma=0;
            for(int i=0;i<cartas_mano;i++){
                suma=suma+aux7->lista_de_cartas[i]->valor;
                printf(" %d%c",aux7->lista_de_cartas[i]->valor,aux7->lista_de_cartas[i]->palo);
            }
            if(suma>21){
                aux7->estado=1;
                printf("\n\n  Game Over!  ");
            }else{
                while(suma<=16){
                    printf("\n\n");
                    struct Pila* carta=pop(&Pila);  
                    aux7->lista_de_cartas[cartas_mano]=carta->carta;
                    cartas_mano++; 
                    printf(" Su nueva mano es: \n",aux7->nombre);
                    suma=0;
                    for(int i=0;i<cartas_mano;i++){
                        int valor=aux7->lista_de_cartas[i]->valor;
                        if(valor>=10){
                            valor=10;
                        }
                        suma=suma+valor;
                        printf(" %d%c",aux7->lista_de_cartas[i]->valor,aux7->lista_de_cartas[i]->palo);
                    }
                    
                }
            }




    return 0;
}


Carta* Pilar(Carta *ArregloPila[]){
    Carta *aux;
    aux=(struct Carta*)malloc(sizeof(struct Carta));
    int random;
    for(int j=0;j<rand()%5;j++){
        for(int i = 0; i < 52; i++)
        {
            random = rand()%52;
            aux = ArregloPila[i];
            ArregloPila[i]=ArregloPila[random];
            ArregloPila[random]=aux;
        }
    }

    return *ArregloPila;
}

void Crear_Pilar_Y_Anadir(struct Pila **Pila){
    Carta *ArregloPila[52];
    
    *ArregloPila=CrearPila(ArregloPila);
    
    *ArregloPila=Pilar(ArregloPila);
    
    for(int i=0;i<52;i++){
        push(&*Pila, ArregloPila[i]);
    }

}

Carta* CrearPila(Carta *ArregloPila[]){
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
                ArregloPila[indice]=carta;
                indice++;
            }        
        }
        return *ArregloPila;
}

int push(struct Pila **Pila, Carta *carta)
{
	struct Pila *nuevo=NULL;

	nuevo=(struct Pila*)malloc(sizeof(struct Pila));
	
	if(nuevo==NULL)
	{
		return -1;
	}

	nuevo->carta=carta;
	nuevo->siguiente=*Pila;
	*Pila=nuevo;

	return 0;
}

Pila* pop(struct Pila **Pila)
{
	struct Pila *aux=NULL;
	aux=*Pila;

	if(*Pila==NULL)
	{
		return NULL;
	}
	else
	{
		*Pila=aux->siguiente;
        return aux;
	}
}

void mostrarPila(struct Pila *Pila)
{
	while(Pila->siguiente!=NULL)
	{
            if( (Pila->carta)->valor <= 10){
                printf("%d%c ",(Pila->carta)->valor,(Pila->carta)->palo);
            }else{
                if((Pila->carta)->valor == 11){
                    printf("J%c ",(Pila->carta)->palo);
                }
                if((Pila->carta)->valor == 12){
                    printf("Q%c ",(Pila->carta)->palo);
                }
                if((Pila->carta)->valor == 13){
                    printf("K%c ",(Pila->carta)->palo);
                }
            }
            Pila=Pila->siguiente;
	}
	printf("\n");
}

void pushLista(Lista* &lista){                            // Paso por referencia
    Lista* nuevo;                                  // nodo* nuevo=new nodo();
    nuevo=(struct Lista*)malloc(sizeof(struct Lista));
    printf("Nombre: ");
    scanf("%s",nuevo->nombre);

    nuevo->apuesta=100;
    nuevo->estado=0;       
    nuevo->siguiente=NULL;     

    if(lista==NULL){                                        // Si la lista esta vacia
        lista=nuevo;
        printf("Lista estaba vacia");              
        printf("Jugador %s anadido\n",nuevo->nombre);
    }else{                                                  // Si no esta vacia                                  
        Lista* sig=lista;                                     // Dos apuntadores auxiliares
        Lista* actual=lista;                                  // Uno a el elemento actual y otro al siguiente (mayor y menor)
        
        while((sig!=NULL)){                                    
            actual=sig;
            sig=sig->siguiente;
        }
                                                            
        if(actual==sig){                                    
            nuevo->siguiente=lista;                     
            lista=nuevo;    
        }else{
            actual->siguiente=nuevo;                        // En caso contrario va entre elementos y se inserta despues de actual y antes de siguiente
            nuevo->siguiente=sig;
        }
        printf("Jugador %s anadido\n",nuevo->nombre);
    }
}

void popLista(Lista* &lista,char nombre[50]){
    if(lista==NULL){
        printf("\nLista vacia");
    }else{
        Lista* sig=lista;                                     // Dos apuntadores auxiliares
        Lista* actual=lista;                                  // Uno a el elemento actual y otro al siguiente (mayor y menor)
        
        while((sig!=NULL)&&(lista->nombre!=nombre)){              // Busco en la lista la posicion en la que va nuevo (entre actual y sig)
            actual=sig;
            sig=sig->siguiente;
        }

        if(sig==NULL){                                              // Ultimo elemento y sin coincidencias
            printf("\nEste jugador %s no esta jugando\n",nombre);
        }

        if(actual==sig){                                            // El elemento a eliminar esta primero
            lista=sig->siguiente;
            printf("\nElemento %s eliminado\n",nombre);
        }else{                                                      // El elemento a eliminar es cualquiera de los otros
            actual->siguiente=sig->siguiente;
            printf("\nElemento %s eliminado\n",nombre);
        }
    }
}

void mostrarLista(Lista* lista, int flg){     
    if(flg==1){
        lista=lista->siguiente;
    }
    Lista* aux=lista;                                         // Apuntador auxiliar que comienza donde inicia la lista (No es necesario XD trabaja con lista)
    if(lista==NULL){
        printf("\nLista vacia\n");
    }else{
        while(aux->siguiente!=NULL){                        // Mientras aux->siguiente sea diferente de nulo va a imprimir el elemento
            printf("- %s\n",aux->nombre);
            aux=aux->siguiente;                             // Imprime y aux avanza al siguente
        }
        printf("- %s\n",aux->nombre);                            // Imprime el ultimo elemento de la lista
    }


}

int tamanoLista(Lista* lista){                                     // Paso por valor
    Lista* aux=lista;                                         // Apuntador auxiliar que comienza donde inicia la lista (No es necesario XD trabaja con lista)
    int pos=0;
    while(aux->siguiente!=NULL){                            // Mientras aux->siguiente sea diferente de nulo (Recorre toda la lista)
        aux=aux->siguiente;                                 // Aumenta el numero de elementos y pasa al siguiente
        pos++;
    }
    pos++;                                                  // Ultimo elemento
    
    return pos;
}

void pushCrupier(Lista* &lista){

   char banca[8]="Crupier";
   for(int i=0;i<7;i++){
       lista->nombre[i]=banca[i];
   }
   lista->apuesta=1000;
   lista->estado=0;                                          
   //printf("Jugador %s anadido\n",lista->nombre);

   Lista* aux=lista;
   lista=lista->siguiente;
   Lista* aux2=lista;
   while(aux2->siguiente!=NULL){
       aux2=aux2->siguiente;
   }
   aux->siguiente=NULL;
   aux2->siguiente=aux;
}