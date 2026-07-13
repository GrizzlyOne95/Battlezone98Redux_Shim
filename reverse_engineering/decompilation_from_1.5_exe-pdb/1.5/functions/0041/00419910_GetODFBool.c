/*
 * Entry: 00419910
 * Name: GetODFBool
 * Namespace: Global
 * Signature: int GetODFBool(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetODFBool(lua_State *param_1)

{
  bool bVar1;
  ParameterDB *this;
  char *pcVar2;
  char *pcVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  undefined1 uVar7;
  bool *pbVar8;
  bool local_5;
  
  this = GetParameterDB(param_1,1);
  if (this == (ParameterDB *)0x0) {
    iVar4 = 0;
  }
  else {
    pcVar2 = luaL_optlstring(param_1,2,(char *)0x0,(uint *)0x0);
    pcVar3 = luaL_checklstring(param_1,3,(uint *)0x0);
    iVar4 = lua_type(param_1,4);
    if (iVar4 < 1) {
      iVar4 = 0;
    }
    else {
      iVar4 = lua_toboolean(param_1,4);
    }
    uVar7 = iVar4 != 0;
    pbVar8 = &local_5;
    uVar5 = Hash(pcVar3,0x811c9dc5);
    uVar6 = Hash(pcVar2,0x811c9dc5);
    bVar1 = ParameterDB::Get(this,uVar6,uVar5,pbVar8,(bool)uVar7);
    lua_pushboolean(param_1,(uint)local_5);
    lua_pushboolean(param_1,(uint)bVar1);
    iVar4 = 2;
  }
  return iVar4;
}
