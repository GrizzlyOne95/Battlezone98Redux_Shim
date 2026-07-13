/*
 * Entry: 004c0488
 * Name: std::sort_heap<RadarItem_*>
 * Namespace: std
 * Signature: void sort_heap<RadarItem_*>(RadarItem * param_1, RadarItem * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl std::sort_heap<RadarItem_*>(RadarItem *param_1,RadarItem *param_2)

{
  uint uVar1;
  
  for (uVar1 = (int)param_2 - (int)param_1; 8 < (int)(uVar1 & 0xfffffff8); uVar1 = uVar1 - 8) {
    pop_heap<RadarItem_*>(param_1,param_2);
    param_2 = param_2 + -1;
  }
  return;
}
