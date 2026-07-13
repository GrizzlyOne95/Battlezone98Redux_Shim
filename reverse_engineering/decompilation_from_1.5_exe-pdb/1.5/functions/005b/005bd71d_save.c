/*
 * Entry: 005bd71d
 * Name: save
 * Namespace: Global
 * Signature: void save(LexState * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl save(LexState *param_1,int param_2)

{
  Mbuffer *pMVar1;
  uint uVar2;
  char *pcVar3;
  LexState *unaff_EBX;
  
  pMVar1 = unaff_EBX->buff;
  if (pMVar1->buffsize < pMVar1->n + 1) {
    if (0x7ffffffd < pMVar1->buffsize) {
      luaX_lexerror(unaff_EBX,"lexical element too long",0);
    }
    uVar2 = pMVar1->buffsize * 2;
    if (uVar2 + 1 < 0xfffffffe) {
      pcVar3 = luaM_realloc_(unaff_EBX->L,pMVar1->buffer,pMVar1->buffsize,uVar2);
    }
    else {
      pcVar3 = luaM_toobig(unaff_EBX->L);
    }
    pMVar1->buffsize = uVar2;
    pMVar1->buffer = pcVar3;
  }
  pMVar1->buffer[pMVar1->n] = (char)param_1;
  pMVar1->n = pMVar1->n + 1;
  return;
}
