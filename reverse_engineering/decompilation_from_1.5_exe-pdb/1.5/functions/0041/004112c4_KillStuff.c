/*
 * Entry: 004112c4
 * Name: KillStuff
 * Namespace: Global
 * Signature: void KillStuff(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl KillStuff(void)

{
  int *piVar1;
  GameObject *pGVar2;
  vector<GameObject_*,std::allocator<GameObject_*>_> *pvVar3;
  bool bVar4;
  GameObject **ppGVar5;
  int iVar6;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_20;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_18;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_10;
  GameObject *local_8;
  
  pvVar3 = GameObject::objectList;
  local_8 = GameObject::userObject;
  std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
            (&local_18,GameObject::objectList->_Myfirst,
             (_Container_base_aux *)GameObject::objectList);
  local_10._padding_ = local_18._padding_;
  local_10._Myptr = local_18._Myptr;
  std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
            (&local_18,pvVar3->_Mylast,(_Container_base_aux *)pvVar3);
  bVar4 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator==
                    (&local_10,&local_18);
  while (!bVar4) {
    ppGVar5 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator*
                        (&local_10);
    pGVar2 = *ppGVar5;
    if (pGVar2 != local_8) {
      piVar1 = &pGVar2->_padding_;
      iVar6 = (**(code **)(*piVar1 + 0x30))();
      if ((((iVar6 != 0) && ((*(uint *)(iVar6 + 0x14) & 0x200) == 0)) &&
          ((pGVar2->seqNo < 5 || (8 < pGVar2->seqNo)))) &&
         (iVar6 = (**(code **)(*piVar1 + 4))(), iVar6 != 3)) {
        (**(code **)(*piVar1 + 8))(3);
        (**(code **)(*piVar1 + 0x10))();
        std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
        _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
                  (&local_20,pvVar3->_Myfirst,(_Container_base_aux *)pvVar3);
        local_10._padding_ = local_20._padding_;
        local_10._Myptr = local_20._Myptr;
      }
    }
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator++(&local_10);
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
    _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
              (&local_18,pvVar3->_Mylast,(_Container_base_aux *)pvVar3);
    bVar4 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator==
                      (&local_10,&local_18);
  }
  return;
}
