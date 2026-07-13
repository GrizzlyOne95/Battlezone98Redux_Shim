/*
 * Entry: 005bd23b
 * Name: luaZ_lookahead
 * Namespace: Global
 * Signature: int luaZ_lookahead(Zio * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaZ_lookahead(Zio *param_1)

{
  int iVar1;
  
  if (param_1->n == 0) {
    iVar1 = luaZ_fill(param_1);
    if (iVar1 == -1) {
      return -1;
    }
    param_1->n = param_1->n + 1;
    param_1->p = param_1->p + -1;
  }
  return (uint)(byte)*param_1->p;
}
