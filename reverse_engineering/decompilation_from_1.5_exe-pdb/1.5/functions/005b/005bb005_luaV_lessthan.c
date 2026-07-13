/*
 * Entry: 005bb005
 * Name: luaV_lessthan
 * Namespace: Global
 * Signature: int luaV_lessthan(lua_State * param_1, lua_TValue * param_2, lua_TValue * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaV_lessthan(lua_State *param_1,lua_TValue *param_2,lua_TValue *param_3)

{
  int iVar1;
  TString *unaff_ESI;
  TString *unaff_EDI;
  
  iVar1 = param_2->tt;
  if (iVar1 == param_3->tt) {
    if (iVar1 == 3) {
      if ((param_2->value).n < (param_3->value).n) {
        return 1;
      }
      return 0;
    }
    if (iVar1 == 4) {
      iVar1 = l_strcmp(unaff_EDI,unaff_ESI);
      return (uint)(iVar1 < 0);
    }
    iVar1 = call_orderTM((lua_State *)param_2,param_3,(lua_TValue *)0xd,(TMS)unaff_EDI);
    if (iVar1 != -1) {
      return iVar1;
    }
  }
  iVar1 = luaG_ordererror(param_1,param_2,param_3);
  return iVar1;
}
