/*
 * Entry: 004eb9f2
 * Name: InvalidateAllBSPs
 * Namespace: Global
 * Signature: void InvalidateAllBSPs(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl InvalidateAllBSPs(void)

{
  tagENTITY *ptVar1;
  int iVar2;
  
  ptVar1 = world;
  for (iVar2 = world_count; 0 < iVar2; iVar2 = iVar2 + -1) {
    if (ptVar1->obj76 != (_OBJ76 *)0x0) {
      Cache_Invalidate_Bsp(ptVar1);
    }
    ptVar1 = ptVar1 + 1;
  }
  return;
}
