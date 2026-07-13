/*
 * Entry: 00419aea
 * Name: GetODFString
 * Namespace: Global
 * Signature: int GetODFString(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetODFString(lua_State *param_1)

{
  ParameterDB *this;
  char *pcVar1;
  char *pcVar2;
  char *pcVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  
  this = GetParameterDB(param_1,1);
  if (this == (ParameterDB *)0x0) {
    iVar6 = 0;
  }
  else {
    pcVar1 = luaL_optlstring(param_1,2,(char *)0x0,(uint *)0x0);
    pcVar2 = luaL_checklstring(param_1,3,(uint *)0x0);
    pcVar3 = luaL_optlstring(param_1,4,(char *)0x0,(uint *)0x0);
    uVar4 = Hash(pcVar2,0x811c9dc5);
    uVar5 = Hash(pcVar1,0x811c9dc5);
    pcVar2 = ParameterDB::Get(this,uVar5,uVar4);
    pcVar1 = pcVar2;
    if (pcVar2 == (char *)0x0) {
      pcVar1 = pcVar3;
    }
    lua_pushstring(param_1,pcVar1);
    lua_pushboolean(param_1,(uint)(pcVar2 != (char *)0x0));
    iVar6 = 2;
  }
  return iVar6;
}
