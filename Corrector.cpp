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
void	Diccionario			(char *szNombre, char szPalabras[][TAMTOKEN], int iEstadisticas[], int &iNumElementos)

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
void	ListaCandidatas		(
	char	szPalabrasSugeridas[][TAMTOKEN],	//Lista de palabras clonadas
	int		iNumSugeridas,						//Lista de palabras clonadas
	char	szPalabras[][TAMTOKEN],				//Lista de palabras del diccionario
	int		iEstadisticas[],					//Lista de las frecuencias de las palabras
	int		iNumElementos,						//Numero de elementos en el diccionario
	char	szListaFinal[][TAMTOKEN],			//Lista final de palabras a sugerir
	int		iPeso[],							//Peso de las palabras en la lista final
	int &	iNumLista)							//Numero de elementos en la szListaFinal

/*****************************************************************************************************************
	ClonaPalabras: toma una palabra y obtiene todas las combinaciones y permutaciones requeridas por el metodo
	char *	szPalabraLeida,						// Palabra a clonar
	char	szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
	int &	iNumSugeridas)						//Numero de elementos en la lista
******************************************************************************************************************/
void	ClonaPalabras(
	char* szPalabraLeida,						// Palabra a clonar
	char	szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
	int& iNumSugeridas)	//Numero de elementos en la lista
{
	char copia[TAMTOKEN] = { 0 };
	char ALFABETO[] = "abcdefghijklmnñopqrstuvwxyzáéíóú";
	int lenPalabraLeida = strlen(szPalabraLeida);
	int lenAlfabeto = strlen(ALFABETO);
	iNumSugeridas = 0;
	//palabra original a la lista de sugerencias
	strcpy_s(szPalabrasSugeridas[iNumSugeridas], TAMTOKEN, szPalabraLeida);
	iNumSugeridas++;
	//sustitucion de caracteres
	for (int i = 0; i < lenPalabraLeida; i++) {
		for (int j = 0; j < lenAlfabeto; j++) {
			strncpy_s(copia, TAMTOKEN, szPalabraLeida, TAMTOKEN - 1);
			copia[i] = ALFABETO[j];
			if (iNumSugeridas < 3300) {
				strcpy_s(szPalabrasSugeridas[iNumSugeridas], TAMTOKEN, copia);
				//printf("Añadido: %s (iNumSugeridas: %d)\n", copia, iNumSugeridas + 1);
				iNumSugeridas++;
			}
		}
	}
	//se ponen los caracteres en los posibles espacios, pero solo si hay uno o mas caractres en la cadena original
	if (lenPalabraLeida >= 1) {
		for (int i = 0; i <= lenPalabraLeida; i++) {
			for (int j = 0; j < lenAlfabeto; j++) {
				strncpy_s(copia, TAMTOKEN, szPalabraLeida, i);
				copia[i] = ALFABETO[j];
				strncpy_s(copia + i + 1, TAMTOKEN - i - 1, szPalabraLeida + i, TAMTOKEN - i - 1);
				copia[lenPalabraLeida + 1] = '\0';
				if (iNumSugeridas < 3300) {
					strcpy_s(szPalabrasSugeridas[iNumSugeridas], TAMTOKEN, copia);
					//printf("Añadido: %s (iNumSugeridas: %d)\n", copia, iNumSugeridas + 1);
					iNumSugeridas++;
				}
			}
		}
	}
	//eliminacion de caracteres pero solo si hay mas de uno
	if (lenPalabraLeida > 1) {
		for (int i = 0; i < lenPalabraLeida; i++) {
			strncpy_s(copia, TAMTOKEN, szPalabraLeida, i);
			strncpy_s(copia + i, TAMTOKEN - i, szPalabraLeida + i + 1, TAMTOKEN - i - 1);
			copia[lenPalabraLeida] = '\0';
			if (iNumSugeridas < 3300) {
				strcpy_s(szPalabrasSugeridas[iNumSugeridas], TAMTOKEN, copia);
				//printf("Añadido: %s (iNumSugeridas: %d)\n", copia, iNumSugeridas + 1);
				iNumSugeridas++;
			}
		}
	}
	// intercambio de caracteres solo si hay mas de uno  
	for (int i = 0; i < lenPalabraLeida - 1; i++) {// i hasta len-1
		for (int j = i + 1; j < i + 2; j++) {  // Solo un intercambio entre i y i+1
			// Crear una copia de la palabra original
			strcpy_s(copia, TAMTOKEN, szPalabraLeida);
			char temp = copia[i];
			copia[i] = copia[i + 1];
			copia[i + 1] = temp;
			if (iNumSugeridas < 3300) {
				strcpy_s(szPalabrasSugeridas[iNumSugeridas], TAMTOKEN, copia);
				//printf("Añadido: %s (iNumSugeridas: %d)\n", copia, iNumSugeridas + 1);
				iNumSugeridas++;
			}
		}
	}
}

}
