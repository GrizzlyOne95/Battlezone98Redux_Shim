/*
 * Entry: 004093db
 * Name: GetClosestObject
 * Namespace: Global
 * Signature: GameObject * GetClosestObject(GameObject * param_1, ulong param_2, int param_3, float param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __cdecl GetClosestObject(GameObject *param_1,ulong param_2,int param_3,float param_4)

{
  int *piVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  VECTOR_3D VVar6;
  bool bVar7;
  VECTOR_3D *pVVar8;
  GameObject **ppGVar9;
  int iVar10;
  SPHERE *pSVar11;
  SPHERE *pSVar12;
  float *pfVar13;
  vector<GameObject_*,std::allocator<GameObject_*>_> *pvVar14;
  GameObject *pGVar15;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_28;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_20;
  undefined4 local_18;
  float local_14;
  GameObject *local_10;
  vector<GameObject_*,std::allocator<GameObject_*>_> *local_c;
  GameObject *local_8;
  
  pVVar8 = (VECTOR_3D *)(**(code **)(param_1->_padding_ + 0xc))();
  fVar2 = pVVar8->x;
  fVar3 = pVVar8->z;
  VVar6 = *pVVar8;
  local_18 = (**(code **)(param_1->_padding_ + 4))();
  pvVar14 = GameObject::objectList;
  local_10 = (GameObject *)0x0;
  local_c = GameObject::objectList;
  std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
            (&local_20,GameObject::objectList->_Myfirst,
             (_Container_base_aux *)GameObject::objectList);
  do {
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
    _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
              (&local_28,pvVar14->_Mylast,(_Container_base_aux *)pvVar14);
    bVar7 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator==
                      (&local_20,&local_28);
    if (bVar7) {
      return local_10;
    }
    ppGVar9 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator*
                        (&local_20);
    pGVar15 = *ppGVar9;
    piVar1 = &pGVar15->_padding_;
    local_8 = pGVar15;
    iVar10 = (**(code **)*piVar1)();
    if (((*(ulong *)(iVar10 + 0x20) == param_2) &&
        (iVar10 = (**(code **)(*piVar1 + 0x30))(), (*(uint *)(iVar10 + 0x14) & 0x200) == 0)) &&
       ((*(int *)(iVar10 + 0xac) != 4 || ((*(byte *)(*(int *)(iVar10 + 0xb0) + 0x10c) & 0xc) == 0)))
       ) {
      if ((*(int *)(iVar10 + 0xac) == 3) &&
         ((*(byte *)(*(int *)(iVar10 + 0xb0) + 0x10c) & 0xc) != 0)) {
        pVVar8 = (VECTOR_3D *)(**(code **)(*piVar1 + 0xc))();
        local_14 = Dist3D_Squared(VVar6,*pVVar8);
        pSVar11 = GameObject::GetSphere(local_8);
        pSVar12 = GameObject::GetSphere(param_1);
        fVar4 = pSVar11->radius + pSVar12->radius + 3.0;
        pvVar14 = local_c;
        pGVar15 = local_8;
        if (fVar4 * fVar4 < local_14) goto LAB_00409535;
      }
      if (((pGVar15->isVisible >> ((byte)local_18 & 0x1f) & 1) != 0) &&
         ((param_3 < 0 || (iVar10 = (**(code **)(*piVar1 + 4))(), iVar10 == param_3)))) {
        pfVar13 = (float *)(**(code **)(*piVar1 + 0xc))();
        fVar4 = fVar2 - *pfVar13;
        fVar5 = fVar3 - pfVar13[2];
        fVar4 = fVar5 * fVar5 + fVar4 * fVar4;
        if (fVar4 < param_4) {
          param_4 = fVar4;
          local_10 = pGVar15;
        }
      }
    }
LAB_00409535:
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator++(&local_20);
  } while( true );
}
