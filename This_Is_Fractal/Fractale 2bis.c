#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
	int Largeur = 1920;
	int Hauteur = 1080;
	int iter = 100;
	int signe =0;
	float x,y,xi,yi,xp,yp; // x+iy
	int i=0;

	float zoom = 1000;
	//(1200/7)
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("Erreur dans l'initialisation de SDL %s\n",SDL_GetError());
		return -1;
	}
				
	SDL_Window * window;
	SDL_Renderer * renderer;
				
	window = SDL_CreateWindow("fracttest",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,Largeur,Hauteur, 0);
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
	SDL_SetRenderDrawColor(renderer,255,0,0,255);
	SDL_RenderDrawLine(renderer,Largeur/2,0,Largeur/2,Hauteur);
	SDL_RenderDrawLine(renderer,0,Hauteur/2,Largeur,Hauteur/2);
	SDL_SetRenderDrawColor(renderer,255,255,255,255);


	//x1 y0.2 c -0.39 -0.59i
	x = 0;
	y= 0;
	xp = -0.8;//-0.8 0.2
	yp = 0.2;
	for (i = 0; i < 100000; ++i)
	{
		//si x > 2 et y >2 c augmente ou x > x * zoom + Largeur/2 y > y * zoom + Hauteur/2 (si x ou y est supérieur au bornes d'affichage)
		//couleur temp de divergence = nombre d'interation avant retour a 0
		//l'incrémentation de c dépend du zoom
		//incrémenter et décrementer (décrémenter si la valeur absolue est plus grande que la moitié des cotés)
		//j'usqua que 1 iitération soit valable pour blauqer la boucle
		//il se peut que l'on tombe sur qqch de extremement bien borné du coup ca fait une boucle ,c'est pourquoi il faux une itermax pour dire combien de fois avant le passage a l'autre
		if (x * zoom + Largeur/2 < 0 || x * zoom + Largeur/2 > Largeur || y * zoom + Hauteur/2 < 0 || y * zoom + Hauteur/2 > Hauteur || i > iter )
		{
			if (xp > 1)
			{
				int signe = -1;
			}
			if (signe != -1)
			{
				xp += 1 / zoom;
				yp += 1 / zoom;
			}
			else
			{
				xp -= 1 / zoom;
				yp -= 1 / zoom;
				printf("inverse\n");
			}
			printf("ok\n");
			x = 0;
			y = 0;
			i =0;
			// zoom += 0.1;
		}
		
		SDL_RenderDrawPoint(renderer,x * zoom + Largeur/2,y * zoom + Hauteur/2);//x + Largeur/(zoom*2)) *zoom
		// printf(" point cree en x %f y %f zoom %f \n",(x + Largeur/(zoom*2)) *zoom,(y +Hauteur/(zoom*2))*zoom,zoom );
		printf("x %f y %f xp %f yp %f\n",x,y,xp,yp);
		SDL_RenderPresent(renderer);
		SDL_Delay(1);
		xi = pow(x,2) - pow(y,2) + xp;
		yi = 2*x*y + yp;
		x = xi;
		y = yi;
		i++;
		
		
	}


	SDL_Delay(10000);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

