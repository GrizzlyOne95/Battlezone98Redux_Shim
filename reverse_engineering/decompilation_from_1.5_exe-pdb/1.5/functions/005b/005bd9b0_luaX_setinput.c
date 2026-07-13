/*
 * Entry: 005bd9b0
 * Name: luaX_setinput
 * Namespace: Global
 * Signature: void luaX_setinput(lua_State * param_1, LexState * param_2, Zio * param_3, TString * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaX_setinput(lua_State *param_1,LexState *param_2,Zio *param_3,TString *param_4)

{
  Mbuffer *pMVar1;
  byte *pbVar2;
  char *pcVar3;
  uint uVar4;
  
  param_2->fs = (FuncState *)0x0;
  param_2->z = param_3;
  param_2->linenumber = 1;
  param_2->lastline = 1;
  param_2->source = param_4;
  pMVar1 = param_2->buff;
  param_2->decpoint = '.';
  param_2->L = param_1;
  (param_2->lookahead).token = 0x11f;
  pcVar3 = luaM_realloc_(param_1,pMVar1->buffer,pMVar1->buffsize,0x20);
  param_2->buff->buffer = pcVar3;
  param_2->buff->buffsize = 0x20;
  uVar4 = param_2->z->n;
  param_2->z->n = uVar4 - 1;
  if (uVar4 == 0) {
    uVar4 = luaZ_fill(param_2->z);
  }
  else {
    pbVar2 = (byte *)param_2->z->p;
    uVar4 = (uint)*pbVar2;
    param_2->z->p = (char *)(pbVar2 + 1);
  }
  param_2->current = uVar4;
  return;
}
