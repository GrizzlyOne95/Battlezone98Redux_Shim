/*
 * Entry: 004bfe3b
 * Name: std::_Construct<RadarItem,RadarItem>
 * Namespace: std
 * Signature: void _Construct<RadarItem,RadarItem>(RadarItem * param_1, RadarItem * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl std::_Construct<RadarItem,RadarItem>(RadarItem *param_1,RadarItem *param_2)

{
  if (param_1 != (RadarItem *)0x0) {
    param_1->obj = param_2->obj;
    param_1->z = param_2->z;
  }
  return;
}
