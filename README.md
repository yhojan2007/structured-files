# Gestor de Alumnos con Archivos Estructurados e Índices

Este proyecto es una aplicación de escritorio desarrollada en **C++** utilizando **Embarcadero C++Builder** y el framework **VCL (Visual Component Library)**. Su objetivo principal es la gestión de registros de alumnos mediante el uso de **archivos binarios estructurados** y la optimización de búsquedas y ordenamientos a través de **archivos de índice**.

Es un proyecto con fines educativos para la materia de **Estructuras de Archivos** o **Estructura de Datos II**.

---

## 🚀 Características Principales

- **Gestión de Registros (CRUD):** 
  - Adición de alumnos con campos de código, nombre, fecha de nacimiento, y teléfono.
  - Actualización directa de registros existentes en el archivo binario.
- **Borrado Lógico y Físico:**
  - **Borrado Lógico:** Marca los registros inactivos con un carácter especial (`*`) en el campo `marca` sin eliminarlos físicamente del disco.
  - **Borrado Físico:** Limpia el archivo binario copiando solo los registros activos a un archivo temporal y reemplazando el original.
- **Indexación Bidireccional:**
  - **Índice por Código (`Alumnoscod.idx`):** Permite realizar búsquedas binarias rápidas mapeando el código del alumno con su posición física en el archivo (`ref`).
  - **Índice por Nombre (`AlumnosNom.idx`):** Facilita la ordenación y listados alfabéticos.
- **Algoritmo de Búsqueda Binaria:** Búsqueda rápida sobre el archivo de índice por código para ubicar directamente la posición del registro en el archivo de datos principal mediante `seekg`.
- **Ordenamiento Físico de Índices:** Implementación del algoritmo **Selection Sort (Ordenación por Selección)** aplicado directamente sobre el archivo binario de índice por código.
- **Procesamiento y Filtros Especiales:**
  - Conversión masiva de nombres a mayúsculas.
  - Conversión masiva a minúsculas para alumnos nacidos en el mes de abril.
  - Eliminación física masiva de alumnos que contengan más de dos letras 'O' en su nombre.
  - Formateador/Migrador de estructuras antiguas (`RegAlumnoAnt`) a la estructura actualizada (`RegAlumno`).
- **Generación de Reportes:** Exportación de listados en formato estructurado **CSV** (delimitado por comas) para su visualización en Excel o editores de texto.

---

## 📂 Estructura del Proyecto

### Archivos Fuentes
*   [Unit1.h](file:///D:/c++%2012/archibos%20estructurados/Unit1.h): Declaración de la clase `TForm1`, componentes visuales y las estructuras de datos fijas (`#pragma pack(1)`).
*   [Unit1.cpp](file:///D:/c++%2012/archibos%20estructurados/Unit1.cpp): Implementación de toda la lógica de manipulación de archivos binarios (`fstream`), búsquedas, ordenación y eventos de interfaz.
*   [Unit1.dfm](file:///D:/c++%2012/archibos%20estructurados/Unit1.dfm): Archivo de diseño visual del formulario de C++Builder.
*   [Project1.cbproj](file:///D:/c++%2012/archibos%20estructurados/Project1.cbproj): Archivo del proyecto de C++Builder / RAD Studio.
*   [Project1.cpp](file:///D:/c++%2012/archibos%20estructurados/Project1.cpp): Punto de entrada principal de la aplicación.

### Estructuras de Datos Definidas

Para asegurar el tamaño exacto de bytes en disco y evitar el padding del compilador, se utiliza la directiva `#pragma pack(1)`:

```cpp
struct TFecha {
    byte dia;      // 1 byte
    byte mes;      // 1 byte
    Word ano;      // 2 bytes
}; // Total: 4 bytes

struct RegAlumno {
    char marca;        // Marca para borrado lógico (' ' para activo, '*' para borrado)
    Word cod;          // Código único de alumno (2 bytes)
    char nom[30];      // Nombre del alumno (30 bytes)
    TFecha fecha;      // Fecha de nacimiento (4 bytes)
    Cardinal telefono; // Teléfono del alumno (4 bytes)
}; // Total: 41 bytes

struct RegIdxCod {
    Word cod;      // Código del alumno (clave de ordenamiento)
    Cardinal ref;  // Referencia física (byte de inicio del registro en Alumnos.dat)
}; // Estructura del archivo de índice por código
```

---

## 🛠️ Requisitos de Compilación y Ejecución

1. **Entorno:** Embarcadero C++Builder (RAD Studio) versión 10.0 o superior (ej: C++Builder 12 Athens).
2. **Sistema Operativo:** Windows 10 u 11.
3. **Ajuste de Ruta (Importante):** 
   En el método `FormCreate` del archivo `Unit1.cpp`, se define la ruta absoluta del proyecto:
   ```cpp
   ruta = "D:\\c++ 12\\archibos estructurados\\";
   ```
   Si descargas o mueves el proyecto, recuerda actualizar esta variable con la ruta de tu carpeta local antes de compilar.

---

## ⚙️ Guía para Subir a GitHub

Si deseas inicializar el repositorio y subir este código a tu cuenta de GitHub, sigue estos pasos desde la consola de comandos (PowerShell o Git Bash) en la carpeta raíz del proyecto:

1. **Inicializar el repositorio local:**
   ```bash
   git init
   ```

2. **Añadir los archivos al área de preparación:**
   *(El archivo `.gitignore` ya está configurado para omitir archivos compilados e índices locales temporales)*
   ```bash
   git add .
   ```

3. **Realizar el primer commit:**
   ```bash
   git commit -m "Initial commit: Proyecto de Archivos Estructurados con C++ Builder"
   ```

4. **Vincular con tu repositorio remoto de GitHub:**
   *(Reemplaza el enlace por el tuyo propio)*
   ```bash
   git branch -M main
   git remote add origin https://github.com/TU_USUARIO/TU_REPOSITORIO.git
   ```

5. **Subir los cambios:**
   ```bash
   git push -u origin main
   ```
