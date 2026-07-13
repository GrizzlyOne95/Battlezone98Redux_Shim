/*
 * Entry: 005b615e
 * Name: lua_objlen
 * Namespace: Global
 * Signature: uint lua_objlen(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __cdecl lua_objlen(lua_State *param_1,int param_2)

{
  lua_TValue *plVar1;
  uint uVar2;
  int iVar3;
  lua_State *unaff_ESI;
  int unaff_retaddr;
  
  plVar1 = index2adr(unaff_ESI,unaff_retaddr);
  iVar3 = plVar1->tt;
  if (iVar3 == 3) {
    iVar3 = luaV_tostring(param_1,plVar1);
    if (iVar3 != 0) goto LAB_005b6191;
  }
  else {
    if (iVar3 == 4) {
LAB_005b6191:
      return *(uint *)((plVar1->value).b + 0xc);
    }
    if (iVar3 == 5) {
      uVar2 = luaH_getn(&((plVar1->value).gc)->h);
      return uVar2;
    }
    if (iVar3 == 7) {
      return *(uint *)((plVar1->value).b + 0x10);
    }
  }
  return 0;
}
