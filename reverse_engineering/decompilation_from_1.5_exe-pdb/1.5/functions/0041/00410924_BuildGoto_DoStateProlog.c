/*
 * Entry: 00410924
 * Name: BuildGoto::DoStateProlog
 * Namespace: BuildGoto
 * Signature: bool DoStateProlog(BuildGoto * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall BuildGoto::DoStateProlog(BuildGoto *this)

{
  int iVar1;
  Producer *this_00;
  int iVar2;
  float fVar3;
  float fVar4;
  bool bVar5;
  char cVar6;
  float *pfVar7;
  GameObject *pGVar8;
  
  if (this->_padding_ == 0xd) {
    return false;
  }
  iVar1 = this->buildStage;
  this->_padding_ = 0;
  this->_padding_ = 0;
  this_00 = (Producer *)this->_padding_;
  if (iVar1 == 0) {
    cVar6 = (**(code **)(this_00->_padding_ + 0x68))();
    if (cVar6 != '\0') {
      this->buildStage = 1;
    }
LAB_00410a26:
    UnitTask::DoSit((UnitTask *)this);
LAB_00410a2d:
    bVar5 = false;
  }
  else {
    if (iVar1 == 1) {
      iVar1 = *(int *)(this->_padding_ + 8);
      iVar2 = *(int *)(this->_padding_ + 4);
      fVar3 = *(float *)(iVar1 + -8 + iVar2 * 8);
      fVar4 = *(float *)(iVar1 + -4 + iVar2 * 8);
      pfVar7 = (float *)(**(code **)(this_00->_padding_ + 0xc))();
      fVar3 = fVar3 - *pfVar7;
      fVar4 = fVar4 - pfVar7[2];
      if (fVar4 * fVar4 + fVar3 * fVar3 < this->buildDistSq) {
        (**(code **)(this_00->_padding_ + 0x5c))();
        this->buildStage = 2;
        goto LAB_00410a2d;
      }
      pGVar8 = AvoidObject((GameObject *)this->_padding_,(GameObject *)0x0);
      this->_padding_ = (int)pGVar8;
    }
    else {
      if (iVar1 == 2) {
        cVar6 = (**(code **)(this_00->_padding_ + 100))();
        if (cVar6 != '\0') {
          this->buildStage = 3;
        }
        goto LAB_00410a2d;
      }
      if (iVar1 == 3) {
        bVar5 = Producer::IsBusy(this_00);
        if (!bVar5) {
          (**(code **)(this_00->_padding_ + 0x60))();
          this->_padding_ = 0xd;
        }
        goto LAB_00410a26;
      }
    }
    bVar5 = true;
  }
  return bVar5;
}
