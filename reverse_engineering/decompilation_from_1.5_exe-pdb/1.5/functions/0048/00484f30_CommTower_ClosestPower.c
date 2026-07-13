/*
 * Entry: 00484f30
 * Name: CommTower::ClosestPower
 * Namespace: CommTower
 * Signature: int ClosestPower(CommTower * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall CommTower::ClosestPower(CommTower *this)

{
  PowerPlant *pPVar1;
  VECTOR_3D VVar2;
  VECTOR_3D VVar3;
  bool bVar4;
  GameObject *pGVar5;
  VECTOR_3D *pVVar6;
  int iVar7;
  PowerPlant **ppPVar8;
  _Vector_const_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> local_20;
  _Vector_const_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> local_18;
  PowerPlant *local_10;
  float local_c;
  CommTower *local_8;
  
  local_8 = this;
  pGVar5 = GameObjectHandle::GetObj(this->powerSource);
  if (pGVar5 != (GameObject *)0x0) {
    pVVar6 = (VECTOR_3D *)(**(code **)(pGVar5->_padding_ + 0xc))();
    VVar2.x = (float)local_8->_padding_;
    VVar2.y = (float)local_8->_padding_;
    VVar2.z = (float)local_8->_padding_;
    local_c = Dist3D_Squared(VVar2,*pVVar6);
    iVar7 = (**(code **)pGVar5->_padding_)();
    if (local_c < *(float *)(iVar7 + 0x160) * *(float *)(iVar7 + 0x160)) {
      return local_8->powerSource;
    }
  }
  std::_Vector_const_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>::
  _Vector_const_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>
            (&local_20,PowerPlant::powerPlantList._Myfirst,
             (_Container_base_aux *)&PowerPlant::powerPlantList);
  local_18._padding_ = local_20._padding_;
  local_18._Myptr = local_20._Myptr;
  do {
    std::_Vector_const_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>::
    _Vector_const_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>
              (&local_20,PowerPlant::powerPlantList._Mylast,
               (_Container_base_aux *)&PowerPlant::powerPlantList);
    bVar4 = std::_Vector_const_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>::operator==
                      (&local_18,&local_20);
    if (bVar4) {
      return 0;
    }
    ppPVar8 = std::_Vector_const_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>::operator*
                        (&local_18);
    pPVar1 = *ppPVar8;
    local_10 = pPVar1;
    bVar4 = GameObject::FriendP((GameObject *)local_8,(GameObject *)pPVar1);
    if (bVar4) {
      pVVar6 = (VECTOR_3D *)(**(code **)(pPVar1->_padding_ + 0xc))();
      VVar3.x = (float)local_8->_padding_;
      VVar3.y = (float)local_8->_padding_;
      VVar3.z = (float)local_8->_padding_;
      local_c = Dist3D_Squared(VVar3,*pVVar6);
      iVar7 = (**(code **)pPVar1->_padding_)();
      if (local_c < *(float *)(iVar7 + 0x160) * *(float *)(iVar7 + 0x160)) {
        iVar7 = GameObject::GetHandle((GameObject *)local_10);
        return iVar7;
      }
    }
    std::_Vector_const_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>::operator++(&local_18);
  } while( true );
}
