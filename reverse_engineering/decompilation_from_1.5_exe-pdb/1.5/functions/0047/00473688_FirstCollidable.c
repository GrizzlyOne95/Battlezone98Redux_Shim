/*
 * Entry: 00473688
 * Name: FirstCollidable
 * Namespace: Global
 * Signature: tagENTITY * FirstCollidable(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

tagENTITY * __cdecl FirstCollidable(void)

{
  if (DynamicEnts == (wrap_struct *)0x0) {
    currentHead = &StaticEnts;
    currentWrap = StaticEnts;
  }
  else {
    currentHead = &DynamicEnts;
    currentWrap = DynamicEnts;
  }
  if (currentWrap == (wrap_struct *)0x0) {
    return (tagENTITY *)0x0;
  }
  return currentWrap->ptr;
}
