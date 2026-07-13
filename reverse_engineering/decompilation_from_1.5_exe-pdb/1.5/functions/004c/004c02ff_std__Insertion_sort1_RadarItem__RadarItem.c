/*
 * Entry: 004c02ff
 * Name: std::_Insertion_sort1<RadarItem_*,RadarItem>
 * Namespace: std
 * Signature: void _Insertion_sort1<RadarItem_*,RadarItem>(RadarItem * param_1, RadarItem * param_2, RadarItem * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Insertion_sort1<RadarItem_*,RadarItem>
          (RadarItem *param_1,RadarItem *param_2,RadarItem *param_3)

{
  int iVar1;
  int iVar2;
  GameObject *pGVar3;
  RadarItem *pRVar4;
  RadarItem *pRVar5;
  
  pRVar5 = param_1;
  if (param_1 != param_2) {
    while (pRVar5 = pRVar5 + 1, pRVar5 != param_2) {
      iVar2 = pRVar5->z;
      pGVar3 = pRVar5->obj;
      if (param_1->z < iVar2) {
        stdext::unchecked_copy_backward<RadarItem_*,RadarItem_*>(param_1,pRVar5,pRVar5 + 1);
        param_1->obj = pGVar3;
        param_1->z = iVar2;
      }
      else {
        iVar1 = pRVar5[-1].z;
        pRVar4 = pRVar5;
        while (iVar1 < iVar2) {
          pRVar4->obj = pRVar4[-1].obj;
          pRVar4->z = pRVar4[-1].z;
          iVar1 = pRVar4[-2].z;
          pRVar4 = pRVar4 + -1;
        }
        pRVar4->obj = pGVar3;
        pRVar4->z = iVar2;
      }
    }
  }
  return;
}
