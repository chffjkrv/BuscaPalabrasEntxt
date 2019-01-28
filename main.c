#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

int main( void )
{
	FILE *filepalclave;																							//Declaramos los archivos.
	FILE *filetxtcomp;
	FILE *results;
	
	char pathpalclav [1000] = "C:\\Users\\chffjkrv\\Documents\\ejerciciosC\\Textos\\palclave\\";					//Declaramos los path de directorios para brir los directorios y los ficheros.
	char pathfileclav1 [1000] = "C:\\Users\\chffjkrv\\Documents\\ejerciciosC\\Textos\\palclave\\";
	char pathtxtcmp [1000] = "C:\\Users\\chffjkrv\\Documents\\ejerciciosC\\Textos\\textcomp\\";
	char pathtxtcmp1 [1000] = "C:\\Users\\chffjkrv\\Documents\\ejerciciosC\\Textos\\textcomp\\";
	char pathresult [1000] = "C:\\Users\\chffjkrv\\Documents\\ejerciciosC\\Textos\\result\\result.txt";
	char palabrasclvarr[5][15];
	char palabrasclv[50];
	char palabrascmp[100];
	char nomtxtclv[50];
	char nomtxtcmp[50];
	float cont;
	int acumnumpalcmp;
	float acum = 0.00;	
	float porcentotal;
	int longitud;
	int rescomp;

	DIR* dirresult;
	struct dirent* direntr;
		
    DIR* dirpalclav;																							//Declaramos los directorios.
    struct dirent* direntp;

	DIR* dirtxtcomp;
	struct dirent* direntp1;
	
	struct palclv{																								//Declaramos la estructura para las palclv.
		char char_Nombre[15];
		char char_NombreFichero[15];
		int int_largoPalabra; 
		int int_vecesrepetida;
		float float_porcentaje;		
		char char_palanterior[50];
		char char_palsiguiente[50];
	};
	struct palclv structpalclv[100];
	
	struct ficherocmp{
		int int_largofichero;															//Crear estructura para los ficheros .cmp		
	};
	
	dirtxtcomp = opendir(pathtxtcmp);																			//Abrimos los 2 directorios.
    dirpalclav = opendir(pathpalclav);
    dirresult = opendir(pathresult);
        
    results = fopen (pathresult, "w");
    
    if(dirpalclav == NULL && dirtxtcomp == NULL && dirresult == NULL) {
        perror( "can't open" );
    } 
		else {
        
			for(;;) {
        	
				int len;
            	direntp = readdir(dirpalclav);																	
            		
					if( direntp == NULL ) break;
            		    				
					char clv[4]=".clv";
    																											//Buscamos el archivo del Palclav.
					len = strspn(clv, direntp->d_name);
						
						if (len==4){
							strcpy(nomtxtclv, direntp->d_name);
							strcat(pathfileclav1,nomtxtclv);
							filepalclave = fopen(pathfileclav1, "r");													//Abrimos el archivo .clv
							
							while (filepalclave && !feof(filepalclave)){
								
								if (filepalclave == NULL){printf("Archivo no encontrado");}
									
									else {
									
									int f;
										for (f=0;f<=5;f++){											
											fscanf(filepalclave,"%s", palabrasclv);				
											strcpy(palabrasclvarr[f],palabrasclv);						//Pasamos sus valores a un array bidimensional.
											strcpy(structpalclv[f].char_Nombre, palabrasclv);			//Añadimos valor a char_Nombre de la estructura palabra.
											strcpy(structpalclv[f].char_NombreFichero, nomtxtclv);		//Añadimos valor a char_NombreFichero de la estructura palabra.
											structpalclv[f].int_largoPalabra=strlen(palabrasclv);		//Añadimos valor a int_largoPalabra de la estructura palabra.
										}			
        							}
    						}
    					fclose(filepalclave);
    					}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////						 					
    				if ( (strcmp(direntp->d_name, ".")!=0) && (strcmp(direntp->d_name, "..")!=0) ) {
            			printf( "El archivo esta listo.");
        			}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////        			
        		}										
    	}
		
		closedir(dirpalclav);

			for (;;){
			
				direntp1 = readdir(dirtxtcomp);		
					
					if (direntp1==NULL) break;
					
				char cmp[4]=".cmp";
				
				if (strspn(cmp,direntp1->d_name)==4){
					
					strcpy(nomtxtcmp,direntp1->d_name);	
					strcpy(pathtxtcmp1,pathtxtcmp);							//Aqui dejamos el path limpio a cada vuelta.
					strcat(pathtxtcmp1,nomtxtcmp);						
					filetxtcomp = fopen(pathtxtcmp1, "r");	
					
					cont=0;
						while(filetxtcomp && !feof(filetxtcomp)){
							
							if(filetxtcomp==NULL){
								printf("Archivo .cmp no encontrado.");
							}
							
								else{
										fscanf(filetxtcomp, "%s", palabrascmp);
										cont ++;
										int f2;
										for(f2=0;f2<=5;f2++){
	
											if (strncmp(palabrascmp,palabrasclvarr[f2],structpalclv[f2].int_largoPalabra)==0){
												structpalclv[f2].int_vecesrepetida+=1;
												
											}
										}	
								}
						}	
								porcentotal=0;
								fprintf(results, "\n\n\n\t\t\t--------\\||El texto %s tiene %.0f palabras||//--------", nomtxtcmp, cont);
								int f3;									//Aqui imprimimos en result la struct de las palabras.
								for (f3=0;f3<=5;f3++){
									fprintf(results, "\nPalabra %s", structpalclv[f3].char_Nombre);
									fprintf(results, "\nNombre Fichero %s", structpalclv[f3].char_NombreFichero);
									fprintf(results, "\nTamanio palabra %d", structpalclv[f3].int_largoPalabra);
									fprintf(results, "\n%d Veces repetida\n", structpalclv[f3].int_vecesrepetida);
									
									if(structpalclv[f3].int_vecesrepetida!=0){
										fprintf(results,"\t\t\t\t<<<<<<<<<<--------------||\n\n");
										structpalclv[f3].float_porcentaje = structpalclv[f3].int_vecesrepetida*100/cont;
										fprintf(results, "El porcentaje de esta palabra sobre el texto es del %.0f%%\n", structpalclv[f3].float_porcentaje );
										porcentotal= structpalclv[f3].float_porcentaje+porcentotal;
									}
								}	
								fprintf(results,"\n***El porcentaje de coincidencia total del texto es del %.0f%%***", porcentotal); 
			/*
			Hay que ver si haciendo una estructura con el fichero se podría guardar ahi el porcentaje
			total de palabras por texto.
			*/
				int fx;
				for(fx=0;fx<=5;fx++){
					structpalclv[fx].int_vecesrepetida=0;
				}						//AQUI PONEMOS A 0 LOS CONTADORES DE VECES REPETIDAS DE LAS STRUCTS.									
			}
			}
			
        fclose(results);
        closedir(dirtxtcomp);

    return 0;
}
