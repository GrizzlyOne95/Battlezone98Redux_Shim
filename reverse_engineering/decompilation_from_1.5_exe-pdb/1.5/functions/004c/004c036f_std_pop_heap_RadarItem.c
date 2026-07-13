/*
 * Entry: 004c036f
 * Name: std::pop_heap<RadarItem_*>
 * Namespace: std
 * Signature: void pop_heap<RadarItem_*>(RadarItem * param_1, RadarItem * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl std::pop_heap<RadarItem_*>(RadarItem *param_1,RadarItem *param_2)

{
  if (8 < (int)((int)param_2 - (int)param_1 & 0xfffffff8U)) {
    _Pop_heap_0<RadarItem_*,RadarItem>(param_1,param_2,(RadarItem *)0x0);
  }
  return;
}
