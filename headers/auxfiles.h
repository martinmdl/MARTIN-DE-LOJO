#ifndef AUXFILES_H
#define AUXFILES_H

void showAllData(FILE* nuevosCompetidores) {
    // Lista en pantalla todos los datos almacenados en el archivo binario

    errno = 0;
    competidoresBin datos;
    
    nuevosCompetidores = fopen("files/competidores.dat", "rb");
    if(nuevosCompetidores == NULL) {
        printf("ERROR: %s", strerror(errno));
        printf("\n\nPresione cualquier tecla para continuar...");
    }

    printf("ORDEN\tCORREDOR\tDIA\tMES\tA%cO\tEDAD\tPAIS\tTIEMPO\t\tACTIVO\n\n", 165);
    fread(&datos, sizeof(competidoresBin), 1, nuevosCompetidores);
    while(!feof(nuevosCompetidores)) {
        printf("%d\t%d\t\t%d\t%s\t%d\t%d\t%s\t%f\t%d\n",
            datos.orden,
            datos.corredor,
            datos.dia,
            datos.mes,
            datos.anio,
            datos.edad,
            datos.pais,
            datos.tiempo,
            datos.activo
        );
        fread(&datos, sizeof(competidoresBin), 1, nuevosCompetidores);
    }

    fclose(nuevosCompetidores);
    printf("\nPresione cualquier tecla para continuar...");
    getchar();
    system("cls");
}

void showDataByState(FILE* nuevosCompetidores) {
    // Lista en pantalla los datos de los corredores activos que se encuentran en el archivo binario

    errno = 0;
    competidoresBin datos;
    int flag = 0;
    
    nuevosCompetidores = fopen("files/competidores.dat", "rb");
    if(nuevosCompetidores == NULL) {
        printf("ERROR: %s", strerror(errno));
        printf("\n\nPresione cualquier tecla para continuar...");
    }

    fread(&datos, sizeof(competidoresBin), 1, nuevosCompetidores);
    printf("ORDEN\tCORREDOR\tDIA\tMES\tA%cO\tEDAD\tPAIS\tTIEMPO\t\tACTIVO\n\n", 165);
    while(!feof(nuevosCompetidores)) {
        if(datos.activo == 1) {
            printf("%d\t%d\t\t%d\t%s\t%d\t%d\t%s\t%f\t%d\n",
                datos.orden,
                datos.corredor,
                datos.dia,
                datos.mes,
                datos.anio,
                datos.edad,
                datos.pais,
                datos.tiempo,
                datos.activo
            );
            flag = 1;
        }
        fread(&datos, sizeof(competidoresBin), 1, nuevosCompetidores);
    }
    if(flag == 0) {
        printf("No hay competidores activos");
    }

    fclose(nuevosCompetidores);
    printf("\nPresione cualquier tecla para continuar...");
    getchar();
    system("cls");
}

void showDataByCountry(FILE* nuevosCompetidores) {
    // Lista en pantalla todos los datos de los competidores del país ingresado por el usuario

    errno = 0;
    competidoresBin datos;
    int flag = 0, i;
    char pais[4], aux[20];

    nuevosCompetidores = fopen("files/competidores.dat", "rb");
    if(nuevosCompetidores == NULL) {
        printf("ERROR: %s", strerror(errno));
        printf("\n\nPresione cualquier tecla para continuar...");
    }

    // VALIDAR
    pais[0] = ' ';
    pais[1] = ' ';
    pais[2] = ' ';
    pais[3] = '\0';
    printf("Ingrese un pa%cs: ", 161);
    while(1) {
        gets(aux);
        fflush(stdin);
        if(strlen(aux) > 2) {
            for(i = 0; i < strlen(pais) && pais[i] != '\0'; i++) {
                pais[i] = toupper(aux[i]);
            }
            break;
        }
        printf("\tIngrese un pa%cs v%clido: ", 161, 160);
    }
    system("cls");

    int valid = fread(&datos, sizeof(competidoresBin), 1, nuevosCompetidores); // DECIDIR SI AGREGAR A LAS DEMAS FUNCIONES
    printf("ORDEN\tCORREDOR\tDIA\tMES\tA%cO\tEDAD\tPAIS\tTIEMPO\t\tACTIVO\n\n", 165);
    while(!feof(nuevosCompetidores)) {
        if(valid == 1) {
            if(strcmp(datos.pais, pais) == 0) {
                printf("%d\t%d\t\t%d\t%s\t%d\t%d\t%s\t%f\t%d\n", 
                    datos.orden,
                    datos.corredor,
                    datos.dia,
                    datos.mes,
                    datos.anio,
                    datos.edad,
                    datos.pais,
                    datos.tiempo,
                    datos.activo
                );
                flag = 1;
            }
        } else {
            system("cls");
            printf("HUBO UN ERROR EN LA LECTURA", 161);
            getchar();
            break;
        }
        fread(&datos, sizeof(competidoresBin), 1, nuevosCompetidores);
    }
    if(flag == 0) {
        printf("\nNo hay competidores de %s", pais);
    }

    fclose(nuevosCompetidores);
    printf("\nPresione cualquier tecla para continuar...");
    getchar();
    system("cls");
}

