/*
 * Entry: 005bda2e
 * Name: check_next
 * Namespace: Global
 * Signature: int check_next(LexState * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl check_next(LexState *param_1,char *param_2)

{
  int iVar1;
  byte *pbVar2;
  uint *in_EAX;
  char *pcVar3;
  uint uVar4;
  int unaff_EBX;
  
  pcVar3 = strchr((char *)param_1,*in_EAX);
  if (pcVar3 == (char *)0x0) {
    return 0;
  }
  save((LexState *)*in_EAX,unaff_EBX);
  iVar1 = *(int *)in_EAX[0xe];
  *(int *)in_EAX[0xe] = iVar1 + -1;
  if (iVar1 == 0) {
    uVar4 = luaZ_fill((Zio *)in_EAX[0xe]);
  }
  else {
    pbVar2 = *(byte **)(in_EAX[0xe] + 4);
    uVar4 = (uint)*pbVar2;
    *(byte **)(in_EAX[0xe] + 4) = pbVar2 + 1;
  }
  *in_EAX = uVar4;
  return 1;
}
