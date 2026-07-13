/*
 * Entry: 00460d8b
 * Name: GetHandle
 * Namespace: Global
 * Signature: int GetHandle(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetHandle(char *param_1)

{
  byte bVar1;
  vector<GameObject_*,std::allocator<GameObject_*>_> *pvVar2;
  bool bVar3;
  byte *pbVar4;
  GameObject **ppGVar5;
  int iVar6;
  byte *pbVar7;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_14;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_c;
  
  pvVar2 = GameObject::objectList;
  std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
            (&local_14,GameObject::objectList->_Myfirst,
             (_Container_base_aux *)GameObject::objectList);
  local_c._padding_ = local_14._padding_;
  local_c._Myptr = local_14._Myptr;
  while( true ) {
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
    _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
              (&local_14,pvVar2->_Mylast,(_Container_base_aux *)pvVar2);
    bVar3 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator==
                      (&local_c,&local_14);
    if (bVar3) break;
    ppGVar5 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator*
                        (&local_c);
    pbVar4 = (byte *)(*ppGVar5)->label;
    pbVar7 = (byte *)param_1;
    do {
      bVar1 = *pbVar4;
      bVar3 = bVar1 < *pbVar7;
      if (bVar1 != *pbVar7) {
LAB_00460de3:
        iVar6 = (1 - (uint)bVar3) - (uint)(bVar3 != 0);
        goto LAB_00460de8;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar4[1];
      bVar3 = bVar1 < pbVar7[1];
      if (bVar1 != pbVar7[1]) goto LAB_00460de3;
      pbVar4 = pbVar4 + 2;
      pbVar7 = pbVar7 + 2;
    } while (bVar1 != 0);
    iVar6 = 0;
LAB_00460de8:
    if (iVar6 == 0) break;
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator++(&local_c);
  }
  std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
            (&local_14,pvVar2->_Mylast,(_Container_base_aux *)pvVar2);
  bVar3 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator==
                    (&local_c,&local_14);
  if (!bVar3) {
    ppGVar5 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator*
                        (&local_c);
    if (*ppGVar5 != (GameObject *)0x0) {
      iVar6 = GameObject::GetHandle(*ppGVar5);
      return iVar6;
    }
  }
  return 0;
}