void showDataByTime(FILE* nuevosCompetidores) {
    // Pide al usuario un rango de tiempo y lista en pantalla todos los corredores que lo satisfagan

    errno = 0;
    competidoresBin datos;
    int flag = 0;
    float min, max;
    char chars;

    nuevosCompetidores = fopen("files/competidores.dat", "rb");
    if(nuevosCompetidores == NULL) {
        printf("ERROR: %s", strerror(errno));
        printf("\n\nPresione cualquier tecla para continuar...");
    }

    // VALIDAR
    printf("Tiempo m%cnimo: ", 161);
    while(1) {
        scanf("%d%c", &min, &chars);
        fflush(stdin);
        if(chars == '\n' && min > 0) {break;}
        printf("\tIngrese un n%cmero positivo: ", 163);
    }

    printf("\nTiempo m%cximo: ", 160);
    while(1) {
        scanf("%d%c", &max, &chars);
        fflush(stdin);
        if(chars == '\n' && max > 0) {break;}
        printf("\tIngrese un n%cmero positivo: ", 163);
    }
    system("cls");
    
    fread(&datos, sizeof(competidoresBin), 1, nuevosCompetidores); // DECIDIR SI AGREGAR A LAS DEMAS FUNCIONES
    printf("ORDEN\tCORREDOR\tDIA\tMES\tA%cO\tEDAD\tPAIS\tTIEMPO\t\tACTIVO\n\n", 165);
    while(!feof(nuevosCompetidores)) {
        if(datos.tiempo >= min && datos.tiempo <= max) {
            printf("%d\t%d\t\t%d\t%s\t%d\t%d\t%s\t%f\t%d\n",
                datos.orden,
                datos.corredor,
                datos.dia,
                datos.mes,
                datos.anio,
                datos.edad,
                datos.pais,
                datos.tiempo,
                datos.activo
            );
            flag = 1;
        }
        fread(&datos, sizeof(competidoresBin), 1, nuevosCompetidores);
    }
    if(flag == 0) {
        printf("\nNo hay competidores en ese rango de tiempo", 161);
    }

    fclose(nuevosCompetidores);
    printf("\nPresione cualquier tecla para continuar...");
    getchar();
    system("cls");
}

void exeLog(FILE* nuevosCompetidores, competidoresBin news) {
    // Coloca todos los datos ingresados por el usuario y validados previamente en la línea correspondiente.
    // Ademas, llena con ceros todas las líneas intermedias hasta llegar a la correspondiente.

    errno = 0;
    competidoresBin last, ceros;
    int i, maxID = 0, lastID, diff;

    // TEMPLATE CEROS
    ceros.orden = 0;
    ceros.corredor = 0;
    ceros.dia = 0;
    ceros.mes[0] = 'N';
    ceros.mes[1] = '/';
    ceros.mes[2] = 'A';
    ceros.mes[3] = '\0';
    ceros.anio = 0;
    ceros.edad = 0;
    ceros.pais[0] = 'N';
    ceros.pais[1] = '/';
    ceros.pais[2] = 'A';
    ceros.pais[3] = '\0';
    ceros.tiempo = 0;
    ceros.activo = 0;

    nuevosCompetidores = fopen("files/competidores.dat", "r+b");
    if(nuevosCompetidores == NULL) {
        printf("ERROR: %s", strerror(errno));
        printf("\n\nPresione cualquier tecla para continuar...");
    }

    // GUARDA ULTIMO ID
    fseek(nuevosCompetidores, 0, SEEK_END);
    int cantIds = ftell(nuevosCompetidores) / sizeof(competidoresBin); // OBTENGO LA CANTIDAD DE REGISTROS

    diff = news.orden - cantIds; // CANTIDAD DE LINEAS A RELLENAR CON CEROS

    if(diff > 0) { // SI ES VERDAD, RELLENO CON CEROS HASTA "news.orden"
        fseek(nuevosCompetidores, 0, SEEK_END);
        for(i = 0; i < diff-1; i++) {
            fwrite(&ceros, sizeof(competidoresBin), 1, nuevosCompetidores); // RELLENO CON CEROS (struct ceros)
        }
    }

    // GUARDA EL ALTA
    fseek(nuevosCompetidores, ((news.orden-1)*sizeof(competidoresBin)), SEEK_SET); // POSICIONO EL PUNTERO EN LA LINEA QUE EL USUARIO SOLICITO
    fwrite(&news, sizeof(competidoresBin), 1, nuevosCompetidores); // ESCRIBO ESA LINEA CON TODA LA INFORMACION GUARDADA (struct news)

    fclose(nuevosCompetidores);
}

