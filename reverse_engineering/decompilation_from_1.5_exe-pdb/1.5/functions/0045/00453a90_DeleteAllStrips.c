/*
 * Entry: 00453a90
 * Name: DeleteAllStrips
 * Namespace: Global
 * Signature: void DeleteAllStrips(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DeleteAllStrips(void)

{
  Strip **ppSVar1;
  Strip *pSVar2;
  Strip **ppSVar3;
  _Vector_const_iterator<Strip_*,std::allocator<Strip_*>_> _Var4;
  _Vector_const_iterator<Strip_*,std::allocator<Strip_*>_> _Var5;
  _Vector_const_iterator<Strip_*,std::allocator<Strip_*>_> _Var6;
  _Vector_const_iterator<Strip_*,std::allocator<Strip_*>_> _Var7;
  _Vector_const_iterator<Strip_*,std::allocator<Strip_*>_> _Var8;
  vector<Strip_*,std::allocator<Strip_*>_> *pvVar9;
  vector<Strip_*,std::allocator<Strip_*>_> *pvVar10;
  int iVar11;
  uint uVar12;
  Strip ***pppSVar13;
  Strip **ppSVar14;
  Strip ***pppSVar15;
  int *piVar16;
  int *piStack_1c;
  undefined1 local_14 [4];
  undefined1 local_10 [4];
  undefined1 auStack_c [8];
  
  if (zones != (PathZone *)0x0) {
    pppSVar13 = (Strip ***)(zoneHeight * zoneWidth);
    if (pppSVar13 != (Strip ***)0x0) {
      pppSVar15 = &(zones->terrainStrips)._Myfirst;
      do {
        ppSVar14 = *pppSVar15;
        pppSVar13 = (Strip ***)((int)pppSVar13 + -1);
        if (pppSVar15[1] < ppSVar14) {
          _invalid_parameter_noinfo();
        }
        piVar16 = (int *)((vector<Strip_*,std::allocator<Strip_*>_> *)(pppSVar15 + -3))->_padding_;
        while( true ) {
          ppSVar1 = pppSVar15[1];
          if (ppSVar1 < *pppSVar15) {
            _invalid_parameter_noinfo();
          }
          if ((piVar16 == (int *)0x0) ||
             (piVar16 !=
              (int *)((vector<Strip_*,std::allocator<Strip_*>_> *)(pppSVar15 + -3))->_padding_)) {
            _invalid_parameter_noinfo();
          }
          if (ppSVar14 == ppSVar1) break;
          if (piVar16 == (int *)0x0) {
            _invalid_parameter_noinfo();
            iVar11 = 0;
          }
          else {
            iVar11 = *piVar16;
          }
          if (*(Strip ***)(iVar11 + 0x10) <= ppSVar14) {
            _invalid_parameter_noinfo();
          }
          pvVar9 = freeStrips;
          pSVar2 = *ppSVar14;
          pSVar2->seqNo = 0;
          pvVar10 = freeStrips;
          ppSVar1 = pvVar9->_Myfirst;
          if (ppSVar1 == (Strip **)0x0) {
            uVar12 = 0;
          }
          else {
            uVar12 = (int)pvVar9->_Myend - (int)ppSVar1 >> 2;
          }
          ppSVar3 = pvVar9->_Mylast;
          if ((uint)((int)ppSVar3 - (int)ppSVar1 >> 2) < uVar12) {
            *ppSVar3 = pSVar2;
            pvVar10->_Mylast = ppSVar3 + 1;
          }
          else {
            if (ppSVar3 < ppSVar1) {
              _invalid_parameter_noinfo();
            }
            _Var6._Myptr = (Strip **)pvVar9->_padding_;
            _Var6._padding_ = (int)local_14;
            std::vector<Strip_*,std::allocator<Strip_*>_>::insert(pvVar9,_Var6,ppSVar3);
          }
          if (piStack_1c == (int *)0x0) {
            _invalid_parameter_noinfo();
            iVar11 = 0;
          }
          else {
            iVar11 = *piStack_1c;
          }
          if (*(Strip ***)(iVar11 + 0x10) <= ppSVar14) {
            _invalid_parameter_noinfo();
          }
          ppSVar14 = ppSVar14 + 1;
          pppSVar15 = pppSVar13;
          piVar16 = piStack_1c;
        }
        if (pppSVar15[1] < *pppSVar15) {
          _invalid_parameter_noinfo();
        }
        ppSVar14 = *pppSVar15;
        ppSVar1 = (Strip **)
                  ((vector<Strip_*,std::allocator<Strip_*>_> *)(pppSVar15 + -3))->_padding_;
        if (pppSVar15[1] < ppSVar14) {
          _invalid_parameter_noinfo();
        }
        _Var5._Myptr = (Strip **)
                       ((vector<Strip_*,std::allocator<Strip_*>_> *)(pppSVar15 + -3))->_padding_;
        _Var5._padding_ = (int)auStack_c;
        _Var8._Myptr = ppSVar1;
        _Var8._padding_ = (int)ppSVar14;
        std::vector<Strip_*,std::allocator<Strip_*>_>::erase
                  ((vector<Strip_*,std::allocator<Strip_*>_> *)(pppSVar15 + -3),_Var5,_Var8);
        pppSVar15 = pppSVar15 + 0x49;
      } while (pppSVar13 != (Strip ***)0x0);
    }
    if (zones != (PathZone *)0x0) {
      PathZone::_vector_deleting_destructor_(zones,3);
    }
    pathMem = pathMem + zoneHeight * zoneWidth * -0x124;
    zones = (PathZone *)0x0;
  }
  pvVar9 = freeStrips;
  if (freeStrips != (vector<Strip_*,std::allocator<Strip_*>_> *)0x0) {
    StripCount = 0;
    pppSVar13 = &freeStrips->_Mylast;
    pppSVar15 = &freeStrips->_Myfirst;
    if (freeStrips->_Mylast < freeStrips->_Myfirst) {
      _invalid_parameter_noinfo();
    }
    ppSVar14 = *pppSVar15;
    ppSVar1 = (Strip **)pvVar9->_padding_;
    if (*pppSVar13 < ppSVar14) {
      _invalid_parameter_noinfo();
    }
    _Var4._Myptr = (Strip **)pvVar9->_padding_;
    _Var4._padding_ = (int)local_10;
    _Var7._Myptr = ppSVar1;
    _Var7._padding_ = (int)ppSVar14;
    std::vector<Strip_*,std::allocator<Strip_*>_>::erase(pvVar9,_Var4,_Var7);
    std::vector<Strip_*,std::allocator<Strip_*>_>::reserve(pvVar9,0x10000);
  }
  if (stripList != (tagSTRIP *)0x0) {
    operator_delete__(stripList);
    stripList = (tagSTRIP *)0x0;
    stripListSize = 0;
    stripListMax = 0;
  }
  if (ContainerNeighbor::neighbors != (ContainerNeighbor *)0x0) {
    operator_delete__(ContainerNeighbor::neighbors);
  }
  iVar11 = ContainerNeighbor::maxNeighbors;
  ContainerNeighbor::neighbors = (ContainerNeighbor *)0x0;
  ContainerNeighbor::maxNeighbors = 0;
  pathMem = pathMem + iVar11 * -0x10;
  ContainerNeighbor::firstFree = -1;
  return;
}
