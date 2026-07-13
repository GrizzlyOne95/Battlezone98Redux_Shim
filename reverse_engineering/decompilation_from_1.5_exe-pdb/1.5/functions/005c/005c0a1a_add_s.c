/*
 * Entry: 005c0a1a
 * Name: add_s
 * Namespace: Global
 * Signature: void add_s(MatchState * param_1, luaL_Buffer * param_2, char * param_3, char * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl add_s(MatchState *param_1,luaL_Buffer *param_2,char *param_3,char *param_4)

{
  char *pcVar1;
  int iVar2;
  luaL_Buffer *unaff_EBX;
  char *unaff_ESI;
  int unaff_EDI;
  char *pcVar3;
  char *pcVar4;
  char *local_8;
  
  pcVar1 = lua_tolstring(param_1->L,3,(uint *)&local_8);
  pcVar3 = (char *)0x0;
  if (local_8 != (char *)0x0) {
    do {
      if (pcVar3[(int)pcVar1] == '%') {
        pcVar3 = pcVar3 + 1;
        pcVar4 = pcVar3;
        iVar2 = isdigit((uint)(byte)pcVar3[(int)pcVar1]);
        if (iVar2 == 0) goto LAB_005c0a5c;
        if (pcVar3[(int)pcVar1] == '0') {
          luaL_addlstring(unaff_EBX,(char *)param_2,(int)param_3 - (int)param_2);
        }
        else {
          push_onecapture((MatchState *)param_2,unaff_EDI,unaff_ESI,pcVar4);
          pcVar3 = pcVar4;
          luaL_addvalue(unaff_EBX);
        }
      }
      else {
LAB_005c0a5c:
        if (unaff_EBX + 1 <= (luaL_Buffer *)unaff_EBX->p) {
          luaL_prepbuffer(unaff_EBX);
        }
        *unaff_EBX->p = pcVar3[(int)pcVar1];
        unaff_EBX->p = unaff_EBX->p + 1;
      }
      pcVar3 = pcVar3 + 1;
    } while (pcVar3 < local_8);
  }
  return;
}
