/*
 * Entry: 004bff46
 * Name: std::_Pop_heap<RadarItem_*,int,RadarItem>
 * Namespace: std
 * Signature: void _Pop_heap<RadarItem_*,int,RadarItem>(RadarItem * param_1, RadarItem * param_2, RadarItem * param_3, RadarItem param_4, int * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Pop_heap<RadarItem_*,int,RadarItem>
          (RadarItem *param_1,RadarItem *param_2,RadarItem *param_3,RadarItem param_4,int *param_5)

{
  param_3->obj = param_1->obj;
  param_3->z = param_1->z;
  _Adjust_heap<RadarItem_*,int,RadarItem>(param_1,0,(int)param_2 - (int)param_1 >> 3,param_4);
  return;
}
