/*
 * Entry: 004a52f1
 * Name: Person_Delete
 * Namespace: Global
 * Signature: void Person_Delete(VEHICLE * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Person_Delete(VEHICLE *param_1)

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
