/*
 * Entry: 004a5452
 * Name: Person_ControlSpeed
 * Namespace: Global
 * Signature: void Person_ControlSpeed(_OBJ76 * param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Person_ControlSpeed(_OBJ76 *param_1,float param_2)

{
  int *piVar1;
  
  if (param_1 == (_OBJ76 *)0x0) {
    piVar1 = (int *)0x0;
  }
  else {
    piVar1 = param_1->gameObj;
  }
  (**(code **)(*piVar1 + 0x84))(param_2);
  return;
}
