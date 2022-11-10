#ifndef MENUS_H
#define MENUS_H

void showMenu1() {
    printf("MEN%c PRINCIPAL\n", 233);
    printf("1 - Ver registro de texto de competidores\n");
    printf("2 - Crear archivo\n");
    printf("3 - Migrar archivo\n");
    printf("4 - Ver datos de competidores\n");
    printf("5 - Registrar nuevo competidor\n");
    printf("6 - Buscar competidor\n");
    printf("7 - Modificar edad o tiempo\n");
    printf("8 - Dar de baja un competidor\n");
    printf("9 - Eliminar competidores inactivos\n");
    printf("10 - Ver competidores eliminados\n");
    printf("11 - Cerrar aplicaci%cn\n", 162);
}

void showMenu2() {
   printf("OPCIONES DE LISTADO\n");
   printf("1 - Listar todos\n");
   printf("2 - Listar activos\n");
   printf("3 - Buscar por pa%cs\n", 161);
   printf("4 - Buscar por rango de tiempo\n");
   printf("5 - Volver al men%c principal\n", 163);
}

void showMenu3() {
   printf("OPCIONES DE BUSQUEDA\n");
   printf("1 - Buscar por n%cmero de orden\n", 163);
   printf("2 - Buscar por n%cmero de corredor\n", 163);
   printf("3 - Volver al men%c principal\n", 163);
}

void showMenu4() {
   printf("OPCIONES DE MODIFICACI%cN\n", 224);
   printf("1 - Modificar edad\n", 163);
   printf("2 - Modificar tiempo\n", 163);
   printf("3 - Volver al men%c principal\n", 163);
}

void showMenu5() {
   printf("ESPERANDO CONFIRMACI%cN\n", 224);
   printf("1 - Realizar alta\n");
   printf("2 - Cancelar y volver al men%c principal\n", 163);
}

#endif