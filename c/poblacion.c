#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <libprobabilidad.h>


/*Previo para generar nÃºmero aleatorio de distribuciÃ³n normal (0,1) segÃºn definiciÃ³n de la librerÃ­a incluida ibprobabilidad*/

long long semilla_normal=SEMILLA;

double normal()
{
	int n;
	double f, s, g;

	s=0.0;
	for(n=0; n<NUNIFORMES; n++)
	{
		semilla_normal=(LINEAL_A*semilla_normal+LINEAL_B)
		               % CONGRUENCIA;
		f=(double)semilla_normal/CONGRUENCIA;
		s=s+f;
	}
	g=(s-0.5*NUNIFORMES)/sqrt((1.0/12)*NUNIFORMES);

	return g;
}


int main()

{
    int n,i,j,k; /*Variables para bucles*/
    double landa; /*Variable para el valor constante de lambda en cada uno de los casos a estudiar*/
    double xi, xant; /*xi es la variable que toma el valor de cada integraciÃ³n y xant la calculada en la integraciÃ³n anterior*/
    double ale; /*Se declara variable para el nÃºmero aleatorio que se emplea en cada cÃ±aculo de xi*/
    int simulaciones[15]; /*Se declara un vector de 15 dimensiones para almacenar las simulaciones en cada paso y utilizarlas en el cÃ¡lculo de la varianza*/
    double suma; /*Variable que acumula los valores de xi para calcular la media*/
    double media; /*Variable que recoge el cÃ¡lculo de la media aritmÃ©tica de las simulaciones de cada paso y se guarda en el fichero al efecto*/
    double desv; /*Variable que recoge el cÃ¡lculo de la varianza de las simulaciones de cada paso y se guarda en el fichero al efecto*/
    FILE *ficheromedia, *ficherovarianza; /*Se declaran las variables para rellenar los ficheros de medias y varianzas en los casos I, II y III recogidos en el enunciado*/


for (n=1; n<=3; n++){
		switch(n){
			/*CASO I: lambda=-1 y sigma=1*/
			case 1:{
				landa=-1;
				/*Apertura de ficheros donde guardar las medias y varianzas del caso I para escritura en binario. Nombrados terminados en 1 para el caso I*/
                ficheromedia = fopen ("ficheromedia1.dat", "wb");
                ficherovarianza = fopen ("ficherovarianza1.dat", "wb");
                break;
			}

            /*CASO II: lambda=3/4 y sigma=1*/
            	case 2:{
				landa=0.75;
				/*Apertura de ficheros donde guardar las medias y varianzas del caso II para escritura en binario. Nombrados terminados en 2 para el caso II*/
                ficheromedia = fopen ("ficheromedia2.dat", "wb");
                ficherovarianza = fopen ("ficherovarianza2.dat", "wb");
                break;
			}

            /*CASO III: lambda=2 y sigma=1*/
            	case 3:{
				landa=2;
				/*Apertura de ficheros donde guardar las medias y varianzas del caso III para escritura en binario. Nombrados terminados en 3 para el caso III*/
                ficheromedia = fopen ("ficheromedia3.dat", "wb");
                ficherovarianza = fopen ("ficherovarianza3.dat", "wb");
                break;
			}
		}

    /*Para pruebas, 10 pasos de 15 simulaciones cada uno. Definitivamente serÃ¡n 100 pasos de 100.000 simulaciones cada uno*/
    /*Calculamos 10 pasos de integraciÃ³n*/
    for (j=0; j<10; j++){

        /*CÃ¡lculo de medias para 14 simulaciones mÃ¡s la condicin inicial, ques x0=1*/
        /*xi es simulaciÃ³n y xant es simulaciÃ³n anterior*/
        /*Cada simulaciÃ³n utiliza un nÃºmero aleatorio de distribuciÃ³n normal*/
        /*Calculada la media de esa simulaciÃ³n, se guarda en la posiciÃ³n j del fichero*/
        /*TambiÃ©n guardamos cada simulaciÃ³n para calcular posteriormente la desviaciÃ³n estandar*/
        xant=1;
        suma=0;
        simulaciones[0]=1;
        for (i=1; i<15; i++){
            ale=normal();
            xi=xant+0.001*(landa*xant-xant*xant)+xant*ale*0.316227766;
            simulaciones[i]=xi;
            suma=suma+xi;

            printf("%i ale: %lf  xi: %lf xant %lf \n", i, ale, xi, xant);

            xant=xi;
        }

        media=(1+suma)/15;

            printf("Media  %lf   \n", media);

        /*Y se guarda esa media en el fichero de medias de cada uno de los casos marcados por el switch*/
        fprintf(ficheromedia, "%lf\n", media);

        /*CÃ¡lculo de la varianza para este paso*/
        for (k=0 ;k<15; k++){
            desv=desv+((simulaciones[k]-media)*(simulaciones[k]-media));
        }
        desv=(desv/15);

        /*Y se guarda esa varianza en el fichero de varianza del caso I*/
        fprintf(ficherovarianza, "%lf\n", desv);


    }

/*Se cierran las variables utilizadas en la confecciÃ³n de los ficheros de datos para confeccionar posteriormente las grÃ¡ficas*/
        fclose (ficheromedia);
        fclose (ficherovarianza);



    }

    return 0;
}
