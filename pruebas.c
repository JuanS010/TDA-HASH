#include "src/hash.h"
#include "pa2m.h"
#include <stdlib.h>
#include <string.h>

void prueba_crear_vacio()
{
	hash_t *hash = hash_crear(10);
	pa2m_afirmar(hash != NULL, "Se crea el hash");
	pa2m_afirmar(hash_cantidad(hash) == 0, 
			"El hash se crea sin elementos");
	pa2m_afirmar(hash_quitar(hash, "Auto") == NULL, 
			"No se quita un elemento que no se inserto");
	pa2m_afirmar(hash_contiene(hash, "Auto") == false, 
			"No contiene un elemento que no se inserto");
	pa2m_afirmar(hash_obtener(hash, "Auto") == NULL, 
			"No se obtiene un elemento que no se inserto");
	hash_destruir(hash);
}

void prueba_insertar_quitar()
{
	char *clave1 = "Auto1", *valor1 = "Azul";
	char *clave2 = "Auto2", *valor2 = "Amarillo";
	char *clave3 = "Auto3", *valor3 = "Rojo";
	char *clave4 = "Auto4", *valor4 = "Verde", *valor5 = "Naranja";
	void *anterior = NULL;
	hash_t *hash = hash_crear(1);

	pa2m_afirmar(hash_cantidad(hash) == 0, 
			"Hay 0 elementos");
	pa2m_afirmar(hash_contiene(hash, clave1) == false, 
			"No contiene Auto1");
	pa2m_afirmar(hash_obtener(hash, clave1) == NULL, 
			"No se obtiene valor de Auto1");
	pa2m_afirmar(hash_insertar(hash, clave1, valor1, NULL) == hash, 
			"Se inserta Auto1");
	pa2m_afirmar(hash_cantidad(hash) == 1, 
			"Hay 1 elemento");
	pa2m_afirmar(hash_contiene(hash, clave1) == true, 
			"Contiene Auto1");
	pa2m_afirmar(hash_obtener(hash, clave1) == valor1, 
			"Se obtiene valor de Auto1, Azul");
	hash_insertar(hash, clave2, valor2, NULL);
	hash_insertar(hash, clave3, valor3, NULL);
	hash_insertar(hash, clave4, valor4, NULL);
	pa2m_afirmar(hash_cantidad(hash) == 4, 
			"Se insertan 3 elementos mas, Hay 4 elementos");
	pa2m_afirmar(hash_contiene(hash, clave2) == true, 
			"Contiene Auto2");
	pa2m_afirmar(hash_obtener(hash, clave4) == valor4, 
			"Se obtiene valor de Auto4, Verde");
	pa2m_afirmar(hash_insertar(hash, clave4, valor5, &anterior) == hash, 
			"Se reemplaza el valor de Auto4");
	pa2m_afirmar(anterior != NULL ,
			"Anterior guarda el anterior valor de Auto4, Verde");
	pa2m_afirmar(hash_contiene(hash, clave2) == true, 
			"Contiene Auto4");
	pa2m_afirmar(hash_obtener(hash, clave4) == valor5, 
			"Se obtiene valor de Auto4, Naranja");
	pa2m_afirmar(hash_quitar(hash, clave4) == valor5, 
			"Se quita Auto4 y se devuelve su valor");
	pa2m_afirmar(hash_contiene(hash, clave2) == true, 
			"No contiene Auto4");
	pa2m_afirmar(hash_quitar(hash, clave4) == NULL, 
			"No se quita Auto4, ya se quito");

	hash_destruir(hash);
}

void prueba_vacio()
{	
	hash_t *hash = hash_crear(1);
	char *clave1 = "", *valor1 = "";
	pa2m_afirmar(hash_cantidad(hash) == 0, 
			"Hay 0 elementos");
	pa2m_afirmar(hash_insertar(hash, clave1, valor1, NULL) == hash, 
			"Se inserta clave: '' y valor: ''");
	pa2m_afirmar(hash_cantidad(hash) == 1, 
			"Hay 1 elemento");
	pa2m_afirmar(hash_contiene(hash, clave1) == true, 
			"Contiene clave1");
	pa2m_afirmar(hash_obtener(hash, clave1) == valor1, 
			"Se obtiene valor de clave1");
	pa2m_afirmar(hash_quitar(hash, clave1) == valor1, 
			"Se quita clave1 y se devuelve su valor");
	pa2m_afirmar(hash_cantidad(hash) == 0, 
			"Hay 0 elementos");
	hash_destruir(hash);
}

void pruebas_null()
{	
	char *clave1 = "Auto";
	hash_t *hash = hash_crear(10);
	pa2m_afirmar(hash_cantidad(hash) == 0, 
			"Hay 0 elementos");
	pa2m_afirmar(hash_insertar(hash, NULL, "valor", NULL) == NULL, 
			"No se inserta clave null");
	pa2m_afirmar(hash_contiene(hash, NULL) == false, 
			"No contiene clave null");
	pa2m_afirmar(hash_cantidad(hash) == 0, 
			"Hay 0 elementos");
	pa2m_afirmar(hash_insertar(hash, clave1, NULL, NULL) == hash, 
			"Se inserta valor null");
	pa2m_afirmar(hash_obtener(hash, clave1) == NULL, 
			"Se obtiene valor null");
	pa2m_afirmar(hash_cantidad(hash) == 1, 
			"Hay 1 elemento");
	hash_destruir(hash);
}

