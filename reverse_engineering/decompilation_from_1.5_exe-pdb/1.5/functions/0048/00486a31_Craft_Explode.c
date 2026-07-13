/*
 * Entry: 00486a31
 * Name: Craft_Explode
 * Namespace: Global
 * Signature: void Craft_Explode(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Craft_Explode(_OBJ76 *param_1)

{
  void *pvVar1;
  
  if (param_1 == (_OBJ76 *)0x0) {
    pvVar1 = (void *)0x0;
  }
  else {
    pvVar1 = param_1->gameObj;
  }
                    /* WARNING: Could not recover jumptable at 0x00486a48. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)((int)pvVar1 + 0x20) + 0x14))();
  return;
}
