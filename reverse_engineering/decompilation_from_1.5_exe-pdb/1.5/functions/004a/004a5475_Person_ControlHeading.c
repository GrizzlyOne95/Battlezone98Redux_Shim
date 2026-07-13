/*
 * Entry: 004a5475
 * Name: Person_ControlHeading
 * Namespace: Global
 * Signature: void Person_ControlHeading(_OBJ76 * param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Person_ControlHeading(_OBJ76 *param_1,float param_2)

{
  int *piVar1;
  SINCOS SVar2;
  
  SVar2 = SinCos(param_2);
  if (param_1 == (_OBJ76 *)0x0) {
    piVar1 = (int *)0x0;
  }
  else {
    piVar1 = param_1->gameObj;
  }
  (**(code **)(*piVar1 + 0x88))(SVar2);
  return;
}