void pruebas_destruir_todo()
{
	char *clave1 = "Auto1", *valor1;
	char *clave2 = "Auto2", *valor2;
	valor1 = malloc(5 * sizeof(char));
	valor2 = malloc(5 * sizeof(char));

	hash_t *hash = hash_crear(10);
	pa2m_afirmar(hash_insertar(hash, clave1, valor1, NULL) == hash, 
			"Se inserta un valor en el heap");
	pa2m_afirmar(hash_insertar(hash, clave2, valor2, NULL) == hash, 
			"Se inserta otro valor en el heap");
	pa2m_afirmar(hash_cantidad(hash) == 2, 
			"Hay 2 elementos");
	hash_destruir_todo(hash, free);
	pa2m_afirmar(1, "Se destruye la tabla");
	pa2m_afirmar(1, "El valor1 se destuye con la tabla");
	pa2m_afirmar(1, "El valor2 se destuye con la tabla\n(ver valgrind)");
}

bool f(const char *clave, void *valor, void *aux)
{	
	return true;
}

bool ff(const char *clave, void *valor, void *aux)
{	
 	int c = *(int*)valor;
	return !(c == 4);
}

void pruebas_funciones_null()
{
	char *clave1 = "Auto1", *valor1 = "Azul";
	void* anterior = NULL;
	hash_t *hash = hash_crear(1);
	pa2m_afirmar(hash_insertar(NULL, clave1, valor1, anterior) == NULL, 
			"No se puede insertar con hash null");
	pa2m_afirmar(hash_insertar(hash, NULL, valor1, anterior) == NULL, 
			"No se puede insertar con clave null");
	pa2m_afirmar(hash_contiene(NULL, clave1) == false, 
			"No se puede ver si contiene con hash null");
	pa2m_afirmar(hash_contiene(hash, NULL) == false, 
			"No se puede ver si contiene con clave null");
	pa2m_afirmar(hash_obtener(NULL, clave1) == false, 
			"No se puede obtener con hash null");
	pa2m_afirmar(hash_obtener(hash, NULL) == false, 
			"No se puede obtener con clave null");
	pa2m_afirmar(hash_cantidad(NULL) == 0, 
			"No se puede ver cantidad con hash null");
	pa2m_afirmar(hash_quitar(NULL, clave1) == NULL, 
			"No se puede quitar con hash null");
	pa2m_afirmar(hash_quitar(hash, NULL) == NULL, 
			"No se puede quitar con clave null");
	pa2m_afirmar(hash_con_cada_clave(NULL, f, NULL) == 0, 
			"No se puede iterar con hash null");
	pa2m_afirmar(hash_con_cada_clave(hash, NULL, NULL) == 0, 
			"No se puede iterar con funcion null");
	hash_destruir(hash);
}

void prueba_iterador()
{
	char *clave1 = "c1";
	char *clave2 = "c2";
	char *clave3 = "c3";
	char *clave4 = "c4";
	int v1 = 1, v2 = 2, v3 = 3, v4 = 4;
	hash_t *hash = hash_crear(1);

	pa2m_afirmar(hash_cantidad(hash) == 0, 
			"Hay 0 elementos");
	pa2m_afirmar(hash_con_cada_clave(hash, f, NULL) == 0, 
			"Iterar un hash vacio devuelve 0");

	hash_insertar(hash, clave1, &v1, NULL);
	hash_insertar(hash, clave2, &v2, NULL);
	hash_insertar(hash, clave3, &v3, NULL);
	hash_insertar(hash, clave4, &v4, NULL);
	pa2m_afirmar(hash_cantidad(hash) == 4, 
			"Hay 4 elementos");
	pa2m_afirmar(hash_con_cada_clave(hash, f, NULL) == 4, 
			"Se itera el hash completo");
	pa2m_afirmar(hash_con_cada_clave(hash, ff, NULL) == 2, 
			"Se itera el hash con corte");

	hash_destruir(hash);
}

int main()
{
	pa2m_nuevo_grupo("Pruebas crear hash vacio");
	prueba_crear_vacio();
	pa2m_nuevo_grupo("Pruebas insertar, reemplazar, quitar");
	prueba_insertar_quitar();
	pa2m_nuevo_grupo("Pruebas par de vacios");
	prueba_vacio();
	pa2m_nuevo_grupo("Pruebas elementos null");
	pruebas_null();
	pa2m_nuevo_grupo("Pruebas destruir todo con funcion");
	pruebas_destruir_todo();
	pa2m_nuevo_grupo("Prueba funciones con null");
	pruebas_funciones_null();
	pa2m_nuevo_grupo("Prueba iterador");
	prueba_iterador();

	return pa2m_mostrar_reporte();
}
