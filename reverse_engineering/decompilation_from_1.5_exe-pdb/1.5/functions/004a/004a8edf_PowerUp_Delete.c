/*
 * Entry: 004a8edf
 * Name: PowerUp_Delete
 * Namespace: Global
 * Signature: void PowerUp_Delete(VEHICLE * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl PowerUp_Delete(VEHICLE *param_1)

{
  undefined4 *puVar1;
  
  puVar1 = param_1->subclass;
  if (puVar1 != (undefined4 *)0x0) {
    (**(code **)*puVar1)(1);
  }
  param_1->subclass = (void *)0x0;
  delete_vehicle(param_1);
  return;
}
