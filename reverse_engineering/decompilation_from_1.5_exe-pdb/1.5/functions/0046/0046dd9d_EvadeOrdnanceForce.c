/*
 * Entry: 0046dd9d
 * Name: EvadeOrdnanceForce
 * Namespace: Global
 * Signature: VECTOR_3D * EvadeOrdnanceForce(VECTOR_3D * __return_storage_ptr__, GameObject * param_1, Ordnance * param_2, Ordnance * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __cdecl
EvadeOrdnanceForce(VECTOR_3D *__return_storage_ptr__,GameObject *param_1,Ordnance *param_2,
                  Ordnance **param_3)

{
  _OBJ76 *p_Var1;
  Missile *this;
  VECTOR_3D VVar2;
  VECTOR_3D VVar3;
  VECTOR_3D VVar4;
  VECTOR_3D VVar5;
  VECTOR_3D VVar6;
  bool bVar7;
  Ordnance **ppOVar8;
  float *pfVar9;
  VECTOR_3D *pVVar10;
  SPHERE *pSVar11;
  GameObject *pGVar12;
  OrdnanceClass *unaff_ESI;
  GameObject *unaff_EDI;
  float fVar13;
  float fVar14;
  double dVar15;
  int iVar16;
  int iVar17;
  float fVar18;
  float fVar19;
  VECTOR_3D local_e4;
  VECTOR_3D local_d8;
  VECTOR_3D local_cc;
  VECTOR_3D local_c0;
  VECTOR_3D local_b4;
  VECTOR_3D local_a8;
  float local_9c;
  float fStack_98;
  float fStack_94;
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  MAT_3D *local_54;
  _Const_iterator<1> local_50;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  _Const_iterator<1> local_30;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  Missile *local_10;
  float local_c;
  float local_8;
  
  p_Var1 = param_1->obj;
  local_28 = 0.0;
  local_10 = (Missile *)0x0;
  __return_storage_ptr__->x = 0.0;
  local_54 = &p_Var1->transform;
  __return_storage_ptr__->y = 0.0;
  __return_storage_ptr__->z = 0.0;
  std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::_Const_iterator<1>
            (&local_30,(Ordnance::ordnanceList._Myhead)->_Next,&Ordnance::ordnanceList);
  std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::_Const_iterator<1>
            (&local_50,Ordnance::ordnanceList._Myhead,&Ordnance::ordnanceList);
  bVar7 = std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::operator==
                    (&local_30,&local_50);
  if (!bVar7) {
    do {
      ppOVar8 = std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::operator*
                          (&local_30);
      this = (Missile *)*ppOVar8;
      if (*(int *)(this->_padding_ + 0xc) != 0x534e4950) {
        iVar16 = this->_padding_;
        local_b4.x = (float)*(double *)(iVar16 + 0x48);
        local_b4.y = (float)*(double *)(iVar16 + 0x50);
        local_b4.z = (float)*(double *)(iVar16 + 0x58);
        local_48 = local_b4.x;
        local_44 = local_b4.y;
        local_40 = local_b4.z;
        pfVar9 = (float *)(**(code **)(param_1->_padding_ + 0xc))();
        local_90 = *pfVar9;
        local_8c = pfVar9[1];
        local_88 = pfVar9[2];
        local_20 = local_48 - local_90;
        local_1c = local_44 - local_8c;
        local_18 = local_40 - local_88;
        if (local_20 * local_20 + local_1c * local_1c + local_18 * local_18 <= 40000.0) {
          if (this == (Missile *)param_2) {
            if (local_10 == (Missile *)0x0) {
              local_10 = (Missile *)param_2;
            }
          }
          else {
            pVVar10 = Vector_Untransform(&local_e4,&local_b4,local_54);
            local_60 = pVVar10->x;
            local_5c = pVVar10->y;
            local_58 = pVVar10->z;
            if ((local_58 < ABS(local_60)) || (local_58 < ABS(local_5c) * 1.5)) goto LAB_0046e18e;
          }
          local_78 = (param_1->euler).v.x;
          local_74 = (param_1->euler).v.y;
          local_70 = (param_1->euler).v.z;
          local_84 = (float)this->_padding_;
          local_80 = (float)this->_padding_;
          local_7c = (float)this->_padding_;
          local_6c = local_84 - local_78;
          local_68 = local_80 - local_74;
          local_64 = local_7c - local_70;
          fVar14 = local_6c * local_6c + local_68 * local_68 + local_64 * local_64;
          if (0.0001 <= fVar14) {
            local_8 = -((local_6c * local_20 + local_68 * local_1c + local_64 * local_18) / fVar14);
            VVar2.y = local_1c;
            VVar2.x = local_20;
            VVar2.z = local_18;
            VVar3.y = local_68;
            VVar3.x = local_6c;
            VVar3.z = local_64;
            pVVar10 = AddMultVectors(&local_c0,VVar2,local_8,VVar3);
            local_3c = pVVar10->x;
            local_38 = pVVar10->y;
            local_34 = pVVar10->z;
            local_c = SQRT(local_3c * local_3c + local_34 * local_34 + local_38 * local_38);
            pVVar10 = ScaleVector(&local_d8,-1.0 / (local_c + 1.1920929e-07),*pVVar10);
            local_9c = pVVar10->x;
            fStack_98 = pVVar10->y;
            fStack_94 = pVVar10->z;
            pSVar11 = GameObject::GetSphere(param_1);
            local_14 = pSVar11->radius + *(float *)(this->_padding_ + 0xd4);
            iVar16 = *(int *)(this->_padding_ + 0xc);
            if ((((iVar16 == 0x494d474d) || (iVar16 == 0x54484d4d)) || (iVar16 == 0x4d53534c)) &&
               (pGVar12 = Missile::GetTarget(this), pGVar12 == param_1)) {
              if (local_8 <= 0.0) {
                local_8 = 0.0;
              }
              if (local_8 < 3.0) {
                local_24 = Min(3.0 - local_8,1.0);
                if ((local_8 < 1.0) && (local_14 < local_c)) {
                  iVar16 = this->_padding_;
                  iVar17 = this->_padding_;
                  fVar14 = (float)this->_padding_;
                  fVar13 = Min(1.0,local_c / local_14 - 1.0);
                  VVar4.y = (float)iVar17;
                  VVar4.x = (float)iVar16;
                  VVar4.z = fVar14;
                  pVVar10 = AddMultVectors(&local_cc,*__return_storage_ptr__,
                                           (local_8 - 1.0) * fVar13,VVar4);
                  __return_storage_ptr__->x = pVVar10->x;
                  __return_storage_ptr__->y = pVVar10->y;
                  __return_storage_ptr__->z = pVVar10->z;
                }
                goto LAB_0046e11e;
              }
            }
            else if ((0.0 < local_8) && (ABS(local_c) < local_14 * 2.5)) {
              local_24 = Min(2.5 - local_c / local_14,1.0);
LAB_0046e11e:
              if (local_24 != 0.0) {
                fVar14 = GetOrdnanceDamage(unaff_EDI,unaff_ESI);
                fVar14 = fVar14 / (local_8 + 1.0);
                if (local_28 < fVar14) {
                  local_28 = fVar14;
                  local_10 = this;
                }
                VVar5.y = fStack_98;
                VVar5.x = local_9c;
                VVar5.z = fStack_94;
                pVVar10 = AddMultVectors(&local_a8,*__return_storage_ptr__,fVar14 * local_24,VVar5);
                __return_storage_ptr__->x = pVVar10->x;
                __return_storage_ptr__->y = pVVar10->y;
                __return_storage_ptr__->z = pVVar10->z;
              }
            }
          }
        }
      }
LAB_0046e18e:
      std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::operator++(&local_30);
      std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::_Const_iterator<1>
                (&local_50,Ordnance::ordnanceList._Myhead,&Ordnance::ordnanceList);
      bVar7 = std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::operator==
                        (&local_30,&local_50);
    } while (!bVar7);
    if ((local_10 != (Missile *)0x0) &&
       (fVar14 = __return_storage_ptr__->x * __return_storage_ptr__->x +
                 __return_storage_ptr__->y * __return_storage_ptr__->y +
                 __return_storage_ptr__->z * __return_storage_ptr__->z, 400.0 < fVar14)) {
      fVar13 = __return_storage_ptr__->x;
      fVar18 = __return_storage_ptr__->y;
      fVar19 = __return_storage_ptr__->z;
      dVar15 = rsqrt((double)fVar14);
      VVar6.y = fVar18;
      VVar6.x = fVar13;
      VVar6.z = fVar19;
      pVVar10 = ScaleVector(&local_a8,(float)dVar15 * 20.0,VVar6);
      __return_storage_ptr__->x = pVVar10->x;
      __return_storage_ptr__->y = pVVar10->y;
      __return_storage_ptr__->z = pVVar10->z;
    }
  }
  if (param_3 != (Ordnance **)0x0) {
    *param_3 = (Ordnance *)local_10;
  }
  return __return_storage_ptr__;
}
