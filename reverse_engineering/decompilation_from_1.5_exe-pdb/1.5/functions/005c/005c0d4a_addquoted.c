/*
 * Entry: 005c0d4a
 * Name: addquoted
 * Namespace: Global
 * Signature: void addquoted(lua_State * param_1, luaL_Buffer * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl addquoted(lua_State *param_1,luaL_Buffer *param_2,int param_3)

{
  luaL_Buffer *plVar1;
  char cVar2;
  char *pcVar3;
  luaL_Buffer *unaff_ESI;
  char *pcVar4;
  uint uVar5;
  uint local_8;
  
  pcVar3 = luaL_checklstring(param_1,(int)param_2,&local_8);
  plVar1 = unaff_ESI + 1;
  if (plVar1 <= (luaL_Buffer *)unaff_ESI->p) {
    luaL_prepbuffer(unaff_ESI);
  }
  *unaff_ESI->p = '\"';
  unaff_ESI->p = unaff_ESI->p + 1;
  do {
    if (local_8 == 0) {
      local_8 = 0xffffffff;
      if (plVar1 <= (luaL_Buffer *)unaff_ESI->p) {
        luaL_prepbuffer(unaff_ESI);
      }
      *unaff_ESI->p = '\"';
      unaff_ESI->p = unaff_ESI->p + 1;
      return;
    }
    local_8 = local_8 - 1;
    cVar2 = *pcVar3;
    if (cVar2 == '\0') {
      uVar5 = 4;
      pcVar4 = "\\000";
LAB_005c0dce:
      luaL_addlstring(unaff_ESI,pcVar4,uVar5);
    }
    else {
      if (cVar2 == '\n') {
LAB_005c0d97:
        if (plVar1 <= (luaL_Buffer *)unaff_ESI->p) {
          luaL_prepbuffer(unaff_ESI);
        }
        *unaff_ESI->p = '\\';
        unaff_ESI->p = unaff_ESI->p + 1;
      }
      else {
        if (cVar2 == '\r') {
          uVar5 = 2;
          pcVar4 = "\\r";
          goto LAB_005c0dce;
        }
        if ((cVar2 == '\"') || (cVar2 == '\\')) goto LAB_005c0d97;
      }
      if (plVar1 <= (luaL_Buffer *)unaff_ESI->p) {
        luaL_prepbuffer(unaff_ESI);
      }
      *unaff_ESI->p = *pcVar3;
      unaff_ESI->p = unaff_ESI->p + 1;
    }
    pcVar3 = pcVar3 + 1;
  } while( true );
}
