#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define TEMPS 0
typedef struct  {
	          float x ;
		 	  float y ;
		 	  double masse ;
		 	  double force ;
		 	  double acceleration ;
		 	  double vitesseX;
		 	  double vitesseY;
		      }objet;
//typedef struct objet objet;
int G = 1;
int N = 2;
	

int main(int argc, char *argv[])
{
printf("octet struct : %d\n",sizeof(objet) );
int taille_struct = sizeof(objet);
// float massetotale(objet a[N]);
// objet nouveauxobj(int x,int y ,double masse ,double force , double accelerationX ,double accelerationY ,double vitesseX,double vitesseY);
objet * t;
t = malloc(N * taille_struct);
if (t == NULL)
{
	printf("erreur\n");
	return -1;
}
// objet t[N];
int appui = 0;
int x;
int y;
int xprim ;
int yprim ;
int taille_obj = 2;
int Largeur = 1280;
int Hauteur = 1024;
t[0].x = 500;
t[0].y = 500;
t[0].masse = 1000;
t[0].force = 0;
t[0].acceleration = 0;
t[0].vitesseX = 0;
t[0].vitesseY = 0;
t[1].x = 200;
t[1].y = 700;
t[1].masse = 0.1;
t[1].force = 0;
t[1].acceleration = 0;
t[1].vitesseX = 0.4;
t[1].vitesseY = 0.7;





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
SDL_Event evenement;

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
	//printf(" FATAL ERROR : %s\n",SDL_GetError() );
	while(SDL_PollEvent(&evenement))
	{
		if (evenement.window.event == SDL_WINDOWEVENT_CLOSE)
		{
			SDL_Quit();
		}
		if (evenement.type == SDL_MOUSEBUTTONUP)
		{
			switch (appui)
			{
				case 0 :  SDL_GetMouseState(&xprim,&yprim) ; appui = 1;printf("%d %d \n",xprim,yprim ) ; break ;
				case 1 : SDL_GetRelativeMouseState(&x,&y);N++;realloc(t, N * sizeof(objet)); appui = 0 ;printf("%d %d \n",x,y );
				t[N-1].x = xprim;
				t[N-1].y = yprim;
				t[N-1].masse = 0.1;
				t[N-1].vitesseX = 0;
				t[N-1].vitesseY = 0;
				t[N-1].force = 0;
				t[N-1].acceleration = 0;
	
	;printf("N %d x %f y %f masse %f force %f acc x %f acc y %f v x %f v y %f \n",N-1,t[N-1].x,t[N-1].y,t[N-1].masse,t[N-1].force,t[N-1].acceleration,t[N-1].acceleration,t[N-1].vitesseX,t[N-1].vitesseY ); break ;
			}
			
		}
	
	}
	//printf("%d\n",t[N].x,t[N].y );
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



				t[i].force = ( G * t[i].masse * t[j].masse/*massetotale(t)*/ ) / ( distanceTOTALE * distanceTOTALE); //massetotal = masse de tout les obets 
				
				


				t[i].acceleration = (1/t[i].masse) * t[i].force;


				t[i].vitesseX  += t[i].acceleration * (distanceX/distanceTOTALE);
				t[i].vitesseY  += t[i].acceleration  * (distanceY/distanceTOTALE);

				t[i].x += t[i].vitesseX;
				t[i].y += t[i].vitesseY;

				// printf("objet no %d vx %f \n",i,t[i].vitesseX );
				// printf("objet no %d acc X =%f \n",i,t[i].acceleration );
				// printf("no %d, x %f, y %f \n",i,t[i].vitesseX,t[i].vitesseY );
				
				SDL_Rect position_obj = {t[i].x,t[i].y,taille_obj,taille_obj};
				if ( SDL_RenderCopy(renderer , texture_obj , NULL , &position_obj) <0 )
				{
					printf(" lol0 :%s\n",SDL_GetError() );
				}	
				
				SDL_RenderPresent(renderer);
				// SDL_RenderClear(renderer);
		    }
		}		
	}
}






free(t);
SDL_Delay(10000);
SDL_DestroyTexture(texture_obj);
SDL_DestroyTexture(texture_fond);
SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(window);
SDL_Quit();


return 0 ;
}

/*float massetotale(objet a[N])
{
	float m = 1;
	int i;
	for ( i = 0; i < N; ++i)
	{
		
		m *= a[i].masse;
	}
		

	printf("m = %f\n", m);
	return m;

}*/
/*objet nouveauxobj(int x,int y ,double masse ,double force , double accelerationX ,double accelerationY ,double vitesseX,double vitesseY)
{
	objet a;
	a.x = x;
	a.y = y;
	a.masse = masse;
	a.force = force;
	a.accelerationX = accelerationX /80;
	a.accelerationY = accelerationY /80;
	a.vitesseX = vitesseX;
	a.vitesseY = vitesseY;
	printf("%f %f\n",a.x,a.y );
	return a;
}*/
/* --------------------------------------------------------------------------------
			 ||||||	 ||     ||       ||||		 ||||||  	|||	   ||  ||		|||||     ||||||
			||		 ||     ||     ||    ||		||	   		|| ||  ||  ||	  ||     ||  ||
		   	||		 | | ||| |    | |||||| |	||	  ||| 	||  || ||  ||     ||     ||	 ||    |||
		   	 ||||||	 ||     ||   ||        || 	 ||||||   	||    |||  ||||||	|||||	  ||||||	



		   	 

-----------------------------------------------------------------------------------*/
// t[N-1] = nouveauxobj(xprim,yprim,0.1,0,x,y,0,0)