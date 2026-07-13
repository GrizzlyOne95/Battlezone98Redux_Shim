/*
 * Entry: 00497dbb
 * Name: GameObject_BroadCast
 * Namespace: Global
 * Signature: void GameObject_BroadCast(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl GameObject_BroadCast(void)

{
  int *this;
  int iVar1;
  bool bVar2;
  GameObject **ppGVar3;
  float *pfVar4;
  VECTOR_3D *pVVar5;
  uint uVar6;
  GameObject *pGVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  VECTOR_3D local_1d4 [22];
  _ToBeSent local_cc;
  undefined1 local_c4 [152];
  uint local_2c;
  float local_28;
  VECTOR_3D *local_24;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_20;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_18;
  uint local_10;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_c;
  
  local_10 = 0;
  memset(&local_cc,0,0xa0);
  std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
            (&local_18,GameObject::objectList->_Myfirst,
             (_Container_base_aux *)GameObject::objectList);
  local_c._padding_ = local_18._padding_;
  local_c._Myptr = local_18._Myptr;
  std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
            (&local_20,GameObject::objectList->_Mylast,(_Container_base_aux *)GameObject::objectList
            );
  bVar2 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator==
                    (&local_c,&local_20);
  if (!bVar2) {
    pVVar5 = local_1d4;
    do {
      if (0x15 < local_10) break;
      ppGVar3 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator*
                          (&local_c);
      pGVar7 = *ppGVar3;
      if (pGVar7 != (GameObject *)0x0) {
        bVar2 = DistributedObject::IsRemote((DistributedObject *)&pGVar7->_padding_);
        if ((bVar2) && ((char)pGVar7->_padding_ != '\0')) {
          pfVar4 = (float *)(**(code **)(pGVar7->_padding_ + 0xc))();
          local_10 = local_10 + 1;
          pVVar5->x = *pfVar4;
          pVVar5->y = pfVar4[1];
          pVVar5->z = pfVar4[2];
          pVVar5 = pVVar5 + 1;
        }
      }
      std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator++(&local_c);
      std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
      _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
                (&local_20,GameObject::objectList->_Mylast,
                 (_Container_base_aux *)GameObject::objectList);
      bVar2 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator==
                        (&local_c,&local_20);
    } while (!bVar2);
  }
  std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
            (&local_18,GameObject::objectList->_Myfirst,
             (_Container_base_aux *)GameObject::objectList);
  local_c._padding_ = local_18._padding_;
  local_c._Myptr = local_18._Myptr;
  do {
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
    _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
              (&local_18,GameObject::objectList->_Mylast,
               (_Container_base_aux *)GameObject::objectList);
    bVar2 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator==
                      (&local_c,&local_18);
    if (bVar2) {
      DistributedObject::TempStateSendAll(&local_cc,0x14);
      return;
    }
    ppGVar3 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator*
                        (&local_c);
    pGVar7 = *ppGVar3;
    local_20._Myptr = (GameObject **)pGVar7;
    if (pGVar7 != (GameObject *)0x0) {
      this = &pGVar7->_padding_;
      bVar2 = DistributedObject::IsLocal((DistributedObject *)this);
      if (bVar2) {
        local_28 = 250.0;
        if (0 < (int)local_10) {
          local_24 = local_1d4;
          local_2c = local_10;
          do {
            pVVar5 = (VECTOR_3D *)(**(code **)(*this + 0xc))();
            fVar9 = Dist3D(*pVVar5,*local_24);
            if (fVar9 < local_28) {
              local_28 = fVar9;
            }
            local_24 = local_24 + 1;
            local_2c = local_2c - 1;
          } while (local_2c != 0);
          local_2c = 0;
          pGVar7 = (GameObject *)local_20._Myptr;
        }
        iVar1 = *this;
        fVar9 = local_28;
        fVar10 = Get_TimeLocal();
        fVar8 = (float10)(**(code **)(iVar1 + 0x18))(fVar10,fVar9);
        local_20._Myptr = (GameObject **)(float)fVar8;
        if ((float10)0 <= fVar8) {
          uVar6 = 0;
          do {
            if ((&local_cc)[uVar6].g == (GameObject *)0x0) {
LAB_00497fb9:
              *(float *)(local_c4 + uVar6 * 8 + -4) = (float)fVar8;
              (&local_cc)[uVar6].g = pGVar7;
              break;
            }
            if ((float10)*(float *)(local_c4 + uVar6 * 8 + -4) < fVar8) {
              if (uVar6 < 0x13) {
                memmove(local_c4 + uVar6 * 8,&local_cc + uVar6,(0x13 - uVar6) * 8);
              }
              fVar8 = (float10)(float)local_20._Myptr;
              goto LAB_00497fb9;
            }
            uVar6 = uVar6 + 1;
          } while (uVar6 < 0x14);
        }
      }
    }
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator++(&local_c);
  } while( true );
}
