/*
 * Entry: 00496710
 * Name: GameObject_CallAI
 * Namespace: Global
 * Signature: void GameObject_CallAI(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl GameObject_CallAI(_OBJ76 *param_1)

{
  void *pvVar1;
  
  if (param_1 == (_OBJ76 *)0x0) {
    pvVar1 = (void *)0x0;
  }
  else {
    pvVar1 = param_1->gameObj;
  }
  if ((pvVar1 != (void *)0x0) && (*(int **)((int)pvVar1 + 0xf0) != (int *)0x0)) {
                    /* WARNING: Could not recover jumptable at 0x00496734. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(**(int **)((int)pvVar1 + 0xf0) + 0x1c))();
    return;
  }
  return;
}
