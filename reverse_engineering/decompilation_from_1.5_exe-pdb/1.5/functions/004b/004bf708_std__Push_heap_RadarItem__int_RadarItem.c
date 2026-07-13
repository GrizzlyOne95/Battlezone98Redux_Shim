/*
 * Entry: 004bf708
 * Name: std::_Push_heap<RadarItem_*,int,RadarItem>
 * Namespace: std
 * Signature: void _Push_heap<RadarItem_*,int,RadarItem>(RadarItem * param_1, int param_2, int param_3, RadarItem param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Push_heap<RadarItem_*,int,RadarItem>
          (RadarItem *param_1,int param_2,int param_3,RadarItem param_4)

{
  int iVar1;
  
  while ((iVar1 = (param_2 + -1) / 2, param_3 < param_2 && (param_4.z < param_1[iVar1].z))) {
    param_1[param_2].obj = param_1[iVar1].obj;
    param_1[param_2].z = param_1[iVar1].z;
    param_2 = iVar1;
  }
  param_1[param_2].z = param_4.z;
  param_1[param_2].obj = param_4.obj;
  return;
}
