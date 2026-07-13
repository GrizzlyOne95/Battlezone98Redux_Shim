/*
 * Entry: 004736ba
 * Name: NextCollidable
 * Namespace: Global
 * Signature: tagENTITY * NextCollidable(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

tagENTITY * __cdecl NextCollidable(void)

{
  if (currentWrap == (wrap_struct *)0x0) {
    return (tagENTITY *)0x0;
  }
  currentWrap = currentWrap->next;
  if (currentWrap == (wrap_struct *)0x0) {
    if (currentHead != &DynamicEnts) {
      return (tagENTITY *)0x0;
    }
    currentHead = &StaticEnts;
    currentWrap = StaticEnts;
    if (StaticEnts == (wrap_struct *)0x0) {
      currentHead = &StaticEnts;
      return (tagENTITY *)0x0;
    }
  }
  return currentWrap->ptr;
}
