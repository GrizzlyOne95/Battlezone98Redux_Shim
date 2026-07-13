/*
 * Entry: 00497c77
 * Name: GameObject::SaveAll
 * Namespace: GameObject
 * Signature: bool SaveAll(_iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl GameObject::SaveAll(_iobuf *param_1)

{
  bool bVar1;
  bool bVar2;
  GameObject **ppGVar3;
  int iVar4;
  GameObject *unaff_EBX;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_18;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_10;
  int local_8;
  
  local_8 = (int)objectList->_Mylast - (int)objectList->_Myfirst >> 2;
  std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
            (&local_18,objectList->_Myfirst,(_Container_base_aux *)objectList);
  local_10._padding_ = local_18._padding_;
  local_10._Myptr = local_18._Myptr;
  while( true ) {
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
    _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
              (&local_18,objectList->_Mylast,(_Container_base_aux *)objectList);
    bVar1 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator==
                      (&local_10,&local_18);
    if (bVar1) break;
    ppGVar3 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator*
                        (&local_10);
    iVar4 = (**(code **)((*ppGVar3)->_padding_ + 0x2c))();
    if (iVar4 == 0) {
      local_8 = local_8 + -1;
    }
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator++(&local_10);
  }
  bVar1 = ::out(param_1,&local_8,4,"size");
  if (userObject != (GameObject *)0x0) {
    if (bVar1) {
      bVar1 = WriteObject(param_1,unaff_EBX);
      if (bVar1) {
        bVar1 = true;
        goto LAB_00497d25;
      }
    }
    bVar1 = false;
  }
LAB_00497d25:
  std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
            (&local_18,objectList->_Myfirst,(_Container_base_aux *)objectList);
  local_10._padding_ = local_18._padding_;
  local_10._Myptr = local_18._Myptr;
  do {
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
    _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
              (&local_18,objectList->_Mylast,(_Container_base_aux *)objectList);
    bVar2 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator==
                      (&local_10,&local_18);
    if (bVar2) {
      return bVar1;
    }
    ppGVar3 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator*
                        (&local_10);
    if (*ppGVar3 != userObject) {
      ppGVar3 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator*
                          (&local_10);
      iVar4 = (**(code **)((*ppGVar3)->_padding_ + 0x2c))();
      if (iVar4 != 0) {
        if (bVar1 != false) {
          std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator*
                    (&local_10);
          bVar1 = WriteObject(param_1,unaff_EBX);
          if (bVar1) {
            bVar1 = true;
            goto LAB_00497d8d;
          }
        }
        bVar1 = false;
      }
    }
LAB_00497d8d:
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator++(&local_10);
  } while( true );
}
