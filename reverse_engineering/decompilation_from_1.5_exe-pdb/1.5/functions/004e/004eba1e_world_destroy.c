/*
 * Entry: 004eba1e
 * Name: world_destroy
 * Namespace: Global
 * Signature: void world_destroy(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl world_destroy(void)

{
  tagENTITY *unaff_ESI;
  tagENTITY *ptVar1;
  
  ptVar1 = world + 0x2ff;
  do {
    if (ptVar1->obj76 != (_OBJ76 *)0x0) {
      call_registered_del_funcs(ptVar1);
      remove_obj(ptVar1->obj76,".\\Obj76\\Entities.c");
    }
    Entity_Clean(unaff_ESI);
    ptVar1 = ptVar1 + -1;
  } while (0xbb278f < (int)ptVar1);
  world_count = 0;
  return;
}
