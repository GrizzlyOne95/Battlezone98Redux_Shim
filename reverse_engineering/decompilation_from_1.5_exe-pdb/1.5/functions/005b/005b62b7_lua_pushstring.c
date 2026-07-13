/*
 * Entry: 005b62b7
 * Name: lua_pushstring
 * Namespace: Global
 * Signature: void lua_pushstring(lua_State * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl lua_pushstring(lua_State *param_1,char *param_2)

{
  char cVar1;
  char *pcVar2;
  
  if (param_2 == (char *)0x0) {
    param_1->top->tt = 0;
    param_1->top = param_1->top + 1;
    return;
  }
  pcVar2 = param_2;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  lua_pushlstring(param_1,param_2,(int)pcVar2 - (int)(param_2 + 1));
  return;
}
