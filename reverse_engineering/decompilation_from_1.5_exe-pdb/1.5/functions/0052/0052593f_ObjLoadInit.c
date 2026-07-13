/*
 * Entry: 0052593f
 * Name: ObjLoadInit
 * Namespace: Global
 * Signature: long ObjLoadInit(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl ObjLoadInit(void)

{
  reg_del_ent_func(RemoveSortObject);
  return 1;
}
