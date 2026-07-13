/*
 * Entry: 004199be
 * Name: GetODFInt
 * Namespace: Global
 * Signature: int GetODFInt(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetODFInt(lua_State *param_1)

{
  bool bVar1;
  char *pcVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int *piVar6;
  int local_10;
  ParameterDB *local_c;
  char *local_8;
  
  local_c = GetParameterDB(param_1,1);
  if (local_c == (ParameterDB *)0x0) {
    iVar3 = 0;
  }
  else {
    pcVar2 = luaL_optlstring(param_1,2,(char *)0x0,(uint *)0x0);
    local_8 = luaL_checklstring(param_1,3,(uint *)0x0);
    iVar3 = luaL_optinteger(param_1,4,0);
    piVar6 = &local_10;
    uVar4 = Hash(local_8,0x811c9dc5);
    uVar5 = Hash(pcVar2,0x811c9dc5);
    bVar1 = ParameterDB::Get(local_c,uVar5,uVar4,piVar6,iVar3);
    lua_pushinteger(param_1,local_10);
    lua_pushboolean(param_1,(uint)bVar1);
    iVar3 = 2;
  }
  return iVar3;
}
