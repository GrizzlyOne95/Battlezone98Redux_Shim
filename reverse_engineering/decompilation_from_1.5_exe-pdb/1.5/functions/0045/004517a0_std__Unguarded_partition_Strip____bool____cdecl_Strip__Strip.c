/*
 * Entry: 004517a0
 * Name: std::_Unguarded_partition<Strip_*_*,bool_(__cdecl*)(Strip_*,Strip_*)>
 * Namespace: std
 * Signature: pair<Strip_*_*,Strip_*_*> _Unguarded_partition<Strip_*_*,bool_(__cdecl*)(Strip_*,Strip_*)>(Strip * * param_1, Strip * * param_2, _func___cdecl_bool_Strip_ptr_Strip_ptr * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

pair<Strip_*_*,Strip_*_*> __cdecl
std::_Unguarded_partition<Strip_*_*,bool_(__cdecl*)(Strip_*,Strip_*)>
          (Strip **param_1,Strip **param_2,_func___cdecl_bool_Strip_ptr_Strip_ptr *param_3)

{
  Strip *pSVar1;
  bool bVar2;
  Strip *extraout_EDX;
  Strip *extraout_EDX_00;
  Strip *extraout_EDX_01;
  Strip *extraout_EDX_02;
  Strip *extraout_EDX_03;
  Strip *extraout_EDX_04;
  Strip *extraout_EDX_05;
  Strip *extraout_EDX_06;
  Strip *extraout_EDX_07;
  Strip *pSVar3;
  Strip *pSVar4;
  Strip *pSVar5;
  Strip *pSVar6;
  Strip *pSVar7;
  Strip *pSVar8;
  pair<Strip_*_*,Strip_*_*> pVar9;
  _func___cdecl_bool_Strip_ptr_Strip_ptr *in_stack_00000010;
  Strip *pSStack_4;
  
  pSVar7 = (Strip *)(param_2 +
                    (((int)param_3 - (int)param_2 >> 2) - ((int)param_3 - (int)param_2 >> 0x1f) >> 1
                    ));
  _Median<Strip_*_*,bool_(__cdecl*)(Strip_*,Strip_*)>
            (param_2,(Strip **)pSVar7,(Strip **)(param_3 + -4),in_stack_00000010);
  pSStack_4 = pSVar7;
  pSVar3 = extraout_EDX;
  while (((param_2 < pSStack_4 &&
          (bVar2 = (*in_stack_00000010)(pSStack_4[-1].next,(Strip *)pSStack_4->_padding_),
          pSVar3 = extraout_EDX_00, !bVar2)) &&
         (bVar2 = (*in_stack_00000010)((Strip *)pSStack_4->_padding_,pSStack_4[-1].next),
         pSVar3 = extraout_EDX_01, !bVar2))) {
    pSStack_4 = (Strip *)&pSStack_4[-1].next;
  }
  do {
    pSVar7 = (Strip *)&pSVar7->x0;
    pSVar4 = pSVar7;
    pSVar6 = pSStack_4;
    pSVar5 = pSStack_4;
    if ((param_3 <= pSVar7) ||
       (bVar2 = (*in_stack_00000010)(*(Strip **)pSVar7,(Strip *)pSStack_4->_padding_),
       pSVar3 = extraout_EDX_02, bVar2)) break;
    bVar2 = (*in_stack_00000010)((Strip *)pSStack_4->_padding_,*(Strip **)pSVar7);
    pSVar3 = extraout_EDX_03;
  } while (!bVar2);
joined_r0x00451838:
  do {
    pSVar8 = pSVar6;
    pSVar1 = pSVar4;
    pSVar4 = pSVar5;
    if (param_3 <= pSVar1) {
joined_r0x00451880:
      while (param_2 < pSVar5) {
        pSVar4 = (Strip *)&pSVar4[-1].next;
        bVar2 = (*in_stack_00000010)(*(Strip **)pSVar4,(Strip *)pSVar8->_padding_);
        pSVar3 = extraout_EDX_06;
        if (!bVar2) {
          bVar2 = (*in_stack_00000010)((Strip *)pSVar8->_padding_,*(Strip **)pSVar4);
          pSVar3 = extraout_EDX_07;
          pSVar5 = pSStack_4;
          if (bVar2) break;
          pSVar8 = (Strip *)&pSVar8[-1].next;
          if (pSVar8 != pSVar4) {
            pSVar5 = *(Strip **)pSVar8;
            *(Strip **)pSVar8 = *(Strip **)pSVar4;
            *(Strip **)pSVar4 = pSVar5;
          }
        }
        pSVar5 = (Strip *)&pSStack_4[-1].next;
        pSStack_4 = pSVar5;
      }
      if (pSVar5 == (Strip *)param_2) {
        if (pSVar1 == (Strip *)param_3) {
          *param_1 = pSVar8;
          param_1[1] = pSVar7;
          pVar9.second = (Strip **)pSVar3;
          pVar9.first = param_1;
          return pVar9;
        }
        if ((pSVar7 != pSVar1) && (pSVar8 != pSVar7)) {
          pSVar3 = (Strip *)pSVar7->_padding_;
          pSVar4 = (Strip *)pSVar8->_padding_;
          pSVar8->_padding_ = (int)pSVar3;
          pSVar7->_padding_ = (int)pSVar4;
        }
        pSVar7 = (Strip *)&pSVar7->x0;
        pSVar4 = (Strip *)&pSVar1->x0;
        pSVar6 = (Strip *)&pSVar8->x0;
        if (pSVar8 != pSVar1) {
          pSVar3 = (Strip *)pSVar8->_padding_;
          pSVar8->_padding_ = (int)pSVar1->_padding_;
          pSVar1->_padding_ = (int)pSVar3;
          pSVar5 = pSStack_4;
        }
      }
      else {
        pSStack_4 = (Strip *)&pSVar5[-1].next;
        pSVar5 = pSStack_4;
        if (pSVar1 == (Strip *)param_3) {
          pSVar6 = (Strip *)&pSVar8[-1].next;
          if (pSStack_4 != pSVar6) {
            pSVar4 = *(Strip **)pSStack_4;
            *(Strip **)pSStack_4 = *(Strip **)pSVar6;
            *(Strip **)pSVar6 = pSVar4;
          }
          pSVar7 = (Strip *)&pSVar7[-1].next;
          pSVar4 = pSVar1;
          if (pSVar6 != pSVar7) {
            pSVar3 = *(Strip **)pSVar7;
            pSVar1 = *(Strip **)pSVar6;
            *(Strip **)pSVar6 = pSVar3;
            *(Strip **)pSVar7 = pSVar1;
          }
        }
        else {
          if (pSVar1 != pSStack_4) {
            pSVar4 = (Strip *)pSVar1->_padding_;
            pSVar1->_padding_ = (int)*(Strip **)pSStack_4;
            *(Strip **)pSStack_4 = pSVar4;
          }
          pSVar4 = (Strip *)&pSVar1->x0;
          pSVar6 = pSVar8;
        }
      }
      goto joined_r0x00451838;
    }
    bVar2 = (*in_stack_00000010)((Strip *)pSVar8->_padding_,(Strip *)pSVar1->_padding_);
    pSVar3 = extraout_EDX_04;
    pSVar6 = pSVar7;
    if (!bVar2) {
      bVar2 = (*in_stack_00000010)((Strip *)pSVar1->_padding_,(Strip *)pSVar8->_padding_);
      pSVar3 = extraout_EDX_05;
      if (bVar2) goto joined_r0x00451880;
      pSVar6 = (Strip *)&pSVar7->x0;
      if (pSVar7 != pSVar1) {
        pSVar3 = (Strip *)pSVar1->_padding_;
        pSVar4 = (Strip *)pSVar7->_padding_;
        pSVar7->_padding_ = (int)pSVar3;
        pSVar1->_padding_ = (int)pSVar4;
      }
    }
    pSVar7 = pSVar6;
    pSVar4 = (Strip *)&pSVar1->x0;
    pSVar6 = pSVar8;
  } while( true );
}
