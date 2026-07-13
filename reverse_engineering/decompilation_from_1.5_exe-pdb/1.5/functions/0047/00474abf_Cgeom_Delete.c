/*
 * Entry: 00474abf
 * Name: Cgeom_Delete
 * Namespace: Global
 * Signature: void Cgeom_Delete(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Cgeom_Delete(_OBJ76 *param_1)

{
  void *_Memory;
  
  _Memory = param_1->clsnInfo;
  if (_Memory != (void *)0x0) {
    free(_Memory);
    param_1->clsnInfo = (void *)0x0;
  }
  return;
}
