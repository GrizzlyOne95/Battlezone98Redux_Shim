/*
 * Entry: 00451a70
 * Name: PreDrawNodes
 * Namespace: Global
 * Signature: void PreDrawNodes(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl PreDrawNodes(void)

{
  Strip ***pppSVar1;
  int *piVar2;
  Strip **ppSVar3;
  vector<Strip_*,std::allocator<Strip_*>_> *pvVar4;
  Strip ***pppSVar5;
  int iVar6;
  Strip **ppSVar7;
  
  pvVar4 = usedStrips;
  ppSVar7 = usedStrips->_Myfirst;
  pppSVar1 = &usedStrips->_Myfirst;
  pppSVar5 = &usedStrips->_Mylast;
  if (*pppSVar5 < ppSVar7) {
    _invalid_parameter_noinfo();
  }
  piVar2 = (int *)pvVar4->_padding_;
  do {
    ppSVar3 = *pppSVar5;
    if (ppSVar3 < *pppSVar1) {
      _invalid_parameter_noinfo();
    }
    if ((piVar2 == (int *)0x0) || (piVar2 != (int *)pvVar4->_padding_)) {
      _invalid_parameter_noinfo();
    }
    if (ppSVar7 == ppSVar3) {
      return;
    }
    if (piVar2 == (int *)0x0) {
      _invalid_parameter_noinfo();
      iVar6 = 0;
    }
    else {
      iVar6 = *piVar2;
    }
    if (*(Strip ***)(iVar6 + 0x10) <= ppSVar7) {
      _invalid_parameter_noinfo();
    }
    iVar6 = (0 < NodeNeighbor::count) - 1;
    do {
      if (iVar6 < 0) break;
      ExpandingArray<NodeNeighbor>::operator[](&NodeNeighbor::neighbors,iVar6);
      iVar6 = iVar6 + 1;
    } while (iVar6 < NodeNeighbor::count);
    if (piVar2 == (int *)0x0) {
      _invalid_parameter_noinfo();
      iVar6 = 0;
    }
    else {
      iVar6 = *piVar2;
    }
    if (*(Strip ***)(iVar6 + 0x10) <= ppSVar7) {
      _invalid_parameter_noinfo();
    }
    ppSVar7 = ppSVar7 + 1;
  } while( true );
}
