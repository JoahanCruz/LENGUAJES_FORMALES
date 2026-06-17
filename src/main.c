#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STACK_SIZE 1000
#define MAX_INPUT_SIZE 2000
#define MAX_TOKEN_SIZE 10

// Estructura de la Pila
typedef struct {
    char items[MAX_STACK_SIZE];
    int top;
} Stack;

void initStack(Stack *s) {
    s->top = -1;
    // Apilamos el símbolo inicial Z0 (representado por 'Z')
    s->items[++(s->top)] = 'Z';
}

bool isFull(Stack *s) {
    return s->top == MAX_STACK_SIZE - 1;
}

bool isEmpty(Stack *s) {
    return s->top == -1;
}

void push(Stack *s, char item) {
    if (isFull(s)) {
        printf("Error: Pila llena.\n");
        return;
    }
    s->items[++(s->top)] = item;
}

char pop(Stack *s) {
    if (isEmpty(s)) {
        return '\0';
    }
    return s->items[(s->top)--];
}

char peek(Stack *s) {
    if (isEmpty(s)) {
        return '\0';
    }
    return s->items[s->top];
}

// Función auxiliar para imprimir el estado de la pila
void printStack(Stack *s, char *buffer) {
    buffer[0] = '\0';
    for (int i = 0; i <= s->top; i++) {
        char temp[10];
        if (s->items[i] == 'Z') {
            sprintf(temp, "Z0 ");
        } else {
            sprintf(temp, "%c ", s->items[i]);
        }
        strcat(buffer, temp);
    }
}

// Procesar una cadena
void processString(const char *inputStr) {
    Stack pila;
    initStack(&pila);
    
    printf("\nProcesando cadena: %s\n", inputStr);
    printf("%-5s | %-15s | %-20s | %-20s\n", "Paso", "Entrada leida", "Accion", "Pila");
    printf("-----------------------------------------------------------------------\n");
    
    int paso = 1;
    int len = strlen(inputStr);
    int i = 0;
    bool rejected = false;
    
    char stackBuf[MAX_STACK_SIZE * 3];
    
    while (i < len && !rejected) {
        // Buscar el inicio de una etiqueta
        if (inputStr[i] == '<') {
            int j = i;
            while (j < len && inputStr[j] != '>') {
                j++;
            }
            if (j == len) {
                // Etiqueta mal formada
                rejected = true;
                break;
            }
            
            // Extraer la etiqueta
            int tagLen = j - i + 1;
            char tag[MAX_TOKEN_SIZE];
            if (tagLen >= MAX_TOKEN_SIZE) tagLen = MAX_TOKEN_SIZE - 1;
            strncpy(tag, &inputStr[i], tagLen);
            tag[tagLen] = '\0';
            
            // Avanzar el indice
            i = j + 1;
            
            char accion[30] = "";
            
            // Analizar la etiqueta
            if (strcmp(tag, "<a>") == 0) {
                push(&pila, 'A');
                strcpy(accion, "Apilar A");
            } else if (strcmp(tag, "<b>") == 0) {
                push(&pila, 'B');
                strcpy(accion, "Apilar B");
            } else if (strcmp(tag, "<c>") == 0) {
                push(&pila, 'C');
                strcpy(accion, "Apilar C");
            } else if (strcmp(tag, "</a>") == 0) {
                if (peek(&pila) == 'A') {
                    pop(&pila);
                    strcpy(accion, "Desapilar A");
                } else {
                    strcpy(accion, "Error: cima no es A");
                    rejected = true;
                }
            } else if (strcmp(tag, "</b>") == 0) {
                if (peek(&pila) == 'B') {
                    pop(&pila);
                    strcpy(accion, "Desapilar B");
                } else {
                    strcpy(accion, "Error: cima no es B");
                    rejected = true;
                }
            } else if (strcmp(tag, "</c>") == 0) {
                if (peek(&pila) == 'C') {
                    pop(&pila);
                    strcpy(accion, "Desapilar C");
                } else {
                    strcpy(accion, "Error: cima no es C");
                    rejected = true;
                }
            } else {
                // Etiqueta desconocida o texto suelto
                strcpy(accion, "Etiqueta invalida");
                rejected = true;
            }
            
            printStack(&pila, stackBuf);
            printf("%-5d | %-15s | %-20s | %-20s\n", paso++, tag, accion, stackBuf);
        } else {
            // Ignorar espacios en blanco o caracteres fuera de etiquetas
            if (inputStr[i] != ' ' && inputStr[i] != '\n' && inputStr[i] != '\r' && inputStr[i] != '\t') {
                rejected = true;
                break;
            }
            i++;
        }
    }
    
    // Verificacion final
    if (!rejected && peek(&pila) == 'Z' && pila.top == 0) {
        char finalAcc[30] = "Aceptar Z0";
        printStack(&pila, stackBuf);
        printf("%-5d | %-15s | %-20s | %-20s\n", paso, "Fin de cadena", finalAcc, stackBuf);
        printf("\n>>> RESULTADO: Cadena aceptada <<<\n\n");
    } else {
        printf("\n>>> RESULTADO: Cadena rechazada <<<\n\n");
    }
}

// Opcion 1: Leer desde teclado
void optionKeyboard() {
    char input[MAX_INPUT_SIZE];
    printf("\nIngrese la cadena de etiquetas (ej. <a><b></b></a>):\n");
    // Limpiar el buffer si es necesario
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
    
    if (fgets(input, sizeof(input), stdin) != NULL) {
        // Remover salto de linea
        input[strcspn(input, "\n")] = 0;
        processString(input);
    }
}

// Opcion 2: Leer desde archivo
void optionFile() {
    char filename[256];
    printf("\nIngrese el nombre del archivo (ej. test_cases.txt):\n");
    scanf("%255s", filename);
    
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: No se pudo abrir el archivo %s\n", filename);
        return;
    }
    
    char line[MAX_INPUT_SIZE];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;
        if (strlen(line) > 0 && line[0] != '#') { // Ignorar comentarios
            processString(line);
        }
    }
    
    fclose(file);
}

// Menu interactivo
int main() {
    int choice = 0;
    
    printf("==================================================\n");
    printf("   Proyecto Autómata de Pila - Validacion HTML    \n");
    printf("==================================================\n");
    
    while (1) {
        printf("Opciones:\n");
        printf("1. Ingresar cadena por teclado\n");
        printf("2. Leer cadenas desde archivo\n");
        printf("3. Salir\n");
        printf("Seleccione una opcion: ");
        
        if (scanf("%d", &choice) != 1) {
            // Manejar entrada no numerica
            int c;
            while ((c = getchar()) != '\n' && c != EOF) { }
            choice = 0;
        }
        
        switch (choice) {
            case 1:
                optionKeyboard();
                break;
            case 2:
                optionFile();
                break;
            case 3:
                printf("Saliendo del programa...\n");
                return 0;
            default:
                printf("Opcion no valida.\n\n");
        }
    }
    
    return 0;
}
