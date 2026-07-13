/*
 * Entry: 005c0ac0
 * Name: add_value
 * Namespace: Global
 * Signature: void add_value(MatchState * param_1, luaL_Buffer * param_2, char * param_3, char * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl add_value(MatchState *param_1,luaL_Buffer *param_2,char *param_3,char *param_4)

{
  lua_State *plVar1;
  MatchState *in_EAX;
  int iVar2;
  char *unaff_EBX;
  char *unaff_ESI;
  int unaff_EDI;
  lua_State *plVar3;
  
  plVar1 = in_EAX->L;
  iVar2 = lua_type(plVar1,3);
  if (2 < iVar2) {
    if (iVar2 < 5) {
      add_s(in_EAX,param_2,param_3,unaff_ESI);
      return;
    }
    if (iVar2 == 5) {
      push_onecapture((MatchState *)param_2,unaff_EDI,unaff_ESI,unaff_EBX);
      lua_gettable(plVar1,3);
    }
    else if (iVar2 == 6) {
      plVar3 = plVar1;
      lua_pushvalue(plVar1,3);
      iVar2 = push_captures((MatchState *)param_2,param_3,(char *)plVar3);
      lua_call(plVar1,iVar2,1);
    }
  }
  iVar2 = lua_toboolean(plVar1,-1);
  if (iVar2 == 0) {
    lua_settop(plVar1,-2);
    lua_pushlstring(plVar1,(char *)param_2,(int)param_3 - (int)param_2);
  }
  else {
    iVar2 = lua_isstring(plVar1,-1);
    if (iVar2 == 0) {
      iVar2 = lua_type(plVar1,-1);
      lua_typename(plVar1,iVar2);
      luaL_error(plVar1,"invalid replacement value (a %s)");
    }
  }
  luaL_addvalue((luaL_Buffer *)param_1);
  return;
}
