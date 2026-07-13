/*
 * Entry: 00419428
 * Name: PackTable
 * Namespace: Global
 * Signature: bool PackTable(char * * param_1, char * param_2, lua_State * param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl PackTable(char **param_1,char *param_2,lua_State *param_3,int param_4)

{
  char *pcVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  char **unaff_EDI;
  
  iVar4 = 0;
  lua_pushnil((lua_State *)param_2);
  iVar3 = lua_next((lua_State *)param_2,(int)param_3);
  while (iVar3 != 0) {
    iVar4 = iVar4 + 1;
    lua_settop((lua_State *)param_2,-2);
    iVar3 = lua_next((lua_State *)param_2,(int)param_3);
  }
  pcVar1 = *unaff_EDI;
  if (iVar4 < 0x1f) {
    pcVar1[-1] = pcVar1[-1] + (char)iVar4;
  }
  else {
    if (param_1 <= pcVar1 + 1) {
      return false;
    }
    pcVar1[-1] = pcVar1[-1] + '\x1f';
    **unaff_EDI = (char)iVar4;
    *unaff_EDI = *unaff_EDI + 1;
  }
  lua_pushnil((lua_State *)param_2);
  iVar3 = lua_next((lua_State *)param_2,(int)param_3);
  while( true ) {
    if (iVar3 == 0) {
      return true;
    }
    bVar2 = PackValue(unaff_EDI,(char *)param_1,(lua_State *)param_2,-2);
    if ((!bVar2) || (bVar2 = PackValue(unaff_EDI,(char *)param_1,(lua_State *)param_2,-1), !bVar2))
    break;
    lua_settop((lua_State *)param_2,-2);
    iVar3 = lua_next((lua_State *)param_2,(int)param_3);
  }
  lua_settop((lua_State *)param_2,-3);
  *unaff_EDI = pcVar1;
  return false;
}
