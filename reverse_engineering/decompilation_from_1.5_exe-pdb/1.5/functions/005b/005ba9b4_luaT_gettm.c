/*
 * Entry: 005ba9b4
 * Name: luaT_gettm
 * Namespace: Global
 * Signature: lua_TValue * luaT_gettm(Table * param_1, TMS param_2, TString * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

lua_TValue * __cdecl luaT_gettm(Table *param_1,TMS param_2,TString *param_3)

{
  lua_TValue *plVar1;
  
  plVar1 = luaH_getstr(param_1,param_3);
  if (plVar1->tt == 0) {
    param_1->flags = param_1->flags | '\x01' << ((byte)param_2 & 0x1f);
    plVar1 = (lua_TValue *)0x0;
  }
  return plVar1;
}
