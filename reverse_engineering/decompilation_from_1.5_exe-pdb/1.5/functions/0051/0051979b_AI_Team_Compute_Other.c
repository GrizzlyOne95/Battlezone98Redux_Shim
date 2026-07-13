/*
 * Entry: 0051979b
 * Name: AI_Team_Compute_Other
 * Namespace: Global
 * Signature: void AI_Team_Compute_Other(tag_strategy_map * param_1, tag_team * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_Team_Compute_Other(tag_strategy_map *param_1,tag_team *param_2)

{
  int *piVar1;
  GameObject *pGVar2;
  ScavengerProcess *this;
  void ***pppvVar3;
  void *pvVar4;
  vector<GameObject_*,std::allocator<GameObject_*>_> *pvVar5;
  bool bVar6;
  GameObject **ppGVar7;
  int iVar8;
  float *pfVar9;
  VECTOR_3D *pVVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  float local_28;
  float local_20;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_1c;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_14;
  vector<GameObject_*,std::allocator<GameObject_*>_> *local_c;
  int local_8;
  
  pvVar5 = GameObject::objectList;
  local_c = GameObject::objectList;
  std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
            (&local_14,GameObject::objectList->_Myfirst,
             (_Container_base_aux *)GameObject::objectList);
  std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
            (&local_1c,pvVar5->_Mylast,(_Container_base_aux *)pvVar5);
  bVar6 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator==
                    (&local_14,&local_1c);
  do {
    if (bVar6) {
      UpdateAOI(param_2,true);
      UpdateAOI(param_2,false);
      return;
    }
    ppGVar7 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator*
                        (&local_14);
    pGVar2 = *ppGVar7;
    piVar1 = &pGVar2->_padding_;
    iVar8 = (**(code **)*piVar1)();
    if (*(int *)(iVar8 + 0x20) == 0x53435250) {
      pfVar9 = (float *)(*(code *)((undefined4 *)*piVar1)[3])();
      local_28 = *pfVar9;
      local_20 = pfVar9[2];
      local_8 = 1;
LAB_0051985b:
      iVar8 = grid_rows + -1;
      iVar12 = 0;
      iVar11 = PosZ2POS((double)local_20);
      iVar8 = Clamp((int)(iVar11 + (iVar11 >> 0x1f & 7U)) >> 3,iVar12,iVar8);
      pppvVar3 = (param_2->strategic_targets).grid;
      iVar11 = grid_columns + -1;
      iVar13 = 0;
      iVar12 = PosX2POS((double)local_28);
      iVar11 = Clamp((int)(iVar12 + (iVar12 >> 0x1f & 7U)) >> 3,iVar13,iVar11);
      pvVar4 = pppvVar3[iVar8][iVar11];
      *(int *)((int)pvVar4 + 0x68) = *(int *)((int)pvVar4 + 0x68) + local_8;
      *(undefined4 *)((int)pvVar4 + 0x6c) = 1;
      *(undefined4 *)((int)pvVar4 + 0x70) = 1;
    }
    else {
      iVar8 = (**(code **)*piVar1)();
      if (((*(int *)(iVar8 + 0x20) == 0x53434156) &&
          (iVar8 = (**(code **)(*piVar1 + 4))(), iVar8 == param_2->team_ID)) &&
         (this = (ScavengerProcess *)pGVar2->aiProcess, this != (ScavengerProcess *)0x0)) {
        pVVar10 = ScavengerProcess::GetScrapPosition(this);
        local_28 = pVVar10->x;
        local_20 = pVVar10->z;
        if (0.0 < pVVar10->y) {
          local_8 = 3;
          goto LAB_0051985b;
        }
      }
    }
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator++(&local_14);
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
    _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
              (&local_1c,local_c->_Mylast,(_Container_base_aux *)local_c);
    bVar6 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator==
                      (&local_14,&local_1c);
  } while( true );
}
