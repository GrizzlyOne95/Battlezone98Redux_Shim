/*
 * Entry: 004bfe5e
 * Name: std::_Med3<RadarItem_*>
 * Namespace: std
 * Signature: void _Med3<RadarItem_*>(RadarItem * param_1, RadarItem * param_2, RadarItem * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl std::_Med3<RadarItem_*>(RadarItem *param_1,RadarItem *param_2,RadarItem *param_3)

{
  if (param_1->z < param_2->z) {
    swap<RadarItem>(param_2,param_1);
  }
  if (param_2->z < param_3->z) {
    swap<RadarItem>(param_3,param_2);
  }
  if (param_1->z < param_2->z) {
    swap<RadarItem>(param_2,param_1);
  }
  return;
}
