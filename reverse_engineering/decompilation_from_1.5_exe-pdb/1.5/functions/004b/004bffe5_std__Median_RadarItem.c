/*
 * Entry: 004bffe5
 * Name: std::_Median<RadarItem_*>
 * Namespace: std
 * Signature: void _Median<RadarItem_*>(RadarItem * param_1, RadarItem * param_2, RadarItem * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl std::_Median<RadarItem_*>(RadarItem *param_1,RadarItem *param_2,RadarItem *param_3)

{
  int iVar1;
  
  iVar1 = (int)param_3 - (int)param_1 >> 3;
  if (iVar1 < 0x29) {
    _Med3<RadarItem_*>(param_1,param_2,param_3);
  }
  else {
    iVar1 = iVar1 + 1;
    iVar1 = (int)(iVar1 + (iVar1 >> 0x1f & 7U)) >> 3;
    _Med3<RadarItem_*>(param_1,param_1 + iVar1,param_1 + iVar1 * 2);
    _Med3<RadarItem_*>(param_2 + -iVar1,param_2,param_2 + iVar1);
    _Med3<RadarItem_*>(param_3 + iVar1 * -2,param_3 + -iVar1,param_3);
    _Med3<RadarItem_*>(param_1 + iVar1,param_2,param_3 + -iVar1);
  }
  return;
}
