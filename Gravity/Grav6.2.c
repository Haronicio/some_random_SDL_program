#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 2
#define TEMPS 35
typedef struct  {
	          float x ;
		 	  float y ;
		 	  double masse ;
		 	  double force ;
		 	  double accelerationX ;
		 	  double accelerationY ;
		 	  double vitesseX;
		 	  double vitesseY;
		      }objet;
//typedef struct objet objet;
int G = 1;

	

int main(int argc, char *argv[])
{
float massetotale(objet a[N]);





objet t[N];
int taille_obj = 2;
t[0].x = 1100;
t[0].y = 500;
t[1].x = 1500.0;
t[1].y = 1080/2.0;

t[0].masse = 10e5;
t[1].masse = 50;

int Largeur = 1920;
int Hauteur = 1080;
t[0].force = 0;
t[1].force = 0;

t[0].accelerationX = 0;
t[0].accelerationY = 0;
t[1].accelerationX = 0;
t[1].accelerationY = 0;

t[0].vitesseX = 0;
t[0].vitesseY = 0;
t[1].vitesseX = 0;
t[1].vitesseY = 30.0;





int temps = 0;



if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
{
		printf("Erreur dans l'initialisation de SDL %s\n",SDL_GetError());
        return -1;
}
//printf("%e\n",t[0].force );

SDL_Window * window;
SDL_Renderer * renderer;
SDL_Surface * fond = NULL;
SDL_Texture * texture_fond = NULL;
SDL_Surface * obj = NULL;
SDL_Texture * texture_obj = NULL;

window = SDL_CreateWindow("Gravity",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,Largeur,Hauteur, 0);
if (window == NULL)
{
	        printf("Erreur lors de la creation de la fenetre %s\n",SDL_GetError());
	        return -1;
}
renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED );
fond = IMG_Load("./src/Sky.png");
texture_fond = SDL_CreateTextureFromSurface(renderer, fond);
SDL_FreeSurface(fond);

obj = IMG_Load("./src/Cercle.png");
texture_obj = SDL_CreateTextureFromSurface(renderer, obj);
SDL_FreeSurface(obj);



	
int i;
int j;

while (1){
	SDL_Delay(TEMPS);
	
	for ( i = 0; i < N; ++i)
	{
				
		
		


		for ( j = 0; j < N; ++j)
		{
			float distanceX = 0, distanceY = 0 ,distanceTOTALE = 0;
			//printf("i = %d j = %d \n",i , j );

			if (i != j )
			{


				distanceX = t[j].x - t[i].x  ;
				distanceY =t[j].y - t[i].y  ;	

				distanceTOTALE = sqrt((distanceX * distanceX) + (distanceY * distanceY));



				t[i].force = ( G * massetotale(t) ) / ( distanceTOTALE * distanceTOTALE); //massetotal = masse de tout les obets 
				// printf("masse total %f\n",massetotale(t));
				


				t[i].accelerationX = (1/t[i].masse) * t[i].force;
				t[i].accelerationY = (1/t[i].masse) * t[i].force;


				t[i].vitesseX  += t[i].accelerationX *(distanceX/distanceTOTALE);
				t[i].vitesseY  += t[i].accelerationY  * (distanceY/distanceTOTALE);

				t[i].x += t[i].vitesseX;
				t[i].y += t[i].vitesseY;

				//printf("objet no 1 vx %f \n",t[1].vitesseX );
				//printf("objet no %d acc X =%f acc Y =%f\n",i,t[i].accelerationX,t[i].accelerationY );
				
				SDL_Rect position_obj = {t[i].x,t[i].y,taille_obj,taille_obj};
				if ( SDL_RenderCopy(renderer , texture_obj , NULL , &position_obj) <0 )
				{
					printf(" lol :%s\n",SDL_GetError() );
				}	
				
				SDL_RenderPresent(renderer);
				// SDL_RenderClear(renderer);
		    }
		}		
	}
}







SDL_Delay(10000);
SDL_DestroyTexture(texture_obj);
SDL_DestroyTexture(texture_fond);
SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(window);
SDL_Quit();


return 0 ;
}

float massetotale(objet a[N])
{
	float m = 1;
	int i;
	for ( i = 0; i < N; ++i)
	{
		
		m *= a[i].masse;
	}
		

	//printf("m = %f\n", m);
	return m;

}
/* --------------------------------------------------------------------------------
			 ||||||	 ||     ||       ||||		 ||||||  	|||	   ||  ||		|||||     ||||||
			||		 ||     ||     ||    ||		||	   		|| ||  ||  ||	  ||     ||  ||
		   	||		 | | ||| |    | |||||| |	||	  ||| 	||  || ||  ||     ||     ||	 ||    |||
		   	 ||||||	 ||     ||   ||        || 	 ||||||   	||    |||  ||||||	|||||	  ||||||	



		   	 INTEGRATION DE VERLET   <--- plus ou moins je crois je vais revoir ??a mais en gros c'est un algo pour plus de pr??cision mais je doute qu'il soit bien a 1er vue peut ??tre

-----------------------------------------------------------------------------------*/