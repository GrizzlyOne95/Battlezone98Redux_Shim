/*
 * Entry: 0048ca34
 * Name: DistributedObject_GetGameObject
 * Namespace: Global
 * Signature: GameObject * DistributedObject_GetGameObject(ushort param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __cdecl DistributedObject_GetGameObject(ushort param_1)

{
  GameObject *pGVar1;
  bool bVar2;
  GameObject **ppGVar3;
  GameObject *pGVar4;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_14;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_c;
  
  pGVar4 = (GameObject *)0x0;
  if (GameObject::objectList != (vector<GameObject_*,std::allocator<GameObject_*>_> *)0x0) {
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
    _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
              (&local_14,GameObject::objectList->_Myfirst,
               (_Container_base_aux *)GameObject::objectList);
    local_c._padding_ = local_14._padding_;
    local_c._Myptr = local_14._Myptr;
    while( true ) {
      std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
      _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
                (&local_14,GameObject::objectList->_Mylast,
                 (_Container_base_aux *)GameObject::objectList);
      bVar2 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator==
                        (&local_c,&local_14);
      if (bVar2) break;
      ppGVar3 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator*
                          (&local_c);
      pGVar1 = *ppGVar3;
      if (((pGVar1 != (GameObject *)0x0) && (*(ushort *)((int)&pGVar1->_padding_ + 2) == param_1))
         && (pGVar4 = pGVar1, (char)pGVar1->_padding_ != '\0')) {
        return pGVar1;
      }
      std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator++(&local_c);
    }
  }
  return pGVar4;
}
