// LIBRERIAS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <ctype.h>
#include <errno.h>

typedef struct competidores {
    int orden;
    int corredor;
    int dia;
    char mes[4];
    int anio;
    int edad;
    char pais[4];
    float tiempo;
} competidores;

typedef struct competidoresBin {
    int orden;
    int corredor;
    int dia;
    char mes[4];
    int anio;
    int edad;
    char pais[4];
    float tiempo;
    int activo;
} competidoresBin;

// LIBRERIAS PROPIAS
#include "headers/menus.h"
#include "headers/validations.h"
#include "headers/auxfiles.h"
#include "headers/files.h"

int main() {

    FILE* registroCompetidores;
    FILE* nuevosCompetidores;
    FILE* deletedCompetidores;

    while(1) {
        switch(validMenu(1, 0, 12)) { // validations.h
            case 1: showLog(registroCompetidores); break; // files.h
            case 2: createBin(); break; // files.h
            case 3: migrateLog(registroCompetidores, nuevosCompetidores); break; // files.h
            case 4: showData(nuevosCompetidores); break; // files.h
            case 5: logElement(nuevosCompetidores); break; // files.h
            case 6: searchElement(nuevosCompetidores); break; // files.h
            case 7: modElement(nuevosCompetidores); break; // files.h
            case 8: unlogElement(nuevosCompetidores); break; // files.h
            case 9: deleteInactiveElements(nuevosCompetidores, deletedCompetidores); break; // files.h
            case 10: showDeletedElements(nuevosCompetidores, deletedCompetidores); break; // files.h
            case 11: return 0;
        }
    }

    fflush(registroCompetidores);
    fflush(nuevosCompetidores);

    getchar();
    return 0;
}