/*
 * Entry: 004c00d0
 * Name: std::_Pop_heap_0<RadarItem_*,RadarItem>
 * Namespace: std
 * Signature: void _Pop_heap_0<RadarItem_*,RadarItem>(RadarItem * param_1, RadarItem * param_2, RadarItem * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Pop_heap_0<RadarItem_*,RadarItem>(RadarItem *param_1,RadarItem *param_2,RadarItem *param_3)

{
  RadarItem *pRVar1;
  
  pRVar1 = param_2 + -1;
  _Pop_heap<RadarItem_*,int,RadarItem>(param_1,pRVar1,pRVar1,*pRVar1,(int *)0x0);
  return;
}
