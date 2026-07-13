/*
 * Entry: 005b76d3
 * Name: luaL_optlstring
 * Namespace: Global
 * Signature: char * luaL_optlstring(lua_State * param_1, int param_2, char * param_3, uint * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl luaL_optlstring(lua_State *param_1,int param_2,char *param_3,uint *param_4)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  uint uVar4;
  
  iVar2 = lua_type(param_1,param_2);
  if (iVar2 < 1) {
    if (param_4 != (uint *)0x0) {
      if (param_3 == (char *)0x0) {
        uVar4 = 0;
      }
      else {
        pcVar3 = param_3;
        do {
          cVar1 = *pcVar3;
          pcVar3 = pcVar3 + 1;
        } while (cVar1 != '\0');
        uVar4 = (int)pcVar3 - (int)(param_3 + 1);
      }
      *param_4 = uVar4;
    }
    return param_3;
  }
  pcVar3 = luaL_checklstring(param_1,param_2,param_4);
  return pcVar3;
}
