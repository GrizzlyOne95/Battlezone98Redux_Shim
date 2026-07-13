/*
 * Entry: 0050dd04
 * Name: Blobs_Shutdown
 * Namespace: Global
 * Signature: void Blobs_Shutdown(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Blobs_Shutdown(void)

{
  _coloring_point *p_Var1;
  _coloring_point *_Memory;
  
  _Memory = point_head;
  if (point_head != (_coloring_point *)0x0) {
    do {
      p_Var1 = _Memory->next;
      free(_Memory);
      point_count = point_count + -1;
      _Memory = p_Var1;
    } while (p_Var1 != (_coloring_point *)0x0);
    point_head = (_coloring_point *)0x0;
  }
  return;
}
