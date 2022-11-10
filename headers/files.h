#ifndef FILES_H
#define FILES_H

void showLog(FILE* registroCompetidores) {
    // FUNCIÓN: EJERCICIO 1.
    // Muestra en pantalla el archivo de texto ".csv" que existe previamente.
    // Se muestra tal cual está escrito, es decir, no se le da formato.

    // DECLARA VARIABLES A UTILIZAR
	errno = 0;
	competidores datos;
	char c;

    // ABRE EL ARCHIVO Y AVISA SI HUBO ALGUN ERROR
	registroCompetidores = fopen("files/corredores_v1.csv", "r");
	if(registroCompetidores == NULL) {
        printf("ERROR: %s", strerror(errno)); // MUESTRA DETALLES DEL ERROR (errno.h)
        printf("\n\nPresione cualquier tecla para continuar...");
    }
    
    // ESPACIO PARA OPERAR CON EL ARCHIVO
	while(fscanf(
            registroCompetidores,
            "%d %c %d %c %d %c %[^;] %c %d %c %d %c %[^;] %c %f",
            &datos.orden, &c,
            &datos.corredor, &c,
            &datos.dia, &c,
            datos.mes, &c,
            &datos.anio, &c,
            &datos.edad, &c,
            datos.pais, &c,
            &datos.tiempo
        ) != EOF) {
		printf("%d;%d;%d;%s;%d;%d;%s;%.6f\n",
            datos.orden,
            datos.corredor,
            datos.dia,
            datos.mes,
            datos.anio,
            datos.edad,
            datos.pais,
            datos.tiempo
        );
	}

    // CIERRA EL ARCHIVO Y VUELVE A MAIN
	fclose(registroCompetidores);
    printf("\nPresione cualquier tecla para continuar...");
    getchar();
    system("cls");
}

