/*
 * Entry: 004ec4ab
 * Name: obj_heap_init
 * Namespace: Global
 * Signature: void obj_heap_init(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl obj_heap_init(void)

{
  free_head = (_OBJ76 *)0x0;
  hObjHeap = (void *)0x1;
  hClassHeap = (void *)0x1;
  obj_seq_no = 1;
  return;
}
