/*
 * Entry: 004a54d5
 * Name: Person_ControlForward
 * Namespace: Global
 * Signature: int Person_ControlForward(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Person_ControlForward(_OBJ76 *param_1)

{
  uint uVar1;
  int *piVar2;
  
  if (param_1 == (_OBJ76 *)0x0) {
    piVar2 = (int *)0x0;
  }
  else {
    piVar2 = param_1->gameObj;
  }
  uVar1 = (**(code **)(*piVar2 + 0x90))();
  return uVar1 & 0xff;
}
