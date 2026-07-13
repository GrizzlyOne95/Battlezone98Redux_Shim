/*
 * Entry: 004ec4c5
 * Name: obj_heap_destroy
 * Namespace: Global
 * Signature: void obj_heap_destroy(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl obj_heap_destroy(void)

{
  _OBJ76 *p_Var1;
  _OBJ76 *_Memory;
  
  _Memory = free_head;
  if (free_head != (_OBJ76 *)0x0) {
    do {
      p_Var1 = _Memory->sibling;
      free(_Memory);
      _Memory = p_Var1;
    } while (p_Var1 != (_OBJ76 *)0x0);
    free_head = (_OBJ76 *)0x0;
  }
  return;
}
