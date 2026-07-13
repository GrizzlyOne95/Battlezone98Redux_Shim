/*
 * Entry: 00409351
 * Name: AiFindObj
 * Namespace: Global
 * Signature: _OBJ76 * AiFindObj(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_OBJ76 * __cdecl AiFindObj(char *param_1)

{
  byte bVar1;
  vector<GameObject_*,std::allocator<GameObject_*>_> *pvVar2;
  bool bVar3;
  GameObject **ppGVar4;
  byte *pbVar5;
  int iVar6;
  _OBJ76 *p_Var7;
  byte *pbVar8;
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
      return (_OBJ76 *)0x0;
    }
    ppGVar4 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator*
                        (&local_c);
    pbVar5 = (byte *)(*ppGVar4)->label;
    pbVar8 = (byte *)param_1;
    do {
      bVar1 = *pbVar5;
      bVar3 = bVar1 < *pbVar8;
      if (bVar1 != *pbVar8) {
LAB_0040939e:
        iVar6 = (1 - (uint)bVar3) - (uint)(bVar3 != 0);
        goto LAB_004093a3;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar5[1];
      bVar3 = bVar1 < pbVar8[1];
      if (bVar1 != pbVar8[1]) goto LAB_0040939e;
      pbVar5 = pbVar5 + 2;
      pbVar8 = pbVar8 + 2;
    } while (bVar1 != 0);
    iVar6 = 0;
LAB_004093a3:
    if (iVar6 == 0) {
      p_Var7 = (_OBJ76 *)(**(code **)((*ppGVar4)->_padding_ + 0x30))();
      return p_Var7;
    }
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator++(&local_c);
  } while( true );
}
