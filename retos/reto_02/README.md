# Cliente de Terminal GPT (C++)

Aplicación básica de terminal en C++ que envía un prompt a un modelo GPT mediante API e imprime la respuesta.

## Requisitos

- macOS (o Linux)
- Compilador C++17 (`clang++` en macOS)
- Biblioteca de desarrollo `libcurl`
- API key compatible con OpenAI en `OPENAI_API_KEY`

## Compilación

```bash
cd /Users/victoruccetina/Documents/Code/chatbot
clang++ -std=c++17 src/main.cpp -lcurl -o gpt_terminal
```

## Ejecución

Crea/edita tu archivo local `.env`:

```bash
cd /Users/victoruccetina/Documents/Code/chatbot
cat .env
```

Carga variables desde `.env` en tu sesión actual de `zsh`:

```bash
set -a
source .env
set +a
```

`gpt_terminal` también carga automáticamente `.env` desde el directorio de trabajo actual, por lo que hacer `source` es opcional cuando ejecutas desde la carpeta del proyecto.

Alternativa manual (sin `.env`):

```bash
export OPENAI_API_KEY="your_api_key_here"
```

Opcional: define una URL base compatible alternativa:

```bash
export OPENAI_BASE_URL="https://api.openai.com"
```

Ejecuta con prompt por argumento:

```bash
./gpt_terminal --model gpt-4o-mini --prompt "Escribe un haiku sobre programación"
```

O ejecuta en modo interactivo (te pedirá una línea de prompt):

```bash
./gpt_terminal --model gpt-4o-mini
```

## Notas

- El modelo por defecto es `gpt-4o-mini`.
- Si el parseo falla, el programa imprime la respuesta JSON cruda.
