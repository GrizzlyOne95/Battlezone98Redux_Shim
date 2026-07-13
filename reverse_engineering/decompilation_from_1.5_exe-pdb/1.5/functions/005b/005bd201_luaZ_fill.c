/*
 * Entry: 005bd201
 * Name: luaZ_fill
 * Namespace: Global
 * Signature: int luaZ_fill(Zio * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaZ_fill(Zio *param_1)

{
  Zio *pZVar1;
  byte *pbVar2;
  uint uVar3;
  
  pZVar1 = param_1;
  pbVar2 = (byte *)(*param_1->reader)(param_1->L,param_1->data,(uint *)&param_1);
  if ((pbVar2 == (byte *)0x0) || (param_1 == (Zio *)0x0)) {
    uVar3 = 0xffffffff;
  }
  else {
    pZVar1->p = (char *)pbVar2;
    pZVar1->n = (uint)((int)&param_1[-1].L + 3);
    uVar3 = (uint)*pbVar2;
    pZVar1->p = (char *)(pbVar2 + 1);
  }
  return uVar3;
}
