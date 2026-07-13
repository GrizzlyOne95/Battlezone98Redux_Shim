/*
 * Entry: 005c220a
 * Name: modinit
 * Namespace: Global
 * Signature: void modinit(lua_State * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl modinit(lua_State *param_1,char *param_2)

{
  char *pcVar1;
  char *pcVar2;
  lua_State *unaff_ESI;
  char *unaff_EDI;
  
  lua_pushvalue(unaff_ESI,-1);
  lua_setfield(unaff_ESI,-2,"_M");
  lua_pushstring(unaff_ESI,unaff_EDI);
  lua_setfield(unaff_ESI,-2,"_NAME");
  pcVar1 = strrchr(unaff_EDI,0x2e);
  pcVar2 = unaff_EDI;
  if (pcVar1 != (char *)0x0) {
    pcVar2 = pcVar1 + 1;
  }
  lua_pushlstring(unaff_ESI,unaff_EDI,(int)pcVar2 - (int)unaff_EDI);
  lua_setfield(unaff_ESI,-2,"_PACKAGE");
  return;
}
