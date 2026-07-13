/*
 * Entry: 00409905
 * Name: NearestVehicle
 * Namespace: Global
 * Signature: GameObject * NearestVehicle(GameObject * param_1, VECTOR_3D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __cdecl NearestVehicle(GameObject *param_1,VECTOR_3D *param_2)

{
  int *piVar1;
  GameObject *pGVar2;
  bool bVar3;
  GameObject **ppGVar4;
  int iVar5;
  VECTOR_3D *pVVar6;
  vector<GameObject_*,std::allocator<GameObject_*>_> *pvVar7;
  float fVar8;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_24;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_1c;
  int local_14;
  GameObject *local_10;
  vector<GameObject_*,std::allocator<GameObject_*>_> *local_c;
  float local_8;
  
  pvVar7 = GameObject::objectList;
  local_10 = (GameObject *)0x0;
  local_8 = 1e+30;
  local_c = GameObject::objectList;
  std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
            (&local_1c,GameObject::objectList->_Myfirst,
             (_Container_base_aux *)GameObject::objectList);
  while( true ) {
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
    _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
              (&local_24,pvVar7->_Mylast,(_Container_base_aux *)pvVar7);
    bVar3 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator==
                      (&local_1c,&local_24);
    if (bVar3) break;
    ppGVar4 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator*
                        (&local_1c);
    pGVar2 = *ppGVar4;
    if ((param_1 != pGVar2) && (pGVar2->isCargo == false)) {
      piVar1 = &pGVar2->_padding_;
      iVar5 = (**(code **)*piVar1)();
      local_14 = *(int *)(iVar5 + 0x20);
      if ((local_14 != 0x54554700) ||
         (iVar5 = (**(code **)param_1->_padding_)(), *(int *)(iVar5 + 0x20) != 0x52435943)) {
        iVar5 = (**(code **)*piVar1)();
        iVar5 = *(int *)(iVar5 + 0x28);
        if (((((iVar5 != 5) && (iVar5 != 7)) && (iVar5 != 2)) && (iVar5 != 10)) &&
           ((iVar5 != 3 || (local_14 == 0x544f5250)))) {
          pVVar6 = (VECTOR_3D *)(**(code **)(*piVar1 + 0xc))();
          fVar8 = Dist3D_Squared(*param_2,*pVVar6);
          pvVar7 = local_c;
          if (fVar8 < local_8) {
            local_10 = pGVar2;
            local_8 = fVar8;
          }
        }
      }
    }
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator++(&local_1c);
  }
  return local_10;
}
