/*
 * Entry: 0054838f
 * Name: in_data
 * Namespace: Global
 * Signature: bool in_data(long param_1, long param_2, void * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl in_data(long param_1,long param_2,void *param_3)

{
  char *pcVar1;
  uint in_ECX;
  bool bVar2;
  
  if (((uint)(byte)*inCurrent == param_1) && (*(ushort *)(inCurrent + 2) == in_ECX)) {
    inCurrent = inCurrent + 4;
    pcVar1 = inCurrent + in_ECX;
    bVar2 = pcVar1 <= inLast;
    if (bVar2) {
      memcpy(param_2,inCurrent);
      inCurrent = pcVar1;
    }
    return bVar2;
  }
  return false;
}
