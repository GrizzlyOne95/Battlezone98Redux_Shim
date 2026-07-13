/*
 * Entry: 0040f25b
 * Name: AttackTask::DoState
 * Namespace: AttackTask
 * Signature: void DoState(AttackTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall AttackTask::DoState(AttackTask *this)

{
  int iVar1;
  VECTOR_3D VVar2;
  bool bVar3;
  GameObject *pGVar4;
  VECTOR_3D *pVVar5;
  _OBJ76 *p_Var6;
  int iVar7;
  _OBJ76 *p_Var8;
  int *piVar9;
  AttackerInfo *pAVar10;
  float *pfVar11;
  float *pfVar12;
  byte bVar13;
  float fVar14;
  float fVar15;
  
  if (this->_padding_ == 0xd) {
    return;
  }
  pGVar4 = GameObjectHandle::GetObj(this->_padding_);
  this->_padding_ = (int)pGVar4;
  if (this->_padding_ == this->_padding_) {
    if (((pGVar4 == (GameObject *)0x0) ||
        (((GameObject *)this->_padding_)->carrier == (Carrier *)0x0)) ||
       ((bVar3 = GameObject::FriendP((GameObject *)this->_padding_,pGVar4), bVar3 &&
        ((*(int *)(this->_padding_ + 0xb0) != 4 || (*(int *)(this->_padding_ + 0xac) == 0)))))) {
      this->_padding_ = 0xd;
      return;
    }
  }
  else if (pGVar4 == (GameObject *)0x0) {
    this->_padding_ = 1;
    return;
  }
  pVVar5 = (VECTOR_3D *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
  pGVar4 = NearestVehicle((GameObject *)this->_padding_,pVVar5);
  this->_padding_ = (int)pGVar4;
  *(undefined1 *)&this->_padding_ = 0;
  iVar1 = *(int *)(this->_padding_ + 0x228);
  switch(this->_padding_) {
  case 2:
    bVar3 = UnitTask::AbleToHit((UnitTask *)this);
    *(bool *)&this->_padding_ = bVar3;
    if (bVar3) {
LAB_0040f59d:
      this->_padding_ = 10;
    }
    else {
      bVar3 = UnitTask::IsStuck((UnitTask *)this);
      if (bVar3) {
LAB_0040f7e1:
        this->_padding_ = 3;
      }
      else {
        pfVar11 = (float *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
        fVar15 = *pfVar11 - (float)this->_padding_;
        fVar14 = pfVar11[2] - (float)this->_padding_;
        if ((10000.0 < fVar14 * fVar14 + fVar15 * fVar15) ||
           (pfVar11 = (float *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))(),
           fVar15 = *pfVar11 - (float)this->_padding_, fVar14 = pfVar11[2] - (float)this->_padding_,
           fVar14 * fVar14 + fVar15 * fVar15 < 100.0)) goto LAB_0040f612;
LAB_0040f72e:
        UnitTask::DoGoto((UnitTask *)this);
      }
    }
    break;
  case 3:
    UnitTask::DoStuck((UnitTask *)this);
    break;
  case 4:
    bVar3 = CheckFollowing(this);
    if (!bVar3) {
      pfVar11 = (float *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
      pfVar12 = (float *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
      if ((pfVar12[2] - pfVar11[2]) * (pfVar12[2] - pfVar11[2]) +
          (*pfVar12 - *pfVar11) * (*pfVar12 - *pfVar11) <= 10000.0) {
        bVar3 = UnitTask::IsStuck((UnitTask *)this);
        if (bVar3) goto LAB_0040f7e1;
        UnitTask::DoFollow((UnitTask *)this);
      }
      else {
        piVar9 = (int *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
        this->_padding_ = *piVar9;
        this->_padding_ = piVar9[1];
        this->_padding_ = piVar9[2];
        this->_padding_ = 0xc;
      }
    }
    break;
  case 5:
    bVar3 = UnitTask::AbleToHit((UnitTask *)this);
    *(bool *)&this->_padding_ = bVar3;
    if (!bVar3) goto LAB_0040f612;
LAB_0040f326:
    UnitTask::DoBlast((UnitTask *)this);
    break;
  case 6:
    bVar3 = CheckWaiting(this);
    if (!bVar3) {
      UnitTask::DoSit((UnitTask *)this);
    }
    break;
  case 7:
    bVar3 = UnitTask::AbleToHit((UnitTask *)this);
    *(bool *)&this->_padding_ = bVar3;
    pfVar11 = (float *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
    pfVar12 = (float *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
    if ((pfVar12[2] - pfVar11[2]) * (pfVar12[2] - pfVar11[2]) +
        (*pfVar12 - *pfVar11) * (*pfVar12 - *pfVar11) <= (float)this->_padding_) {
      p_Var6 = (_OBJ76 *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0x30))();
      iVar7 = IsBuilding(p_Var6);
      if (iVar7 != 0) goto LAB_0040f59d;
      fVar15 = Get_Time();
      if (fVar15 <= (float)this->_padding_ + 10.0) {
        bVar3 = UnitTask::IsStuck((UnitTask *)this);
        if (!bVar3) {
          if ((char)this->_padding_ == '\0') {
            UnitTask::DoSlide((UnitTask *)this);
            VVar2.x = (float)this->_padding_;
            VVar2.y = (float)this->_padding_;
            VVar2.z = (float)this->_padding_;
            fVar15 = VecLen(VVar2);
            bVar13 = fVar15 < 5.0 | (byte)((ushort)((ushort)NAN(fVar15) << 10) >> 8);
            goto LAB_0040f57f;
          }
          iVar7 = this->_padding_;
          p_Var6 = (_OBJ76 *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0x30))();
          p_Var8 = (_OBJ76 *)(**(code **)(*(int *)(iVar7 + 0x20) + 0x30))();
          iVar7 = SidewaysAndClose(p_Var8,p_Var6);
          iVar7 = (-(uint)(iVar7 != 0) & 0xfffffffe) + 10;
          goto LAB_0040f441;
        }
        goto LAB_0040f7e1;
      }
    }
LAB_0040f612:
    this->_padding_ = 2;
    break;
  case 8:
    bVar3 = UnitTask::AbleToHit((UnitTask *)this);
    iVar7 = this->_padding_;
    *(bool *)&this->_padding_ = bVar3;
    if (*(float *)(iVar7 + 0x1e0) <= (float)this->_padding_) {
      if (!bVar3) goto LAB_0040f54e;
      fVar15 = Get_Time();
      if (fVar15 <= (float)this->_padding_ + 8.0) {
        UnitTask::DoStand((UnitTask *)this);
      }
      else {
        this->_padding_ = 9;
        iVar7 = GameObject::GetHandle((GameObject *)this->_padding_);
        this->fleeFrom = iVar7;
      }
    }
    else {
LAB_0040f498:
      this->fleeFrom = *(int *)(iVar7 + 0x1ec);
      this->_padding_ = 9;
    }
    break;
  case 9:
    bVar3 = UnitTask::AbleToHit((UnitTask *)this);
    *(bool *)&this->_padding_ = bVar3;
    pGVar4 = GameObjectHandle::GetObj(this->fleeFrom);
    this->_padding_ = (int)pGVar4;
    if (pGVar4 != (GameObject *)0x0) {
      pfVar11 = (float *)(**(code **)(pGVar4->_padding_ + 0xc))();
      pfVar12 = (float *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
      if ((pfVar12[2] - pfVar11[2]) * (pfVar12[2] - pfVar11[2]) +
          (*pfVar12 - *pfVar11) * (*pfVar12 - *pfVar11) <= 5625.0) {
        bVar3 = UnitTask::IsStuck((UnitTask *)this);
        if (!bVar3) {
          UnitTask::DoFlee((UnitTask *)this);
          fVar14 = Get_Time();
          fVar15 = (float)this->_padding_ + 3.0;
          bVar13 = fVar15 < fVar14 |
                   (byte)((ushort)((ushort)(NAN(fVar15) || NAN(fVar14)) << 10) >> 8);
LAB_0040f57f:
          if ((POPCOUNT(bVar13) & 1U) == 0) break;
        }
        goto LAB_0040f59d;
      }
    }
LAB_0040f54e:
    this->_padding_ = 7;
    break;
  case 10:
    bVar3 = UnitTask::AbleToHit((UnitTask *)this);
    iVar7 = this->_padding_;
    *(bool *)&this->_padding_ = bVar3;
    if ((float)this->_padding_ < *(float *)(iVar7 + 0x1e0)) goto LAB_0040f498;
    if (bVar3) goto LAB_0040f326;
    p_Var6 = (_OBJ76 *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0x30))();
    iVar7 = IsBuilding(p_Var6);
    iVar7 = (-(uint)(iVar7 != 0) & 0xfffffffb) + 7;
LAB_0040f441:
    this->_padding_ = iVar7;
    break;
  case 0xb:
    pfVar11 = (float *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
    fVar15 = *pfVar11 - (float)this->_padding_;
    fVar14 = pfVar11[2] - (float)this->_padding_;
    if (this->waitRangeSq <= fVar14 * fVar14 + fVar15 * fVar15) {
      bVar3 = UnitTask::IsStuck((UnitTask *)this);
      if (bVar3) goto LAB_0040f7e1;
      pfVar11 = (float *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
      fVar15 = *pfVar11 - (float)this->_padding_;
      fVar14 = pfVar11[2] - (float)this->_padding_;
      if (fVar14 * fVar14 + fVar15 * fVar15 <= 10000.0) goto LAB_0040f72e;
      this->_padding_ = 0xb;
    }
    else {
      this->_padding_ = 6;
    }
    break;
  case 0xc:
    bVar3 = CheckFollowing(this);
    if (!bVar3) {
      pfVar11 = (float *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
      pfVar12 = (float *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
      if (2500.0 <= (pfVar12[2] - pfVar11[2]) * (pfVar12[2] - pfVar11[2]) +
                    (*pfVar12 - *pfVar11) * (*pfVar12 - *pfVar11)) {
        pfVar11 = (float *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
        fVar15 = *pfVar11 - (float)this->_padding_;
        fVar14 = pfVar11[2] - (float)this->_padding_;
        if (fVar14 * fVar14 + fVar15 * fVar15 <= 10000.0) {
          bVar3 = UnitTask::IsStuck((UnitTask *)this);
          if (bVar3) goto LAB_0040f7e1;
          pfVar11 = (float *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
          fVar15 = *pfVar11 - (float)this->_padding_;
          fVar14 = pfVar11[2] - (float)this->_padding_;
          if (225.0 <= fVar14 * fVar14 + fVar15 * fVar15) {
            UnitTask::DoGoto((UnitTask *)this);
            if (*(float *)(iVar1 + 0xd0) == 1.0) {
              *(undefined4 *)(iVar1 + 0xd4) = 1;
            }
            else {
              *(undefined4 *)(iVar1 + 0xd4) = 0;
            }
            break;
          }
        }
        this->_padding_ = 0xc;
      }
      else {
        this->_padding_ = 4;
      }
    }
  }
  if ((char)this->_padding_ == '\0') {
    bVar3 = false;
    goto LAB_0040f8f3;
  }
  bVar3 = MayHitFriends((GameObject *)this->_padding_,(float)this->_padding_,0.3,1.0);
  pAVar10 = AttackGroup::GetLeft((AttackGroup *)this->_padding_,(GameObject *)this->_padding_);
  if (pAVar10 == (AttackerInfo *)0x0) {
LAB_0040f8c4:
    if (bVar3) {
      fVar15 = Min(*(float *)(iVar1 + 0xcc) + 0.25,1.0);
      goto LAB_0040f8e3;
    }
  }
  else {
    pfVar11 = (float *)(**(code **)(pAVar10->attacker->_padding_ + 0xc))();
    pfVar12 = (float *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
    if (25.0 <= (pfVar12[2] - pfVar11[2]) * (pfVar12[2] - pfVar11[2]) +
                (*pfVar12 - *pfVar11) * (*pfVar12 - *pfVar11)) goto LAB_0040f8c4;
    fVar15 = 1.0;
LAB_0040f8e3:
    *(float *)(iVar1 + 0xcc) = fVar15;
  }
  bVar3 = !bVar3;
LAB_0040f8f3:
  UnitTask::UpdateWeapon((UnitTask *)this,bVar3);
  UnitTask::UpdateSpecial((UnitTask *)this);
  return;
}
