/*
 * Entry: 004e7291
 * Name: AnimObj_Close
 * Namespace: Global
 * Signature: long AnimObj_Close(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl AnimObj_Close(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = AnimCount;
  if ((AnimHeap != (void *)0x0) && (iVar2 = 0, 0 < AnimCount)) {
    do {
      if (AnimList[iVar2] != (tagANIMOBJ_HEADER *)0x0) {
        free(AnimList[iVar2]);
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < iVar1);
  }
  AnimHeap = (void *)0x0;
  AnimObj_ActiveCount = 0;
  AnimCount = 0;
  memset(AnimList,0,0x800);
  memset(AnimActiveList,0,0x4000);
  return 0;
}
