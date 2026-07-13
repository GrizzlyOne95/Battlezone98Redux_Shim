/*
 * Entry: 005499f7
 * Name: ConvertHandle
 * Namespace: Global
 * Signature: int ConvertHandle(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl ConvertHandle(int param_1)

{
  vector<GameObject_*,std::allocator<GameObject_*>_> *pvVar1;
  bool bVar2;
  GameObject **ppGVar3;
  int iVar4;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_14;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_c;
  
  pvVar1 = GameObject::objectList;
  if (param_1 == 0) {
    return 0;
  }
  std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
            (&local_c,GameObject::objectList->_Myfirst,(_Container_base_aux *)GameObject::objectList
            );
  while( true ) {
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
    _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
              (&local_14,pvVar1->_Mylast,(_Container_base_aux *)pvVar1);
    bVar2 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator==
                      (&local_c,&local_14);
    if (bVar2) {
      return 0;
    }
    ppGVar3 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator*
                        (&local_c);
    if ((*ppGVar3)->seqNo == (param_1 & 0x7fffffU)) break;
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator++(&local_c);
  }
  iVar4 = GameObject::GetHandle(*ppGVar3);
  return iVar4;
}
