/*
 * Entry: 004ea253
 * Name: del_entity
 * Namespace: Global
 * Signature: void del_entity(tagENTITY * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl del_entity(tagENTITY *param_1)

{
  int iVar1;
  tagENTITY *unaff_EDI;
  
  call_registered_del_funcs(param_1);
  iVar1 = is_user_vhcl(param_1->obj76);
  if (iVar1 != 0) {
    user_entity_ptr = (tagENTITY *)0x0;
  }
  Entity_Clean(unaff_EDI);
  if ((int)&param_1[-0xf473].shadowPoly[1].y / 0xc4 == world_count + -1) {
    world_count = world_count + -1;
  }
  return;
}
