/*
 * Entry: 004e9a80
 * Name: ClassAllocateDamage
 * Namespace: Global
 * Signature: int ClassAllocateDamage(_OBJ76 * param_1, DAMAGE * param_2, VECTOR_3D * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl ClassAllocateDamage(_OBJ76 *param_1,DAMAGE *param_2,VECTOR_3D *param_3)

{
  int iVar1;
  OBJECT_CLASS_T unaff_ESI;
  
  iVar1 = ClassIDtoIndex(unaff_ESI);
  if (funk[iVar1].damage_alloc_fn != (_func___cdecl_int__OBJ76_ptr_DAMAGE_ptr_VECTOR_3D_ptr *)0x0) {
    iVar1 = (*funk[iVar1].damage_alloc_fn)(param_1,param_2,param_3);
    return iVar1;
  }
  return 0;
}
