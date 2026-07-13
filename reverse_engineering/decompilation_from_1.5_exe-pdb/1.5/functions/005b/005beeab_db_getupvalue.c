/*
 * Entry: 005beeab
 * Name: db_getupvalue
 * Namespace: Global
 * Signature: int db_getupvalue(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl db_getupvalue(lua_State *param_1)

{
  int iVar1;
  int unaff_ESI;
  
  iVar1 = auxupvalue((lua_State *)0x1,unaff_ESI);
  return iVar1;
}