void searchByID(FILE* nuevosCompetidores, int* searched, int flag) {
    // Busca un competidor por número de orden y lo muestra en pantalla.
    // Siempre va a mostrar un único corredor.
    // Además, con la flag en 1, permite modificar el valor de "*searched" haciendo uso de punteros.
    // Pudiendo así "retornar" el número de orden a otras funciones.

    errno = 0;
    competidoresBin datos;
    int id;
    char chars;

    nuevosCompetidores = fopen("files/competidores.dat", "rb");
    if(nuevosCompetidores == NULL) {
        printf("ERROR: %s", strerror(errno));
        printf("\n\nPresione cualquier tecla para continuar...");
    }

    // VALIDACION ORDEN
    printf("N%cmero de orden: ", 163);
    while(1) {
        scanf("%d%c", &id, &chars);
        fflush(stdin);
        if(chars == '\n' && id > 0) {break;}
        printf("\tIngrese un n%cmero positivo: ", 163);
    }
    if(fseek(nuevosCompetidores, ((id-1)*sizeof(competidoresBin)), SEEK_SET) != 0) {
        system("cls");
        fclose(nuevosCompetidores);
        printf("No se encontr%c ning%cn corredor con ese n%cmero de orden.\n", 162, 163, 163);
        printf("\nPresione cualquier tecla para continuar...");
        getchar();
        system("cls");
        return;
    }

    fread(&datos, sizeof(competidoresBin), 1, nuevosCompetidores);

    if(datos.orden == id) {

        if(flag == 1 || flag == 2) { // MOSTRAR PARA MODIFICAR O DAR DE BAJA (RETORNA "*searched = orden")
            system("cls");
            if(flag == 1) {printf("Est%c seguro que desea modificar los datos de:\n\n", 160);} // MODIFICAR
            if(flag == 2) {printf("Est%c seguro que desea dar de baja a:\n\n", 160);} // DAR DE BAJA
            printf("ORDEN\tCORREDOR\tDIA\tMES\tA%cO\tEDAD\tPAIS\tTIEMPO\t\tACTIVO\n", 165);
            printf("%d\t%d\t\t%d\t%s\t%d\t%d\t%s\t%f\t%d\n\n",
                datos.orden,
                datos.corredor,
                datos.dia,
                datos.mes,
                datos.anio,
                datos.edad,
                datos.pais,
                datos.tiempo,
                datos.activo
            );
            *searched = datos.orden;
            fclose(nuevosCompetidores);
            return;
        }

        system("cls");
        printf("ORDEN\tCORREDOR\tDIA\tMES\tA%cO\tEDAD\tPAIS\tTIEMPO\t\tACTIVO\n\n", 165);
        printf("%d\t%d\t\t%d\t%s\t%d\t%d\t%s\t%f\t%d\n",
            datos.orden,
            datos.corredor,
            datos.dia,
            datos.mes,
            datos.anio,
            datos.edad,
            datos.pais,
            datos.tiempo,
            datos.activo
        );

    } else {
        system("cls");
        printf("No se encontr%c ning%cn corredor con ese n%cmero de orden.\n", 162, 163, 163);
    }

    fclose(nuevosCompetidores);        
    printf("\nPresione cualquier tecla para continuar...");
    getchar();
    system("cls");
}

