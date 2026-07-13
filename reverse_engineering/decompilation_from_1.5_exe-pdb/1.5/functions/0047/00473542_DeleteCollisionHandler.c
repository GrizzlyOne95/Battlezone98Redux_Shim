/*
 * Entry: 00473542
 * Name: DeleteCollisionHandler
 * Namespace: Global
 * Signature: void DeleteCollisionHandler(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DeleteCollisionHandler(void)

{
  while (DynamicEnts != (wrap_struct *)0x0) {
    DeleteWrapper(&DynamicEnts,DynamicEnts);
  }
  while (StaticEnts != (wrap_struct *)0x0) {
    DeleteWrapper(&StaticEnts,StaticEnts);
  }
  currentHead = (wrap_struct **)0x0;
  currentWrap = (wrap_struct *)0x0;
  DeleteFloorHandler();
  Cgeom_Shutdown();
  return;
}
