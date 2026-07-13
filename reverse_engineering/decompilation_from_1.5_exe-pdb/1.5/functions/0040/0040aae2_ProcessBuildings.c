/*
 * Entry: 0040aae2
 * Name: ProcessBuildings
 * Namespace: Global
 * Signature: void ProcessBuildings(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ProcessBuildings(void)

{
  int *piVar1;
  GameObject *pGVar2;
  vector<GameObject_*,std::allocator<GameObject_*>_> *pvVar3;
  bool bVar4;
  GameObject **ppGVar5;
  int iVar6;
  int iVar7;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_18;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_10;
  vector<GameObject_*,std::allocator<GameObject_*>_> *local_8;
  
  pvVar3 = GameObject::objectList;
  local_8 = GameObject::objectList;
  std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
            (&local_10,GameObject::objectList->_Myfirst,
             (_Container_base_aux *)GameObject::objectList);
  std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
            (&local_18,pvVar3->_Mylast,(_Container_base_aux *)pvVar3);
  bVar4 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator==
                    (&local_10,&local_18);
  while (!bVar4) {
    ppGVar5 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator*
                        (&local_10);
    pGVar2 = *ppGVar5;
    piVar1 = &pGVar2->_padding_;
    iVar6 = (**(code **)*piVar1)();
    iVar7 = (**(code **)*piVar1)();
    iVar6 = *(int *)(iVar6 + 0x28);
    iVar7 = *(int *)(iVar7 + 0x20);
    if (((((iVar6 == 2) || (iVar6 == 10)) || (iVar6 == 5)) || (iVar7 == 0x54555252)) &&
       (((iVar7 != 0x50524f58 && (iVar7 != 0x4745495a)) &&
        ((iVar7 != 0x53464c44 &&
         ((iVar7 != 0x5350574e &&
          (iVar6 = (**(code **)(*piVar1 + 0x30))(), (*(uint *)(iVar6 + 0x14) & 0x200) == 0)))))))) {
      BlockCells(pGVar2,true);
    }
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator++(&local_10);
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
    _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
              (&local_18,local_8->_Mylast,(_Container_base_aux *)local_8);
    bVar4 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator==
                      (&local_10,&local_18);
  }
  return;
}
