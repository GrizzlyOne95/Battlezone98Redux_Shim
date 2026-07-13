/*
 * Entry: 00482a78
 * Name: Building_Delete
 * Namespace: Global
 * Signature: void Building_Delete(void * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Building_Delete(void *param_1)

{
  if (*(undefined4 **)param_1 != (undefined4 *)0x0) {
    (**(code **)**(undefined4 **)param_1)(1);
  }
  operator_delete(param_1);
  terrainChanged = 1;
  return;
}
