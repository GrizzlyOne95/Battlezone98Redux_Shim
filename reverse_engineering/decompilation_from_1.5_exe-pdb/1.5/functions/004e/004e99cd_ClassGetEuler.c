/*
 * Entry: 004e99cd
 * Name: ClassGetEuler
 * Namespace: Global
 * Signature: EULER * ClassGetEuler(EULER * __return_storage_ptr__, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

EULER * __cdecl ClassGetEuler(EULER *__return_storage_ptr__,_OBJ76 *param_1)

{
  int iVar1;
  EULER *pEVar2;
  OBJECT_CLASS_T unaff_ESI;
  EULER *pEVar3;
  EULER local_4c;
  
  iVar1 = ClassIDtoIndex(unaff_ESI);
  if (funk[iVar1].euler_fn == (_func___cdecl_EULER__OBJ76_ptr *)0x0) {
    InitEuler(__return_storage_ptr__);
  }
  else {
    pEVar2 = (*funk[iVar1].euler_fn)(&local_4c,param_1);
    pEVar3 = __return_storage_ptr__;
    for (iVar1 = 0x12; iVar1 != 0; iVar1 = iVar1 + -1) {
      pEVar3->mass = pEVar2->mass;
      pEVar2 = (EULER *)&pEVar2->mass_inv;
      pEVar3 = (EULER *)&pEVar3->mass_inv;
    }
  }
  return __return_storage_ptr__;
}
