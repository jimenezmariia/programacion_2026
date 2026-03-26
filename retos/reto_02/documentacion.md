# 📖 Documentación Técnica — Cliente de Terminal (C++)

## 1. Resumen General
`gpt_terminal` es una herramienta ligera de línea de comandos desarrollada en **C++17**. Permite interactuar con modelos de lenguaje (LLM) a través de la API de **Groq**, enviando prompts y recibiendo respuestas directamente en la terminal.

**Objetivos:**
- Uso de `libcurl` para comunicación HTTP segura.
- Configuración mediante archivos `.env` para proteger credenciales.
- Compatibilidad total con **Windows (MSYS2/MINGW64)**.

---

## 2. Estructura del Proyecto
```text
reto_02/
├── .env               # Configuración (API Key y URL)
├── .gitignore         # Excluye archivos sensibles de Git
├── gpt_terminal.exe   # Binario generado (Windows)
├── src/
│   └── main.cpp       # Código fuente único
└── documentacion.md   # Este archivo
```

---

## 3. Requisitos de Ejecución (Windows)
Para compilar y ejecutar este proyecto en Windows, se requiere **MSYS2** con los siguientes paquetes instalados:
- `mingw-w64-x86_64-gcc` (Compilador G++)
- `mingw-w64-x86_64-curl` (Librería de red)

**Comando de compilación:**
```bash
g++ -std=c++17 src/main.cpp -lcurl -o gpt_terminal.exe
```

---

## 4. Configuración del Entorno (`.env`)
El programa carga automáticamente las variables desde un archivo `.env` en la raíz. 

**Contenido del archivo:**
```text
OPENAI_API_KEY=gsk_tu_llave_de_groq_aqui
OPENAI_BASE_URL=[https://api.groq.com/openai](https://api.groq.com/openai)
```
*Nota: No incluyas comillas ni espacios alrededor del signo `=`.*

---

## 5. Arquitectura del Código
El código utiliza un namespace anónimo para encapsular la lógica interna:

- **`load_dotenv()`**: Parser minimalista que define variables de entorno usando `_putenv_s` (específico para Windows).
- **`escape_json()` / `unescape_json()`**: Manejo manual de caracteres especiales (comillas, saltos de línea) para construir y leer el JSON sin librerías externas.
- **`get_content()`**: Extrae la respuesta del modelo del cuerpo JSON mediante expresiones regulares (`std::regex`).
- **`do_request()`**: Orquestador de la conexión HTTP. Configura los headers de autenticación (Bearer Token) y ejecuta el método POST.

---

## 6. Uso de la Aplicación
El programa admite dos modos de operación:

**A. Modo Directo (Argumentos):**
```bash
./gpt_terminal.exe --model llama-3.1-8b-instant --prompt "¿Qué es el polimorfismo?"
```

**B. Modo Interactivo:**
```bash
./gpt_terminal.exe
# El programa solicitará la entrada del usuario manualmente.
```

---

## 7. Notas de Seguridad
1. **Protección de Credenciales:** La API Key nunca se escribe directamente en el código fuente (hardcoding). Se recupera desde el entorno en tiempo de ejecución.
2. **Exclusión en Git:** El archivo `.env` está incluido en el `.gitignore` para evitar filtraciones accidentales en repositorios públicos.
3. **Salida Segura:** El programa no imprime la API Key en consola, incluso en caso de error HTTP.

---

## 8. Limitaciones
- **Single-turn:** El programa no mantiene memoria de mensajes anteriores (sin historial).
- **JSON Parsing:** Utiliza un método de extracción basado en Regex; estructuras JSON muy complejas podrían requerir un parser dedicado (como `nlohmann/json`) en versiones futuras.