void createBin() {
    // FUNCIÓN: EJERCICIO 2.
    // Crea un archivo binario que me permitirá manipular los datos mas comodamente.
    // Si el archivo ya existe, le sobreescribe un archivo binario vacío.

    if(validBin(1) == 's') { // validations.h
        fopen("files/competidores.dat", "wb");
        printf("ARCHIVO CREADO\n");
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

void migrateLog(FILE* registroCompetidores, FILE* nuevosCompetidores) {
    // FUNCIÓN: EJERCICIO 3.
    // Migra los archivos sin formato pertenecientes al archivo de texto
    // y los guarda en el archivo binario creado en la función anterior.

    errno = 0;
    competidoresBin datos;
    char c;

    registroCompetidores = fopen("files/corredores_v1.csv", "r");
    nuevosCompetidores = fopen("files/competidores.dat", "wb");
    if(registroCompetidores == NULL) {
        printf("corredores_v1.csv\n");
		printf("ERROR: %s", strerror(errno));
        printf("\n\nPresione cualquier tecla para continuar...");
    }
    if(nuevosCompetidores == NULL) {
        printf("competidores.dat\n");
		printf("ERROR: %s", strerror(errno));
        printf("\n\nPresione cualquier tecla para continuar...");
    }

    while(fscanf(
            registroCompetidores,
            "%d %c %d %c %d %c %[^;] %c %d %c %d %c %[^;] %c %f",
            &datos.orden, &c,
            &datos.corredor, &c,
            &datos.dia, &c,
            datos.mes, &c,
            &datos.anio, &c,
            &datos.edad, &c,
            datos.pais, &c,
            &datos.tiempo
        ) != EOF) {
        datos.activo = 1;
		fwrite(&datos, sizeof(competidoresBin), 1, nuevosCompetidores);
	}

    fclose(registroCompetidores);
    fclose(nuevosCompetidores);
    printf("ARCHIVO MIGRADO\n");
    printf("\nPresione cualquier tecla para continuar...");
    getchar();
    system("cls");
}

void showData(FILE* nuevosCompetidores) {
    // FUNCIÓN: EJERCICIO 4.
    // Muestra en pantalla un menú que le permite al usuario elegir como quiere ver los datos.
    // Puede listar: todos los competidores, solo los activos, buscar por país o buscar por rango de tiempo.

    switch(validMenu(2, 0, 6)) { // validations.h
        case 1: showAllData(nuevosCompetidores); break; // auxfiles.h
        case 2: showDataByState(nuevosCompetidores); break; // auxfiles.h
        case 3: showDataByCountry(nuevosCompetidores); break; // auxfiles.h
        case 4: showDataByTime(nuevosCompetidores); break; // auxfiles.h
        case 5: break;
    }    
}

void logElement(FILE* nuevosCompetidores) {
    // FUNCIÓN: EJERCICIO 5.
    // Permite la entrada de datos para dar de alta un nuevo competidor.
    // Todos los inputs están validados antes de ejecutar la escritura.

    errno = 0;
    competidoresBin datos, news;
    int currentYear, i, firstYear, flag = 0;
    char chars, aux[20];

    nuevosCompetidores = fopen("files/competidores.dat", "r+b");
    if(nuevosCompetidores == NULL) {
        printf("ERROR: %s", strerror(errno));
        printf("\n\nPresione cualquier tecla para continuar...");
    }

    // ESTABLECE PRIMER AÑO Y AÑO ACTUAL
    time_t tiempo = time(NULL);
    struct tm currentTime = *localtime(&tiempo);
    currentYear = currentTime.tm_year + 1900;
    firstYear = currentYear;
    fseek(nuevosCompetidores, 0, SEEK_SET);
    while(!feof(nuevosCompetidores)) {
        fread(&datos, sizeof(competidoresBin), 1, nuevosCompetidores);
        if(datos.anio < firstYear && datos.anio != 0) {firstYear = datos.anio;}
    }

    // VALIDACION ORDEN
    printf("N%cmero de orden: ", 163);
    while(1) {
        while(1) {
            scanf("%d%c", &news.orden, &chars);
            fflush(stdin);
            if(chars == '\n' && news.orden > 0) {break;}
            printf("\tIngrese un n%cmero positivo: ", 163);
        }
        fseek(nuevosCompetidores, ((news.orden-1)*sizeof(competidoresBin)), SEEK_SET);
        fread(&datos, sizeof(competidoresBin), 1, nuevosCompetidores);
        if(datos.orden != news.orden) {break;}
        printf("\tIngrese un n%cmero no repetido: ", 163);
    }

        // MUESTREO PARCIAL
        system("cls");
        printf("Orden: %d\n\n", news.orden);

    // VALIDACION CORREDOR
    printf("N%cmero de corredor: ", 163);    
    while(1) {
        scanf("%d%c", &news.corredor, &chars);
        fflush(stdin);
        if(chars == '\n' && news.corredor > 0) {break;}
        printf("\tIngrese un n%cmero positivo: ", 163);
    }

        // MUESTREO PARCIAL
        system("cls");
        printf("Orden: %d\n", news.orden);
        printf("Corredor: %d\n\n", news.corredor);

    // VALIDACION AÑO        
    printf("A%co: ", 164);
    while(1) {
        scanf("%d%c", &news.anio, &chars);
        fflush(stdin);
        if(chars == '\n' && news.anio >= firstYear && news.anio <= currentYear) {break;}
        printf("\tIngrese un a%co entre %d y %d: ", 164, firstYear, currentYear);
    }

        // MUESTREO PARCIAL
        system("cls");
        printf("Orden: %d\n", news.orden);
        printf("Corredor: %d\n", news.corredor);
        printf("A%co: %d\n\n", 164, news.anio);

    // VALIDACION MES
    printf("Mes: ");
    while(1) {
        news.mes[0] = ' ';
        news.mes[1] = ' ';
        news.mes[2] = ' ';
        news.mes[3] = '\0';
        gets(aux);
        fflush(stdin);
        for(i = 0; i < strlen(aux); i++) {
            aux[i] = tolower(aux[i]);
        }
        if(
            strcmp(aux, "enero") == 0 ||
            strcmp(aux, "febrero") == 0 ||
            strcmp(aux, "marzo") == 0 ||
            strcmp(aux, "abril") == 0 ||
            strcmp(aux, "mayo") == 0 ||
            strcmp(aux, "junio") == 0 ||
            strcmp(aux, "julio") == 0 ||
            strcmp(aux, "agosto") == 0 ||
            strcmp(aux, "septiembre") == 0 ||
            strcmp(aux, "octubre") == 0 ||
            strcmp(aux, "noviembre") == 0 ||
            strcmp(aux, "diciembre") == 0
        ) {
            for(i = 0; i < strlen(news.mes); i++) {
                news.mes[i] = tolower(aux[i]);
            }
            break;
        }
        printf("\tIngrese un mes v%clido: ", 160);
    }

        // MUESTREO PARCIAL
        system("cls");
        printf("Orden: %d\n", news.orden);
        printf("Corredor: %d\n", news.corredor);
        printf("A%co: %d\n", 164, news.anio);
        printf("Mes: %s\n\n", news.mes);

    // VALIDACION DIA
    printf("D%ca: ", 161);
    while(1) {
        while(1) {
            scanf("%d%c", &news.dia, &chars);
            fflush(stdin);
            if(chars == '\n' && news.dia > 0) {break;}
            printf("\tIngrese un n%cmero positivo: ", 163);
        }
        if(
            strcmp(news.mes, "ene") == 0 ||
            strcmp(news.mes, "mar") == 0 ||
            strcmp(news.mes, "may") == 0 ||
            strcmp(news.mes, "jul") == 0 ||
            strcmp(news.mes, "ago") == 0 ||
            strcmp(news.mes, "oct") == 0 ||
            strcmp(news.mes, "dic") == 0
        ) {
            if(news.dia <= 31) {break;}
            printf("\tIngrese un d%ca v%clido: ", 161, 160);
        }
        if(
            strcmp(news.mes, "abr") == 0 ||
            strcmp(news.mes, "jun") == 0 ||
            strcmp(news.mes, "sep") == 0 ||
            strcmp(news.mes, "nov") == 0
        ) {
            if(news.dia <= 30) {break;}
            printf("\tIngrese un d%ca v%clido: ", 161, 160);
        }
        if(strcmp(news.mes, "feb") == 0) {
            if(news.dia <= 28) {break;}
            printf("\tIngrese un d%ca v%clido: ", 161, 160);
        }
    }

        // MUESTREO PARCIAL
        system("cls");
        printf("Orden: %d\n", news.orden);
        printf("Corredor: %d\n", news.corredor);
        printf("A%co: %d\n", 164, news.anio);
        printf("Mes: %s\n", news.mes);
        printf("D%ca: %d\n\n", 161, news.dia);

    // VALIDACION EDAD
    printf("Edad: ");
    while(1) {
        scanf("%d%c", &news.edad, &chars);
        fflush(stdin);
        if(chars == '\n' && news.edad > 0 && news.edad < 110) {break;}
        printf("\tIngrese una edad v%clida: ", 160);
    }

        // MUESTREO PARCIAL
        system("cls");
        printf("Orden: %d\n", news.orden);
        printf("Corredor: %d\n", news.corredor);
        printf("A%co: %d\n", 164, news.anio);
        printf("Mes: %s\n", news.mes);
        printf("D%ca: %d\n", 161, news.dia);
        printf("Edad: %d\n\n", news.edad);

    // VALIDACION PAIS
    news.pais[0] = ' ';
    news.pais[1] = ' ';
    news.pais[2] = ' ';
    news.pais[3] = '\0';
    printf("Pa%cs: ", 161);
    while(1) {
        gets(aux);
        fflush(stdin);
        if(strlen(aux) > 2) {
            for(i = 0; i < strlen(news.pais) && news.pais[i] != '\0'; i++) {
                news.pais[i] = toupper(aux[i]);
            }
            break;
        }
        printf("\tIngrese un pa%cs v%clido: ", 161, 160);
    }

        // MUESTREO PARCIAL
        system("cls");
        printf("Orden: %d\n", news.orden);
        printf("Corredor: %d\n", news.corredor);
        printf("A%co: %d\n", 164, news.anio);
        printf("Mes: %s\n", news.mes);
        printf("D%ca: %d\n", 161, news.dia);
        printf("Edad: %d\n", news.edad);
        printf("Pa%cs: %s\n\n", 161, news.pais);

    // VALIDACION TIEMPO
    printf("Tiempo: ");
    while(1) {
        scanf("%f%c", &news.tiempo, &chars);
        fflush(stdin);
        if(chars == '\n' && news.tiempo >= 0) {break;}
        printf("\tIngrese un n%cmero positivo: ", 163);
    } 

    news.activo = 1;

    system("cls");
    while(1) {
            printf("Orden: %d\n", news.orden);
            printf("Corredor: %d\n", news.corredor);
            printf("A%co: %d\n", 164, news.anio);
            printf("Mes: %s\n", news.mes);
            printf("D%ca: %d\n", 161, news.dia);
            printf("Edad: %d\n", news.edad);
            printf("Pa%cs: %s\n", 161, news.pais);
            printf("Tiempo: %.2f\n\n", news.tiempo);
        switch(validMenu(5, 0, 3)) { // validations.h
            case 1:
                exeLog(nuevosCompetidores, news); // auxfiles.h
                flag = 1;
                break;
            case 2: break;
        }
        break;
    }

    fclose(nuevosCompetidores);
    system("cls");
    if(flag == 1) {printf("ALTA REALIZADA\n");}
    else {printf("VOLVIENDO AL MEN%c PRINCIPAL\n", 233);}
    printf("\nPresione cualquier tecla para continuar...");
    getchar();
    system("cls");
}

void searchElement(FILE* nuevosCompetidores) {
    // FUNCIÓN: EJERCICIO 6.
    // Permite buscar un elemento de la lista por número de orden o por número de corredor.
    // Esta función puede emitir más de un dato por pantalla si existen dos corredores con el mismo número de corredor.
    // En caso de elegir buscar por número de orden, siempre habra un solo resultado.

    switch(validMenu(3, 0, 4)) { // validations.h
        case 1: searchByID(nuevosCompetidores, 0, 0); break; // auxfiles.h
        case 2: searchByNum(nuevosCompetidores, 0, 0); break; // auxfiles.h
        case 3: break;
    }
}

void modElement(FILE* nuevosCompetidores) {
    // FUNCIÓN: EJERCICIO 7.
    // Cambia la edad o el tiempo de un corredor ya registrado.
    // Éste puede ser buscado por número de corredor o por número de orden,
    // para esto se apoya en funciones previamente creadas.

    switch(validMenu(4, 0, 4)) { // validations.h
        case 1: // EDAD
            switch(validMenu(3, 0, 4)) { // validations.h
                case 1: modifyAge(1, nuevosCompetidores); break; // auxfiles.h (searchByID)
                case 2: modifyAge(2, nuevosCompetidores); break; // auxfiles.h (searchByNum)
                case 3: break;
            }
            break;
        case 2: // TIEMPO
            switch(validMenu(3, 0, 4)) {
                case 1: modifyTime(1, nuevosCompetidores); break; // auxfiles.h (searchByID)
                case 2: modifyTime(2, nuevosCompetidores); break; // auxfiles.h (searchByNum)
                case 3: break;
            }
            break;
        case 3: break;
    }
}

void unlogElement(FILE* nuevosCompetidores) {
    // FUNCIÓN: EJERCICIO 8.
    // Permite cambiar el estado de un corredor a "inactivo".
    // Solo puede buscarlo por el número de orden.

    errno = 0;
    int orden = 0;
    competidoresBin baja;

    searchByID(nuevosCompetidores, &orden, 2); // auxfiles.h
    if(validBin(0) == 's') { // validations.h
        nuevosCompetidores = fopen("files/competidores.dat", "r+b");
        if(nuevosCompetidores == NULL) {
            printf("ERROR: %s", strerror(errno));
            printf("\n\nPresione cualquier tecla para continuar...");
        }

        fseek(nuevosCompetidores, ((orden-1)*sizeof(competidoresBin)), SEEK_SET);
        fread(&baja, sizeof(competidoresBin), 1, nuevosCompetidores);
        baja.activo = 0;
        fseek(nuevosCompetidores, ((orden-1)*sizeof(competidoresBin)), SEEK_SET);
        fwrite(&baja, sizeof(competidoresBin), 1, nuevosCompetidores);

        system("cls");
        fclose(nuevosCompetidores);
        printf("BAJA EXITOSA\n");
        printf("\nPresione cualquier tecla para continuar...");
        getchar();
        system("cls");
        showDataByState(nuevosCompetidores);
    } else {
        printf("VOLVIENDO AL MEN%c PRINCIPAL\n", 233);
        printf("\nPresione cualquier tecla para continuar...");
        getchar();
        system("cls");
    }
}

void deleteInactiveElements(FILE* nuevosCompetidores, FILE* deletedCompetidores) {
    // FUNCIÓN: EJERCICIO 9.
    // Borra a todos los corredores inactivos del archivo principal, rellenando sus líneas con una línea vacía (ceros).
    // Además, crea archivos binarios dependiendo de la fecha. En ellos se registra los archivos que fueron dados de baja.

    errno = 0;
    competidoresBin corredores;

    // FECHA ACTUAL
    int currYear, currMonth, currDay;
    time_t tiempo = time(NULL);
    struct tm tiempoActual = *localtime(&tiempo);
    currYear = tiempoActual.tm_year + 1900;
    currMonth = tiempoActual.tm_mon + 1;
    currDay = tiempoActual.tm_mday;

    // CONVIERTO INTS A CHARS
    char cYear[5], cMonth[3], cDay[3];
    sprintf(cYear, "%d", currYear);
    sprintf(cMonth, "%d", currMonth);
    sprintf(cDay, "%d", currDay);

    // NOMBRE ARCHIVO CON FECHA (STRING)
    char fileName[40] = "", intro[30] = "competidores_bajas_", guion[] = "-", ext[] = ".xyz", dir[] = "files/";
    strcat(fileName, dir);
    strcat(fileName, intro);
    strcat(fileName, cDay);
    strcat(fileName, guion);
    strcat(fileName, cMonth);
    strcat(fileName, guion);
    strcat(fileName, cYear);
    strcat(fileName, ext);
    
    if(validBin(2) == 's') { // validations.h
        nuevosCompetidores = fopen("files/competidores.dat", "r+b");
        if(nuevosCompetidores == NULL) {
            printf("competidores.dat\n");
            printf("ERROR: %s", strerror(errno));
            printf("\n\nPresione cualquier tecla para continuar...");
        }
        deletedCompetidores = fopen(fileName, "ab");
        if(deletedCompetidores == NULL) {
            printf("competidores_bajas_<fecha>.xyz\n");
            printf("ERROR: %s", strerror(errno));
            printf("\n\nPresione cualquier tecla para continuar...");
        }

        // ESCRIBIR EN NUEVO ARCHIVO
        fread(&corredores, sizeof(competidoresBin), 1, nuevosCompetidores);
        while(!feof(nuevosCompetidores)) {
            if(corredores.orden != 0 && corredores.activo == 0) {
                fwrite(&corredores, sizeof(competidoresBin), 1, deletedCompetidores); // mueve puntero de deletedCompetidores
            }
            fread(&corredores, sizeof(competidoresBin), 1, nuevosCompetidores); // mueve puntero de nuevosCompetidores
        }

        // ESCRIBIR CEROS EN ARCHIVO PRINCIPAL
        fseek(nuevosCompetidores, 0, SEEK_SET);
        fread(&corredores, sizeof(competidoresBin), 1, nuevosCompetidores);
        while(!feof(nuevosCompetidores)) {
            if(corredores.orden != 0 && corredores.activo == 0) {
                writeCeros(nuevosCompetidores, corredores.orden); // auxfiles.h
            }
            fread(&corredores, sizeof(competidoresBin), 1, nuevosCompetidores);
        }

        fclose(nuevosCompetidores);
        fclose(deletedCompetidores);
        printf("ELIMINADOS Y ARCHIVADOS\n");
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

void showDeletedElements(FILE* nuevosCompetidores, FILE* deletedCompetidores) {
    // FUNCIÓN: EJERCICIO 10.
    // Muestra las bajas guardadas en cierta fecha.
    // Si en la fecha ingresada no se encontro ningún archivo, se avisa del error.

    errno = 0;
    competidoresBin datos;
    int currentYear, i, firstYear, anio, mes, dia;
    char chars, aux[20];

    nuevosCompetidores = fopen("files/competidores.dat", "r+b");
    if(nuevosCompetidores == NULL) {
        printf("ERROR: %s", strerror(errno));
        printf("\n\nPresione cualquier tecla para continuar...");
    }

    // ESTABLECE PRIMER AÑO Y AÑO ACTUAL
    time_t tiempo = time(NULL);
    struct tm currentTime = *localtime(&tiempo);
    currentYear = currentTime.tm_year + 1900;
    firstYear = currentYear;
    fseek(nuevosCompetidores, 0, SEEK_SET);
    while(!feof(nuevosCompetidores)) {
        fread(&datos, sizeof(competidoresBin), 1, nuevosCompetidores);
        if(datos.anio < firstYear && datos.anio != 0) {firstYear = datos.anio;}
    }

    fclose(nuevosCompetidores);

    printf("Ingrese una fecha\n");

    // VALIDACION AÑO
    printf("A%co: ", 164);
    while(1) {
        scanf("%d%c", &anio, &chars);
        fflush(stdin);
        if(chars == '\n' && anio >= firstYear && anio <= currentYear) {break;}
        printf("\tIngrese un a%co entre %d y %d: ", 164, firstYear, currentYear);
    }

        // MUESTREO PARCIAL
        system("cls");
        printf("A%co: %d\n\n", 164, anio);

    // VALIDACION MES
    printf("Mes: ");

    while(1) {
        scanf("%d%c", &mes, &chars);
        fflush(stdin);
        if(chars == '\n' && mes > 0 && mes < 13) {break;}
        printf("\tIngrese un mes v%clido: ", 160);
    }

        // MUESTREO PARCIAL
        system("cls");
        printf("A%co: %d\n", 164, anio);
        printf("Mes: %d\n\n", mes);

    // VALIDACION DIA
    printf("D%ca: ", 161);
    while(1) {
        while(1) {
            scanf("%d%c", &dia, &chars);
            fflush(stdin);
            if(chars == '\n' && dia > 0) {break;}
            printf("\tIngrese un n%cmero positivo: ", 163);
        }
        if(
            mes == 1 ||
            mes == 3 ||
            mes == 5 ||
            mes == 7 ||
            mes == 8 ||
            mes == 10 ||
            mes == 12
        ) {
            if(dia <= 31) {break;}
            printf("\tIngrese un d%ca v%clido: ", 161, 160);
        }
        if(
            mes == 4 ||
            mes == 6 ||
            mes == 9 ||
            mes == 11
        ) {
            if(dia <= 30) {break;}
            printf("\tIngrese un d%ca v%clido: ", 161, 160);
        }
        if(mes == 2) {
            if(dia <= 28) {break;}
            printf("\tIngrese un d%ca v%clido: ", 161, 160);
        }
    }

    system("cls");
    printf("A%co: %d\n", 164, anio);
    printf("Mes: %d\n", mes);
    printf("D%ca: %d\n\n", 161, dia);
    printf("Presione cualquier tecla para continuar...");
    getchar();
    system("cls");

    char cYear[5], cMonth[3], cDay[3];
    sprintf(cYear, "%d", anio);
    sprintf(cMonth, "%d", mes);
    sprintf(cDay, "%d", dia);

    char fileName[50] = "", intro[30] = "competidores_bajas_", guion[] = "-", ext[] = ".xyz", dir[] = "files/";
    strcat(fileName, dir);
    strcat(fileName, intro);
    strcat(fileName, cDay);
    strcat(fileName, guion);
    strcat(fileName, cMonth);
    strcat(fileName, guion);
    strcat(fileName, cYear);
    strcat(fileName, ext);

    deletedCompetidores = fopen(fileName, "rb");
    if(deletedCompetidores == NULL) {
        printf("ERROR: %s", strerror(errno));
        printf("\n(Ning%cn archivo fue creado en esa fecha)", 163);
        printf("\n\nPresione cualquier tecla para continuar...");
        getchar();
        system("cls");
        return;
    }

    printf("ORDEN\tCORREDOR\tDIA\tMES\tA%cO\tEDAD\tPAIS\tTIEMPO\t\tACTIVO\n\n", 165);
    fread(&datos, sizeof(competidoresBin), 1, deletedCompetidores);
    while(!feof(deletedCompetidores)) {
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
        fread(&datos, sizeof(competidoresBin), 1, deletedCompetidores);
    }

    fclose(deletedCompetidores);
    printf("\nPresione cualquier tecla para continuar...");
    getchar();
    system("cls");

    // fclose(deletedCompetidores);
    // printf("\nPresione cualquier tecla para continuar...");
    // getchar();
    // system("cls");
}

#endif