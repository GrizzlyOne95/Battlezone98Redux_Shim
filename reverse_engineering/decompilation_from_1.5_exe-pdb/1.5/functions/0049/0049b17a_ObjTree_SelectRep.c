/*
 * Entry: 0049b17a
 * Name: ObjTree_SelectRep
 * Namespace: Global
 * Signature: int ObjTree_SelectRep(_OBJ76 * param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl ObjTree_SelectRep(_OBJ76 *param_1,long param_2)

{
  uint uVar1;
  int iVar2;
  _OBJ76 *p_Var3;
  
  if (param_1 == (_OBJ76 *)0x0) {
    uVar1 = 0;
  }
  else {
    iVar2 = GeoCache_SelectRep(param_1,param_2);
    uVar1 = (uint)(iVar2 != 0);
    for (p_Var3 = param_1->child; p_Var3 != (_OBJ76 *)0x0; p_Var3 = p_Var3->sibling) {
      iVar2 = ObjTree_SelectRep(p_Var3,param_2);
      if (iVar2 != 0) {
        uVar1 = 1;
      }
    }
  }
  return uVar1;
}