void searchByNum(FILE* nuevosCompetidores, int* searched, int flag) {
    // Busca competidores por número de corredor y los muestra en pantalla.
    // Va a mostrar todos los corredores que tengan el número buscado.
    // Además, con la flag en 1, permite modificar el valor de "*searched" haciendo uso de punteros.
    // Pudiendo así "retornar" el número de orden a otras funciones.
    // ("*searched" solo retorna un número de orden y va a ser el primero que aparezca)

    errno = 0;
    competidoresBin datos;
    int num, err = 1, repetido = 0;
    char chars;

    nuevosCompetidores = fopen("files/competidores.dat", "rb");
    if(nuevosCompetidores == NULL) {
        printf("ERROR: %s", strerror(errno));
        printf("\n\nPresione cualquier tecla para continuar...");
    }

    // VALIDACION CORREDOR
    printf("N%cmero de corredor: ", 163);
    while(1) {
        scanf("%d%c", &num, &chars);
        fflush(stdin);
        if(chars == '\n' && num > 0) {break;}
        printf("\tIngrese un n%cmero positivo: ", 163);
    }

    fseek(nuevosCompetidores, 0, SEEK_SET);
    fread(&datos, sizeof(competidoresBin), 1, nuevosCompetidores);
    while(!feof(nuevosCompetidores)) {
        if(datos.corredor == num) {
            if(flag == 1) {
                system("cls");
                printf("Est%c seguro que desea modificar los datos de:\n\n", 160);
                printf("ORDEN\tCORREDOR\tDIA\tMES\tA%cO\tEDAD\tPAIS\tTIEMPO\t\tACTIVO\n", 165);
                printf("%d\t%d\t\t%d\t%s\t%d\t%d\t%s\t%f\t%d\n\n",
                    datos.orden,
                    datos.corredor,
                    datos.dia,
                    datos.mes,
                    datos.anio,
                    datos.edad,
                    datos.pais,
                    datos.tiempo,
                    datos.activo
                );
                *searched = datos.orden;
                fclose(nuevosCompetidores);
                return;
            }
            if(repetido == 0) {
                system("cls");
                printf("ORDEN\tCORREDOR\tDIA\tMES\tA%cO\tEDAD\tPAIS\tTIEMPO\t\tACTIVO\n\n", 165);
            }
            printf("%d\t%d\t\t%d\t%s\t%d\t%d\t%s\t%f\t%d\n",
                datos.orden,
                datos.corredor,
                datos.dia,
                datos.mes,
                datos.anio,
                datos.edad,
                datos.pais,
                datos.tiempo,
                datos.activo
            );
            repetido++;
            err = 0;
        }
        fread(&datos, sizeof(competidoresBin), 1, nuevosCompetidores);
    }

    if(err != 0) {
        system("cls");
        printf("No se encontr%c ning%cn corredor con ese n%cmero.\n", 162, 163, 163);
    }
    fclose(nuevosCompetidores);        
    printf("\nPresione cualquier tecla para continuar...");
    getchar();
    system("cls");
}

void modifyAge(int searchMode, FILE* nuevosCompetidores) {
    // searchMode = 1 (BUSCAR POR NUMERO DE ORDEN)
    // searchMode = 2 (BUSCAR POR NUMERO DE CORREDOR)
    // Modifica la edad de un competidor permitiendo buscarlo por número de corredor o por número de orden
    // "searchMode" es pedido al usuario en files.h 

    errno = 0;
    int orden = 0;
    competidoresBin mod;
    char chars;

    switch (searchMode) {
        case 1: searchByID(nuevosCompetidores, &orden, 1); break;
        case 2: searchByNum(nuevosCompetidores, &orden, 1); break;
    }
    
    if(orden != 0) {
        if(validBin(0) == 's') { // validations.h
            nuevosCompetidores = fopen("files/competidores.dat", "r+b");
            if(nuevosCompetidores == NULL) {
                printf("ERROR: %s", strerror(errno));
                printf("\n\nPresione cualquier tecla para continuar...");
            }
            fseek(nuevosCompetidores, ((orden-1)*sizeof(competidoresBin)), SEEK_SET);
            fread(&mod, sizeof(competidoresBin), 1, nuevosCompetidores);
            printf("Ingrese edad: ");
            while(1) {
                scanf("%d%c", &mod.edad, &chars);
                fflush(stdin);
                if(chars == '\n' && mod.edad > 0 && mod.edad < 110) {break;}
                printf("\tIngrese una edad v%clida: ", 160);
            }
            fseek(nuevosCompetidores, ((orden-1)*sizeof(competidoresBin)), SEEK_SET);
            fwrite(&mod, sizeof(competidoresBin), 1, nuevosCompetidores);
            system("cls");
            fclose(nuevosCompetidores);
            printf("EDAD MODIFICADA CON %cXITO\n", 144);
            printf("\nPresione cualquier tecla para continuar...");
            getchar();
            system("cls");
        } else {
            printf("VOLVIENDO AL MEN%c PRINCIPAL\n", 233);
            printf("\nPresione cualquier tecla para continuar...");
            getchar();
            system("cls");
        }
    }
}

