/*
 * Entry: 005c03ae
 * Name: match_capture
 * Namespace: Global
 * Signature: char * match_capture(MatchState * param_1, char * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl match_capture(MatchState *param_1,char *param_2,int param_3)

{
  uint uVar1;
  int in_EAX;
  int iVar2;
  int in_ECX;
  uint uVar3;
  char *unaff_EBX;
  char *pcVar4;
  char *pcVar5;
  bool bVar6;
  
  iVar2 = in_EAX + -0x31;
  if (((iVar2 < 0) || (*(int *)(in_ECX + 0xc) <= iVar2)) ||
     (*(int *)(in_ECX + 0x14 + iVar2 * 8) == -1)) {
    iVar2 = luaL_error(*(lua_State **)(in_ECX + 8),"invalid capture index");
  }
  uVar1 = *(uint *)(in_ECX + 0x14 + iVar2 * 8);
  if (uVar1 <= (uint)(*(int *)(in_ECX + 4) - (int)unaff_EBX)) {
    bVar6 = true;
    uVar3 = uVar1;
    pcVar4 = *(char **)(in_ECX + 0x10 + iVar2 * 8);
    pcVar5 = unaff_EBX;
    do {
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      bVar6 = *pcVar4 == *pcVar5;
      pcVar4 = pcVar4 + 1;
      pcVar5 = pcVar5 + 1;
    } while (bVar6);
    if (bVar6) {
      return unaff_EBX + uVar1;
    }
  }
  return (char *)0x0;
}
