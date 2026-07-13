/*
 * Entry: 00453560
 * Name: Search::Clean
 * Namespace: Search
 * Signature: void Clean(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Search::Clean(void)

{
  Strip ***pppSVar1;
  int *piVar2;
  Strip **ppSVar3;
  Strip *pSVar4;
  Strip **ppSVar5;
  _Vector_const_iterator<Strip_*,std::allocator<Strip_*>_> _Var6;
  _Vector_const_iterator<Strip_*,std::allocator<Strip_*>_> _Var7;
  _Vector_const_iterator<Strip_*,std::allocator<Strip_*>_> _Var8;
  vector<Strip_*,std::allocator<Strip_*>_> *this;
  vector<Strip_*,std::allocator<Strip_*>_> *this_00;
  Strip ***pppSVar9;
  int iVar10;
  uint uVar11;
  Strip **ppSVar12;
  undefined1 local_8 [8];
  
  this = usedStrips;
  ppSVar12 = usedStrips->_Myfirst;
  pppSVar1 = &usedStrips->_Myfirst;
  pppSVar9 = &usedStrips->_Mylast;
  if (*pppSVar9 < ppSVar12) {
    _invalid_parameter_noinfo();
  }
  piVar2 = (int *)this->_padding_;
  while( true ) {
    ppSVar3 = *pppSVar9;
    if (ppSVar3 < *pppSVar1) {
      _invalid_parameter_noinfo();
    }
    if ((piVar2 == (int *)0x0) || (piVar2 != (int *)this->_padding_)) {
      _invalid_parameter_noinfo();
    }
    if (ppSVar12 == ppSVar3) break;
    if (piVar2 == (int *)0x0) {
      _invalid_parameter_noinfo();
      iVar10 = 0;
    }
    else {
      iVar10 = *piVar2;
    }
    if (*(Strip ***)(iVar10 + 0x10) <= ppSVar12) {
      _invalid_parameter_noinfo();
    }
    this_00 = freeStrips;
    pSVar4 = *ppSVar12;
    if ((pSVar4->detour == false) && (pSVar4->link == false)) {
      pSVar4->link = false;
      pSVar4->g = 0.0;
      pSVar4->open = false;
      pSVar4->backward = false;
      pSVar4->detour = false;
      pSVar4->visited = false;
      pSVar4->prev = (Strip *)0x0;
      pSVar4->next = (Strip *)0x0;
    }
    else {
      pSVar4->seqNo = 0;
      ppSVar3 = this_00->_Myfirst;
      if (ppSVar3 == (Strip **)0x0) {
        uVar11 = 0;
      }
      else {
        uVar11 = (int)this_00->_Myend - (int)ppSVar3 >> 2;
      }
      ppSVar5 = this_00->_Mylast;
      if ((uint)((int)ppSVar5 - (int)ppSVar3 >> 2) < uVar11) {
        *ppSVar5 = pSVar4;
        freeStrips->_Mylast = ppSVar5 + 1;
      }
      else {
        if (ppSVar5 < ppSVar3) {
          _invalid_parameter_noinfo();
        }
        _Var7._Myptr = (Strip **)this_00->_padding_;
        _Var7._padding_ = (int)local_8;
        std::vector<Strip_*,std::allocator<Strip_*>_>::insert(this_00,_Var7,ppSVar5);
      }
    }
    if (piVar2 == (int *)0x0) {
      _invalid_parameter_noinfo();
      iVar10 = 0;
    }
    else {
      iVar10 = *piVar2;
    }
    if (*(Strip ***)(iVar10 + 0x10) <= ppSVar12) {
      _invalid_parameter_noinfo();
    }
    ppSVar12 = ppSVar12 + 1;
  }
  if (*pppSVar9 < *pppSVar1) {
    _invalid_parameter_noinfo();
  }
  ppSVar12 = *pppSVar1;
  ppSVar3 = (Strip **)this->_padding_;
  if (*pppSVar9 < ppSVar12) {
    _invalid_parameter_noinfo();
  }
  _Var6._Myptr = (Strip **)this->_padding_;
  _Var6._padding_ = (int)local_8;
  _Var8._Myptr = ppSVar3;
  _Var8._padding_ = (int)ppSVar12;
  std::vector<Strip_*,std::allocator<Strip_*>_>::erase(this,_Var6,_Var8);
  NodeNeighbor::count = 0;
  curFindPath = (PathPlan *)0x0;
  return;
}
