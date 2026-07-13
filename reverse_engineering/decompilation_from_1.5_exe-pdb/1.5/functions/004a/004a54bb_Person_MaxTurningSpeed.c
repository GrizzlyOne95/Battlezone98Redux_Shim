/*
 * Entry: 004a54bb
 * Name: Person_MaxTurningSpeed
 * Namespace: Global
 * Signature: float Person_MaxTurningSpeed(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl Person_MaxTurningSpeed(_OBJ76 *param_1)

{
  int *piVar1;
  float10 fVar2;
  
  if (param_1 == (_OBJ76 *)0x0) {
    piVar1 = (int *)0x0;
  }
  else {
    piVar1 = param_1->gameObj;
  }
                    /* WARNING: Could not recover jumptable at 0x004a54cf. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  fVar2 = (float10)(**(code **)(*piVar1 + 0x8c))();
  return (float)fVar2;
}
