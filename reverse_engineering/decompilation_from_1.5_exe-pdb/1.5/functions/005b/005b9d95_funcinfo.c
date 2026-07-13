/*
 * Entry: 005b9d95
 * Name: funcinfo
 * Namespace: Global
 * Signature: void funcinfo(lua_Debug * param_1, Closure * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl funcinfo(lua_Debug *param_1,Closure *param_2)

{
  int iVar1;
  int in_EAX;
  int in_ECX;
  char *pcVar2;
  
  if (*(char *)(in_ECX + 6) == '\0') {
    *(int *)(in_EAX + 0x10) = *(int *)(*(int *)(in_ECX + 0x10) + 0x20) + 0x10;
    iVar1 = *(int *)(*(int *)(in_ECX + 0x10) + 0x3c);
    *(int *)(in_EAX + 0x1c) = iVar1;
    *(undefined4 *)(in_EAX + 0x20) = *(undefined4 *)(*(int *)(in_ECX + 0x10) + 0x40);
    pcVar2 = "main";
    if (iVar1 != 0) {
      pcVar2 = "Lua";
    }
    *(char **)(in_EAX + 0xc) = pcVar2;
  }
  else {
    *(undefined4 *)(in_EAX + 0x1c) = 0xffffffff;
    *(undefined4 *)(in_EAX + 0x20) = 0xffffffff;
    *(char **)(in_EAX + 0x10) = "=[C]";
    *(char **)(in_EAX + 0xc) = "C";
  }
  luaO_chunkid((char *)(in_EAX + 0x24),*(char **)(in_EAX + 0x10),0x3c);
  return;
}
