/*
 * Entry: 004c01bc
 * Name: std::_Unguarded_partition<RadarItem_*>
 * Namespace: std
 * Signature: pair<RadarItem_*,RadarItem_*> _Unguarded_partition<RadarItem_*>(RadarItem * param_1, RadarItem * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

pair<RadarItem_*,RadarItem_*> __cdecl
std::_Unguarded_partition<RadarItem_*>(RadarItem *param_1,RadarItem *param_2)

{
  RadarItem *pRVar1;
  RadarItem *pRVar2;
  GameObject *pGVar3;
  GameObject *pGVar4;
  RadarItem *pRVar5;
  RadarItem *pRVar6;
  pair<RadarItem_*,RadarItem_*> pVar7;
  RadarItem *in_stack_0000000c;
  RadarItem *pRVar8;
  GameObject *local_8;
  
  pGVar3 = (GameObject *)
           (param_2 +
           (((int)in_stack_0000000c - (int)param_2 >> 3) -
            ((int)in_stack_0000000c - (int)param_2 >> 0x1f) >> 1));
  _Median<RadarItem_*>(param_2,(RadarItem *)pGVar3,in_stack_0000000c + -1);
  pRVar2 = (RadarItem *)&pGVar3->_padding_;
  for (; param_2 < pGVar3; pGVar3 = (GameObject *)&pGVar3[-1].hitch) {
    if ((pGVar3->_padding_ < pGVar3[-1].ownerHandle) || (pGVar3[-1].ownerHandle < pGVar3->_padding_)
       ) break;
  }
  pRVar5 = pRVar2;
  local_8 = pGVar3;
  if (pRVar2 < in_stack_0000000c) {
    do {
      pRVar5 = pRVar2;
      if ((pGVar3->_padding_ < pRVar2->z) || (pRVar2->z < pGVar3->_padding_)) break;
      pRVar2 = pRVar2 + 1;
      pRVar5 = pRVar2;
    } while (pRVar2 < in_stack_0000000c);
  }
LAB_004c023b:
  do {
    if (in_stack_0000000c <= pRVar5) {
LAB_004c0267:
      for (; param_2 < local_8; local_8 = (GameObject *)&local_8[-1].hitch) {
        if (local_8[-1].ownerHandle <= pGVar3->_padding_) {
          if (local_8[-1].ownerHandle < pGVar3->_padding_) break;
          pGVar3 = (GameObject *)&pGVar3[-1].hitch;
          swap<RadarItem>((RadarItem *)pGVar3,(RadarItem *)&local_8[-1].hitch);
        }
      }
      if (local_8 == (GameObject *)param_2) {
        if (pRVar5 == in_stack_0000000c) {
          param_1->obj = pGVar3;
          param_1->z = (long)pRVar2;
          pVar7.second = param_2;
          pVar7.first = param_1;
          return pVar7;
        }
        if (pRVar2 != pRVar5) {
          swap<RadarItem>((RadarItem *)pGVar3,pRVar2);
        }
        pRVar2 = pRVar2 + 1;
        pGVar4 = (GameObject *)&pGVar3->_padding_;
        pRVar6 = pRVar5 + 1;
      }
      else {
        pRVar6 = (RadarItem *)&local_8[-1].hitch;
        pRVar1 = pRVar2;
        pRVar8 = pRVar5;
        local_8 = (GameObject *)pRVar6;
        if (pRVar5 != in_stack_0000000c) goto LAB_004c0231;
        pGVar4 = (GameObject *)&pGVar3[-1].hitch;
        if ((GameObject *)pRVar6 != pGVar4) {
          swap<RadarItem>(pRVar6,(RadarItem *)pGVar4);
        }
        pRVar2 = pRVar2 + -1;
        pRVar6 = pRVar5;
        pGVar3 = pGVar4;
        pRVar5 = pRVar2;
      }
      swap<RadarItem>((RadarItem *)pGVar3,pRVar5);
      pGVar3 = pGVar4;
      pRVar5 = pRVar6;
      goto LAB_004c023b;
    }
    if (pGVar3->_padding_ <= pRVar5->z) {
      if (pGVar3->_padding_ < pRVar5->z) goto LAB_004c0267;
      pRVar1 = pRVar2 + 1;
      pRVar8 = pRVar2;
      pRVar6 = pRVar5;
LAB_004c0231:
      swap<RadarItem>(pRVar8,pRVar6);
      pRVar2 = pRVar1;
    }
    pRVar5 = pRVar5 + 1;
  } while( true );
}
