/*
 * Entry: 005c1c50
 * Name: pushnexttemplate
 * Namespace: Global
 * Signature: char * pushnexttemplate(lua_State * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl pushnexttemplate(lua_State *param_1,char *param_2)

{
  char *pcVar1;
  char *in_EAX;
  char *pcVar2;
  
  for (; *in_EAX == ';'; in_EAX = in_EAX + 1) {
  }
  if (*in_EAX != '\0') {
    pcVar2 = strchr(in_EAX,0x3b);
    pcVar1 = in_EAX;
    if (pcVar2 == (char *)0x0) {
      do {
        pcVar2 = pcVar1;
        pcVar1 = pcVar2 + 1;
      } while (*pcVar2 != '\0');
    }
    lua_pushlstring(param_1,in_EAX,(int)pcVar2 - (int)in_EAX);
    return pcVar2;
  }
  return (char *)0x0;
}
