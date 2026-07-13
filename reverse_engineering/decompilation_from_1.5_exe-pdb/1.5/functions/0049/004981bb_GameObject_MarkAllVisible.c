/*
 * Entry: 004981bb
 * Name: GameObject_MarkAllVisible
 * Namespace: Global
 * Signature: void GameObject_MarkAllVisible(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl GameObject_MarkAllVisible(void)

{
  GameObject *pGVar1;
  bool bVar2;
  GameObject **ppGVar3;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_14;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_c;
  
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
    pGVar1->illumination = 1.0;
    pGVar1->isVisible = 0xffffffff;
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator++(&local_c);
  }
  return;
}
