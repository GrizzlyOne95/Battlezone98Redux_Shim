/*
 * Entry: 004e9a15
 * Name: ClassRegisterClsn
 * Namespace: Global
 * Signature: int ClassRegisterClsn(_OBJ76 * param_1, _OBJ76 * param_2, CLSN_INFO * param_3, CLSN_INFO * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl ClassRegisterClsn(_OBJ76 *param_1,_OBJ76 *param_2,CLSN_INFO *param_3,CLSN_INFO *param_4)

{
  int iVar1;
  int iVar2;
  OBJECT_CLASS_T unaff_EDI;
  
  iVar2 = 0;
  iVar1 = ClassIDtoIndex(unaff_EDI);
  if (funk[iVar1].reg_clsn_fn !=
      (_func___cdecl_int__OBJ76_ptr__OBJ76_ptr_CLSN_INFO_ptr_CLSN_INFO_ptr *)0x0) {
    iVar1 = (*funk[iVar1].reg_clsn_fn)(param_1,param_2,param_3,param_4);
    if (iVar1 != 0) {
      iVar2 = 1;
    }
  }
  iVar1 = ClassIDtoIndex(unaff_EDI);
  if (funk[iVar1].reg_clsn_fn !=
      (_func___cdecl_int__OBJ76_ptr__OBJ76_ptr_CLSN_INFO_ptr_CLSN_INFO_ptr *)0x0) {
    iVar1 = (*funk[iVar1].reg_clsn_fn)(param_2,param_1,param_4,param_3);
    if (iVar1 != 0) {
      iVar2 = 1;
    }
  }
  return iVar2;
}
