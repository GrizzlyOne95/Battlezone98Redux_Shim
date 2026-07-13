/*
 * Entry: 004980ac
 * Name: GameObject_ComputeVisibility
 * Namespace: Global
 * Signature: void GameObject_ComputeVisibility(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl GameObject_ComputeVisibility(void)

{
  GameObject *this;
  float fVar1;
  long lVar2;
  vector<GameObject_*,std::allocator<GameObject_*>_> *pvVar3;
  bool bVar4;
  Scanner **ppSVar5;
  GameObject **ppGVar6;
  int iVar7;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_1c;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_14;
  _Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_> local_c;
  
  Scanner::BasicVisibility();
  std::_Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_>::
  _Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_>
            ((_Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_> *)&local_1c,
             Scanner::scannerList._Myfirst,(_Container_base_aux *)&Scanner::scannerList);
  local_c._padding_ = local_1c._padding_;
  local_c._Myptr = (Scanner **)local_1c._Myptr;
  while( true ) {
    std::_Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_>::
    _Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_>
              ((_Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_> *)&local_14,
               Scanner::scannerList._Mylast,(_Container_base_aux *)&Scanner::scannerList);
    bVar4 = std::_Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_>::operator==
                      (&local_c,(_Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_> *)
                                &local_14);
    if (bVar4) break;
    ppSVar5 = std::_Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_>::operator*(&local_c)
    ;
    Scanner::SweepVisibility(*ppSVar5);
    std::_Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_>::operator++(&local_c);
  }
  local_c._Myptr = (Scanner **)TimeStep();
  pvVar3 = GameObject::objectList;
  lVar2 = GameObject::userTeamNumber;
  std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
            (&local_1c,GameObject::objectList->_Myfirst,
             (_Container_base_aux *)GameObject::objectList);
  local_14._padding_ = local_1c._padding_;
  local_14._Myptr = local_1c._Myptr;
  do {
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
    _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
              (&local_1c,pvVar3->_Mylast,(_Container_base_aux *)pvVar3);
    bVar4 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator==
                      (&local_14,&local_1c);
    if (bVar4) {
      return;
    }
    ppGVar6 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator*
                        (&local_14);
    this = *ppGVar6;
    iVar7 = (**(code **)(this->_padding_ + 4))();
    if (iVar7 < 0) {
LAB_0049818a:
      fVar1 = 0.0;
    }
    else {
      GameObject::AssignColor(this);
      if ((this->isVisible >> ((byte)lVar2 & 0x1f) & 1) == 0) {
        if ((float)local_c._Myptr < this->illumination ==
            ((float)local_c._Myptr == this->illumination)) goto LAB_0049818a;
        fVar1 = this->illumination - (float)local_c._Myptr;
      }
      else {
        fVar1 = 1.0;
      }
    }
    this->illumination = fVar1;
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator++(&local_14);
  } while( true );
}
