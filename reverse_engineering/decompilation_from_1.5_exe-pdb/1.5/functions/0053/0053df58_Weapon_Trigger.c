/*
 * Entry: 0053df58
 * Name: Weapon_Trigger
 * Namespace: Global
 * Signature: void Weapon_Trigger(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Weapon_Trigger(_OBJ76 *param_1)

{
  int *piVar1;
  
  if (param_1 == (_OBJ76 *)0x0) {
    piVar1 = (int *)0x0;
  }
  else {
    piVar1 = param_1->class_ptr;
  }
                    /* WARNING: Could not recover jumptable at 0x0053df6c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*piVar1 + 8))();
  return;
}
