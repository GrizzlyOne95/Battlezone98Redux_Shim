/*
 * Entry: 004092d1
 * Name: FindObject
 * Namespace: Global
 * Signature: GameObject * FindObject(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __cdecl FindObject(char *param_1)

{
  byte bVar1;
  vector<GameObject_*,std::allocator<GameObject_*>_> *pvVar2;
  bool bVar3;
  GameObject **ppGVar4;
  byte *pbVar5;
  int iVar6;
  byte *pbVar7;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_14;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_c;
  
  pvVar2 = GameObject::objectList;
  std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
            (&local_c,GameObject::objectList->_Myfirst,(_Container_base_aux *)GameObject::objectList
            );
  do {
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
    _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
              (&local_14,pvVar2->_Mylast,(_Container_base_aux *)pvVar2);
    bVar3 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator==
                      (&local_c,&local_14);
    if (bVar3) {
      return (GameObject *)0x0;
    }
    ppGVar4 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator*
                        (&local_c);
    pbVar5 = (byte *)(*ppGVar4)->label;
    pbVar7 = (byte *)param_1;
    do {
      bVar1 = *pbVar5;
      bVar3 = bVar1 < *pbVar7;
      if (bVar1 != *pbVar7) {
LAB_0040931e:
        iVar6 = (1 - (uint)bVar3) - (uint)(bVar3 != 0);
        goto LAB_00409323;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar5[1];
      bVar3 = bVar1 < pbVar7[1];
      if (bVar1 != pbVar7[1]) goto LAB_0040931e;
      pbVar5 = pbVar5 + 2;
      pbVar7 = pbVar7 + 2;
    } while (bVar1 != 0);
    iVar6 = 0;
LAB_00409323:
    if (iVar6 == 0) {
      return *ppGVar4;
    }
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator++(&local_c);
  } while( true );
}
