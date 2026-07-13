/*
 * Entry: 004b225b
 * Name: oneshot_cb
 * Namespace: Global
 * Signature: void oneshot_cb(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl oneshot_cb(_OBJ76 *param_1)

{
  tagENTITY *ptVar1;
  
  ptVar1 = FindObjectEntity(param_1);
  if (ptVar1 != (tagENTITY *)0x0) {
    Cache_Invalidate_Bsp(ptVar1);
  }
  remove_obj(param_1,"texmgr");
  return;
}
