/*
 * Entry: 004c0069
 * Name: std::_Make_heap<RadarItem_*,int,RadarItem>
 * Namespace: std
 * Signature: void _Make_heap<RadarItem_*,int,RadarItem>(RadarItem * param_1, RadarItem * param_2, int * param_3, RadarItem * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Make_heap<RadarItem_*,int,RadarItem>
          (RadarItem *param_1,RadarItem *param_2,int *param_3,RadarItem *param_4)

{
  RadarItem *pRVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = (int)param_2 - (int)param_1 >> 3;
  iVar2 = iVar3 - ((int)param_2 - (int)param_1 >> 0x1f) >> 1;
  if (0 < iVar2) {
    pRVar1 = param_1 + iVar2;
    do {
      pRVar1 = pRVar1 + -1;
      iVar2 = iVar2 + -1;
      _Adjust_heap<RadarItem_*,int,RadarItem>(param_1,iVar2,iVar3,*pRVar1);
    } while (0 < iVar2);
  }
  return;
}
