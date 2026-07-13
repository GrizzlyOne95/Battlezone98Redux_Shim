/*
 * Entry: 00452f40
 * Name: InvalidateZoneStrips
 * Namespace: Global
 * Signature: void InvalidateZoneStrips(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl InvalidateZoneStrips(int param_1,int param_2)

{
  vector<Strip_*,std::allocator<Strip_*>_> *this;
  Strip *pSVar1;
  float fVar2;
  vector<Strip_*,std::allocator<Strip_*>_> *this_00;
  Strip **ppSVar3;
  PathZone *pPVar4;
  _Vector_iterator<Strip_*,std::allocator<Strip_*>_> _Var5;
  Strip *local_1c [2];
  undefined8 local_14;
  
  if ((((-1 < param_1) && (param_1 <= sBuiltZoneHeight)) && (-1 < param_2)) &&
     ((param_2 <= sBuiltZoneWidth &&
      (pPVar4 = zones + zoneWidth * param_1 + param_2, pPVar4->built != false)))) {
    this = &pPVar4->terrainStrips;
    _Var5 = std::vector<Strip_*,std::allocator<Strip_*>_>::begin(this);
    local_14._0_4_ = (Strip *)*_Var5._0_4_;
    local_14._4_4_ = (Strip *)_Var5._0_4_[1];
    while( true ) {
      local_1c[0] = (Strip *)(pPVar4->terrainStrips)._Mylast;
      if (local_1c[0] < (Strip *)(pPVar4->terrainStrips)._Myfirst) {
        _invalid_parameter_noinfo();
      }
      if (((Strip *)local_14 == (Strip *)0x0) || ((Strip *)local_14 != (Strip *)this->_padding_)) {
        _invalid_parameter_noinfo();
      }
      if (local_14._4_4_ == local_1c[0]) break;
      ppSVar3 = std::_Vector_iterator<Strip_*,std::allocator<Strip_*>_>::operator*
                          ((_Vector_iterator<Strip_*,std::allocator<Strip_*>_> *)&local_14);
      pSVar1 = *ppSVar3;
      ContainerNeighbor::Unlink(pSVar1);
      this_00 = freeStrips;
      pSVar1->seqNo = 0;
      local_1c[0] = pSVar1;
      std::vector<Strip_*,std::allocator<Strip_*>_>::push_back(this_00,local_1c);
      std::_Vector_iterator<Strip_*,std::allocator<Strip_*>_>::operator++
                ((_Vector_iterator<Strip_*,std::allocator<Strip_*>_> *)&local_14);
    }
    std::vector<Strip_*,std::allocator<Strip_*>_>::clear(this);
    local_14._0_4_ = AllocStrip(true);
    ((Strip *)local_14)->material = 7;
    ((Strip *)local_14)->neighbor = -2;
    fVar2 = (float)(param_2 * 0x10 + GridMinX);
    ((Strip *)local_14)->x0 = fVar2;
    ((Strip *)local_14)->x1 = fVar2 + 16.0;
    local_1c[0] = (Strip *)(param_1 * 0x10 + GridMinZ);
    ((Strip *)local_14)->z0 = (float)(int)local_1c[0];
    ((Strip *)local_14)->z1 = (float)(int)local_1c[0] + 16.0;
    std::vector<Strip_*,std::allocator<Strip_*>_>::push_back(this,(Strip **)&local_14);
    pPVar4->built = false;
  }
  return;
}
