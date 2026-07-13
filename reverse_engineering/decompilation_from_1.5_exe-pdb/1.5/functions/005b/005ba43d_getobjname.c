/*
 * Entry: 005ba43d
 * Name: getobjname
 * Namespace: Global
 * Signature: char * getobjname(lua_State * param_1, CallInfo * param_2, int param_3, char * * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl getobjname(lua_State *param_1,CallInfo *param_2,int param_3,char **param_4)

{
  Proto *pPVar1;
  uint in_EAX;
  int iVar2;
  lua_TValue *plVar3;
  uint uVar4;
  char *pcVar5;
  uint uVar6;
  char *extraout_EDX;
  int unaff_EBX;
  CallInfo *unaff_ESI;
  lua_State *unaff_EDI;
  
  while( true ) {
    if ((*(int **)(unaff_EBX + 4))[2] != 6) {
      return (char *)0x0;
    }
    iVar2 = **(int **)(unaff_EBX + 4);
    if (*(char *)(iVar2 + 6) != '\0') {
      return (char *)0x0;
    }
    pPVar1 = *(Proto **)(iVar2 + 0x10);
    iVar2 = currentpc(unaff_EDI,unaff_ESI);
    plVar3 = (lua_TValue *)luaF_getlocalname(pPVar1,in_EAX + 1,iVar2);
    param_2->base = plVar3;
    if (plVar3 != (lua_TValue *)0x0) {
      return "local";
    }
    uVar4 = symbexec(pPVar1,iVar2,in_EAX);
    uVar6 = uVar4 & 0x3f;
    if (uVar6 != 0) break;
    in_EAX = uVar4 >> 0x17;
    if ((uVar4 >> 6 & 0xff) <= in_EAX) {
      return (char *)0x0;
    }
  }
  if (uVar6 == 4) {
    if (pPVar1->upvalues == (TString **)0x0) {
      pcVar5 = "?";
    }
    else {
      pcVar5 = (char *)(pPVar1->upvalues[uVar4 >> 0x17] + 1);
    }
    param_2->base = (lua_TValue *)pcVar5;
    return "upvalue";
  }
  if (uVar6 != 5) {
    if ((uVar6 != 6) && (uVar6 != 0xb)) {
      return (char *)0x0;
    }
    plVar3 = (lua_TValue *)kname((Proto *)unaff_EDI,(int)unaff_ESI);
    param_2->base = plVar3;
    return extraout_EDX;
  }
  param_2->base = (lua_TValue *)(pPVar1->k[uVar4 >> 0xe].value.b + 0x10);
  return "global";
}
