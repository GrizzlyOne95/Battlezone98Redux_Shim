/*
 * Entry: 004bfea2
 * Name: std::_Adjust_heap<RadarItem_*,int,RadarItem>
 * Namespace: std
 * Signature: void _Adjust_heap<RadarItem_*,int,RadarItem>(RadarItem * param_1, int param_2, int param_3, RadarItem param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Adjust_heap<RadarItem_*,int,RadarItem>
          (RadarItem *param_1,int param_2,int param_3,RadarItem param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = param_2;
  while( true ) {
    iVar1 = iVar3 * 2;
    iVar2 = iVar1 + 2;
    if (param_3 <= iVar2) break;
    if (param_1[iVar1 + 1].z < param_1[iVar2].z) {
      iVar2 = iVar1 + 1;
    }
    param_1[iVar3].obj = param_1[iVar2].obj;
    param_1[iVar3].z = param_1[iVar2].z;
    iVar3 = iVar2;
  }
  if (iVar2 == param_3) {
    param_1[iVar3].obj = param_1[param_3 + -1].obj;
    param_1[iVar3].z = param_1[param_3 + -1].z;
    iVar3 = param_3 + -1;
  }
  _Push_heap<RadarItem_*,int,RadarItem>(param_1,iVar3,param_2,param_4);
  return;
}
