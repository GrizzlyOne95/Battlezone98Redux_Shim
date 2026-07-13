/*
 * Entry: 00474a75
 * Name: InitCollisions
 * Namespace: Global
 * Signature: void InitCollisions(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl InitCollisions(void)

{
  DynamicEnts = (wrap_struct *)0x0;
  StaticEnts = (wrap_struct *)0x0;
  currentHead = (wrap_struct **)0x0;
  currentWrap = (wrap_struct *)0x0;
  reg_add_ent_func(AddCollisionEntity);
  reg_del_ent_func(DeleteCollisionEntity);
  Cgeom_Init();
  InitFloors();
  return;
}
