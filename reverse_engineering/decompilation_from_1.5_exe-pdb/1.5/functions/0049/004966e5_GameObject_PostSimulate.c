/*
 * Entry: 004966e5
 * Name: GameObject_PostSimulate
 * Namespace: Global
 * Signature: void GameObject_PostSimulate(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl GameObject_PostSimulate(_OBJ76 *param_1)

{
  int iVar1;
  int *piVar2;
  float fVar3;
  
  if (param_1 == (_OBJ76 *)0x0) {
    piVar2 = (int *)0x0;
  }
  else {
    piVar2 = param_1->gameObj;
  }
  if (piVar2 != (int *)0x0) {
    iVar1 = *piVar2;
    fVar3 = TimeStep();
    (**(code **)(iVar1 + 0x40))(fVar3);
  }
  return;
}
