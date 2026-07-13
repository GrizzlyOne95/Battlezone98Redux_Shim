/*
 * Entry: 00414742
 * Name: GoPoints::DoStateProlog
 * Namespace: GoPoints
 * Signature: bool DoStateProlog(GoPoints * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall GoPoints::DoStateProlog(GoPoints *this)

{
  int *piVar1;
  float fVar2;
  float fVar3;
  char cVar4;
  AiPath *pAVar5;
  VECTOR_3D *pVVar6;
  float *pfVar7;
  int iVar8;
  int iVar9;
  GameObject *pGVar10;
  int iVar11;
  VECTOR_3D *pVVar12;
  VECTOR_3D local_14;
  
  if (this->_padding_ == 6) {
    if (((char)this->_padding_ != '\0') && ((AiPath *)this->_padding_ != (AiPath *)0x0)) {
      AiPath::Release((AiPath *)this->_padding_);
    }
    this->_padding_ = 0;
    cVar4 = (**(code **)(this->_padding_ + 0x38))(&local_14);
    if (cVar4 == '\0') {
      this->_padding_ = 0xd;
      return false;
    }
    pAVar5 = operator_new(0x1c);
    if (pAVar5 == (AiPath *)0x0) {
      pAVar5 = (AiPath *)0x0;
    }
    else {
      pVVar12 = &local_14;
      pVVar6 = (VECTOR_3D *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
      pAVar5 = AiPath::AiPath(pAVar5,pVVar6,pVVar12);
    }
    this->_padding_ = (int)pAVar5;
    if (*(int *)(this->_padding_ + 0x22c) == 0) {
      piVar1 = (int *)(this->_padding_ + 0x20);
      pfVar7 = (float *)(**(code **)(*piVar1 + 0xc))();
      iVar8 = (**(code **)(*piVar1 + 4))();
      iVar11 = 1;
      iVar9 = (**(code **)(*piVar1 + 0xc))();
      pAVar5 = FindPlan(*pfVar7,*(float *)(iVar9 + 8),local_14.x,local_14.z,iVar11,iVar8);
      this->_padding_ = (int)pAVar5;
    }
    *(undefined1 *)&this->_padding_ = 1;
    this->_padding_ = 1;
  }
  else if ((((AiPath *)this->_padding_ == (AiPath *)0x0) ||
           ((AiPath *)this->_padding_ == this->lastPlan)) ||
          (cVar4 = (**(code **)(this->_padding_ + 0x40))(), cVar4 != '\0')) {
    this->lastPlan = (AiPath *)this->_padding_;
    pfVar7 = (float *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
    fVar2 = *pfVar7 - (float)this->_padding_;
    fVar3 = pfVar7[2] - (float)this->_padding_;
    if (25.0 <= fVar3 * fVar3 + fVar2 * fVar2) {
      pGVar10 = AvoidObject((GameObject *)this->_padding_,(GameObject *)0x0);
      this->_padding_ = (int)pGVar10;
    }
    else {
      cVar4 = (**(code **)(this->_padding_ + 0x3c))();
      if (cVar4 == '\0') {
        UnitTask::DoSit((UnitTask *)this);
        return false;
      }
      this->_padding_ = 6;
      this->_padding_ = 0;
    }
  }
  else {
    this->_padding_ = 6;
  }
  return true;
}
