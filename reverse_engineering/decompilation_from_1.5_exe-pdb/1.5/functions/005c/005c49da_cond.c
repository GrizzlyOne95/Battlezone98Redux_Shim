/*
 * Entry: 005c49da
 * Name: cond
 * Namespace: Global
 * Signature: int cond(LexState * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl cond(LexState *param_1)

{
  LexState *unaff_ESI;
  expdesc local_1c;
  
  expr(unaff_ESI,&local_1c);
  if (local_1c.k == VNIL) {
    local_1c.k = VFALSE;
  }
  luaK_goiftrue(unaff_ESI->fs,&local_1c);
  return local_1c.f;
}
