/*
 * Entry: 00409565
 * Name: GetClosestSilo
 * Namespace: Global
 * Signature: GameObject * GetClosestSilo(GameObject * param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __cdecl GetClosestSilo(GameObject *param_1,float param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  vector<GameObject_*,std::allocator<GameObject_*>_> *pvVar4;
  bool bVar5;
  float *pfVar6;
  GameObject **ppGVar7;
  int iVar8;
  int *piVar9;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_20;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_18;
  GameObject *local_10;
  int local_c;
  GameObject *local_8;
  
  pfVar6 = (float *)(**(code **)(param_1->_padding_ + 0xc))();
  pvVar4 = GameObject::objectList;
  local_8 = (GameObject *)0x0;
  fVar1 = *pfVar6;
  fVar2 = pfVar6[2];
  std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
            (&local_18,GameObject::objectList->_Myfirst,
             (_Container_base_aux *)GameObject::objectList);
  while( true ) {
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
    _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
              (&local_20,pvVar4->_Mylast,(_Container_base_aux *)pvVar4);
    bVar5 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator==
                      (&local_18,&local_20);
    if (bVar5) break;
    ppGVar7 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator*
                        (&local_18);
    local_10 = *ppGVar7;
    piVar9 = &local_10->_padding_;
    iVar8 = (**(code **)*piVar9)();
    if (*(int *)(iVar8 + 0x20) == 0x53494c4f) {
      local_c = (**(code **)(*piVar9 + 4))();
      iVar8 = (**(code **)(param_1->_padding_ + 4))();
      if ((iVar8 == local_c) &&
         (iVar8 = (**(code **)(*piVar9 + 0x30))(), (*(uint *)(iVar8 + 0x14) & 0x200) == 0)) {
        pfVar6 = (float *)(**(code **)(*piVar9 + 0xc))();
        fVar3 = (fVar2 - pfVar6[2]) * (fVar2 - pfVar6[2]) + (fVar1 - *pfVar6) * (fVar1 - *pfVar6);
        if (fVar3 <= param_2) {
          local_8 = local_10;
          param_2 = fVar3;
        }
      }
    }
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator++(&local_18);
  }
  return local_8;
}
