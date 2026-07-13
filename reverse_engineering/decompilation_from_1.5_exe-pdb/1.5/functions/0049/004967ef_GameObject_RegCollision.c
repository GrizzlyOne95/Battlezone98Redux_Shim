/*
 * Entry: 004967ef
 * Name: GameObject_RegCollision
 * Namespace: Global
 * Signature: int GameObject_RegCollision(_OBJ76 * param_1, _OBJ76 * param_2, CLSN_INFO * param_3, CLSN_INFO * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
GameObject_RegCollision(_OBJ76 *param_1,_OBJ76 *param_2,CLSN_INFO *param_3,CLSN_INFO *param_4)

{
  uint uVar1;
  int *piVar2;
  
  if (param_1 == (_OBJ76 *)0x0) {
    piVar2 = (int *)0x0;
  }
  else {
    piVar2 = param_1->gameObj;
  }
  uVar1 = (**(code **)(*piVar2 + 0x48))(param_2,param_3,param_4);
  return uVar1 & 0xff;
}
