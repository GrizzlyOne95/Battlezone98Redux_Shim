/*
 * Entry: 004e7f17
 * Name: Cache_Invalidate_Bsp
 * Namespace: Global
 * Signature: void Cache_Invalidate_Bsp(tagENTITY * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Cache_Invalidate_Bsp(tagENTITY *param_1)

{
  param_1->Bsp_Geom_LOD = -1;
  param_1->Bsp_LRU_Stamp = 0;
  if (param_1->Bsp_Container != (BSP_CONTAINER *)0x0) {
    Delete_Container(param_1);
  }
  return;
}
