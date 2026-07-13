/*
 * Entry: 005b79e1
 * Name: luaL_checkoption
 * Namespace: Global
 * Signature: int luaL_checkoption(lua_State * param_1, int param_2, char * param_3, char * * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaL_checkoption(lua_State *param_1,int param_2,char *param_3,char **param_4)

{
  byte bVar1;
  byte *pbVar2;
  char *pcVar3;
  byte *pbVar4;
  int iVar5;
  byte *pbVar6;
  int iVar7;
  bool bVar8;
  
  iVar7 = 0;
  if (param_3 == (char *)0x0) {
    pbVar2 = (byte *)luaL_checklstring(param_1,param_2,(uint *)0x0);
  }
  else {
    pbVar2 = (byte *)luaL_optlstring(param_1,param_2,param_3,(uint *)0x0);
  }
  pbVar4 = (byte *)*param_4;
  do {
    pbVar6 = pbVar2;
    if (pbVar4 == (byte *)0x0) {
      pcVar3 = lua_pushfstring(param_1,"invalid option \'%s\'");
      iVar7 = luaL_argerror(param_1,param_2,pcVar3);
      return iVar7;
    }
    do {
      bVar1 = *pbVar4;
      bVar8 = bVar1 < *pbVar6;
      if (bVar1 != *pbVar6) {
LAB_005b7a39:
        iVar5 = (1 - (uint)bVar8) - (uint)(bVar8 != 0);
        goto LAB_005b7a3e;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar4[1];
      bVar8 = bVar1 < pbVar6[1];
      if (bVar1 != pbVar6[1]) goto LAB_005b7a39;
      pbVar4 = pbVar4 + 2;
      pbVar6 = pbVar6 + 2;
    } while (bVar1 != 0);
    iVar5 = 0;
LAB_005b7a3e:
    if (iVar5 == 0) {
      return iVar7;
    }
    iVar7 = iVar7 + 1;
    pbVar4 = (byte *)param_4[iVar7];
  } while( true );
}
