/*
 * Entry: 005ba5b8
 * Name: addinfo
 * Namespace: Global
 * Signature: void addinfo(lua_State * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl addinfo(lua_State *param_1,char *param_2)

{
  CallInfo *pCVar1;
  lua_TValue *plVar2;
  lua_State *unaff_EBX;
  CallInfo *unaff_ESI;
  int iVar3;
  lua_State *unaff_EDI;
  char local_44 [60];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  pCVar1 = unaff_EDI->ci;
  plVar2 = pCVar1->func;
  if ((plVar2->tt == 6) && (*(char *)((plVar2->value).b + 6) == '\0')) {
    currentline(unaff_EBX,unaff_ESI);
    plVar2 = pCVar1->func;
    if ((plVar2->tt == 6) && (iVar3 = (plVar2->value).b, *(char *)(iVar3 + 6) == '\0')) {
      iVar3 = *(int *)(iVar3 + 0x10);
    }
    else {
      iVar3 = 0;
    }
    luaO_chunkid(local_44,(char *)(*(int *)(iVar3 + 0x20) + 0x10),0x3c);
    luaO_pushfstring(unaff_EDI,"%s:%d: %s");
  }
  return;
}
