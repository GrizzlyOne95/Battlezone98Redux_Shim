/*
 * Entry: 0040dc46
 * Name: ArtilleryProcess::ShouldAttack
 * Namespace: ArtilleryProcess
 * Signature: bool ShouldAttack(ArtilleryProcess * this, State param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall ArtilleryProcess::ShouldAttack(ArtilleryProcess *this,State param_1)

{
  char cVar1;
  float *pfVar2;
  float *pfVar3;
  
  cVar1 = (**(code **)(*(int *)this->_padding_ + 100))();
  if ((cVar1 != '\0') && (param_1 != ATTACK)) {
    pfVar2 = (float *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
    pfVar3 = (float *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
    if ((pfVar3[2] - pfVar2[2]) * (pfVar3[2] - pfVar2[2]) +
        (*pfVar3 - *pfVar2) * (*pfVar3 - *pfVar2) < (float)this->_padding_) {
      return true;
    }
  }
  return false;
}
