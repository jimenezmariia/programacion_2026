# Cliente de Terminal LLM (C++)

Aplicación de terminal en C++ que conecta con modelos de lenguaje (como Llama 3) mediante la API de Groq (compatible con el formato de OpenAI). Esta versión ha sido ajustada para funcionar en Windows.

## Requisitos

- **Windows** (usando MSYS2 MINGW64)
- **Compilador G++** (instalado vía `pacman -S mingw-w64-x86_64-gcc`)
- **Biblioteca libcurl** (instalada vía `pacman -S mingw-w64-x86_64-curl`)
- **API Key de Groq** (obtenida gratis en console.groq.com)

## Compilación (MSYS2 MINGW64)

Navega a la carpeta de tu proyecto y ejecuta:

```bash
g++ -std=c++17 src/main.cpp -lcurl -o gpt_terminal.exe
```

## Configuración

Crea un archivo llamado `.env` en la raíz del proyecto para guardar tu llave y la URL de Groq (esto evita que tu clave se suba a GitHub):

```text
OPENAI_API_KEY=gsk_tu_llave_aqui
OPENAI_BASE_URL=[https://api.groq.com/openai](https://api.groq.com/openai)
```

*Nota: Asegúrate de que el archivo se llame exactamente `.env` y no `env.txt`.*

## Ejecución

### Modo Directo (con argumentos)
Para una respuesta rápida, especifica el modelo y tu pregunta:

```bash
./gpt_terminal.exe --model llama-3.1-8b-instant --prompt "¿Qué es el polimorfismo en C++?"
```

### Modo Interactivo
Si solo ejecutas el programa, este te pedirá que escribas tu pregunta manualmente:

```bash
./gpt_terminal.exe
```

## Notas Técnicas

- **Modelo por defecto:** `llama-3.1-8b-instant` (configurado para Groq).
- **Compatibilidad:** Se utiliza `_putenv_s` para el manejo de variables de entorno en Windows.
- **Seguridad:** El archivo `.env` debe estar incluido en tu `.gitignore` para proteger tu API Key.
- **Parsing:** La respuesta se extrae mediante expresiones regulares (`std::regex`) del JSON devuelto por la API.

---
*Proyecto desarrollado como parte del Reto 02 - Programación 2026.*
