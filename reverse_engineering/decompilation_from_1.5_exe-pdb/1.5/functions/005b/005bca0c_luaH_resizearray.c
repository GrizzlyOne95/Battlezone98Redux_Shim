/*
 * Entry: 005bca0c
 * Name: luaH_resizearray
 * Namespace: Global
 * Signature: void luaH_resizearray(lua_State * param_1, Table * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaH_resizearray(lua_State *param_1,Table *param_2,int param_3)

{
  int iVar1;
  int unaff_retaddr;
  
  iVar1 = 0;
  if (param_2->node != &dummynode_) {
    iVar1 = 1 << (param_2->lsizenode & 0x1f);
  }
  resize(param_1,(Table *)param_3,iVar1,unaff_retaddr);
  return;
}
