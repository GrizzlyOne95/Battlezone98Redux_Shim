/*
 * Entry: 004e9f69
 * Name: world_init
 * Namespace: Global
 * Signature: void world_init(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl world_init(void)

{
  int iVar1;
  tagENTITY *ptVar2;
  _func___cdecl_void_tagENTITY_ptr **pp_Var3;
  
  ptVar2 = world;
  do {
    Entity_Clear(ptVar2);
    ptVar2 = ptVar2 + 1;
  } while ((int)ptVar2 < 0xbd7391);
  obj_heap_init();
  pp_Var3 = DelEntFuncs;
  for (iVar1 = 0x33; iVar1 != 0; iVar1 = iVar1 + -1) {
    *pp_Var3 = (_func___cdecl_void_tagENTITY_ptr *)0x0;
    pp_Var3 = pp_Var3 + 1;
  }
  pp_Var3 = AddEntFuncs;
  for (iVar1 = 0x33; iVar1 != 0; iVar1 = iVar1 + -1) {
    *pp_Var3 = (_func___cdecl_void_tagENTITY_ptr *)0x0;
    pp_Var3 = pp_Var3 + 1;
  }
  world_count = 0;
  current_entity_ptr = 0;
  user_entity_ptr = (tagENTITY *)0x0;
  AddFunc_Count = 0;
  DelFunc_Count = 0;
  return;
}
