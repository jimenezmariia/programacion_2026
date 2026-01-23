#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct Estudiante {
    char nombre[100];
    char codigo[20];
    int edad;
    float promedio;
    bool activo;
};

void actualizarPromedio(struct Estudiante *e, float nuevoPromedio) {
    if (nuevoPromedio >= 0.0 && nuevoPromedio <= 10.0) {
        e->promedio = nuevoPromedio;
    } else {
        e->promedio = 0.0;
    }
}

void mostrarInformacionCompleta(struct Estudiante e) {
    printf("\n----------------------------------");
    printf("\nNombre: %s", e.nombre);
    printf("\nCodigo: %s", e.codigo);
    printf("\nEdad: %d", e.edad);
    printf("\nPromedio: %.2f", e.promedio);
    printf("\nEstado: %s", e.activo ? "Activo" : "Inactivo");
    printf("\n----------------------------------\n");
}

int main() {
    struct Estudiante lista[50];
    struct Estudiante nuevo;
    int totalEstudiantes = 0;
    int opcion = 0;
    char codigoBusqueda[20];
    float prom;
    bool encontrado;

    do {
        printf("\n=== MENU ===");
        printf("\n1) Agregar estudiante");
        printf("\n2) Mostrar estudiante");
        printf("\n3) Mostrar todos");
        printf("\n4) Salir");
        printf("\nOpcion: ");
        scanf("%d", &opcion);
        getchar();

        if (opcion == 1) {
            if (totalEstudiantes < 50) {
                printf("Nombre: ");
                fgets(nuevo.nombre, 100, stdin);
                nuevo.nombre[strcspn(nuevo.nombre, "\n")] = 0;

                printf("Codigo: ");
                scanf("%s", nuevo.codigo);

                printf("Edad: ");
                scanf("%d", &nuevo.edad);

                printf("Promedio: ");
                scanf("%f", &prom);
                actualizarPromedio(&nuevo, prom);

                nuevo.activo = true;
                lista[totalEstudiantes] = nuevo;
                totalEstudiantes++;
                printf("Estudiante agregado.\n");
            } else {
                printf("Lista llena.\n");
            }
        } 
        else if (opcion == 2) {
            printf("Codigo a buscar: ");
            scanf("%s", codigoBusqueda);
            encontrado = false;

            for (int i = 0; i < totalEstudiantes; i++) {
                if (strcmp(lista[i].codigo, codigoBusqueda) == 0) {
                    mostrarInformacionCompleta(lista[i]);
                    encontrado = true;
                    break;
                }
            }

            if (!encontrado) {
                printf("Estudiante no encontrado.\n");
            }
        } 
        else if (opcion == 3) {
            if (totalEstudiantes == 0) {
                printf("No hay estudiantes.\n");
            } else {
                for (int i = 0; i < totalEstudiantes; i++) {
                    mostrarInformacionCompleta(lista[i]);
                }
            }
        } 
        else if (opcion == 4) {
            printf("Saliendo...\n");
        } 
        else {
            printf("Opcion invalida.\n");
        }

    } while (opcion != 4);

    return 0;
}