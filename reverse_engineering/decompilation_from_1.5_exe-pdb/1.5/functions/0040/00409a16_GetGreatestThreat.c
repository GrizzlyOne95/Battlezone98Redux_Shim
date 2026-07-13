/*
 * Entry: 00409a16
 * Name: GetGreatestThreat
 * Namespace: Global
 * Signature: GameObject * GetGreatestThreat(GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __cdecl GetGreatestThreat(GameObject *param_1)

{
  GameObject *pGVar1;
  float fVar2;
  bool bVar3;
  GameObject **ppGVar4;
  int iVar5;
  float *pfVar6;
  float *pfVar7;
  GameObject *pGVar8;
  vector<GameObject_*,std::allocator<GameObject_*>_> *pvVar9;
  float fVar10;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_2c;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_24;
  GameObject *local_1c;
  GameObject *local_18;
  vector<GameObject_*,std::allocator<GameObject_*>_> *local_14;
  float local_10;
  float local_c;
  _OBJ76 *local_8;
  
  local_1c = GameObjectHandle::GetObj(param_1->who_shot_JR);
  pvVar9 = GameObject::objectList;
  local_10 = -1e+30;
  local_18 = (GameObject *)0x0;
  local_14 = GameObject::objectList;
  std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
            (&local_24,GameObject::objectList->_Myfirst,
             (_Container_base_aux *)GameObject::objectList);
  std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
            (&local_2c,pvVar9->_Mylast,(_Container_base_aux *)pvVar9);
  bVar3 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator==
                    (&local_24,&local_2c);
  while (!bVar3) {
    ppGVar4 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator*
                        (&local_24);
    pGVar1 = *ppGVar4;
    bVar3 = GameObject::EnemyP(param_1,pGVar1);
    if (bVar3) {
      local_8 = (_OBJ76 *)(**(code **)(pGVar1->_padding_ + 0x30))();
      iVar5 = IsCraft(local_8);
      if ((((iVar5 != 0) || (local_8->class_id == CLASS_ID_PERSON)) &&
          ((local_8->flags & 0x200) == 0)) &&
         (((local_8->class_id != CLASS_ID_PERSON || (pGVar1 == local_1c)) ||
          ((*(byte *)((int)local_8->class_ptr + 0x10c) & 0xc) == 0)))) {
        pfVar6 = (float *)(**(code **)(param_1->_padding_ + 0xc))();
        pfVar7 = (float *)(**(code **)(pGVar1->_padding_ + 0xc))();
        local_8 = (_OBJ76 *)(*pfVar7 - *pfVar6);
        local_c = pfVar7[2] - pfVar6[2];
        pGVar8 = GameObject::GetObj(pGVar1->targetHandle);
        fVar10 = GetDamageRatio(pGVar1);
        if (pGVar8 == param_1) {
          fVar2 = 2500.0;
        }
        else {
          fVar2 = 0.0;
        }
        fVar10 = fVar10 * 100.0 +
                 fVar2 + (local_c * local_c + (float)local_8 * (float)local_8) * -1.0;
        pvVar9 = local_14;
        if (local_10 < fVar10) {
          local_18 = pGVar1;
          local_10 = fVar10;
        }
      }
    }
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator++(&local_24);
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
    _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
              (&local_2c,pvVar9->_Mylast,(_Container_base_aux *)pvVar9);
    bVar3 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator==
                      (&local_24,&local_2c);
  }
  return local_18;
}
