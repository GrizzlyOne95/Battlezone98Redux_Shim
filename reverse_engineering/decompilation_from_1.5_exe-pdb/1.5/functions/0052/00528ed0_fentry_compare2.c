/*
 * Entry: 00528ed0
 * Name: fentry_compare2
 * Namespace: Global
 * Signature: int fentry_compare2(void * param_1, void * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl fentry_compare2(void *param_1,void *param_2)

{
  byte bVar1;
  bool bVar2;
  
  while( true ) {
    bVar1 = *(byte *)param_1;
    bVar2 = bVar1 < *(byte *)param_2;
    if (bVar1 != *(byte *)param_2) break;
    if (bVar1 == 0) {
      return 0;
    }
    bVar1 = *(byte *)((int)param_1 + 1);
    bVar2 = bVar1 < *(byte *)((int)param_2 + 1);
    if (bVar1 != *(byte *)((int)param_2 + 1)) break;
    param_1 = (void *)((int)param_1 + 2);
    param_2 = (void *)((int)param_2 + 2);
    if (bVar1 == 0) {
      return 0;
    }
  }
  return (1 - (uint)bVar2) - (uint)(bVar2 != 0);
}
