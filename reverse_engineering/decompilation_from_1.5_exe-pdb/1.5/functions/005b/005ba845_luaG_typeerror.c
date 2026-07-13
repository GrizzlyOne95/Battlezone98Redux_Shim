/*
 * Entry: 005ba845
 * Name: luaG_typeerror
 * Namespace: Global
 * Signature: void luaG_typeerror(lua_State * param_1, lua_TValue * param_2, char * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaG_typeerror(lua_State *param_1,lua_TValue *param_2,char *param_3)

{
  char *pcVar1;
  lua_TValue *plVar2;
  char **unaff_ESI;
  int unaff_EDI;
  lua_TValue *local_8;
  
  local_8 = (lua_TValue *)0x0;
  plVar2 = param_1->ci->base;
  do {
    if (param_1->ci->top <= plVar2) {
      pcVar1 = (char *)0x0;
LAB_005ba877:
      if (pcVar1 == (char *)0x0) {
        luaG_runerror(param_1,"attempt to %s a %s value");
      }
      else {
        luaG_runerror(param_1,"attempt to %s %s \'%s\' (a %s value)");
      }
      return;
    }
    if (param_2 == plVar2) {
      pcVar1 = getobjname(param_1,(CallInfo *)&local_8,unaff_EDI,unaff_ESI);
      goto LAB_005ba877;
    }
    plVar2 = plVar2 + 1;
  } while( true );
}
