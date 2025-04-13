# Sistema de gestion de tickets

## Descripción 

Este programa consiste en un modulo de gestion donde se presentan 5 posibles acciones, estas cumplen funcionalidades como incluir un nuevo ticket en el sistema, reasignar su prioridad, motrar la lista de tickets por orden de llegada y prioridad, procesar el ticket con mayor prioridad y mas antiguiedad en el sistema, y por ultimo consultar las especificaciones de un tikcet. 

## Requisitos previos:

- Tener instalado [Visual Studio Code](https://code.visualstudio.com/).
- Instalar la extensión **C/C++** (Microsoft).
- Tener instalado un compilador de C (como **gcc**). Si estás en Windows, se recomienda instalar [MinGW](https://www.mingw-w64.org/) o utilizar el entorno [WSL](https://learn.microsoft.com/en-us/windows/wsl/).

### Pasos para compilar y ejecutar:

1. **Clonar el repositorio desde GitHub:**
    - Abre una terminal o línea de comandos.
    - Clona el repositorio usando el siguiente comando:

    ```bash
    git clone https://github.com/VicenteGonzalez14/Sistema-gesti-n-tickets.git
    ```

2. **Abrir el proyecto en Visual Studio Code**
    - Inicia Visual Studio Code.
    - Selecciona `Archivo > Abrir carpeta...` y elige la carpeta donde clonaste el repositorio.

3. **Compilar el código**
    - Abre el archivo principal (por ejemplo, `tarea1.c`).
    - Abre la terminal integrada (`Terminal > Nueva terminal`).
    - En la terminal, compila el programa con el siguiente comando (ajusta el nombre si el archivo principal tiene otro nombre):
    
    ```bash
    gcc *.c -o sistema_tickets
    ```

4. **Ejecuta el programa**
    - Una vez compilado, puedes ejecutar la aplicación con:
    
    ```bash
    ./sistema_tickets
    ```

   git clone https://github.com/VicenteGonzalez14/Sistema-gesti-n-tickets.git

# FUNCIONALIDADES

## FUNCIONANDO CORRECTAMENTE:
1. Ingresar tickets con sus datos basicos(ID, prioridad, descripción problema y hora de registro).
2. Reasignar prioridad de tickets a traves de su ID.
3. Mostrar la lista de tickets ingresados por orden de llegada y prioridad desde la "ALTA" a la "BAJA".
4. Procesar ticket de mayor prioridad y con mas tiempo ingresado en el sistema.
5. Buscar ticket para ver sus datos a traves de su ID.

## PROBLEMAS CONOCIDOS:
1. El programa no entrega errores si la ID del ticket es ingresada con un caracter distinto de un numero, y tampoco entrega error si el usuario no especifica el problema del ticket. 
2. Parece ser que el programa cumple con todas las funcionalidades, pero haciendo casos de prueba ingresando mas de 10 tickets hubieron algunos problemas con la funcion de mostrar los tickets.

## A MEJORAR: 
1. Lograr un mejor manejo de los tickets para casos de pruebas donde sean muchos tickets a procesar.
2. Incluir limitaciones a lo que el usuario puede ingresar en la consola, y tambien invalidar el ticket cuando lo que ingrese sea invalido, como por ejemplo un ticket con letras o una descripcion de un solo caracter o solo numeros.

## EJEMPLO DE USO

### Opción 1: Registrar ticket con ID y descripcion del problema.
El usuario registra su tikcet con el numero que prefiera, junto con una descripcion de su problema
1)Registrar nuevo ticket

    Ingrese su opcion: 1
    Registrar nuevo ticket
    Ingrese la ID  de su ticket: 9
    Ingrese su problema: Mi equipo no funciona pipipi.
    Agregando ticket con ID: 9
    Gracias por preferirnos, su ticket es el numero: 9
    Presione cualquier tecla para continuar...

### Opción 2: Reasignar prioridad de ticket.
  El usuario ingresa la ID de su tikcet para reasginarle la prioridad que eliga en la consola
  2) Reasiganr prioridad de su ticket.
    
      Ingrese su opcion: 2
      Ingrese el ID del ticket para reasignar la prioridad: 9
      Seleccione la nueva prioridad:
      1) Establecer prioridad ALTA  
      2) Establecer prioridad MEDIA 
      Ingrese opcion (1 o 2): 1
      Buscando ticket con ID: 23
      La prioridad del ticket con ID 23 ha sido cambiada a: ALTA
      Presione cualquier tecla para continuar...

### Opción 3: Mostrar lista de espera de tickets por prioridad
  La consola entrega un listado de todos los tickets ingresados en el sistema por orden de llegada desde la prioridad mas alta hasta la mas baja. 
  3)Mostrar lista de espera de tickets por prioridad
    
      Ingrese su opcion: 3
      Tickets en espera, ordenados por prioridad (de alta a baja) y hora de registro:
      Ticket ID: 1
      Problema: "descripción"
      Prioridad: ALTA
      Hora de Registro: 13/04/2025 16:52:23
      Ticket ID: a
      Problema: "descripción"
      Prioridad: BAJA
      Hora de Registro: 13/04/2025 16:53:44
      Presione cualquier tecla para continuar...

 ### Opcion 4: Atender al siguiente ticket
  La consola procesa el ticket mas antiguo y de mayor prioridad y lo elimina del sistema. 
  4)Atender al siguiente ticket
    
      Ingrese su opción: 4
      Procesando el siguiente ticket:
      Ticket ID: 1
      Problema: "descripción"
      Prioridad: ALTA
      Hora de Registro: 13/04/2025 16:52:23
      Presione cualquier tecla para continuar...
    
 ### Opcion 5: Mostrar detalles ticket
  La consola le pide al usuario la ID del ticket que se quiere visualizar. 
  5)Mostrar detalles ticket
    
      Ingrese el ID del ticket que desea buscar: 1
      === Ticket Encontrado ===
      Ticket ID: 1
      Problema: "descripción"
      Prioridad: BAJA
      Hora de Registro: 13/04/2025 17:07:00
      Presione cualquier tecla para continuar...
  ### Opcion 6: Salir del sistema 
  La consola finaliza el programa, libera la memoria de todos los tickets. 
  6)Salir
    
      Ingrese su opci├│n: 6
      Saliendo del sistema de gestion de tickets...
      Presione cualquier tecla para continuar...

  ## Contribuciones: 
  No hubieron contribuciones de terceros en este programa, era indivual.























