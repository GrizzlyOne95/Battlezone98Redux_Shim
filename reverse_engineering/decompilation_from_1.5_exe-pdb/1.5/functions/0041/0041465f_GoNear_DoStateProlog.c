/*
 * Entry: 0041465f
 * Name: GoNear::DoStateProlog
 * Namespace: GoNear
 * Signature: bool DoStateProlog(GoNear * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall GoNear::DoStateProlog(GoNear *this)

{
  char cVar1;
  GameObject *pGVar2;
  float *pfVar3;
  float *pfVar4;
  float fVar5;
  
  pGVar2 = GameObjectHandle::GetObj(this->_padding_);
  this->_padding_ = (int)pGVar2;
  if (pGVar2 == (GameObject *)0x0) {
    this->_padding_ = 0xd;
    return false;
  }
  pfVar3 = (float *)(**(code **)(pGVar2->_padding_ + 0xc))();
  pfVar4 = (float *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
  fVar5 = (pfVar4[2] - pfVar3[2]) * (pfVar4[2] - pfVar3[2]) +
          (*pfVar4 - *pfVar3) * (*pfVar4 - *pfVar3);
  this->destDistSq = fVar5;
  if (fVar5 < this->nearSq) {
    if (this->wasNear == false) {
      fVar5 = Get_Time();
      this->nearTime = fVar5;
      this->wasNear = true;
    }
    this->_padding_ = 0;
    cVar1 = (**(code **)(this->_padding_ + 0x38))();
    if (cVar1 == '\0') {
      return false;
    }
  }
  this->_padding_ = this->_padding_;
  pGVar2 = AvoidObject((GameObject *)this->_padding_,(GameObject *)this->_padding_);
  this->_padding_ = (int)pGVar2;
  return true;
}
