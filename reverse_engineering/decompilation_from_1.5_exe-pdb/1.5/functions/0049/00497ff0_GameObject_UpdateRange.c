/*
 * Entry: 00497ff0
 * Name: GameObject_UpdateRange
 * Namespace: Global
 * Signature: void GameObject_UpdateRange(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl GameObject_UpdateRange(void)

{
  GameObject *this;
  vector<GameObject_*,std::allocator<GameObject_*>_> *pvVar1;
  bool bVar2;
  GameObject **ppGVar3;
  float *pfVar4;
  int iVar5;
  undefined4 unaff_EDI;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_14;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_c;
  
  Range::Clear(GameObject::objectRange);
  pvVar1 = GameObject::objectList;
  std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
            (&local_14,GameObject::objectList->_Myfirst,
             (_Container_base_aux *)GameObject::objectList);
  local_c._padding_ = local_14._padding_;
  local_c._Myptr = local_14._Myptr;
  std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
            (&local_14,pvVar1->_Mylast,(_Container_base_aux *)pvVar1);
  bVar2 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator==
                    (&local_c,&local_14);
  while (!bVar2) {
    ppGVar3 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator*
                        (&local_c);
    this = *ppGVar3;
    pfVar4 = (float *)(**(code **)(this->_padding_ + 0xc))();
    iVar5 = GameObject::GetHandle(this);
    if (iVar5 != 0) {
      Range::Insert(GameObject::objectRange,iVar5,
                    (double)CONCAT44(SUB84((double)pfVar4[2],0),
                                     (int)((ulonglong)(double)*pfVar4 >> 0x20)),
                    (double)CONCAT44(unaff_EDI,(int)((ulonglong)(double)pfVar4[2] >> 0x20)));
    }
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator++(&local_c);
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
    _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
              (&local_14,pvVar1->_Mylast,(_Container_base_aux *)pvVar1);
    bVar2 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator==
                      (&local_c,&local_14);
  }
  Range::Done_Inserting(GameObject::objectRange);
  return;
}
