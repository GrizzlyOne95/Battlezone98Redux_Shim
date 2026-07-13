/*
 * Entry: 005c4a0c
 * Name: breakstat
 * Namespace: Global
 * Signature: void breakstat(LexState * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl breakstat(LexState *param_1)

{
  uchar *puVar1;
  FuncState *pFVar2;
  LexState *in_EAX;
  int iVar3;
  byte bVar4;
  BlockCnt *pBVar5;
  
  pFVar2 = in_EAX->fs;
  pBVar5 = pFVar2->bl;
  bVar4 = 0;
  if (pBVar5 != (BlockCnt *)0x0) {
    do {
      if (pBVar5->isbreakable != '\0') break;
      puVar1 = &pBVar5->upval;
      pBVar5 = pBVar5->previous;
      bVar4 = bVar4 | *puVar1;
    } while (pBVar5 != (BlockCnt *)0x0);
    if (pBVar5 != (BlockCnt *)0x0) goto LAB_005c4a3e;
  }
  luaX_syntaxerror(in_EAX,"no loop to break");
LAB_005c4a3e:
  if (bVar4 != 0) {
    luaK_codeABC(pFVar2,OP_CLOSE,(uint)pBVar5->nactvar,0,0);
  }
  iVar3 = luaK_jump(pFVar2);
  luaK_concat(pFVar2,&pBVar5->breaklist,iVar3);
  return;
}
