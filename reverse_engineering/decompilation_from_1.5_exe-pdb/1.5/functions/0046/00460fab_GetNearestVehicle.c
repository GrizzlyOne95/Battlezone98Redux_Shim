/*
 * Entry: 00460fab
 * Name: GetNearestVehicle
 * Namespace: Global
 * Signature: int GetNearestVehicle(VECTOR_3D * param_1, GameObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetNearestVehicle(VECTOR_3D *param_1,GameObject *param_2)

{
  GameObject *pGVar1;
  float fVar2;
  float fVar3;
  vector<GameObject_*,std::allocator<GameObject_*>_> *pvVar4;
  bool bVar5;
  GameObject **ppGVar6;
  _OBJ76 *p_Var7;
  int iVar8;
  float *pfVar9;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_1c;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_14;
  GameObject *local_c;
  float local_8;
  
  pvVar4 = GameObject::objectList;
  local_c = (GameObject *)0x0;
  local_8 = 1e+30;
  std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
            (&local_14,GameObject::objectList->_Myfirst,
             (_Container_base_aux *)GameObject::objectList);
  std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
            (&local_1c,pvVar4->_Mylast,(_Container_base_aux *)pvVar4);
  bVar5 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator==
                    (&local_14,&local_1c);
  if (!bVar5) {
    do {
      ppGVar6 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator*
                          (&local_14);
      pGVar1 = *ppGVar6;
      if (pGVar1 != param_2) {
        p_Var7 = (_OBJ76 *)(**(code **)(pGVar1->_padding_ + 0x30))();
        if (((p_Var7->flags & 0x200) == 0) && (iVar8 = IsCraft(p_Var7), iVar8 != 0)) {
          pfVar9 = (float *)(**(code **)(pGVar1->_padding_ + 0xc))();
          fVar2 = param_1->x - *pfVar9;
          fVar3 = param_1->z - pfVar9[2];
          fVar2 = fVar3 * fVar3 + fVar2 * fVar2;
          if (fVar2 < local_8) {
            local_c = pGVar1;
            local_8 = fVar2;
          }
        }
      }
      std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator++(&local_14)
      ;
      std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
      _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
                (&local_1c,pvVar4->_Mylast,(_Container_base_aux *)pvVar4);
      bVar5 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator==
                        (&local_14,&local_1c);
    } while (!bVar5);
    if (local_c != (GameObject *)0x0) {
      iVar8 = GameObject::GetHandle(local_c);
      return iVar8;
    }
  }
  return 0;
}
