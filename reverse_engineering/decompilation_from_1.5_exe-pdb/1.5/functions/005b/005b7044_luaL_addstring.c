/*
 * Entry: 005b7044
 * Name: luaL_addstring
 * Namespace: Global
 * Signature: void luaL_addstring(luaL_Buffer * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaL_addstring(luaL_Buffer *param_1,char *param_2)

{
  char cVar1;
  char *pcVar2;
  
  pcVar2 = param_2;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  luaL_addlstring(param_1,param_2,(int)pcVar2 - (int)(param_2 + 1));
  return;
}
