/*
 * Entry: 00410249
 * Name: Collision_Fill_In_Range_Search_Structure
 * Namespace: Global
 * Signature: void Collision_Fill_In_Range_Search_Structure(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Collision_Fill_In_Range_Search_Structure(void)

{
  Craft *this;
  bool bVar1;
  Craft **ppCVar2;
  int iVar3;
  float *pfVar4;
  undefined4 uVar5;
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> local_14;
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> local_c;
  
  Range::Clear(collision_range_search);
  std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>
            (&local_14,Craft::craftList._Myfirst,(_Container_base_aux *)&Craft::craftList);
  local_c._padding_ = local_14._padding_;
  local_c._Myptr = local_14._Myptr;
  std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>
            (&local_14,Craft::craftList._Mylast,(_Container_base_aux *)&Craft::craftList);
  bVar1 = std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::operator==
                    (&local_c,&local_14);
  while (!bVar1) {
    ppCVar2 = std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::operator*(&local_c);
    this = *ppCVar2;
    iVar3 = GameObject::GetHandle((GameObject *)this);
    if (iVar3 != 0) {
      uVar5 = 0x4102bb;
      pfVar4 = (float *)(**(code **)(this->_padding_ + 0xc))();
      Range::Insert(collision_range_search,iVar3,
                    (double)CONCAT44(SUB84((double)pfVar4[2],0),
                                     (int)((ulonglong)(double)*pfVar4 >> 0x20)),
                    (double)CONCAT44(uVar5,(int)((ulonglong)(double)pfVar4[2] >> 0x20)));
    }
    std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::operator++(&local_c);
    std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::
    _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>
              (&local_14,Craft::craftList._Mylast,(_Container_base_aux *)&Craft::craftList);
    bVar1 = std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::operator==
                      (&local_c,&local_14);
  }
  Range::Done_Inserting(collision_range_search);
  return;
}
