/*
 * Entry: 004af3ce
 * Name: Scrap_UpdateRange
 * Namespace: Global
 * Signature: void Scrap_UpdateRange(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Scrap_UpdateRange(void)

{
  Scrap *this;
  bool bVar1;
  Scrap **ppSVar2;
  int iVar3;
  float *pfVar4;
  undefined4 uVar5;
  _Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_> local_14;
  _Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_> local_c;
  
  if (updateScrap) {
    Range::Clear(Scrap::scrapRange);
    std::_Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_>::
    _Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_>
              (&local_14,Scrap::scrapList._Myfirst,(_Container_base_aux *)&Scrap::scrapList);
    local_c._padding_ = local_14._padding_;
    local_c._Myptr = local_14._Myptr;
    std::_Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_>::
    _Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_>
              (&local_14,Scrap::scrapList._Mylast,(_Container_base_aux *)&Scrap::scrapList);
    bVar1 = std::_Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_>::operator==
                      (&local_c,&local_14);
    while (!bVar1) {
      ppSVar2 = std::_Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_>::operator*(&local_c);
      this = *ppSVar2;
      iVar3 = GameObject::GetHandle((GameObject *)this);
      if (iVar3 != 0) {
        uVar5 = 0x4af44d;
        pfVar4 = (float *)(**(code **)(this->_padding_ + 0xc))();
        Range::Insert(Scrap::scrapRange,iVar3,
                      (double)CONCAT44(SUB84((double)pfVar4[2],0),
                                       (int)((ulonglong)(double)*pfVar4 >> 0x20)),
                      (double)CONCAT44(uVar5,(int)((ulonglong)(double)pfVar4[2] >> 0x20)));
      }
      std::_Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_>::operator++(&local_c);
      std::_Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_>::
      _Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_>
                (&local_14,Scrap::scrapList._Mylast,(_Container_base_aux *)&Scrap::scrapList);
      bVar1 = std::_Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_>::operator==
                        (&local_c,&local_14);
    }
    Range::Done_Inserting(Scrap::scrapRange);
    updateScrap = false;
  }
  return;
}
