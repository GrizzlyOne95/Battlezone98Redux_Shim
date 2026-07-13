/*
 * Entry: 00482d82
 * Name: Building_Remove
 * Namespace: Global
 * Signature: void Building_Remove(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Building_Remove(_OBJ76 *param_1)

{
  void *pvVar1;
  
  if (param_1 == (_OBJ76 *)0x0) {
    pvVar1 = (void *)0x0;
  }
  else {
    pvVar1 = param_1->gameObj;
  }
                    /* WARNING: Could not recover jumptable at 0x00482d99. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)((int)pvVar1 + 0x20) + 0x10))();
  return;
}
