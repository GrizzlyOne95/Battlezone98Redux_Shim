/*
 * Entry: 004b0011
 * Name: ShieldTower::Simulate
 * Namespace: ShieldTower
 * Signature: void Simulate(ShieldTower * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ShieldTower::Simulate(ShieldTower *this,float param_1)

{
  VECTOR_3D *pVVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  Ordnance *pOVar5;
  ShieldTower *pSVar6;
  bool bVar7;
  int iVar8;
  GameObject *pGVar9;
  MAT_3D *pMVar10;
  float *pfVar11;
  Ordnance **ppOVar12;
  int iVar13;
  MAT_3D *unaff_EDI;
  MAT_3D *pMVar14;
  float *pfVar15;
  float fVar16;
  MAT_3D local_164;
  MAT_3D local_124;
  Range_Search_Results local_e4;
  VECTOR_3D local_b8;
  float local_ac;
  float local_a8;
  float local_a4;
  float local_a0;
  float local_9c;
  float local_98;
  float local_94;
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
  MAT_3D *local_58;
  float local_54;
  _Const_iterator<1> local_50;
  VECTOR_3D local_48;
  float local_3c [4];
  float local_2c;
  float local_28;
  _Const_iterator<1> local_24;
  _Const_iterator<1> local_1c;
  ShieldTower *local_14;
  VECTOR_3D local_10;
  
  local_14 = this;
  iVar8 = ClosestPower(this);
  this->powerSource = iVar8;
  pGVar9 = GameObjectHandle::GetObj(iVar8);
  if (pGVar9 != (GameObject *)0x0) {
    iVar8 = this->_padding_;
    local_58 = (MAT_3D *)(iVar8 + 0x20);
    pMVar10 = Matrix_Inverse(&local_164,unaff_EDI);
    pSVar6 = local_14;
    pMVar14 = &local_124;
    for (iVar13 = 0x10; iVar13 != 0; iVar13 = iVar13 + -1) {
      pMVar14->right_x = pMVar10->right_x;
      pMVar10 = (MAT_3D *)&pMVar10->right_y;
      pMVar14 = (MAT_3D *)&pMVar14->right_y;
    }
    pfVar11 = (float *)(pSVar6->_padding_ + 0x160);
    pfVar15 = local_3c;
    for (iVar13 = 6; iVar13 != 0; iVar13 = iVar13 + -1) {
      *pfVar15 = *pfVar11;
      pfVar11 = pfVar11 + 1;
      pfVar15 = pfVar15 + 1;
    }
    local_b8.x = local_3c[0];
    local_b8.y = local_3c[1];
    local_b8.z = local_3c[2];
    local_ac = local_3c[3];
    local_a8 = local_3c[1];
    local_9c = local_3c[1];
    local_a4 = local_3c[2];
    local_a0 = local_3c[0];
    local_98 = local_28;
    local_8c = local_28;
    local_94 = local_3c[3];
    local_90 = local_3c[1];
    local_88 = local_3c[0];
    local_84 = local_2c;
    local_78 = local_2c;
    local_6c = local_2c;
    local_60 = local_2c;
    local_80 = local_3c[2];
    local_74 = local_3c[2];
    local_7c = local_3c[3];
    local_64 = local_3c[3];
    local_70 = local_3c[0];
    local_68 = local_28;
    local_5c = local_28;
    Vector_Transform(&local_b8,&local_b8,8,(MAT_3D *)(iVar8 + 0x20));
    pfVar11 = &local_b8.z;
    fVar3 = 1e+30;
    fVar16 = 1e+30;
    fVar4 = -1e+30;
    fVar2 = -1e+30;
    iVar13 = 8;
    do {
      if (((VECTOR_3D *)(pfVar11 + -2))->x < fVar16) {
        fVar16 = ((VECTOR_3D *)(pfVar11 + -2))->x;
      }
      if (fVar2 < ((VECTOR_3D *)(pfVar11 + -2))->x) {
        fVar2 = ((VECTOR_3D *)(pfVar11 + -2))->x;
      }
      if (*pfVar11 < fVar3) {
        fVar3 = *pfVar11;
      }
      if (fVar4 < *pfVar11) {
        fVar4 = *pfVar11;
      }
      pfVar11 = pfVar11 + 3;
      iVar13 = iVar13 + -1;
    } while (iVar13 != 0);
    Range::Search(collision_range_search,(double)fVar16,(double)fVar3,(double)fVar2,(double)fVar4,
                  &local_e4);
    while (bVar7 = Range_Search_Results::Get_Next_Object(&local_e4,(int **)&local_24._Ptr), bVar7) {
      local_1c._Ptr = (_Node *)GameObject::GetObj((int)(local_24._Ptr)->_Next);
      if ((GameObject *)local_1c._Ptr != (GameObject *)0x0) {
        pfVar11 = (float *)(**(code **)(((GameObject *)local_1c._Ptr)->_padding_ + 0xc))();
        local_10.x = *pfVar11;
        local_10.y = pfVar11[1];
        local_10.z = pfVar11[2];
        Vector_Transform(&local_10,&local_10,1,&local_124);
        if (((local_3c[0] < local_10.x) && (local_10.x < local_3c[3])) &&
           ((local_3c[1] < local_10.y &&
            (((local_10.y < local_2c && (local_3c[2] < local_10.z)) && (local_10.z < local_28))))))
        {
          fVar16 = *(float *)(local_14->_padding_ + 0x178) * param_1;
          local_54 = (((EULER *)((int)local_1c._Ptr + 0x108))->v).x;
          fVar2 = *(float *)(local_14->_padding_ + 0x17c) * param_1;
          local_50._padding_ = (int)(((EULER *)((int)local_1c._Ptr + 0x108))->v).y;
          local_50._Ptr = (_Node *)(((EULER *)((int)local_1c._Ptr + 0x108))->v).z;
          local_48.x = *(float *)(iVar8 + 0x38) * fVar16 - local_54 * fVar2;
          local_48.y = *(float *)(iVar8 + 0x3c) * fVar16 - (float)local_50._padding_ * fVar2;
          local_48.z = *(float *)(iVar8 + 0x40) * fVar16 - fVar2 * (float)local_50._Ptr;
          GameObject::AddVelocity((GameObject *)local_1c._Ptr,&local_48);
        }
      }
    }
    std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::_Const_iterator<1>
              (&local_1c,(Ordnance::ordnanceList._Myhead)->_Next,&Ordnance::ordnanceList);
    while( true ) {
      std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::_Const_iterator<1>
                (&local_24,Ordnance::ordnanceList._Myhead,&Ordnance::ordnanceList);
      bVar7 = std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::operator==
                        (&local_1c,&local_24);
      if (bVar7) break;
      local_50._padding_ = local_1c._padding_;
      local_50._Ptr = local_1c._Ptr;
      std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::operator++(&local_1c);
      ppOVar12 = std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::operator*
                           (&local_50);
      pOVar5 = *ppOVar12;
      local_10.x = (float)(pOVar5->obj->transform).posit_x;
      local_10.y = (float)(pOVar5->obj->transform).posit_y;
      local_10.z = (float)(pOVar5->obj->transform).posit_z;
      Vector_Transform(&local_10,&local_10,1,&local_124);
      if ((((local_3c[0] < local_10.x) && (local_10.x < local_3c[3])) && (local_3c[1] < local_10.y))
         && (((local_10.y < local_2c && (local_3c[2] < local_10.z)) && (local_10.z < local_28)))) {
        pVVar1 = &(pOVar5->euler).v;
        fVar16 = *(float *)(local_14->_padding_ + 0x180) * param_1;
        fVar2 = *(float *)(local_14->_padding_ + 0x184) * param_1;
        local_48.x = pVVar1->x;
        local_48.y = (pOVar5->euler).v.y;
        local_48.z = (pOVar5->euler).v.z;
        pVVar1->x = (local_58->front_x * fVar16 - local_48.x * fVar2) + pVVar1->x;
        (pOVar5->euler).v.y =
             (local_58->front_y * fVar16 - local_48.y * fVar2) + (pOVar5->euler).v.y;
        (pOVar5->euler).v.z =
             (local_58->front_z * fVar16 - fVar2 * local_48.z) + (pOVar5->euler).v.z;
        fVar16 = VecLen(*pVVar1);
        (pOVar5->euler).v_mag = fVar16;
        if (fVar16 == 0.0) {
          fVar16 = 1e+30;
        }
        else {
          fVar16 = 1.0 / fVar16;
        }
        (pOVar5->euler).v_mag_inv = fVar16;
      }
    }
  }
  Building::Simulate((Building *)local_14,param_1);
  return;
}
