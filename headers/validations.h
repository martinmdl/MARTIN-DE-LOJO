#ifndef VALIDATIONS_H
#define VALIDATIONS_H

int validMenu(int menu, int min, int max) {
   // Muestra distintos menús de opciones según sean los parámetros.
   // Incluye una validación de enteros positivos entre un rango especificado en parámetros.

   int opcion;
   
   switch(menu) {
      case 1: showMenu1(); break; // menus.h
      case 2: showMenu2(); break; // menus.h
      case 3: showMenu3(); break; // menus.h
      case 4: showMenu4(); break; // menus.h
      case 5: showMenu5(); break; // menus.h
   }

   while(1) {
      printf("\nIngrese una opci%cn: ", 162, 160);
      scanf("%d", &opcion);
      fflush(stdin);
      system("cls");
      if(opcion > min && opcion < max) {return opcion;}
      printf("Elija una opci%cn v%clida\n\n", 162, 160);
      switch(menu) {
         case 1: showMenu1(); break; // menus.h
         case 2: showMenu2(); break; // menus.h
         case 3: showMenu3(); break; // menus.h
         case 4: showMenu4(); break; // menus.h
         case 5: showMenu5(); break; // menus.h
      }
   }
}

char validBin(int flag) {
   // Pide una confirmación para seguir ejecutando.
   // El parámetro me permite reutilizar esta función aunque requiera mostrar diferentes textos.

   char opcion;

   while(1) {
      if(flag == 1) {printf("Si ya existe un archivo binario se perder%cn los datos\n", 160);}      
      if(flag == 2) {printf("Est%c apunto de eliminar los competidores inactivos\n", 160);}      
      printf("Desea continuar? (S/N): ");
      scanf("%c", &opcion);
      fflush(stdin);
      opcion = tolower(opcion);
      system("cls");
      if(opcion == 's' || opcion == 'n') {return opcion;}
      printf("Elija una opci%cn v%clida\n\n", 162, 160);
   }
}

#endif