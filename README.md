# Proyecto: Autómata de Pila — Validación de Etiquetas HTML/XML (Repositorio LENGUAJES_FORMALES)

Este proyecto implementa un Autómata de Pila (PDA) en C para validar que las etiquetas de tipo HTML/XML (`<a>`, `<b>`, `<c>`) estén correctamente balanceadas y anidadas.

## Requisitos
- Compilador GCC (MinGW en Windows o GCC en Linux/Mac).
- Terminal o consola de comandos.

## Compilación

Para compilar el código fuente, abre la terminal en la raíz de este proyecto y ejecuta:

```bash
gcc -o pda_html src/main.c -Wall -Wextra
```

Esto generará el ejecutable `pda_html` (o `pda_html.exe` en Windows).

## Ejecución

Ejecuta el programa compilado:

```bash
./pda_html
```

Aparecerá un menú interactivo con las siguientes opciones:

1. **Ingresar cadena por teclado**: Permite escribir una cadena de etiquetas manualmente (ejemplo: `<a><b></b></a>`).
2. **Leer cadenas desde archivo**: Permite cargar un archivo de texto donde cada línea es una cadena a procesar. Se incluye el archivo `test_cases.txt` para este propósito.
3. **Salir**: Termina la ejecución.

### Ejecución con archivo de pruebas
Para ejecutar las pruebas automatizadas, selecciona la opción `2` e ingresa `test_cases.txt` cuando el programa te solicite el nombre del archivo.

## Estructura del Repositorio
- `src/main.c`: Código fuente del simulador de autómata de pila.
- `pruebas_casos.txt`: Archivo con más de 20 casos de prueba (aceptados y rechazados).
- `reporte.md`: Reporte del proyecto detallando lenguaje, gramática, transiciones y más.
