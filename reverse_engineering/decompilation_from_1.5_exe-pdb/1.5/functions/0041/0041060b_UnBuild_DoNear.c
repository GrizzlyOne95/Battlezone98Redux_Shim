/*
 * Entry: 0041060b
 * Name: UnBuild::DoNear
 * Namespace: UnBuild
 * Signature: bool DoNear(UnBuild * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall UnBuild::DoNear(UnBuild *this)

{
  char cVar1;
  float fVar2;
  
  cVar1 = (**(code **)(*(int *)this->_padding_ + 0x68))();
  if (cVar1 == '\0') {
    cVar1 = (**(code **)(*(int *)this->_padding_ + 100))();
    if (cVar1 != '\0') {
      if (this->unbuildStage == 0) {
        ConstructionRig::StartUnbuild
                  ((ConstructionRig *)this->_padding_,(GameObject *)this->_padding_);
        this->unbuildStage = 1;
      }
      if (this->unbuildStage == 1) {
        fVar2 = TimeStep();
        ConstructionRig::UpdateUnbuild((ConstructionRig *)this->_padding_,fVar2);
        if (((int *)this->_padding_)[0xd8] == 0) {
          this->unbuildStage = 2;
          (**(code **)(*(int *)this->_padding_ + 0x60))();
          this->_padding_ = 0xd;
        }
      }
    }
  }
  else {
    (**(code **)(*(int *)this->_padding_ + 0x5c))();
    fVar2 = (float)this->_padding_;
    this->_padding_ = (int)(fVar2 + fVar2);
  }
  return false;
}
