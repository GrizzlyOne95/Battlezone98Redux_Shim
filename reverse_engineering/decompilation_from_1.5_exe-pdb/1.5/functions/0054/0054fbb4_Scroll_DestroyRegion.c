/*
 * Entry: 0054fbb4
 * Name: Scroll_DestroyRegion
 * Namespace: Global
 * Signature: void Scroll_DestroyRegion(void * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Scroll_DestroyRegion(void *param_1)

{
  void *_Memory;
  
  _Memory = *(void **)((int)param_1 + 8);
  free(*(void **)((int)_Memory + 0x28));
  free(_Memory);
  DeleteWrapper(&region_list,param_1);
  return;
}
