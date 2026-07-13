/*
 * Entry: 00486a6e
 * Name: Craft_ControlHeading
 * Namespace: Global
 * Signature: void Craft_ControlHeading(_OBJ76 * param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Craft_ControlHeading(_OBJ76 *param_1,float param_2)

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
