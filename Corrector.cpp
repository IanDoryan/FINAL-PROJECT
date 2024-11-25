/*****************************************************************************************************************
	UNIVERSIDAD NACIONAL AUTONOMA DE MEXICO
	FACULTAD DE ESTUDIOS SUPERIORES -ARAGON-

	Computadoras y programacion. 
	(c) Ponga su nombre y numero de cuenta aqui.
	
	Quiso decir: Programa principal de la aplicacion de la distancia de Levenstein.
	
******************************************************************************************************************/


#include "stdafx.h"
#include <string.h>
#include "corrector.h"
//Funciones publicas del proyecto
/*****************************************************************************************************************
	DICCIONARIO: Esta funcion crea el diccionario completo
	char *	szNombre				:	Nombre del archivo de donde se sacaran las palabras del diccionario	
	char	szPalabras[][TAMTOKEN]	:	Arreglo con las palabras completas del diccionario
	int		iEstadisticas[]			:	Arreglo con el numero de veces que aparecen las palabras en el diccionario
	int &	iNumElementos			:	Numero de elementos en el diccionario
******************************************************************************************************************/
void	Diccionario(char* szNombre, char szPalabras[][TAMTOKEN], int iEstadisticas[], int& iNumElementos)
{
    FILE* fp;
    char buffer[500];
    char palabra[TAMTOKEN];
    int conta, contaPalabra;
    iNumElementos = 0;
    if (fopen_s(&fp, szNombre, "r") != 0) {
        printf("No se pudo abrir el archivo: %s\n", szNombre);
        return;
    }
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        conta = 0;
        contaPalabra = 0;
        while (buffer[conta] != '\0') {
            //esto sirve para terminar una linea  si encuentra alguno termina la palabra
            if (buffer[conta] == ' ' || buffer[conta] == ',' || buffer[conta] == '.' || buffer[conta] == '(' || buffer[conta] == ')' || buffer[conta] == ';' || buffer[conta] == '\n') {
                palabra[contaPalabra] = '\0';
                //convierto las letras en minusculas
                for (int i = 0; i < contaPalabra; i++) {
                    if (palabra[i] >= 'A' && palabra[i] <= 'Z') {
                        palabra[i] += 32;
                    }
                }
                //si la palabra esta en el arreglo solo aumenta las estadisticas
                if (contaPalabra > 0) {
                    int found = 0;
                    for (int i = 0; i < iNumElementos; i++) {
                        if (strcmp(szPalabras[i], palabra) == 0) {
                            iEstadisticas[i]++;
                            found = 1;
                            break;
                        }
                    }
                    //si la palabra no esta la copia a e incrementa las estadisticas 1 pq hay 1 palabra
                    if (!found && iNumElementos < NUMPALABRAS) {
                        strcpy_s(szPalabras[iNumElementos], TAMTOKEN, palabra);
                        iEstadisticas[iNumElementos] = 1;
                        (iNumElementos)++;
                    }
                }
                contaPalabra = 0;
            }
            else
            {
                //si en la linea no encuentra alguno de estos entonces toma todos los caractres y los va copiando

                    // acumula carácter en la palabra
                if (contaPalabra < TAMTOKEN - 1) {
                    palabra[contaPalabra++] = buffer[conta];
                }

            }
            conta++;
        }
        //pasar la ultima palabra
        if (contaPalabra > 0) {
            palabra[contaPalabra] = '\0';

            //pasarla a minuscul
            for (int i = 0; i < contaPalabra; i++) {
                if (palabra[i] >= 'A' && palabra[i] <= 'Z') {
                    palabra[i] += 32;
                }
            }

            //procesarla
            int found = 0;
            for (int i = 0; i < iNumElementos; i++) {
                if (strcmp(szPalabras[i], palabra) == 0) {
                    iEstadisticas[i]++;
                    found = 1;
                    break;
                }
            }
            if (!found && iNumElementos < NUMPALABRAS) {
                strcpy_s(szPalabras[iNumElementos], TAMTOKEN, palabra);
                iEstadisticas[iNumElementos] = 1;
                iNumElementos++;
            }
        }


    }

    fclose(fp);
    //esta funcion ordena las palabras alfabeticamente :v
    for (int i = 0; i < iNumElementos - 1; i++) {
        for (int j = 0; j < iNumElementos - i - 1; j++) {
            if (strcmp(szPalabras[j], szPalabras[j + 1]) > 0) {
                char tempPalabra[TAMTOKEN];
                strcpy_s(tempPalabra, TAMTOKEN, szPalabras[j]);
                strcpy_s(szPalabras[j], TAMTOKEN, szPalabras[j + 1]);
                strcpy_s(szPalabras[j + 1], TAMTOKEN, tempPalabra);

                int tempEstadistica = iEstadisticas[j];
                iEstadisticas[j] = iEstadisticas[j + 1];
                iEstadisticas[j + 1] = tempEstadistica;
            }
        }
    }
}
/*****************************************************************************************************************
	ListaCandidatas: Esta funcion recupera desde el diccionario las palabras validas y su peso
	Regresa las palabras ordenadas por su peso
	char	szPalabrasSugeridas[][TAMTOKEN],	//Lista de palabras clonadas
	int		iNumSugeridas,						//Lista de palabras clonadas
	char	szPalabras[][TAMTOKEN],				//Lista de palabras del diccionario
	int		iEstadisticas[],					//Lista de las frecuencias de las palabras
	int		iNumElementos,						//Numero de elementos en el diccionario
	char	szListaFinal[][TAMTOKEN],			//Lista final de palabras a sugerir
	int		iPeso[],							//Peso de las palabras en la lista final
	int &	iNumLista)							//Numero de elementos en la szListaFinal
******************************************************************************************************************/
void	ListaCandidatas(
    char	szPalabrasSugeridas[][TAMTOKEN],	//Lista de palabras clonadas
    int		iNumSugeridas,						//Lista de palabras clonadas
    char	szPalabras[][TAMTOKEN],				//Lista de palabras del diccionario
    int		iEstadisticas[],					//Lista de las frecuencias de las palabras
    int		iNumElementos,						//Numero de elementos en el diccionario
    char	szListaFinal[][TAMTOKEN],			//Lista final de palabras a sugerir
    int		iPeso[],							//Peso de las palabras en la lista final
    int& iNumLista)
{
    iNumLista = 0;
    for (int i = 0; i < iNumSugeridas; i++) {
        for (int j = 0; j < iNumElementos; j++) {
            if (strcmp(szPalabrasSugeridas[i], szPalabras[j]) == 0) {
                strcpy_s(szListaFinal[iNumLista], TAMTOKEN, szPalabras[j]);
                iPeso[iNumLista] = iEstadisticas[j];
                (iNumLista)++;
            }

        }
    }
    for (int i = 0; i < iNumLista - 1; i++) {
        for (int j = i + 1; j < iNumLista; j++) {
            if (iPeso[i] < iPeso[j]) {
                int tempPeso = iPeso[i];
                iPeso[i] = iPeso[j];
                iPeso[j] = tempPeso;

                char tempPalabra[TAMTOKEN];
                strcpy_s(tempPalabra, szListaFinal[i]);
                strcpy_s(szListaFinal[i], TAMTOKEN, szListaFinal[j]);
                strcpy_s(szListaFinal[j], TAMTOKEN, tempPalabra);
            }
        }
    }
}

/*****************************************************************************************************************
	ClonaPalabras: toma una palabra y obtiene todas las combinaciones y permutaciones requeridas por el metodo
	char *	szPalabraLeida,						// Palabra a clonar
	char	szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
	int &	iNumSugeridas)						//Numero de elementos en la lista
******************************************************************************************************************/
void	ClonaPalabras(
	char *	szPalabraLeida,						// Palabra a clonar
	char	szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
	int &	iNumSugeridas)						//Numero de elementos en la lista
