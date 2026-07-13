/*
 * Entry: 004096bf
 * Name: GetClosestEnemyPersonWithin
 * Namespace: Global
 * Signature: GameObject * GetClosestEnemyPersonWithin(GameObject * param_1, float * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __cdecl GetClosestEnemyPersonWithin(GameObject *param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  GameObject *pGVar3;
  vector<GameObject_*,std::allocator<GameObject_*>_> *pvVar4;
  bool bVar5;
  float *pfVar6;
  GameObject **ppGVar7;
  int iVar8;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_20;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_18;
  GameObject *local_10;
  GameObject *local_c;
  GameObject *local_8;
  
  local_c = GameObjectHandle::GetObj(param_1->who_shot_JR);
  pfVar6 = (float *)(**(code **)(param_1->_padding_ + 0xc))();
  pvVar4 = GameObject::objectList;
  local_8 = (GameObject *)0x0;
  param_2 = (float *)*param_2;
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
    pGVar3 = *ppGVar7;
    local_10 = pGVar3;
    bVar5 = GameObject::EnemyP(param_1,pGVar3);
    if (bVar5) {
      iVar8 = (**(code **)(pGVar3->_padding_ + 0x30))();
      if (((*(int *)(iVar8 + 0xac) == 4) && ((*(uint *)(iVar8 + 0x14) & 0x200) == 0)) &&
         ((pGVar3 == local_c || ((*(byte *)(*(int *)(iVar8 + 0xb0) + 0x10c) & 0xc) == 0)))) {
        pfVar6 = (float *)(**(code **)(pGVar3->_padding_ + 0xc))();
        pfVar6 = (float *)((pfVar6[2] - fVar2) * (pfVar6[2] - fVar2) +
                          (*pfVar6 - fVar1) * (*pfVar6 - fVar1));
        if ((float)pfVar6 < (float)param_2) {
          local_8 = local_10;
          param_2 = pfVar6;
        }
      }
    }
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator++(&local_18);
  }
  return local_8;
}
