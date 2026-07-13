/*
 * Entry: 00496361
 * Name: GameObject_GetEuler
 * Namespace: Global
 * Signature: EULER * GameObject_GetEuler(EULER * __return_storage_ptr__, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

EULER * __cdecl GameObject_GetEuler(EULER *__return_storage_ptr__,_OBJ76 *param_1)

{
  void *pvVar1;
  int iVar2;
  float *pfVar3;
  EULER *pEVar4;
  
  if (param_1 == (_OBJ76 *)0x0) {
    pvVar1 = (void *)0x0;
  }
  else {
    pvVar1 = param_1->gameObj;
  }
  pfVar3 = (float *)((int)pvVar1 + 0x108);
  pEVar4 = __return_storage_ptr__;
  for (iVar2 = 0x12; iVar2 != 0; iVar2 = iVar2 + -1) {
    pEVar4->mass = *pfVar3;
    pfVar3 = pfVar3 + 1;
    pEVar4 = (EULER *)&pEVar4->mass_inv;
  }
  return __return_storage_ptr__;
}
