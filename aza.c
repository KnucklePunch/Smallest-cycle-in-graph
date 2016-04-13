// uloha-1.cpp -- Uloha 1
// Patrik Scensny, 5.4.2016 14:10:26
/*
 *  Úlohou je pre daný neorientovaný neohodnotený graf bez slučiek a násobných hrán zistiť dĺžku najkratšej kružnice, ktorú tento graf obsahuje. (Tento invariant sa nazýva obvod grafu.)

Kružnica v grafe je postupnosť vrcholov v0, v1, ..., vk taká, že medzi vrcholmi vi a vi+1 je hrana pre každé i z množiny {0, 1, ..., k} (vk+1 = v0); jej dĺžka je počet jej vrcholov. Ak graf žiadnu kružnicu neobsahuje, na výstup treba vypísať -1.

Váš program by mal čítať dáta zo štandardného vstupu a písať výsledky na štandardný výstup.

Program by mal skončiť do 5 sekúnd aj pre grafy s desiatkami tisíc hrán.
Formát vstupu

Na vstupe je v prvom riadku nezáporné celé číslo k udávajúce počet grafov na vstupe. Nasleduje k grafov; pred každým grafom je jeden prázdny riadok. Graf začína riadkom, v ktorom je počet jeho vrcholov, a potom nasleduje pre každý vrchol jeden riadok: prvé číslo v riadku je počet susedov daného vrchola a za ním nasledujú čísla týchto susedov; čísla v riadku sú oddelené medzerami. Vrcholy grafu sú číslované celými číslami od 1 nahor.

Príklad vstupu:

4

5
0
0
0
1 5
1 4

3
2 2 3
2 1 3
2 1 2

4
2 2 4
2 1 3
2 2 4
2 1 3

8
3 2 7 8
2 1 3
2 2 4
2 3 5
2 4 6
3 5 7 8
2 1 6
2 1 6

 * 
-1
3
4
4
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct vertices{  
  int depth;  
  int index;
  int numNeigh;  
  struct vertices *parent;
  struct vertices **neigh;  
}Vertices;

void verticesFree(Vertices **vertices, int num){
    int i;
    for(i=0;i<num;i++){
        free(vertices[i]);
    }
}

void resetValue(Vertices **vertices, int num){
    int i;
    for(i=0;i<num;i++){
        vertices[i]->depth=0;
        vertices[i]->parent=NULL;        
    }
}

int cycles(Vertices **vertices, int numOfVertices){
    int k=numOfVertices,i;
    int upperIndex, loverIndex, flag;
    Vertices **queue,*vertice,*neighbour;
    short *nextRoot;
    nextRoot =(short*)malloc(sizeof(short)*numOfVertices);
    for(i=0;i<numOfVertices;i++){
      nextRoot[i]=0;
    }
    int smallestCycle=-1;
    
    while(k){
        printf("Zacinam cyklus s nenavstivenymi %d\n",k);
        if(smallestCycle == 3){break;}
        queue=(Vertices**)malloc(sizeof(Vertices*)*numOfVertices);//toto moze robit problem
        for(i=0;i<numOfVertices;i++){
            if(nextRoot[i] == 0){
                queue[0]=vertices[i];
                upperIndex=0;
                loverIndex=1;
                vertices[i]->depth=0;
                vertices[i]->parent=NULL; 
                break;
            }
        }
        flag=1;
        while(flag){
            if(upperIndex == loverIndex){break;}
            vertice=queue[upperIndex];
            upperIndex++;            
            if(!nextRoot[vertice->index]){
                k--;
                nextRoot[vertice->index]++;
            }

            printf("Spracovavam bod s cislom %d a %d susedmi v hlbke %d \n",vertice->index+1,vertice->numNeigh,vertice->depth);
            
            for(i=0;i<vertice->numNeigh;i++){
                neighbour=vertice->neigh[i];
                printf("Sused je bod s indexom %d, ",neighbour->index+1);
                if(neighbour == vertice->parent){printf("je to rodic\n");continue;}
                printf("ma hlbku %d, ",vertice->depth+1);
                if(neighbour->depth != 0){                    
                    if(smallestCycle > (neighbour->depth+vertice->depth+1) || smallestCycle == -1){smallestCycle=neighbour->depth+vertice->depth+1;printf("nasli sme mensi kruh dlzky %d\n",smallestCycle);flag--;break;}
                    flag--;break;
                }
                printf("v tomto vrchole sme este neboli, v tomto prehladavani\n");
                neighbour->depth=vertice->depth+1;
                neighbour->parent=vertice;
                queue[loverIndex]=neighbour;
                loverIndex++;                
            }
        }
        free(queue);
        resetValue(vertices,numOfVertices);
    }
    return smallestCycle;
}


int main()
{
  int numGraph,numVert,numNeigh,neigh,i,j;
  Vertices **vertices;
  
  scanf("%d",&numGraph);
  for(;numGraph>0;numGraph--){
    
    scanf("%d",&numVert);    
    vertices=(Vertices**)malloc(sizeof(Vertices*)*numVert);
    for(i=0;i<numVert;i++){vertices[i]=(Vertices*)malloc(sizeof(Vertices));}
    for(i=0;i<numVert;i++){      
      scanf("%d",&numNeigh);            
      vertices[i]->depth=0;  
      vertices[i]->index=i;
      vertices[i]->numNeigh=numNeigh;
      vertices[i]->parent=NULL;
      vertices[i]->neigh=(Vertices**)malloc(sizeof(Vertices*)*numNeigh);      
      for(j=0;j<numNeigh;j++){
          scanf("%d",&neigh);
          vertices[i]->neigh[j]=vertices[neigh-1];
      }           
    }
    
    printf("%d\n",cycles(vertices,numVert));  
    verticesFree(vertices,numVert);
    vertices=NULL;
  }
  
  return 0;
}
