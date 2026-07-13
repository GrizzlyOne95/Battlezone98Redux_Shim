/*
 * Entry: 004167ed
 * Name: luaL_setfuncs
 * Namespace: Global
 * Signature: void luaL_setfuncs(lua_State * param_1, luaL_Reg * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaL_setfuncs(lua_State *param_1,luaL_Reg *param_2,int param_3)

{
  int *in_EAX;
  lua_State *unaff_EBX;
  int unaff_EDI;
  int iVar1;
  
  luaL_checkstack(unaff_EBX,unaff_EDI,"too many upvalues");
  if (*in_EAX != 0) {
    do {
      if (0 < unaff_EDI) {
        iVar1 = unaff_EDI;
        do {
          lua_pushvalue(unaff_EBX,-unaff_EDI);
          iVar1 = iVar1 + -1;
        } while (iVar1 != 0);
      }
      lua_pushstring(unaff_EBX,(char *)*in_EAX);
      lua_pushcclosure(unaff_EBX,(_func___cdecl_int_lua_State_ptr *)in_EAX[1],unaff_EDI);
      lua_settable(unaff_EBX,-3 - unaff_EDI);
      in_EAX = in_EAX + 2;
    } while (*in_EAX != 0);
  }
  lua_settop(unaff_EBX,-1 - unaff_EDI);
  return;
}
