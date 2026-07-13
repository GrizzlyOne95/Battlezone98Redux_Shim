/*
 * Entry: 00585f30
 * Name: lzo_memcmp
 * Namespace: Global
 * Signature: int lzo_memcmp(void * param_1, void * param_2, ulong param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl lzo_memcmp(void *param_1,void *param_2,ulong param_3)

{
  int iVar1;
  bool bVar2;
  bool bVar3;
  
  bVar2 = false;
  iVar1 = 0;
  bVar3 = true;
  do {
    if (param_3 == 0) break;
    param_3 = param_3 - 1;
    bVar2 = *(byte *)param_1 < *(byte *)param_2;
    bVar3 = *(byte *)param_1 == *(byte *)param_2;
    param_1 = (byte *)((int)param_1 + 1);
    param_2 = (byte *)((int)param_2 + 1);
  } while (bVar3);
  if (!bVar3) {
    iVar1 = (1 - (uint)bVar2) - (uint)(bVar2 != 0);
  }
  return iVar1;
}
