/*
 * Entry: 004097c5
 * Name: GetClosestThreatWithin
 * Namespace: Global
 * Signature: GameObject * GetClosestThreatWithin(int param_1, VECTOR_3D param_2, float * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __cdecl GetClosestThreatWithin(int param_1,VECTOR_3D param_2,float *param_3)

{
  int *piVar1;
  GameObject *pGVar2;
  bool bVar3;
  GameObject **ppGVar4;
  int iVar5;
  VECTOR_3D *pVVar6;
  float *pfVar7;
  vector<GameObject_*,std::allocator<GameObject_*>_> *pvVar8;
  float fVar9;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_2c;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_24;
  _OBJ76 *local_1c;
  Team *local_18;
  GameObject *local_14;
  GameObject *local_10;
  vector<GameObject_*,std::allocator<GameObject_*>_> *local_c;
  float local_8;
  
  pvVar8 = GameObject::objectList;
  local_8 = *param_3;
  local_10 = (GameObject *)0x0;
  local_c = GameObject::objectList;
  local_18 = Team::GetTeam(param_1);
  std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
            (&local_24,pvVar8->_Myfirst,(_Container_base_aux *)pvVar8);
  do {
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
    _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
              (&local_2c,pvVar8->_Mylast,(_Container_base_aux *)pvVar8);
    bVar3 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator==
                      (&local_24,&local_2c);
    if (bVar3) {
      *param_3 = local_8;
      return local_10;
    }
    ppGVar4 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator*
                        (&local_24);
    pGVar2 = *ppGVar4;
    piVar1 = &pGVar2->_padding_;
    local_14 = pGVar2;
    iVar5 = (**(code **)(*piVar1 + 4))();
    bVar3 = Team::EnemyP(local_18,iVar5);
    if (bVar3) {
      iVar5 = (**(code **)*piVar1)();
      if (*(int *)(iVar5 + 0x20) == 0x4d494e45) {
        pVVar6 = (VECTOR_3D *)(**(code **)(*piVar1 + 0xc))();
        fVar9 = Dist3D_Squared(*pVVar6,param_2);
      }
      else {
        local_1c = (_OBJ76 *)(**(code **)(*piVar1 + 0x30))();
        iVar5 = IsCraft(local_1c);
        if (((iVar5 == 0) || ((local_1c->flags & 0x200) != 0)) ||
           (pGVar2->aiProcess == (AiProcess *)0x0)) goto LAB_004098cd;
        pfVar7 = (float *)(**(code **)(*piVar1 + 0xc))();
        fVar9 = (pfVar7[2] - param_2.z) * (pfVar7[2] - param_2.z) +
                (*pfVar7 - param_2.x) * (*pfVar7 - param_2.x);
      }
      pvVar8 = local_c;
      if (fVar9 < local_8) {
        local_10 = local_14;
        local_8 = fVar9;
      }
    }
LAB_004098cd:
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator++(&local_24);
  } while( true );
}
