/*
 * Entry: 00415666
 * Name: HuntTask::Hunt_New_Spot
 * Namespace: HuntTask
 * Signature: int Hunt_New_Spot(HuntTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall HuntTask::Hunt_New_Spot(HuntTask *this)

{
  int *piVar1;
  int iVar2;
  AiPath *pAVar3;
  VECTOR_3D *pVVar4;
  int iVar5;
  float *pfVar6;
  float *pfVar7;
  float fVar8;
  VECTOR_3D *pVVar9;
  VECTOR_3D local_10;
  
  piVar1 = &this->total_tries;
  iVar5 = 5;
  if (*piVar1 < 5) {
    fVar8 = Get_Time();
    this->time_of_Mth_last_try[*piVar1] = fVar8;
    *piVar1 = *piVar1 + 1;
  }
  else {
    pfVar6 = this->time_of_Mth_last_try;
    pfVar7 = this->time_of_Mth_last_try;
    for (; pfVar6 = pfVar6 + 1, iVar5 != 0; iVar5 = iVar5 + -1) {
      *pfVar7 = *pfVar6;
      pfVar7 = pfVar7 + 1;
    }
    fVar8 = Get_Time();
    this->time_of_Mth_last_try[4] = fVar8;
  }
  if ((char)this->_padding_ != '\0') {
    pAVar3 = (AiPath *)this->_padding_;
    if (pAVar3 != (AiPath *)0x0) {
      AiPath::Release(pAVar3);
      this->_padding_ = 0;
    }
  }
  iVar2 = Choose_Next_Spot(this,&local_10);
  iVar5 = 0;
  if (iVar2 != 0) {
    pAVar3 = operator_new(0x1c);
    if (pAVar3 == (AiPath *)0x0) {
      pAVar3 = (AiPath *)0x0;
    }
    else {
      pVVar9 = &local_10;
      pVVar4 = (VECTOR_3D *)(**(code **)(this->my_craft->_padding_ + 0xc))();
      pAVar3 = AiPath::AiPath(pAVar3,pVVar4,pVVar9);
    }
    this->_padding_ = (int)pAVar3;
    iVar5 = 1;
    this->_padding_ = 0;
    *(undefined1 *)&this->_padding_ = 1;
    this->_padding_ = 1;
    this->_padding_ = 1;
  }
  return iVar5;
}
