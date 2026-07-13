/*
 * Entry: 005b7cc7
 * Name: lua_newstate
 * Namespace: Global
 * Signature: lua_State * lua_newstate(_func___cdecl_void_ptr_void_ptr_void_ptr_uint_uint * param_1, void * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

lua_State * __cdecl
lua_newstate(_func___cdecl_void_ptr_void_ptr_void_ptr_uint_uint *param_1,void *param_2)

{
  lua_State *plVar1;
  int iVar2;
  lua_State *unaff_ESI;
  global_State *unaff_EDI;
  CallInfo **ppCVar3;
  
  plVar1 = (*param_1)(param_2,(void *)0x0,0,0x178);
  if (plVar1 == (lua_State *)0x0) {
    plVar1 = (lua_State *)0x0;
  }
  else {
    plVar1->next = (GCObject *)0x0;
    plVar1->tt = '\b';
    *(undefined1 *)&plVar1[1].ci = 0x21;
    plVar1->marked = 'a';
    preinit_state(unaff_ESI,unaff_EDI);
    plVar1[1].base = (lua_TValue *)param_1;
    plVar1[1].l_G = param_2;
    plVar1[2].l_G = (global_State *)(plVar1 + 2);
    plVar1[2].ci = (CallInfo *)(plVar1 + 2);
    plVar1[1].hookcount = 0;
    plVar1[1].top = (lua_TValue *)0x0;
    plVar1[1].tt = '\0';
    plVar1[1].marked = '\0';
    plVar1[1].status = '\0';
    plVar1[1].field_0x7 = 0;
    plVar1[1].next = (GCObject *)0x0;
    plVar1[1].errorJmp = (lua_longjmp *)plVar1;
    (plVar1->l_G->l_registry).tt = 0;
    plVar1[1].stack = (lua_TValue *)&plVar1[1].stack_last;
    plVar1[1].stack_last = (lua_TValue *)plVar1;
    plVar1[1].l_gt.tt = 200;
    *(undefined4 *)&plVar1[1].l_gt.field_0xc = 200;
    plVar1[1].nCcalls = 0;
    plVar1[1].baseCcalls = 0;
    plVar1[1].basehookcount = 0;
    plVar1[1].env.value.gc = (GCObject *)0x0;
    plVar1[1].savedpc = (uint *)0x0;
    plVar1[1].end_ci = (CallInfo *)0x0;
    plVar1[1].base_ci = (CallInfo *)0x0;
    plVar1[1].stacksize = 0;
    plVar1[1].size_ci = 0;
    *(undefined4 *)((int)&plVar1[1].l_gt.value + 4) = 0;
    *(undefined1 *)((int)&plVar1[1].ci + 1) = 0;
    plVar1[1].hook = (_func___cdecl_void_lua_State_ptr_lua_Debug_ptr *)0x178;
    ppCVar3 = (CallInfo **)&plVar1[2].stack;
    for (iVar2 = 9; iVar2 != 0; iVar2 = iVar2 + -1) {
      *ppCVar3 = (CallInfo *)0x0;
      ppCVar3 = ppCVar3 + 1;
    }
    iVar2 = luaD_rawrunprotected(plVar1,f_luaopen,(void *)0x0);
    if (iVar2 != 0) {
      close_state((lua_State *)unaff_EDI);
      plVar1 = (lua_State *)0x0;
    }
  }
  return plVar1;
}
