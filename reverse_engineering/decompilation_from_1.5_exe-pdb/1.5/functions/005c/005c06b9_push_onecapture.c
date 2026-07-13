/*
 * Entry: 005c06b9
 * Name: push_onecapture
 * Namespace: Global
 * Signature: void push_onecapture(MatchState * param_1, int param_2, char * param_3, char * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl push_onecapture(MatchState *param_1,int param_2,char *param_3,char *param_4)

{
  uint uVar1;
  int in_EAX;
  int *unaff_ESI;
  int unaff_EDI;
  
  if (unaff_ESI[3] <= unaff_EDI) {
    if (unaff_EDI == 0) {
      lua_pushlstring((lua_State *)unaff_ESI[2],(char *)param_1,in_EAX - (int)param_1);
      return;
    }
    luaL_error((lua_State *)unaff_ESI[2],"invalid capture index");
    return;
  }
  uVar1 = unaff_ESI[unaff_EDI * 2 + 5];
  if (uVar1 == 0xffffffff) {
    luaL_error((lua_State *)unaff_ESI[2],"unfinished capture");
  }
  if (uVar1 == 0xfffffffe) {
    lua_pushinteger((lua_State *)unaff_ESI[2],(unaff_ESI[unaff_EDI * 2 + 4] - *unaff_ESI) + 1);
    return;
  }
  lua_pushlstring((lua_State *)unaff_ESI[2],(char *)unaff_ESI[unaff_EDI * 2 + 4],uVar1);
  return;
}
