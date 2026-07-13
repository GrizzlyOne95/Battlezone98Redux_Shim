/*
 * Entry: 005c7e80
 * Name: FUN_005c7e80
 * Namespace: Global
 * Signature: undefined FUN_005c7e80()
 * Symbol source: DEFAULT
 * Export status: ok
 */

undefined4 FUN_005c7e80(void)

{
  int iVar1;
  void *pvVar2;
  int in_ECX;
  undefined4 *unaff_ESI;
  size_t _NewSize;
  
  iVar1 = unaff_ESI[1];
  if ((int)unaff_ESI[2] < iVar1 - in_ECX) {
    return 0;
  }
  if (iVar1 <= 0x7fffffff - in_ECX) {
    _NewSize = iVar1 + in_ECX;
    if ((int)_NewSize < 0x7ffffbff) {
      _NewSize = _NewSize + 0x400;
    }
    pvVar2 = realloc((void *)*unaff_ESI,_NewSize);
    if (pvVar2 != (void *)0x0) {
      unaff_ESI[1] = _NewSize;
      *unaff_ESI = pvVar2;
      return 0;
    }
  }
  ogg_stream_clear();
  return 0xffffffff;
}
