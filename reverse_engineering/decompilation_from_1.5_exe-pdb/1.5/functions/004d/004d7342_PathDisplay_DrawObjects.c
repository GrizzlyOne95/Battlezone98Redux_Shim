/*
 * Entry: 004d7342
 * Name: PathDisplay::DrawObjects
 * Namespace: PathDisplay
 * Signature: void DrawObjects(PathDisplay * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PathDisplay::DrawObjects(PathDisplay *this)

{
  GameObject *this_00;
  vector<GameObject_*,std::allocator<GameObject_*>_> *pvVar1;
  bool bVar2;
  GameObject **ppGVar3;
  int iVar4;
  float *pfVar5;
  SPHERE *pSVar6;
  long lVar7;
  float fVar8;
  float local_2c;
  undefined4 local_28;
  float local_24;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_20;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_18;
  vector<GameObject_*,std::allocator<GameObject_*>_> *local_10;
  float local_c;
  uint local_8;
  
  local_2c = 0.0;
  local_28 = 0;
  local_24 = 0.0;
  (**(code **)(this->_padding_ + 0x24))
            (DisplayInterface::mousePos.x,DisplayInterface::mousePos.y,&local_2c,&local_24);
  pvVar1 = GameObject::objectList;
  local_c = 2.0 / this->scale;
  local_10 = GameObject::objectList;
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
      local_8 = local_8 & 0xffffff00;
      if ((this->controlMode == CONTROL_OBJECT) ||
         ((lVar7 = DisplayInterface::colorBlack, this->controlMode == CONTROL_TASK &&
          (this_00->aiProcess != (AiProcess *)0x0)))) {
        pfVar5 = (float *)(**(code **)(this_00->_padding_ + 0xc))();
        pSVar6 = GameObject::GetSphere(this_00);
        fVar8 = Max(this_00->collisionRadius,pSVar6->radius);
        if ((fVar8 + local_c) * (fVar8 + local_c) <=
            (*pfVar5 - local_2c) * (*pfVar5 - local_2c) +
            (pfVar5[2] - local_24) * (pfVar5[2] - local_24)) {
          local_8 = (uint)local_8._1_3_ << 8;
          lVar7 = DisplayInterface::colorBlack;
        }
        else {
          local_8 = CONCAT31(local_8._1_3_,1);
          lVar7 = DisplayInterface::colorDkGrey;
        }
      }
      DrawObject(this,this_00,SUB41(local_8,0),lVar7);
    }
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator++(&local_18);
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
    _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
              (&local_20,local_10->_Mylast,(_Container_base_aux *)local_10);
    bVar2 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator==
                      (&local_18,&local_20);
  }
  return;
}
