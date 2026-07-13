/*
 * Entry: 005bd283
 * Name: luaZ_read
 * Namespace: Global
 * Signature: uint luaZ_read(Zio * param_1, void * param_2, uint param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __cdecl luaZ_read(Zio *param_1,void *param_2,uint param_3)

{
  int iVar1;
  uint uVar2;
  
  while( true ) {
    if (param_3 == 0) {
      return 0;
    }
    iVar1 = luaZ_lookahead(param_1);
    if (iVar1 == -1) break;
    uVar2 = param_1->n;
    if (param_3 <= param_1->n) {
      uVar2 = param_3;
    }
    memcpy(param_2,param_1->p,uVar2);
    param_1->n = param_1->n - uVar2;
    param_1->p = param_1->p + uVar2;
    param_2 = (void *)((int)param_2 + uVar2);
    param_3 = param_3 - uVar2;
  }
  return param_3;
}
