# Simple wasm_demo

How to run


```yarn install```

```yarn run start```

The public file canvas.js was generated using emscripten (https://emscripten.org/)
Make sure to install the latest version of 1.38.0 if you'd like to modify the recompile the C

Recompiling C to update canvas.js:

`emcc lib/canvas.c -s WASM=1 -s EXPORTED_FUNCTIONS="['_main', '_getCircles']" -o public/canvas.js`
