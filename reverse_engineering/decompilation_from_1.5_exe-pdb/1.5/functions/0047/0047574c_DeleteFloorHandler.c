/*
 * Entry: 0047574c
 * Name: DeleteFloorHandler
 * Namespace: Global
 * Signature: void DeleteFloorHandler(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DeleteFloorHandler(void)

{
  while (FloorList != (wrap_struct *)0x0) {
    Floor_ClearEntity(FloorList->ptr);
    DeleteWrapper(&FloorList,FloorList);
  }
  return;
}
