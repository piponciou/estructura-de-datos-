#include <stdio.h>


struct Evaluacion {
    int id;
    char *fecha;
    int nota;
};
struct Alumno {
    char *rut;
    char *nombre;
    struct Evaluacion **evaluaciones;
    int tam;
};

struct NodoAlumno {
    struct Alumno *datoAlumno;
    struct NodoAlumno *sig;
};
struct Curso {
    int sigla;
    struct NodoAlumno *head;
};


/* 1)CALCULAR PROMEDIO FINAL DE TODAS LAS EVALUACIONES DE UN ALUMNO (SI HAY UN NULL SERA IGUAL A 1) --OK
 * 2)VER SI EL ALUMNO APRUEBA --OK
 * 3)CONTAR CANTIDAD DE ALUMNOS APROBADOS Y RETORNAR --OK
 */



/*RECORRO ARREGLO EVALUACIONES EL CUAL ES NO COMPACTO, Y SI ENCUENTRO UN VALOR NULL LO CUENTO COMO UN 1*/
float calcularPromedio(struct Evaluacion **evaluaciones,int tam)
{
    float suma = 0;
    int i;

    for (i=0; i<tam; i++)
    {
        if (evaluaciones[i] == NULL)
            suma+=1;
        else
            suma+=(float)(evaluaciones[i]->nota);
    }
    if (tam > 0)
        return (suma/tam);
    return 0;
}


int aprueba(float promedioAlumno, float umbral)
{
    if (promedioAlumno >= umbral)
        return 1;
    return 0;
}

int calcularCantidadAprobados(struct Curso *curso, float umbral)
{
    struct NodoAlumno *rec = curso->head;
    int contador = 0;
    float promedioAlumno;

    while (rec != NULL)
    {
        promedioAlumno = calcularPromedio(rec->datoAlumno->evaluaciones,rec->datoAlumno->tam);
        if (aprueba(promedioAlumno,umbral) == 1)
            contador++;

        rec = rec->sig;
    }

    return contador;
}
