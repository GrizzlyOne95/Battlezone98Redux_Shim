/*
 * Entry: 004ab871
 * Name: Producer::HasPower
 * Namespace: Producer
 * Signature: bool HasPower(Producer * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Producer::HasPower(Producer *this)

{
  float fVar1;
  float fVar2;
  bool bVar3;
  Geizer *pGVar4;
  float *pfVar5;
  Geizer **ppGVar6;
  _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_> local_1c;
  float local_14;
  _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_> local_10;
  Geizer *local_8;
  
  if (this->poweredBuilder != false) {
    pGVar4 = (Geizer *)GameObjectHandle::GetObj(this->powerHandle);
    this->powerSource = pGVar4;
    if (pGVar4 != (Geizer *)0x0) {
      local_14 = (float)this->_padding_;
      local_10._padding_ = this->_padding_;
      local_10._Myptr = (Geizer **)this->_padding_;
      pfVar5 = (float *)(**(code **)(pGVar4->_padding_ + 0xc))();
      local_1c._padding_ = (int)pfVar5[1];
      local_1c._Myptr = (Geizer **)pfVar5[2];
      fVar1 = ((float)local_1c._Myptr - (float)local_10._Myptr) *
              ((float)local_1c._Myptr - (float)local_10._Myptr) +
              (*pfVar5 - local_14) * (*pfVar5 - local_14);
      if (fVar1 < 100.0 != (fVar1 == 100.0)) {
        return true;
      }
      Trace("powerSource is too far\n");
      this->powerSource->isLocked = false;
    }
    this->powerHandle = 0;
    std::_Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>::
    _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>
              (&local_1c,Geizer::geizerList._Myfirst,(_Container_base_aux *)&Geizer::geizerList);
    local_10._padding_ = local_1c._padding_;
    local_10._Myptr = local_1c._Myptr;
    while( true ) {
      std::_Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>::
      _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>
                (&local_1c,Geizer::geizerList._Mylast,(_Container_base_aux *)&Geizer::geizerList);
      bVar3 = std::_Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>::operator==
                        (&local_10,&local_1c);
      if (bVar3) break;
      ppGVar6 = std::_Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>::operator*
                          (&local_10);
      local_8 = *ppGVar6;
      if ((local_8->isLocked == false) &&
         (fVar1 = (float)this->_padding_, fVar2 = (float)this->_padding_,
         pfVar5 = (float *)(**(code **)(local_8->_padding_ + 0xc))(), fVar1 = *pfVar5 - fVar1,
         fVar2 = pfVar5[2] - fVar2, fVar2 * fVar2 + fVar1 * fVar1 < 100.0)) {
        this->powerSource = local_8;
        return true;
      }
      std::_Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>::operator++(&local_10);
    }
    this->powerSource = (Geizer *)0x0;
  }
  return false;
}
