/*
 * Entry: 00536268
 * Name: Popper::Control
 * Namespace: Popper
 * Signature: void Control(Popper * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Popper::Control(Popper *this,float param_1)

{
  undefined1 *puVar1;
  uint *puVar2;
  Craft *pCVar3;
  _OBJ76 *p_Var4;
  float fVar5;
  float fVar6;
  VECTOR_3D VVar7;
  bool bVar8;
  Craft **ppCVar9;
  int iVar10;
  VECTOR_3D *pVVar11;
  float *pfVar12;
  MAT_3D *pMVar13;
  Ordnance *pOVar14;
  ushort uVar15;
  VECTOR_3D *unaff_ESI;
  VECTOR_3D *unaff_EDI;
  MAT_3D *pMVar16;
  float fVar17;
  MAT_3D local_c4;
  MAT_3D local_84;
  float local_44;
  float fStack_40;
  float fStack_3c;
  Team *local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  Craft *local_24;
  float local_20;
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> local_1c;
  float local_14;
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> local_10;
  Craft *local_8;
  
  if (*(float *)&this->field_0x38 < 0.0) {
    local_34 = *(float *)(*(int *)&this->field_0x10 + 0xb0);
    iVar10 = *(int *)&this->field_0x18;
    local_8 = (Craft *)0x0;
    local_34 = local_34 * local_34;
    local_30 = (float)*(double *)(iVar10 + 0x48);
    local_2c = (float)*(double *)(iVar10 + 0x50);
    local_28 = (float)*(double *)(iVar10 + 0x58);
    local_38 = Team::GetTeam(*(ushort *)(iVar10 + 0x16) & 0xf);
    std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::
    _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>
              (&local_10,Craft::craftList._Myfirst,(_Container_base_aux *)&Craft::craftList);
    local_1c._padding_ = local_10._padding_;
    local_1c._Myptr = local_10._Myptr;
    std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::
    _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>
              (&local_10,Craft::craftList._Mylast,(_Container_base_aux *)&Craft::craftList);
    bVar8 = std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::operator==
                      (&local_1c,&local_10);
    if (!bVar8) {
      do {
        ppCVar9 = std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::operator*
                            (&local_1c);
        pCVar3 = *ppCVar9;
        local_24 = pCVar3;
        iVar10 = (**(code **)(pCVar3->_padding_ + 4))();
        bVar8 = Team::EnemyP(local_38,iVar10);
        if ((bVar8) && ((*(uint *)(pCVar3->_padding_ + 0x14) & 0x200) == 0)) {
          pVVar11 = (VECTOR_3D *)(**(code **)(pCVar3->_padding_ + 0xc))();
          VVar7.y = local_2c;
          VVar7.x = local_30;
          VVar7.z = local_28;
          fVar17 = Dist3D_Squared(*pVVar11,VVar7);
          if (fVar17 < local_34) {
            local_8 = local_24;
            local_34 = fVar17;
          }
        }
        std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::operator++(&local_1c);
        std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::
        _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>
                  (&local_10,Craft::craftList._Mylast,(_Container_base_aux *)&Craft::craftList);
        bVar8 = std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::operator==
                          (&local_1c,&local_10);
      } while (!bVar8);
      if (local_8 != (Craft *)0x0) {
        pfVar12 = (float *)(**(code **)(local_8->_padding_ + 0xc))();
        iVar10 = *(int *)&this->field_0x18;
        local_44 = (float)*(double *)(iVar10 + 0x48);
        fStack_40 = (float)*(double *)(iVar10 + 0x50);
        fStack_3c = (float)*(double *)(iVar10 + 0x58);
        local_14 = (float)local_8->_padding_;
        local_10._padding_ = local_8->_padding_;
        local_10._Myptr = (Craft **)local_8->_padding_;
        local_24 = *(Craft **)(*(int *)&this->field_0x10 + 0xb8);
        local_20 = *pfVar12 - local_44;
        local_1c._padding_ = (int)(pfVar12[1] - fStack_40);
        fVar6 = pfVar12[2] - fStack_3c;
        local_8 = (Craft *)((local_14 * local_14 +
                            (float)local_10._padding_ * (float)local_10._padding_ +
                            (float)local_10._Myptr * (float)local_10._Myptr) -
                           ((OrdnanceClass *)local_24)->shotSpeed *
                           ((OrdnanceClass *)local_24)->shotSpeed);
        fVar5 = local_14 * local_20 +
                (float)local_10._padding_ * (float)local_1c._padding_ +
                (float)local_10._Myptr * fVar6;
        fVar17 = fVar5 * fVar5 -
                 (local_20 * local_20 +
                 (float)local_1c._padding_ * (float)local_1c._padding_ + fVar6 * fVar6) *
                 (float)local_8;
        if (0.0 < fVar17) {
          fVar17 = (-fVar5 - SQRT(fVar17)) / (float)local_8;
        }
        else {
          fVar17 = -(fVar5 / (float)local_8);
        }
        local_20 = local_14 * fVar17 + local_20;
        local_1c._padding_ = (int)(fVar17 * (float)local_10._padding_ + (float)local_1c._padding_);
        local_1c._Myptr = (Craft **)(fVar6 + fVar17 * (float)local_10._Myptr);
        local_30 = local_44;
        local_2c = fStack_40;
        local_28 = fStack_3c;
        pMVar13 = Build_Directinal_Matrix(&local_c4,unaff_EDI,unaff_ESI);
        p_Var4 = *(_OBJ76 **)&this->field_0xcc;
        pMVar16 = &local_84;
        for (iVar10 = 0x10; iVar10 != 0; iVar10 = iVar10 + -1) {
          pMVar16->right_x = pMVar13->right_x;
          pMVar13 = (MAT_3D *)&pMVar13->right_y;
          pMVar16 = (MAT_3D *)&pMVar16->right_y;
        }
        pOVar14 = OrdnanceClass::Build((OrdnanceClass *)local_24,&local_84,p_Var4);
        puVar1 = &(pOVar14->damage).field_0x8;
        *(ushort *)puVar1 =
             *(ushort *)puVar1 ^
             (*(ushort *)&(pOVar14->damage).field_0x8 ^ *(ushort *)&this->field_0x6c) & 0x10;
        uVar15 = *(ushort *)&(pOVar14->damage).field_0x8;
        uVar15 = (*(ushort *)&this->field_0x6c ^ uVar15) & 0x20 ^ uVar15;
        *(ushort *)&(pOVar14->damage).field_0x8 = uVar15;
        *(ushort *)&(pOVar14->damage).field_0x8 =
             (*(ushort *)&this->field_0x6c ^ uVar15) & 0x3c0 ^ uVar15;
        pOVar14->source = *(ushort *)&this->field_0x7c;
        pOVar14->ordid = *(short *)&this->field_0x7e + 1;
        pOVar14->bSend = (uint)(*(short *)&this->field_0x7c == -0x5ff);
        ExplosionClass::Build
                  (*(ExplosionClass **)(*(int *)&this->field_0x10 + 0xb4),
                   (MAT_3D *)(*(int *)&this->field_0x18 + 0x20),*(_OBJ76 **)&this->field_0xcc);
        puVar2 = (uint *)(*(int *)&this->field_0x18 + 0x14);
        *puVar2 = *puVar2 | 0x200;
      }
    }
  }
  return;
}