void modifyTime(int searchMode, FILE* nuevosCompetidores) {
    // searchMode = 1 (BUSCAR POR NUMERO DE ORDEN)
    // searchMode = 2 (BUSCAR POR NUMERO DE CORREDOR)
    // Modifica el tiempo de un competidor permitiendo buscarlo por número de corredor o por número de orden
    // "searchMode" es pedido al usuario en files.h

    errno = 0;
    int orden = 0;
    competidoresBin mod;
    char chars;

    switch (searchMode) {
        case 1: searchByID(nuevosCompetidores, &orden, 1); break;
        case 2: searchByNum(nuevosCompetidores, &orden, 1); break;
    }

    if(validBin(0) == 's') { // validations.h
        nuevosCompetidores = fopen("files/competidores.dat", "r+b");
        if(nuevosCompetidores == NULL) {
            printf("ERROR: %s", strerror(errno));
            printf("\n\nPresione cualquier tecla para continuar...");
        }
        fseek(nuevosCompetidores, ((orden-1)*sizeof(competidoresBin)), SEEK_SET);
        fread(&mod, sizeof(competidoresBin), 1, nuevosCompetidores);
        printf("Ingrese tiempo: ");
        while(1) {
            scanf("%f%c", &mod.tiempo, &chars);
            fflush(stdin);
            if(chars == '\n' && mod.tiempo >= 0) {break;}
            printf("\tIngrese un n%cmero positivo: ", 163);
        } 
        fseek(nuevosCompetidores, ((orden-1)*sizeof(competidoresBin)), SEEK_SET);
        fwrite(&mod, sizeof(competidoresBin), 1, nuevosCompetidores);
        system("cls");
        fclose(nuevosCompetidores);
        printf("TIEMPO MODIFICADO CON %cXITO\n", 144);
        printf("\nPresione cualquier tecla para continuar...");
        getchar();
        system("cls");
    } else {
        printf("VOLVIENDO AL MEN%c PRINCIPAL\n", 233);
        printf("\nPresione cualquier tecla para continuar...");
        getchar();
        system("cls");
    }
}

void writeCeros(FILE* nuevosCompetidores, int orden) {
    // Escribe en el archivo binario una linea de ceros en la posición correspondiente a "orden"
    // Esta función fue creada para evitar perder la ubicación del puntero de stream en "deletedInactiveElementes()" (EJERCICIO 10)
    // Para evitar perderlo, es necesario usar "fseek()", pero esta función dentro de un "while", generaba errores
    // Por eso la única tarea realizada en este código es la de escribir ceros.

    competidoresBin ceros;

    ceros.orden = 0;
    ceros.corredor = 0;
    ceros.dia = 0;
    ceros.mes[0] = 'N';
    ceros.mes[1] = '/';
    ceros.mes[2] = 'A';
    ceros.mes[3] = '\0';
    ceros.anio = 0;
    ceros.edad = 0;
    ceros.pais[0] = 'N';
    ceros.pais[1] = '/';
    ceros.pais[2] = 'A';
    ceros.pais[3] = '\0';
    ceros.tiempo = 0;
    ceros.activo = 0;

    nuevosCompetidores = fopen("files/competidores.dat", "r+b");
    if(nuevosCompetidores == NULL) {
        printf("competidores.dat\n");
        printf("ERROR: %s", strerror(errno));
        printf("\n\nPresione cualquier tecla para continuar...");
    }

    fseek(nuevosCompetidores, (orden-1)*sizeof(competidoresBin), SEEK_SET);
    fwrite(&ceros , sizeof(competidoresBin), 1, nuevosCompetidores);

    fclose(nuevosCompetidores);
}

#endif