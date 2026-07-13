/*
 * Entry: 004140a1
 * Name: GotoTask::DoState
 * Namespace: GotoTask
 * Signature: void DoState(GotoTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GotoTask::DoState(GotoTask *this)

{
  int *piVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  VECTOR_2D *pVVar5;
  char cVar6;
  bool bVar7;
  GameObject *pGVar8;
  float *pfVar9;
  VECTOR_3D *pVVar10;
  float *pfVar11;
  SPHERE *pSVar12;
  AiPath *pAVar13;
  VECTOR_3D *pVVar14;
  int iVar15;
  _OBJ76 *p_Var16;
  _OBJ76 *p_Var17;
  float fVar18;
  float fVar19;
  float local_10;
  float local_8;
  
  cVar6 = (**(code **)(this->_padding_ + 0x34))();
  if (cVar6 == '\0') {
    return;
  }
  if (this->_padding_ == 0) {
LAB_004142ec:
    iVar15 = this->_padding_;
    if (iVar15 != 1) {
      if (iVar15 == 2) {
        if (this->_padding_ < *(int *)(this->_padding_ + 4) + -1) goto LAB_004144cf;
        pfVar9 = (float *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
        fVar18 = *pfVar9 - (float)this->_padding_;
        fVar2 = pfVar9[2] - (float)this->_padding_;
        fVar18 = fVar2 * fVar2 + fVar18 * fVar18;
        local_8 = 5.0;
        if ((this->_padding_ != 0) && (5.0 < *(float *)(this->_padding_ + 0x158))) {
          iVar15 = (*(code *)**(undefined4 **)(this->_padding_ + 0x20))();
          if ((*(int *)(iVar15 + 0x28) != 3) && (*(int *)(iVar15 + 0x28) != 7)) {
            local_8 = *(float *)(this->_padding_ + 0x158);
          }
        }
        fVar2 = (local_8 + 5.0) * (local_8 + 5.0);
        local_8 = local_8 * local_8;
        if (this->exact == false) {
          fVar2 = fVar2 + fVar2;
          local_8 = local_8 * 6.0;
        }
        if (fVar18 < fVar2) {
          pVVar10 = (VECTOR_3D *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
          bVar7 = OnBlocked(pVVar10);
          if (!bVar7) {
            UnitTask::CleanStuck((UnitTask *)this);
          }
        }
        if (local_8 <= fVar18) {
          if ((*(int *)(*(int *)(this->_padding_ + 0x228) + 0x4c) == 0) ||
             (pGVar8 = GameObjectHandle::GetObj(this->_padding_), pGVar8 == (GameObject *)0x0)) {
LAB_004144cf:
            bVar7 = UnitTask::IsStuck((UnitTask *)this);
            if (bVar7) {
              this->_padding_ = 3;
              return;
            }
            UnitTask::DoGoto((UnitTask *)this);
            return;
          }
          pGVar8 = GameObjectHandle::GetObj(this->_padding_);
          p_Var16 = obj_get_root(*(_OBJ76 **)(*(int *)(this->_padding_ + 0x228) + 0x50));
          p_Var17 = (_OBJ76 *)(**(code **)(pGVar8->_padding_ + 0x30))();
          if (p_Var16 != p_Var17) goto LAB_004144cf;
        }
        pAVar13 = this->path;
        if (this->pathPoint < pAVar13->pointCount + -1) {
          iVar15 = this->pathPoint + 1;
          this->pathPoint = iVar15;
          this->_padding_ = 2;
          local_10 = pAVar13->points[iVar15].x;
          fVar18 = pAVar13->points[iVar15].z;
        }
        else {
          if (pAVar13->pathType != LOOP_PATH) {
            if (this->skipdone != false) {
              return;
            }
            this->_padding_ = 0xd;
            return;
          }
          this->pathPoint = 0;
          this->_padding_ = 2;
          local_10 = pAVar13->points->x;
          fVar18 = pAVar13->points->z;
        }
        goto LAB_004144ad;
      }
      if (iVar15 == 3) {
        UnitTask::DoStuck((UnitTask *)this);
        return;
      }
      if (iVar15 != 6) {
        return;
      }
    }
    UnitTask::DoSit((UnitTask *)this);
  }
  else {
    pGVar8 = GameObjectHandle::GetObj(this->_padding_);
    if (pGVar8 == (GameObject *)0x0) {
      this->_padding_ = 0;
      this->_padding_ = 0xd;
      return;
    }
    pfVar9 = (float *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
    piVar1 = &pGVar8->_padding_;
    pVVar10 = (VECTOR_3D *)(**(code **)(*piVar1 + 0xc))();
    if (((pGVar8->euler).v_mag <= 0.1) ||
       (fVar18 = pVVar10->x - (this->destPoint).x, fVar2 = pVVar10->z - (this->destPoint).z,
       fVar2 * fVar2 + fVar18 * fVar18 <= 1600.0)) {
      if ((this->_padding_ != 0) &&
         ((((this->_padding_ == *(int *)(this->_padding_ + 4) + -1 &&
            (bVar7 = OnBlocked(pVVar10), !bVar7)) &&
           (bVar7 = PlanPossible(*pfVar9,pfVar9[2],pVVar10->x,pVVar10->z), bVar7)) &&
          (fVar18 = *pfVar9 - (float)this->_padding_, fVar2 = pfVar9[2] - (float)this->_padding_,
          fVar2 * fVar2 + fVar18 * fVar18 < 25.0)))) {
        pfVar9 = (float *)(**(code **)(*piVar1 + 0xc))();
        pfVar11 = (float *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
        fVar18 = *pfVar11;
        fVar2 = *pfVar9;
        fVar3 = pfVar11[2];
        fVar4 = pfVar9[2];
        pSVar12 = GameObject::GetSphere(pGVar8);
        fVar19 = Max(pGVar8->collisionRadius,pSVar12->radius);
        fVar19 = fVar19 + *(float *)(this->_padding_ + 0x158) + 5.0;
        if (fVar19 * fVar19 <=
            (fVar18 - fVar2) * (fVar18 - fVar2) + (fVar3 - fVar4) * (fVar3 - fVar4))
        goto LAB_00414233;
      }
      goto LAB_004142ec;
    }
LAB_00414233:
    pAVar13 = (AiPath *)this->_padding_;
    if (pAVar13 != (AiPath *)0x0) {
      AiPath::~AiPath(pAVar13);
      operator_delete(pAVar13);
      this->_padding_ = 0;
    }
    if (this->release != false) {
      pAVar13 = this->path;
      if (pAVar13 != (AiPath *)0x0) {
        AiPath::Release(pAVar13);
        this->path = (AiPath *)0x0;
      }
    }
    this->_padding_ = 2;
    pfVar9 = (float *)(**(code **)(*piVar1 + 0xc))();
    (this->destPoint).x = *pfVar9;
    (this->destPoint).y = pfVar9[1];
    (this->destPoint).z = pfVar9[2];
    pAVar13 = operator_new(0x1c);
    if (pAVar13 == (AiPath *)0x0) {
      pAVar13 = (AiPath *)0x0;
    }
    else {
      pVVar10 = &this->destPoint;
      pVVar14 = (VECTOR_3D *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
      pAVar13 = AiPath::AiPath(pAVar13,pVVar14,pVVar10);
    }
    this->pathPoint = 0;
    this->path = pAVar13;
    this->release = true;
    UnitTask::CleanStuck((UnitTask *)this);
    ChoosePathPoint(this);
    pVVar5 = this->path->points;
    iVar15 = this->pathPoint;
    local_10 = pVVar5[iVar15].x;
    fVar18 = pVVar5[iVar15].z;
LAB_004144ad:
    this->_padding_ = (int)local_10;
    this->_padding_ = 0;
    this->_padding_ = (int)fVar18;
  }
  return;
}
