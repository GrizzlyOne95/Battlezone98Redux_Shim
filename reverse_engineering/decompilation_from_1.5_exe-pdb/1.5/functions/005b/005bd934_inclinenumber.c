/*
 * Entry: 005bd934
 * Name: inclinenumber
 * Namespace: Global
 * Signature: void inclinenumber(LexState * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl inclinenumber(LexState *param_1)

{
  uint uVar1;
  byte *pbVar2;
  uint uVar3;
  LexState *unaff_ESI;
  
  uVar3 = unaff_ESI->z->n;
  uVar1 = unaff_ESI->current;
  unaff_ESI->z->n = uVar3 - 1;
  if (uVar3 == 0) {
    uVar3 = luaZ_fill(unaff_ESI->z);
  }
  else {
    pbVar2 = (byte *)unaff_ESI->z->p;
    uVar3 = (uint)*pbVar2;
    unaff_ESI->z->p = (char *)(pbVar2 + 1);
  }
  unaff_ESI->current = uVar3;
  if (((uVar3 == 10) || (uVar3 == 0xd)) && (uVar3 != uVar1)) {
    uVar3 = unaff_ESI->z->n;
    unaff_ESI->z->n = uVar3 - 1;
    if (uVar3 == 0) {
      uVar3 = luaZ_fill(unaff_ESI->z);
    }
    else {
      pbVar2 = (byte *)unaff_ESI->z->p;
      uVar3 = (uint)*pbVar2;
      unaff_ESI->z->p = (char *)(pbVar2 + 1);
    }
    unaff_ESI->current = uVar3;
  }
  unaff_ESI->linenumber = unaff_ESI->linenumber + 1;
  if (0x7ffffffc < unaff_ESI->linenumber) {
    luaX_syntaxerror(unaff_ESI,"chunk has too many lines");
  }
  return;
}
