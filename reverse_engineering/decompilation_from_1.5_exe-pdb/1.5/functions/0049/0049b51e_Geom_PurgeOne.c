/*
 * Entry: 0049b51e
 * Name: Geom_PurgeOne
 * Namespace: Global
 * Signature: _CACHE_INFO * Geom_PurgeOne(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_CACHE_INFO * __cdecl Geom_PurgeOne(void)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  _CACHE_INFO *p_Var4;
  
  iVar3 = 0;
  p_Var4 = (_CACHE_INFO *)0x0;
  uVar2 = 0;
  do {
    if (((*(int *)((int)&gcache[0].data + uVar2) != 0) &&
        (*(int *)((int)&gcache[0].refCount + uVar2) < 1)) &&
       (iVar1 = *(int *)((int)&gcache[0].size + uVar2), iVar3 < iVar1)) {
      p_Var4 = (_CACHE_INFO *)((int)&gcache[0].id + uVar2);
      iVar3 = iVar1;
    }
    uVar2 = uVar2 + 0x18;
  } while (uVar2 < 0x6000);
  if (p_Var4 != (_CACHE_INFO *)0x0) {
    operator_delete__(p_Var4->data);
    p_Var4->data = (char *)0x0;
    gcacheCount = gcacheCount + -1;
  }
  return p_Var4;
}
