/*
 * Entry: 004c02da
 * Name: std::make_heap<RadarItem_*>
 * Namespace: std
 * Signature: void make_heap<RadarItem_*>(RadarItem * param_1, RadarItem * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl std::make_heap<RadarItem_*>(RadarItem *param_1,RadarItem *param_2)

{
  if (8 < (int)((int)param_2 - (int)param_1 & 0xfffffff8U)) {
    _Make_heap<RadarItem_*,int,RadarItem>(param_1,param_2,(int *)0x0,(RadarItem *)0x0);
  }
  return;
}
