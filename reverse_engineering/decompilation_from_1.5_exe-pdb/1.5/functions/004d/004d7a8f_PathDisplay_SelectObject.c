/*
 * Entry: 004d7a8f
 * Name: PathDisplay::SelectObject
 * Namespace: PathDisplay
 * Signature: void SelectObject(PathDisplay * this, GameObject * * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PathDisplay::SelectObject(PathDisplay *this,GameObject **param_1)

{
  GameObject *this_00;
  vector<GameObject_*,std::allocator<GameObject_*>_> *pvVar1;
  bool bVar2;
  GameObject **ppGVar3;
  int iVar4;
  float *pfVar5;
  SPHERE *pSVar6;
  float fVar7;
  float local_2c;
  undefined4 local_28;
  float local_24;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_20;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_18;
  float local_10;
  float local_c;
  float local_8;
  
  local_2c = 0.0;
  local_28 = 0;
  local_24 = 0.0;
  (**(code **)(this->_padding_ + 0x24))
            (DisplayInterface::mousePos.x,DisplayInterface::mousePos.y,&local_2c,&local_24);
  local_10 = 2.0 / this->scale;
  *param_1 = (GameObject *)0x0;
  pvVar1 = GameObject::objectList;
  local_c = 3.4028235e+38;
  std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
            (&local_20,GameObject::objectList->_Myfirst,
             (_Container_base_aux *)GameObject::objectList);
  local_18._padding_ = local_20._padding_;
  local_18._Myptr = local_20._Myptr;
  std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
            (&local_20,pvVar1->_Mylast,(_Container_base_aux *)pvVar1);
  bVar2 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator==
                    (&local_18,&local_20);
  while (!bVar2) {
    ppGVar3 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator*
                        (&local_18);
    this_00 = *ppGVar3;
    iVar4 = (**(code **)(this_00->_padding_ + 0x2c))();
    if ((iVar4 != 0) && (this_00->isCargo == false)) {
      pfVar5 = (float *)(**(code **)(this_00->_padding_ + 0xc))();
      local_8 = (*pfVar5 - local_2c) * (*pfVar5 - local_2c) +
                (pfVar5[2] - local_24) * (pfVar5[2] - local_24);
      if (local_c < local_8 == (local_c == local_8)) {
        pSVar6 = GameObject::GetSphere(this_00);
        fVar7 = Max(this_00->collisionRadius,pSVar6->radius);
        fVar7 = (fVar7 + local_10) * (fVar7 + local_10);
        if (fVar7 < local_8 == (fVar7 == local_8)) {
          local_c = local_8;
          *param_1 = this_00;
        }
      }
    }
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator++(&local_18);
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
    _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
              (&local_20,pvVar1->_Mylast,(_Container_base_aux *)pvVar1);
    bVar2 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator==
                      (&local_18,&local_20);
  }
  return;
}
