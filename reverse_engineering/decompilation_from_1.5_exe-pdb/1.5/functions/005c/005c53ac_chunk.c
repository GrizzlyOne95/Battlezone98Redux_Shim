/*
 * Entry: 005c53ac
 * Name: chunk
 * Namespace: Global
 * Signature: void chunk(LexState * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl chunk(LexState *param_1)

{
  ushort *puVar1;
  int iVar2;
  LexState *unaff_EDI;
  
  enterlevel(unaff_EDI);
  do {
    iVar2 = block_follow((int)unaff_EDI);
    if (iVar2 != 0) break;
    iVar2 = statement(unaff_EDI);
    testnext((LexState *)0x3b,(int)unaff_EDI);
    param_1->fs->freereg = (uint)param_1->fs->nactvar;
  } while (iVar2 == 0);
  puVar1 = &param_1->L->nCcalls;
  *puVar1 = *puVar1 - 1;
  return;
}
