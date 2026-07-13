/*
 * Entry: 004ae8ad
 * Name: Scavenger::ControlHeading
 * Namespace: Scavenger
 * Signature: void ControlHeading(Scavenger * this, VECTOR_2D param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Scavenger::ControlHeading(Scavenger *this,VECTOR_2D param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  
  fVar3 = *(float *)(this->_padding_ + 0x38);
  fVar1 = *(float *)(this->_padding_ + 0x40);
  fVar2 = fVar3 * param_1.z - fVar1 * param_1.x;
  if (fVar3 * param_1.x + fVar1 * param_1.z <= 0.0) {
    if (0.0 <= fVar2) {
      fVar3 = 1.0;
    }
    else {
      fVar3 = -1.0;
    }
  }
  else {
    fVar3 = Clamp(fVar2 * 3.0 - (float)this->_padding_ * 0.5,-1.0,1.0);
  }
  *(float *)(this->_padding_ + 0xc4) = fVar3;
  return;
}
