/*
 * Entry: 004134d9
 * Name: GotoGeyser::DoStateProlog
 * Namespace: GotoGeyser
 * Signature: bool DoStateProlog(GotoGeyser * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall GotoGeyser::DoStateProlog(GotoGeyser *this)

{
  float fVar1;
  GotoGeyser *pGVar2;
  bool bVar3;
  Geizer *pGVar4;
  GameObject *pGVar5;
  float *pfVar6;
  float *pfVar7;
  VECTOR_3D *pVVar8;
  int iVar9;
  int *piVar10;
  AiPath *pAVar11;
  Craft *unaff_ESI;
  int unaff_EDI;
  VECTOR_3D local_4c;
  float local_40;
  float local_3c;
  float local_38;
  VECTOR_3D local_34;
  float local_28;
  float local_24;
  float local_20;
  Geizer *local_1c;
  float local_18;
  float local_14;
  float local_10;
  GotoGeyser *local_c;
  Geizer *local_8;
  
  if (this->_padding_ == 0xd) {
    return false;
  }
  local_c = this;
  pGVar4 = (Geizer *)GameObjectHandle::GetObj(this->_padding_);
  local_1c = (Geizer *)0x0;
  local_8 = pGVar4;
  if (pGVar4 == (Geizer *)0x0) {
LAB_00413786:
    if (this->oneGeyser == 0) {
      pGVar4 = local_1c;
      pVVar8 = (VECTOR_3D *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
      pGVar4 = GetNearestGeizer(pVVar8,pGVar4);
      if (pGVar4 != (Geizer *)0x0) {
        iVar9 = GameObject::GetHandle((GameObject *)pGVar4);
        this->_padding_ = iVar9;
        AiPath::Release((AiPath *)this->_padding_);
        this->_padding_ = 0;
        this->_padding_ = 1;
        this->_padding_ = 1;
        piVar10 = (int *)(**(code **)(pGVar4->_padding_ + 0xc))();
        local_1c = (Geizer *)&this->_padding_;
        *(int *)local_1c = *piVar10;
        this->_padding_ = piVar10[1];
        this->_padding_ = piVar10[2];
        pAVar11 = operator_new(0x1c);
        pGVar2 = local_c;
        if (pAVar11 == (AiPath *)0x0) {
          pAVar11 = (AiPath *)0x0;
        }
        else {
          pGVar4 = local_1c;
          pVVar8 = (VECTOR_3D *)(**(code **)(*(int *)(local_c->_padding_ + 0x20) + 0xc))();
          pAVar11 = AiPath::AiPath(pAVar11,pVVar8,(VECTOR_3D *)pGVar4);
        }
        pGVar2->_padding_ = 0;
        pGVar2->_padding_ = (int)pAVar11;
        *(undefined1 *)&pGVar2->_padding_ = 1;
        return false;
      }
      Say((Craft *)this->_padding_,ATTACK_MSG,0);
    }
    this->_padding_ = 0xd;
    return false;
  }
  bVar3 = BetterMatch((Geizer *)0x1,unaff_EDI,unaff_ESI);
  if (((bVar3) || (bVar3 = BetterMatch((Geizer *)0x2,unaff_EDI,unaff_ESI), bVar3)) ||
     (bVar3 = BetterMatch((Geizer *)0x3,unaff_EDI,unaff_ESI), bVar3)) {
    pGVar4 = (Geizer *)0x0;
    local_1c = local_8;
    local_8 = (Geizer *)0x0;
  }
  if ((pGVar4 == (Geizer *)0x0) || (pGVar4->isLocked != false)) goto LAB_00413786;
  this->_padding_ = (int)pGVar4;
  pGVar5 = AvoidObject((GameObject *)this->_padding_,(GameObject *)pGVar4);
  this->_padding_ = (int)pGVar5;
  if (pGVar5 == (GameObject *)0x0) {
LAB_0041365f:
    this->blocked = false;
  }
  else {
    pfVar6 = (float *)(**(code **)(pGVar5->_padding_ + 0xc))();
    pfVar7 = (float *)(**(code **)(pGVar4->_padding_ + 0xc))();
    local_14 = *pfVar7 - *pfVar6;
    local_10 = pfVar7[2] - pfVar6[2];
    pfVar6 = (float *)(**(code **)(pGVar4->_padding_ + 0xc))();
    pfVar7 = (float *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
    local_1c = (Geizer *)(*pfVar7 - *pfVar6);
    local_18 = pfVar7[2] - pfVar6[2];
    pfVar6 = (float *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
    pfVar7 = (float *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
    fVar1 = (pfVar7[2] - pfVar6[2]) * (pfVar7[2] - pfVar6[2]) +
            (*pfVar7 - *pfVar6) * (*pfVar7 - *pfVar6);
    if (((900.0 <= local_14 * local_14 + local_10 * local_10) ||
        ((float)local_1c * (float)local_1c + local_18 * local_18 <= fVar1)) || (900.0 <= fVar1))
    goto LAB_0041365f;
    if (this->blocked != false) goto LAB_00413778;
    this->blocked = true;
    Say((Craft *)this->_padding_,BLOCKED_MSG,0);
  }
  if (((this->blocked == false) && (this->_padding_ != 0)) &&
     (this->_padding_ == *(int *)(this->_padding_ + 4) + -1)) {
    pfVar6 = (float *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
    local_40 = *pfVar6;
    local_3c = pfVar6[1];
    local_38 = pfVar6[2];
    pfVar6 = (float *)(**(code **)(local_8->_padding_ + 0xc))();
    pGVar2 = local_c;
    local_34.x = *pfVar6;
    local_34.y = pfVar6[1];
    local_34.z = pfVar6[2];
    local_4c.x = local_34.x - local_40;
    local_4c.y = local_34.y - local_3c;
    local_4c.z = local_34.z - local_38;
    fVar1 = local_4c.x * local_4c.x + local_4c.z * local_4c.z;
    local_28 = local_4c.x;
    local_24 = local_4c.y;
    local_20 = local_4c.z;
    if (9.0 <= fVar1) {
      this = local_c;
      if (64.0 <= fVar1) goto LAB_00413778;
    }
    else if (((float)((Producer *)local_c->_padding_)->_padding_ < 0.5) &&
            (bVar3 = Producer::HasPower((Producer *)local_c->_padding_), bVar3)) {
      pGVar2->_padding_ = 0xd;
      return false;
    }
    pGVar2->_padding_ = 0x3da3d70a;
    pGVar2->_padding_ = 0x3dcccccd;
    local_40 = 0.0;
    local_3c = 0.0;
    local_38 = 1.0;
    local_34.x = 0.0;
    local_34.y = 0.0;
    local_34.z = 1.0;
    UnitTask::LookInLocalDir((UnitTask *)pGVar2,&local_34);
    UnitTask::ApplyForce((UnitTask *)pGVar2,&local_4c);
    return false;
  }
LAB_00413778:
  this->_padding_ = 0;
  return true;
}
