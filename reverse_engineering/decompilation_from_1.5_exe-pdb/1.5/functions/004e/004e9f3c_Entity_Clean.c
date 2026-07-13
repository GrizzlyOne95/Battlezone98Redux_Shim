/*
 * Entry: 004e9f3c
 * Name: Entity_Clean
 * Namespace: Global
 * Signature: void Entity_Clean(tagENTITY * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Entity_Clean(tagENTITY *param_1)

{
  tagENTITY *unaff_ESI;
  
  if (((unaff_ESI->cType == CLSN_TYPE_CAR) && (unaff_ESI->clsnDetails != (void *)0x0)) &&
     (hDefaultHeap != (void *)0x0)) {
    free(unaff_ESI->clsnDetails);
  }
  Cache_Invalidate_Bsp(unaff_ESI);
  Entity_Clear(unaff_ESI);
  return;
}
