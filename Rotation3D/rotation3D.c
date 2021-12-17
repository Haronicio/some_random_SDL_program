#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(int argc, char *argv[])
{
	void quadri(float x[17],float y[17],float z[17],float d, float xp ,float yp,SDL_Renderer * renderer);
	
	int Hauteur = 600;
	double pi = 3.14159265358979323846264338327950288419716939937510;
	int Largeur = 800;
	int Ox = Largeur/2;
	int Oy = Hauteur/2;							   //10
	float x[17]={-50,50, 50,-50,-50,-50, 50, 50,-50,-50,-50,50, 50, 50, 50,-50,-50};
	float y[17]={ 50,50,-50,-50, 50, 50, 50,-50,-50, 50, 50,50, 50,-50,-50,-50,-50};
	float z[17]={ 50,50, 50, 50, 50,-50,-50,-50,-50,-50, 50,50,-50,-50, 50, 50,-50};

	float angle =0.1;
	float xp =0;
	float yp = 0;
	float zp = 0;
	float d = -256;
	int i;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("Erreur dans l'initialisation de SDL %s\n",SDL_GetError());
		return -1;
	}
				
	SDL_Window * window;
	SDL_Renderer * renderer;
				
	window = SDL_CreateWindow("rotation",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,Largeur,Hauteur, 0);
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
	SDL_SetRenderDrawColor(renderer,255,255,255,255);


	// perspective(x,y,z,d);
	
	while (1) 
	{	
		
		quadri(x,y,z,d,xp,yp,renderer);
		for (i = 0; i <= 16; ++i)
		{
			
			//rotation axe Z
			xp = x[i]* cos(0/57.2958) - y[i] * sin(0/57.2958);
			y[i] = y[i]* cos(0/57.2958) + x[i] * sin(0/57.2958);
			x[i]=xp;
			printf("%f %f\n",x[i],y[i] );
		
		

			//rotation axe X
			zp = z[i]* cos(angle/57.2958) - y[i] * sin(angle/57.2958);
			y[i] = y[i]* cos(angle/57.2958) + z[i] * sin(angle/57.2958);
			z[i]=zp;
			printf("%f %f\n",z[i],y[i] );
		


			//rotation axe Y
			xp = x[i]* cos(0/57.2958) - z[i] * sin(0/57.2958);
			z[i] = z[i]* cos(0/57.2958) + x[i] * sin(0/57.2958);
			x[i]=xp;
			printf("%f %f\n",x[i],z[i] );

		}

		SDL_Delay(0);
		SDL_SetRenderDrawColor(renderer,0,0,0,255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer,255,255,255,255);
		
		
	}

	

	






	SDL_Delay(0);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
void quadri(float x[17],float y[17],float z[17], float d,float xp,float yp,SDL_Renderer * renderer)
{
	float xs;
	float ys;
	int i;
	for (i = 0; i < 16; ++i)
	{
		xp=(d*x[i])/(d+z[i]);
		yp=(d*y[i])/(d+z[i]);
		xs=(d*x[i+1])/(d+z[i+1]);
		ys=(d*y[i+1])/(d+z[i+1]);

		SDL_RenderDrawLine(renderer,xp+400,yp+300,xs+400,ys+300);
		printf("%f %f\n",x[i],y[i] );
		
	}	
	SDL_RenderPresent(renderer);
}

