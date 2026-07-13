/*
 * Entry: 005b8bb4
 * Name: luaD_call
 * Namespace: Global
 * Signature: void luaD_call(lua_State * param_1, lua_TValue * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaD_call(lua_State *param_1,lua_TValue *param_2,int param_3)

{
  ushort uVar1;
  int iVar2;
  
  param_1->nCcalls = param_1->nCcalls + 1;
  uVar1 = param_1->nCcalls;
  if (199 < uVar1) {
    if (uVar1 == 200) {
      luaG_runerror(param_1,"C stack overflow");
    }
    else if (0xe0 < uVar1) {
                    /* WARNING: Subroutine does not return */
      luaD_throw(param_1,5);
    }
  }
  iVar2 = luaD_precall(param_1,param_2,param_3);
  if (iVar2 == 0) {
    luaV_execute(param_1,1);
  }
  param_1->nCcalls = param_1->nCcalls - 1;
  if (param_1->l_G->GCthreshold <= param_1->l_G->totalbytes) {
    luaC_step(param_1);
  }
  return;
}
