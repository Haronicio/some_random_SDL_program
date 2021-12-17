#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define TEMPS 0
/*typedef struct {
					float x;
					float y;
				}point;*/


int main(int argc, char *argv[])
{
	int Hauteur = 500;
	int b,g;
	int Largeur = 2048;
	int A;
	int n = 0;
	float U = 0;
	float V = 0;
	int y = Hauteur/2;
	int i;
	
	
			

				if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
				{
					printf("Erreur dans l'initialisation de SDL %s\n",SDL_GetError());
					return -1;
				}
				
				SDL_Window * window;
				SDL_Renderer * renderer;
				
				
				printf("Donnez la longueur -> A\n");
				scanf("%d",&A);
				
				

				window = SDL_CreateWindow("terraingen 1.0",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,Largeur,Hauteur, 0);
				if (window == NULL)
				{
					printf("Erreur lors de la creation de la fenetre %s\n",SDL_GetError());
					return -1;
				}
				renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED );
				if (renderer == NULL)
				{
					printf("erreur\n");
					return -1;
				}
				// SDL_SetRenderDrawColor(renderer,255,255,255,255);
				
				while(1)
				{
					
					SDL_SetRenderDrawColor(renderer,255,255-g,255-b,255);
					U = (A / pow(2,n)) ;
					
					printf("A %d U %f n %d \n",A,U,n );

					while(V < A)
					{

						SDL_Delay(TEMPS);
						V = V + U;
						

						SDL_RenderDrawPoint(renderer, V , y);	
						y =rand()%3 - 1 + y;
						printf(" point cree en x %f y %d \n",V,y);
							
						
					}
					SDL_RenderPresent(renderer);
					y = Hauteur/2;
					V = 0;
					n++;
					b=b+10;
					g=g+10;
				}

				


				
				
				
				
				
				







	SDL_Delay(10000);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
