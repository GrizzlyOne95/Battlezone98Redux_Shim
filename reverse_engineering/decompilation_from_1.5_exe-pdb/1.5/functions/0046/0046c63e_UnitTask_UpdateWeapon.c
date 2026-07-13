/*
 * Entry: 0046c63e
 * Name: UnitTask::UpdateWeapon
 * Namespace: UnitTask
 * Signature: void UpdateWeapon(UnitTask * this, bool param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitTask::UpdateWeapon(UnitTask *this,bool param_1)

{
  int *piVar1;
  WeaponClass *pWVar2;
  GameObject *pGVar3;
  VECTOR_3D VVar4;
  VECTOR_3D VVar5;
  VECTOR_3D VVar6;
  VECTOR_3D VVar7;
  char cVar8;
  bool bVar9;
  SPHERE *pSVar10;
  SPHERE *pSVar11;
  float *pfVar12;
  uint uVar13;
  _OBJ76 *p_Var14;
  int iVar15;
  MAT_3D *pMVar16;
  VECTOR_3D *pVVar17;
  Weapon *pWVar18;
  OrdnanceClass *unaff_ESI;
  GameObject *unaff_EDI;
  double *pdVar19;
  float fVar20;
  float fVar21;
  double dVar22;
  undefined3 in_stack_00000005;
  float fVar23;
  char *pcVar24;
  float fVar25;
  MAT_3D local_e4;
  float local_a4 [6];
  undefined4 local_8c;
  undefined4 local_88;
  float local_84;
  double local_7c;
  double local_74;
  double local_6c;
  VECTOR_3D local_64;
  float local_58;
  VECTOR_3D local_54;
  float local_48;
  VECTOR_3D local_44;
  VECTOR_3D local_38;
  float local_2c;
  float local_28;
  float local_24;
  Carrier *local_20;
  int *local_1c;
  _OBJ76 *local_18;
  _OBJ76 *local_14;
  float *local_10;
  float local_c;
  float local_8;
  
  local_20 = (Carrier *)this->me->_padding_;
  if (local_20 == (Carrier *)0x0) {
    pcVar24 = "UpdateWeapon with no carrier\n";
LAB_0046c665:
    Trace(pcVar24);
    return;
  }
  if (this->weapon == (Weapon *)0x0) {
    pcVar24 = "UpdateWeapon with no weapon\n";
    goto LAB_0046c665;
  }
  if (this->him == (GameObject *)0x0) {
    local_8 = 0.0;
  }
  else {
    local_14 = (_OBJ76 *)this->him->collisionRadius;
    dVar22 = rsqrt((double)(this->targetDistSq + 0.0001));
    local_8 = (float)dVar22 * (float)local_14;
  }
  pWVar18 = this->weapon;
  pWVar2 = pWVar18->weaponClass;
  uVar13 = pWVar2->sig;
  if (uVar13 < 0x52444555) {
    if (uVar13 == 0x52444554) {
      if (*(char *)&pWVar18[1].M.right_x == '\0') {
        if (param_1 == false) {
          return;
        }
      }
      else {
        local_14 = pWVar18[1].obj;
        if (local_14 != (_OBJ76 *)0x0) {
          iVar15 = local_14->render_type_override;
          local_38.x = (float)*(double *)(iVar15 + 0x48);
          local_10 = &(local_14->transform).up_z;
          local_38.y = (float)*(double *)(iVar15 + 0x50);
          local_38.z = (float)*(double *)(iVar15 + 0x58);
          fVar20 = *local_10;
          fVar23 = (local_14->transform).front_x;
          fVar25 = (local_14->transform).front_y;
          fVar21 = TimeStep();
          VVar4.y = local_38.y;
          VVar4.x = local_38.x;
          VVar4.z = local_38.z;
          VVar6.y = fVar23;
          VVar6.x = fVar20;
          VVar6.z = fVar25;
          pVVar17 = AddMultVectors(&local_64,VVar4,fVar21,VVar6);
          local_38.x = pVVar17->x;
          local_38.y = pVVar17->y;
          local_38.z = pVVar17->z;
          iVar15 = *(int *)(*(int *)&local_14->gravestone + 0x3c);
          if ((iVar15 != 0) && (0.0 < *(float *)(iVar15 + 0x50))) {
            pSVar10 = GameObject::GetSphere((GameObject *)this->me);
            pSVar11 = GameObject::GetSphere(this->him);
            local_c = pSVar10->radius + pSVar11->radius + *(float *)(iVar15 + 0x50);
            pVVar17 = (VECTOR_3D *)(**(code **)(this->me->_padding_ + 0xc))();
            VVar5.y = local_38.y;
            VVar5.x = local_38.x;
            VVar5.z = local_38.z;
            fVar20 = Dist3D_Squared(VVar5,*pVVar17);
            if (fVar20 < local_c * local_c) {
              return;
            }
          }
          pGVar3 = this->him;
          local_2c = *local_10;
          local_28 = local_10[1];
          local_24 = local_10[2];
          local_54.x = (pGVar3->euler).v.x;
          local_54.y = (pGVar3->euler).v.y;
          local_54.z = (pGVar3->euler).v.z;
          local_44.x = local_54.x - local_2c;
          local_44.y = local_54.y - local_28;
          local_44.z = local_54.z - local_24;
          pfVar12 = (float *)(**(code **)(pGVar3->_padding_ + 0xc))();
          local_2c = *pfVar12;
          local_28 = pfVar12[1];
          local_24 = pfVar12[2];
          if (0.0 < (local_2c - local_38.x) * local_44.x +
                    (local_28 - local_38.y) * local_44.y + (local_24 - local_38.z) * local_44.z) {
            pWVar18 = this->weapon;
            goto LAB_0046c7d8;
          }
        }
      }
    }
    else if (uVar13 != 0x43485247) {
      if (uVar13 == 0x44495350) {
        if (param_1 == false) {
          return;
        }
LAB_0046c7d8:
        iVar15 = pWVar18->_padding_;
        goto LAB_0046ce24;
      }
      if (uVar13 != 0x494d474c) {
        if (uVar13 == 0x49524546) {
          return;
        }
        if (uVar13 != 0x4c4e4348) goto LAB_0046c725;
      }
LAB_0046c6ff:
      if (param_1 == false) {
        return;
      }
      local_8 = Max(local_8,(float)pWVar2[1].label);
      goto LAB_0046c725;
    }
  }
  else {
    if (uVar13 == 0x52444d50) {
      return;
    }
    if (uVar13 == 0x5244524c) {
      if (param_1 == false) {
        return;
      }
      if ((*(int *)pWVar18->ordnanceClass->odf == 0x544f5250) &&
         (this->targetDistSq < this->closeSq)) {
        return;
      }
      local_8 = Max(local_8,(float)pWVar2[1].label);
    }
    else {
      if (uVar13 == 0x54484d4c) goto LAB_0046c6ff;
      if (uVar13 == 0x54525850) {
        return;
      }
LAB_0046c725:
      if (param_1 == false) {
        return;
      }
      if (this->targetDistSq < this->closeSq * this->closeAdjust) {
        fVar20 = TimeStep();
        this->closeAdjust = this->closeAdjust - fVar20 * 0.1;
        if (this->himHandle != this->me->_padding_) {
          return;
        }
        _param_1 = (float)this->me->_padding_;
        fVar20 = Get_TimeLocal();
        if (1.0 <= fVar20 - _param_1) {
          return;
        }
        if (this->me->_padding_ == 0) {
          return;
        }
        fVar20 = TimeStep();
        this->closeAdjust =
             this->closeAdjust - fVar20 * *(float *)(this->me->_padding_ + 0x54) * 0.01;
        return;
      }
      this->closeAdjust = 1.0;
    }
  }
  if ((((this->targetDir).z <= 0.0) || (this->fireConeX + local_8 <= ABS((this->targetDir).x))) ||
     (local_8 * 0.5 + this->fireConeY <= ABS((this->targetDir).y))) {
    if (this->weapon->weaponClass->sig != 0x43485247) {
      return;
    }
    iVar15 = this->weapon->_padding_;
LAB_0046ce24:
    (**(code **)(iVar15 + 8))();
    return;
  }
  GameObject::SetTarget((GameObject *)this->me,this->him);
  uVar13 = this->me->_padding_;
  if (-1 < this->specialSlot) {
    uVar13 = uVar13 & ~(1 << ((byte)this->specialSlot & 0x1f));
  }
  Carrier::SetSelected(local_20,uVar13);
  pWVar18 = this->weapon;
  uVar13 = pWVar18->weaponClass->sig;
  if (uVar13 < 0x504f5053) {
    if (uVar13 == 0x504f5052) goto LAB_0046ce04;
    if (uVar13 == 0x43485247) {
      if (0 < (int)pWVar18[1].M.right_x) {
        return;
      }
      if (param_1 == false) {
        (**(code **)(pWVar18->_padding_ + 8))();
      }
      pWVar18 = this->weapon;
      local_18 = pWVar18[1].hard;
      if (*(int *)&local_18->field_0x1c == 0) goto LAB_0046ce04;
      if (local_18 == *(_OBJ76 **)&pWVar18[1].field_0x1c) {
        return;
      }
      local_8 = (float)this->me->_padding_;
      local_14 = (_OBJ76 *)0x0;
      if (*(int *)&local_18->field_0x1c != 0) {
        _param_1 = *(float *)&local_18->field_0x4;
        piVar1 = (int *)(*(int *)&local_18->field_0x1c + 0x48);
        iVar15 = *piVar1;
        if ((0 < iVar15) &&
           (uVar13 = this->me->_padding_,
           fVar20 = (float)((longlong)
                            (CONCAT44((int)(uVar13 ^ 0x33333333) >> 0x1f,uVar13) ^ 0x33333333) /
                           (longlong)iVar15), (int)fVar20 < (int)_param_1)) {
          _param_1 = fVar20;
        }
        local_c = (float)(int)_param_1;
        fVar20 = GetOrdnanceDamage(unaff_EDI,unaff_ESI);
        local_10 = (float *)(fVar20 * local_c);
        pWVar18 = this->weapon;
        _param_1 = (float)((int)_param_1 + -1);
        fVar20 = Max(0.0001,(float)(int)_param_1 * *(float *)&local_18->id +
                            (float)pWVar18[1]._padding_);
        local_14 = (_OBJ76 *)(local_8 / fVar20);
        _param_1 = 1.0 - local_8;
        fVar20 = Max(0.0001,(float)*piVar1 * local_c);
        local_14 = (_OBJ76 *)((_param_1 / fVar20 + (float)local_14) * (float)local_10);
      }
      pdVar19 = (double *)&(local_18->transform).right_y;
      local_c = 0.0;
      if (pdVar19 <= *(undefined1 **)&pWVar18[1].field_0x1c) {
        local_18 = (_OBJ76 *)(-4 - (int)local_18);
        do {
          if (*(float *)((int)pdVar19 + 0x1c) != 0.0) {
            _param_1 = *(float *)((int)pdVar19 + 4);
            local_1c = (int *)((int)*(float *)((int)pdVar19 + 0x1c) + 0x48);
            if ((0 < *local_1c) &&
               (uVar13 = this->me->_padding_,
               fVar20 = (float)((longlong)
                                (CONCAT44((int)(uVar13 ^ 0x33333333) >> 0x1f,uVar13) ^ 0x33333333) /
                               (longlong)*local_1c), (int)fVar20 < (int)_param_1)) {
              _param_1 = fVar20;
            }
            local_10 = (float *)(float)(int)_param_1;
            local_58 = GetOrdnanceDamage(unaff_EDI,unaff_ESI);
            local_58 = local_58 * (float)local_10;
            _param_1 = (float)((int)_param_1 + -1);
            local_10 = (float *)((float)*local_1c * (float)local_10);
            local_1c = (int *)this->me->_padding_;
            local_48 = (float)(int)_param_1 * *(float *)(pdVar19 + 1) + *(float *)pdVar19;
            fVar20 = Get_Time();
            _param_1 = (float)((int)(&local_18->field_0x4 + (int)pdVar19) / 0x24);
            fVar20 = Noise1D((float)(int)local_1c * 0.61 +
                             (float)(int)_param_1 * 2.73 + fVar20 * 3.0);
            local_1c = (int *)(fVar20 * 0.1 + 1.0);
            _param_1 = 1.0 - local_8;
            fVar20 = Max(0.0001,(float)local_10);
            _param_1 = _param_1 / fVar20;
            fVar20 = Max(0.0001,local_48);
            fVar20 = (local_8 / fVar20 + _param_1) * local_58 * (float)local_1c;
            if (local_c < fVar20) {
              local_c = fVar20;
            }
          }
          pdVar19 = (double *)((int)pdVar19 + 0x24);
        } while (pdVar19 <= *(float **)&this->weapon[1].field_0x1c);
      }
      fVar20 = (float)(uint)(ushort)((ushort)(local_c < (float)local_14) << 8 |
                                    (ushort)(local_c == (float)local_14) << 0xe);
LAB_0046ce02:
      if (fVar20 != 0.0) {
        return;
      }
      goto LAB_0046ce04;
    }
    if ((uVar13 == 0x494d474c) || (uVar13 == 0x4c4e4348)) goto LAB_0046cdfc;
    if (uVar13 == 0x4d4f5254) goto LAB_0046ce04;
  }
  else {
    if (uVar13 == 0x52444554) goto LAB_0046ce04;
    if ((uVar13 == 0x5244524c) || (uVar13 == 0x54484d4c)) {
LAB_0046cdfc:
      fVar20 = pWVar18[1].M.right_y;
      goto LAB_0046ce02;
    }
  }
  p_Var14 = (_OBJ76 *)(**(code **)(this->him->_padding_ + 0x30))();
  iVar15 = dynamic_object(p_Var14);
  if (iVar15 != 0) {
    p_Var14 = (_OBJ76 *)(**(code **)(this->him->_padding_ + 0x30))();
    iVar15 = IsCraft(p_Var14);
    if ((iVar15 == 0) || (cVar8 = (**(code **)(this->him->_padding_ + 0x68))(), cVar8 != '\0'))
    goto LAB_0046ce04;
  }
  pMVar16 = Matrix_Multiply(&local_e4,&this->weapon->obj->transform,&this->weapon->M);
  _param_1 = this->time;
  pfVar12 = local_a4;
  for (iVar15 = 0x10; iVar15 != 0; iVar15 = iVar15 + -1) {
    *pfVar12 = pMVar16->right_x;
    pMVar16 = (MAT_3D *)&pMVar16->right_y;
    pfVar12 = pfVar12 + 1;
  }
  local_2c = (float)local_8c;
  local_28 = (float)local_88;
  local_24 = local_84;
  VVar7.y = (float)local_88;
  VVar7.x = (float)local_8c;
  VVar7.z = local_84;
  pVVar17 = ScaleVector(&local_64,this->shotSpeed,VVar7);
  local_38.x = (float)local_7c;
  local_54.x = pVVar17->x;
  local_38.y = (float)local_74;
  local_38.z = (float)local_6c;
  local_54.y = pVVar17->y;
  local_54.z = pVVar17->z;
  local_2c = local_38.x;
  local_28 = local_38.y;
  local_24 = local_38.z;
  bVar9 = IntersectGameObject(&local_38,&local_54,(float *)&param_1,&local_44,this->him,0.0);
  if (!bVar9) {
    return;
  }
LAB_0046ce04:
  Carrier::TriggerSelected(local_20);
  return;
}
