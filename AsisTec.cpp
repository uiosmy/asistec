#include <stdio.h>
#include <string.h>

#define MAX 50

// estructura de estudiante
struct Estudiante {
	int id;
	char nombre[50];
	int asistencia; // 1 = presente, 0 = ausente, -1 = no registro
};


struct Estudiante estudiantes[MAX];
int total = 0;

// archivo

// Guardar datos en archivo
void guardarArchivo() {
	FILE *archivo = fopen("asistencia.dat", "wb");
	
	if (archivo == NULL) {
		printf("Error al guardar archivo\n");
		return;
	}
	
	fwrite(&total, sizeof(int), 1, archivo);
	fwrite(estudiantes, sizeof(struct Estudiante), total, archivo);
	
	fclose(archivo);
}

// Cargar datos desde archivo
void cargarArchivo() {
	FILE *archivo = fopen("asistencia.dat", "rb");
	
	if (archivo == NULL) {
		return; 
	}
	
	fread(&total, sizeof(int), 1, archivo);
	fread(estudiantes, sizeof(struct Estudiante), total, archivo);
	
	fclose(archivo);
}

// funcion

// Registra estudiante
void registrarEstudiante() {
	if (total >= MAX) {
		printf("Limite de estudiantes alcanzado\n");
		return;
	}
	
	int nuevoID;
	
	printf("\nID: ");
	scanf("%d", &nuevoID);
	
	
	for (int i = 0; i < total; i++) {
		if (estudiantes[i].id == nuevoID) {
			printf("Error: ID ya registrado\n");
			return;
		}
	}
	
	estudiantes[total].id = nuevoID;
	
	printf("Nombre: ");
	scanf(" %[^\n]", estudiantes[total].nombre);
	
	estudiantes[total].asistencia = -1;
	
	total++;
	
	guardarArchivo();
	
	printf("Estudiante registrado correctamente\n");
}

// asistencia
void marcarAsistencia() {
	int id, encontrado = 0;
	
	printf("\nID del estudiante: ");
	scanf("%d", &id);
	
	for (int i = 0; i < total; i++) {
		if (estudiantes[i].id == id) {
			
			int opcion;
			
			printf("1. Presente\n0. Ausente\n: ");
			scanf("%d", &opcion);
			
			printf("¿Confirmar cambio? (1=Si / 0=No): ");
			int confirm;
			scanf("%d", &confirm);
			
			if (confirm == 1) {
				estudiantes[i].asistencia = opcion;
				guardarArchivo();
				printf("Asistencia registrada\n");
			} else {
				printf("Operacion cancelada\n");
			}
			
			encontrado = 1;
			break;
		}
	}
	
	if (!encontrado) {
		printf("Estudiante no encontrado\n");
	}
}

// lista
void mostrar() {
	printf("\n--- LISTA DE ASISTENCIA ---\n");
	
	if (total == 0) {
		printf("No hay estudiantes registrados\n");
		return;
	}
	
	for (int i = 0; i < total; i++) {
		printf("[%d] %s - ", estudiantes[i].id, estudiantes[i].nombre);
		
		if (estudiantes[i].asistencia == 1)
			printf("Presente\n");
		else if (estudiantes[i].asistencia == 0)
			printf("Ausente\n");
		else
			printf("Sin registrar\n");
	}
}

// Reinicio de asistencia
void reiniciarAsistencia() {
	for (int i = 0; i < total; i++) {
		estudiantes[i].asistencia = -1;
	}
	
	guardarArchivo();
	
	printf("Todas las asistencias han sido reiniciadas\n");
}



int main() {
	int opcion;
	
	cargarArchivo(); // Cargar datos al iniciar
	
	do {
		printf("\n--- MENU ---\n");
		printf("1. Registrar estudiante\n");
		printf("2. Marcar asistencia\n");
		printf("3. Mostrar lista\n");
		printf("4. Reiniciar asistencias\n");
		printf("5. Salir\n");
		printf("Opcion: ");
		scanf("%d", &opcion);
		
		switch (opcion) {
		case 1:
			registrarEstudiante();
			break;
		case 2:
			marcarAsistencia();
			break;
		case 3:
			mostrar();
			break;
		case 4:
			reiniciarAsistencia();
			break;
		case 5:
			printf("Saliendo...\n");
			break;
		default:
			printf("Opcion invalida\n");
		}
		
	} while (opcion != 5);
	
	return 0;
}
