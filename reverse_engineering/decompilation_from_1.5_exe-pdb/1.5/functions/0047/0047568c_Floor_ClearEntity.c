/*
 * Entry: 0047568c
 * Name: Floor_ClearEntity
 * Namespace: Global
 * Signature: void Floor_ClearEntity(tagENTITY * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Floor_ClearEntity(tagENTITY *param_1)

{
  void *pvVar1;
  void *_Memory;
  
  _Memory = param_1->clsnDetails;
  while (_Memory != (void *)0x0) {
    pvVar1 = *(void **)((int)_Memory + 0x18);
    free(_Memory);
    _Memory = pvVar1;
  }
  param_1->clsnDetails = (void *)0x0;
  return;
}
