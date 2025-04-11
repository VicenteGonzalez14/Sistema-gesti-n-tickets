#include "tdas/list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Menú principal
void mostrarMenuPrincipal() {
  puts("=========================================");
  puts("MODULO DE GESTION TICKETS SOPORTE TECNICO");
  puts("=========================================");

  puts("1) Registrar nuevo ticket");
  puts("2) Reasignar prioridad de su ticket");
  puts("3) Mostrar lista de espera de tickets por prioridad");
  puts("4) Atender al siguiente ticket");
  puts("5) Mostrar detalles ticket");
  puts("6) Salir");
}

void limpiar_buffer() {
  char c;
  while (getchar() != '\n' && c != EOF);  // Limpiar todo el buffer
}

// Función para registrar un nuevo ticket, el usuario registra los datos de su ticket segun su Id y puede especificar su problema, su prioridad es inicalizada en "BAJA" y su hora de llegada es en torno al sistema. 
void registrarTicket(List *ticket) {
  printf("Registrar nuevo ticket\n");

  char Id[100];  
  char *prioridad = "BAJA";  // Establecer prioridad inicial
  printf("Ingrese la ID de su ticket: ");
  fgets(Id, sizeof(Id), stdin);  
  Id[strcspn(Id, "\n")] = 0;  // Eliminar salto de línea
  // Leer el problema del ticket
  char problema[200];  
  printf("Ingrese su problema: ");
  fgets(problema, sizeof(problema), stdin);  
  problema[strcspn(problema, "\n")] = 0;  // Eliminar salto de línea

  // Asignar memoria para el nuevo ticket
  Node *nuevoTicket = malloc(sizeof(Node));  // Asignar memoria para el nodo
  if (nuevoTicket == NULL) { 
      printf("Error al asignar memoria para el nuevo ticket.\n"); 
      return; 
  }

  // Asignar los valores del ticket
  nuevoTicket->data = malloc(strlen(Id) + 1); 
  strcpy(nuevoTicket->data, Id);  // Copiar ID
  nuevoTicket->problema = malloc(strlen(problema) + 1);
  strcpy(nuevoTicket->problema, problema);  // Copiar problema
  nuevoTicket->prioridad = malloc(strlen(prioridad) + 1);
  strcpy(nuevoTicket->prioridad, prioridad);  // Establecer prioridad

  // Asignar memoria dinámica para hora de registro
  nuevoTicket->horaRegistro = malloc(100); // Asignar memoria para la hora
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  sprintf(nuevoTicket->horaRegistro, "%02d/%02d/%d %02d:%02d:%02d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);

  // El siguiente nodo es NULL ya que es el último
  nuevoTicket->next = NULL;  

  // Insertar el nuevo ticket al final de la lista
  list_pushBack(ticket, nuevoTicket);  

  printf("Gracias por preferirnos, su ticket es el numero: %s\n", nuevoTicket->data);
}

void mergeSort(Node** head);

//Esta funcion reasgina la prioridad del ticket requerido por el usuario, le da la opcion 1 y la 2 para cambiar la priorirda de su ticket
void reasignarPrioridad(List *ticket) {
  char id[100];
  int opcion;

  printf("Ingrese el ID del ticket para reasignar la prioridad: ");
  fgets(id, sizeof(id), stdin);
  id[strcspn(id, "\n")] = 0; // Eliminar salto de línea
  limpiar_buffer(); // Limpiar el buffer después de usar fgets
  
  // Pedir al usuario que elija la nueva prioridad
  printf("Seleccione la nueva prioridad:\n");
  printf("1) Establecer prioridad ALTA\n");
  printf("2) Establecer prioridad MEDIA\n");
  printf("Ingrese opción (1 o 2): ");
  scanf("%d", &opcion);
  limpiar_buffer(); // Limpiar el buffer después de usar scanf

  // Definir el valor de la nueva prioridad según la opción elegida
  char *nuevaPrioridad = NULL;
  switch (opcion) {
      case 1:
          nuevaPrioridad = "ALTA";
          break;
      case 2:
          nuevaPrioridad = "MEDIA";
          break;
      default:
          printf("Opción inválida. No se cambia la prioridad.\n");
          return;
  }

  // Buscar el ticket en la lista
  Node *current = ticket->head;
  printf("Buscando ticket con ID: %s\n", id);
  while (current != NULL) {
      if (strcmp((char *)current->data, id) == 0) { // Comparar ID del ticket
          // Reasignar la prioridad
          free(current->prioridad);  // Liberar la memoria de la prioridad anterior
          current->prioridad = malloc(strlen(nuevaPrioridad) + 1); // Asignar memoria para la nueva prioridad
          strcpy(current->prioridad, nuevaPrioridad); // Asignar la nueva prioridad

          printf("La prioridad del ticket con ID %s ha sido cambiada a: %s\n", id, nuevaPrioridad);
          
          // Reordenar la lista después de reasignar la prioridad
          mergeSort(&ticket->head);

          return; // Salir después de reasignar y reordenar
      }
      current = current->next;
  }

  printf("No se encontró un ticket con ID %s.\n", id); // Si no se encontró el ticket
}

//Función complementaria para reasignar la prioridad. 
int prioridadToValor(char *prioridad) {
  if (strcmp(prioridad, "ALTA") == 0) {
      return 3;
  } else if (strcmp(prioridad, "MEDIA") == 0) {
      return 2;
  } else if (strcmp(prioridad, "BAJA") == 0) {
      return 1;
  }
  return 0;  // Caso por defecto
}

// Función para dividir la lista en dos mitades, esta funcion es para implementar el mergeSort
Node* dividirLista(Node* head) {
  if (head == NULL || head->next == NULL) {
      return head;
  }
  
  Node* medio = head;
  Node* fin = head->next;
  
  while (fin != NULL && fin->next != NULL) {
      medio = medio->next;
      fin = fin->next->next;
  }
  
  Node* mitad = medio->next;
  medio->next = NULL;  // Dividir la lista en dos partes
  
  return mitad;
}

// Función para fusionar dos listas ordenadas, esta funcion hace una iteracion de comparaciones para que la lista quede ordenada por orden de prioridad y llegada.
Node* fusionarListas(Node* izquierda, Node* derecha) {
  if (izquierda == NULL) {
      return derecha;
  } else if (derecha == NULL) {
      return izquierda;
  }
  
  Node* resultado = NULL;
  
  // Comparar las prioridades
  if (prioridadToValor(izquierda->prioridad) > prioridadToValor(derecha->prioridad)) {
      resultado = izquierda;
      resultado->next = fusionarListas(izquierda->next, derecha);
  } else if (prioridadToValor(izquierda->prioridad) < prioridadToValor(derecha->prioridad)) {
      resultado = derecha;
      resultado->next = fusionarListas(izquierda, derecha->next);
  } else {
      // Si las prioridades son iguales, comparar por hora de registro
      if (strcmp(izquierda->horaRegistro, derecha->horaRegistro) < 0) {
          resultado = izquierda;
          resultado->next = fusionarListas(izquierda->next, derecha);
      } else {
          resultado = derecha;
          resultado->next = fusionarListas(izquierda, derecha->next);
      }
  }
  
  return resultado;
}

// Función para ordenar la lista usando Merge Sort
void mergeSort(Node** head) {
  if (*head == NULL || (*head)->next == NULL) {
      return;
  }
  
  Node* mitad = dividirLista(*head);  // Dividir la lista en dos mitades
  
  mergeSort(&(*head));         // Recursión en la primera mitad
  mergeSort(&mitad);           // Recursión en la segunda mitad
  
  *head = fusionarListas(*head, mitad);  // Fusionar las mitades ordenadas
}

// Función para mostrar los tickets ordenados por prioridad
void mostrarTicketsPorPrioridad(List *ticketList) {
  printf("Tickets en espera, ordenados por prioridad (de alta a baja) y hora de registro:\n");

  Node* current = ticketList->head;
  
  // Ordenar los tickets de la lista usando Merge Sort
  mergeSort(&current);  
  
  // Recorrer la lista y mostrar los tickets, muestra cada una de sus componentes de manera ordenada.
  while (current != NULL) {
      printf("Ticket ID: %s\n", current->data);  
      printf("Problema: %s\n", current->problema);  
      printf("Prioridad: %s\n", current->prioridad);  
      printf("Hora de Registro: %s\n", current->horaRegistro);  
      printf("\n");  // Salto de línea entre cada ticket para mejor legibilidad
      current = current->next;  // Avanza al siguiente nodo
  }
}

void procesarSiguienteTicket(List *ticketList) {
  // Verificar si la lista está vacía
  if (ticketList->head == NULL) {
      printf("No hay tickets pendientes.\n");
      return;
  }

  // El primer ticket en la lista es el de mayor prioridad (y más antiguo dentro de su nivel)
  Node *ticketProcesado = ticketList->head;

  // Mostrar los detalles del ticket
  printf("\nProcesando el siguiente ticket:\n");
  printf("Ticket ID: %s\n", ticketProcesado->data);
  printf("Problema: %s\n", ticketProcesado->problema);
  printf("Prioridad: %s\n", ticketProcesado->prioridad);
  printf("Hora de Registro: %s\n", ticketProcesado->horaRegistro);

  // Eliminar el ticket de la lista
  ticketList->head = ticketList->head->next;  // La cabeza apunta al siguiente nodo
  free(ticketProcesado->data);
  free(ticketProcesado->problema);
  free(ticketProcesado->prioridad);
  free(ticketProcesado->horaRegistro);  // Liberar la memoria de la hora de registro
  free(ticketProcesado);  // Liberar la memoria del nodo

  ticketList->size--; 
}

//Función implementada para cumplir con la funcionalidad de buscar tickets.  
void buscarTicketPorID(List *ticketList) {
  char idBuscar[100];
  printf("Ingrese el ID del ticket que desea buscar: ");
  fgets(idBuscar, sizeof(idBuscar), stdin);
  idBuscar[strcspn(idBuscar, "\n")] = 0;  // Eliminar salto de línea

  Node *current = ticketList->head;
  while (current != NULL) {
      if (strcmp(current->data, idBuscar) == 0) {
          // Si se encuentra el ticket, mostrar sus detalles
          printf("\n=== Ticket Encontrado ===\n");
          printf("Ticket ID: %s\n", current->data);
          printf("Problema: %s\n", current->problema);
          printf("Prioridad: %s\n", current->prioridad);
          printf("Hora de Registro: %s\n", current->horaRegistro);
          return;
      }
      current = current->next;  // Avanzar al siguiente ticket
  }

  // Si no se encuentra el ticket
  printf("\nNo se encontró ningún ticket con el ID: %s\n", idBuscar);
}
int main() {
  char opcion;
  List *ticket = list_create();  // Crear la lista de tickets

  do {
    mostrarMenuPrincipal();  // Mostrar el menú
    char opcion_str[10];
    printf("Ingrese su opción: ");
    fgets(opcion_str, sizeof(opcion_str), stdin);
    opcion = opcion_str[0];
    switch (opcion) {
    case '1':
      registrarTicket(ticket);  // Registrar un nuevo ticket
      break;
    case '2':
      reasignarPrioridad(ticket);// Lógica para reasignar prioridad de un ticket
      break;
    case '3':
      mostrarTicketsPorPrioridad(ticket);// Lógica para mostrar tickets por prioridad 
      break;
    case '4':
      procesarSiguienteTicket(ticket);// Lógica para procesar y eliminar el ticket de mayor prioridad.
      break;
    case '5':
      buscarTicketPorID(ticket);//Logica para buscar un Id y mostrar su informacion; 
      break;
    case '6':
      puts("Saliendo del sistema de gestión de tickets...");
      break;
    default:
      puts("Opción no válida. Por favor, intente de nuevo.");
    }

    printf("Presione cualquier tecla para continuar...\n");
    getchar();  // Espera que el usuario presione una tecla para continuar


  } while (opcion != '6');

  // Liberar memoria de la lista antes de terminar
  list_clean(ticket);
  free(ticket);  // Liberar la memoria de la lista

  return 0;
}
