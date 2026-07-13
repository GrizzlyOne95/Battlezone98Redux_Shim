/*
 * Entry: 005bdbdd
 * Name: skip_sep
 * Namespace: Global
 * Signature: int skip_sep(LexState * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl skip_sep(LexState *param_1)

{
  LexState *pLVar1;
  int iVar2;
  byte *pbVar3;
  undefined4 *in_EAX;
  LexState *pLVar4;
  int unaff_EDI;
  int iVar5;
  
  pLVar1 = (LexState *)*in_EAX;
  iVar5 = 0;
  save(pLVar1,unaff_EDI);
  iVar2 = *(int *)in_EAX[0xe];
  *(int *)in_EAX[0xe] = iVar2 + -1;
  if (iVar2 == 0) {
    pLVar4 = (LexState *)luaZ_fill((Zio *)in_EAX[0xe]);
  }
  else {
    pbVar3 = *(byte **)(in_EAX[0xe] + 4);
    pLVar4 = (LexState *)(uint)*pbVar3;
    *(byte **)(in_EAX[0xe] + 4) = pbVar3 + 1;
  }
  while (*in_EAX = pLVar4, pLVar4 == (LexState *)0x3d) {
    save((LexState *)*in_EAX,unaff_EDI);
    iVar2 = *(int *)in_EAX[0xe];
    *(int *)in_EAX[0xe] = iVar2 + -1;
    if (iVar2 == 0) {
      pLVar4 = (LexState *)luaZ_fill((Zio *)in_EAX[0xe]);
    }
    else {
      pbVar3 = *(byte **)(in_EAX[0xe] + 4);
      pLVar4 = (LexState *)(uint)*pbVar3;
      *(byte **)(in_EAX[0xe] + 4) = pbVar3 + 1;
    }
    iVar5 = iVar5 + 1;
  }
  if (pLVar4 != pLVar1) {
    iVar5 = -1 - iVar5;
  }
  return iVar5;
}
