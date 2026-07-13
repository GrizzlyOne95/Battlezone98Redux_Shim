/*
 * Entry: 00497ab2
 * Name: GameObjectFeature::Control
 * Namespace: GameObjectFeature
 * Signature: void Control(GameObjectFeature * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GameObjectFeature::Control(GameObjectFeature *this)

{
  GameObject *pGVar1;
  vector<GameObject_*,std::allocator<GameObject_*>_> *pvVar2;
  bool bVar3;
  GameObject **ppGVar4;
  int iVar5;
  GameObject *pGVar6;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_28;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_20;
  GameObject *local_18;
  uint local_14;
  uint local_10;
  int local_c;
  int local_8;
  
  pvVar2 = GameObject::objectList;
  if (freeObjectCount < 0x33) {
    pGVar6 = (GameObject *)0x0;
    local_8 = 0;
    local_c = 0;
    local_18 = (GameObject *)0x0;
    local_10 = 0x7fffff;
    local_14 = 0x7fffff;
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
    _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
              (&local_28,GameObject::objectList->_Myfirst,
               (_Container_base_aux *)GameObject::objectList);
    local_20._padding_ = local_28._padding_;
    local_20._Myptr = local_28._Myptr;
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
    _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
              (&local_28,pvVar2->_Mylast,(_Container_base_aux *)pvVar2);
    bVar3 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator==
                      (&local_20,&local_28);
    while (!bVar3) {
      ppGVar4 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator*
                          (&local_20);
      pGVar1 = *ppGVar4;
      iVar5 = (**(code **)pGVar1->_padding_)();
      if (*(int *)(iVar5 + 0x20) == 0x53435250) {
        local_8 = local_8 + 1;
        if ((uint)pGVar1->seqNo < local_10) {
          pGVar6 = pGVar1;
          local_10 = pGVar1->seqNo;
        }
      }
      else {
        bVar3 = IsMine(pGVar1);
        if (bVar3) {
          local_c = local_c + 1;
          if ((uint)pGVar1->seqNo < local_14) {
            local_18 = pGVar1;
            local_14 = pGVar1->seqNo;
          }
        }
      }
      std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator++(&local_20)
      ;
      std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
      _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
                (&local_28,pvVar2->_Mylast,(_Container_base_aux *)pvVar2);
      bVar3 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator==
                        (&local_20,&local_28);
    }
    if ((freeObjectCount / 2 < local_8) && (pGVar6 != (GameObject *)0x0)) {
      (**(code **)(pGVar6->_padding_ + 0x10))();
    }
    if ((freeObjectCount / 2 < local_c) && (local_18 != (GameObject *)0x0)) {
      (**(code **)(local_18->_padding_ + 0x10))();
    }
  }
  return;
}
