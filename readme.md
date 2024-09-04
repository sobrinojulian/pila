# pila
## uso
`gcc pila.c pruebas_pila.c testing.c -o pruebas_pila`

## temas
- `void**`
- `malloc` `realloc` `free`
- `void*`
- `pila_t*`
- `&`
```c
pila_t* pila = pila_crear();
char elem = 'a';
pila_apilar(pila, &elem);
void* tope_anterior = pila_ver_tope(pila);
```
