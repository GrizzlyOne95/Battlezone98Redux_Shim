/*
 * Entry: 005b60fa
 * Name: lua_tolstring
 * Namespace: Global
 * Signature: char * lua_tolstring(lua_State * param_1, int param_2, uint * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl lua_tolstring(lua_State *param_1,int param_2,uint *param_3)

{
  lua_TValue *plVar1;
  int iVar2;
  int unaff_EBP;
  lua_State *unaff_ESI;
  
  plVar1 = index2adr(unaff_ESI,unaff_EBP);
  if (plVar1->tt != 4) {
    iVar2 = luaV_tostring(param_1,plVar1);
    if (iVar2 == 0) {
      if (param_3 != (uint *)0x0) {
        *param_3 = 0;
      }
      return (char *)0x0;
    }
    if (param_1->l_G->GCthreshold <= param_1->l_G->totalbytes) {
      luaC_step(param_1);
    }
    plVar1 = index2adr(unaff_ESI,unaff_EBP);
  }
  if (param_3 != (uint *)0x0) {
    *param_3 = *(uint *)((plVar1->value).b + 0xc);
  }
  return (char *)((plVar1->value).b + 0x10);
}
