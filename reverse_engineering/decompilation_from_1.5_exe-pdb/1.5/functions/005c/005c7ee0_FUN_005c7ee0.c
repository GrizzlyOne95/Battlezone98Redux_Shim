/*
 * Entry: 005c7ee0
 * Name: FUN_005c7ee0
 * Namespace: Global
 * Signature: undefined FUN_005c7ee0()
 * Symbol source: DEFAULT
 * Export status: ok
 */

undefined4 FUN_005c7ee0(void)

{
  void *pvVar1;
  int in_ECX;
  int unaff_ESI;
  int iVar2;
  
  iVar2 = *(int *)(unaff_ESI + 0x18);
  if (*(int *)(unaff_ESI + 0x1c) < iVar2 - in_ECX) {
    return 0;
  }
  if (iVar2 <= 0x7fffffff - in_ECX) {
    iVar2 = iVar2 + in_ECX;
    if (iVar2 < 0x7fffffdf) {
      iVar2 = iVar2 + 0x20;
    }
    pvVar1 = realloc(*(void **)(unaff_ESI + 0x10),iVar2 * 4);
    if (pvVar1 != (void *)0x0) {
      *(void **)(unaff_ESI + 0x10) = pvVar1;
      pvVar1 = realloc(*(void **)(unaff_ESI + 0x14),iVar2 * 8);
      if (pvVar1 != (void *)0x0) {
        *(void **)(unaff_ESI + 0x14) = pvVar1;
        *(int *)(unaff_ESI + 0x18) = iVar2;
        return 0;
      }
    }
  }
  ogg_stream_clear();
  return 0xffffffff;
}
