/*
 * Entry: 004a55c1
 * Name: Person::ControlSpeed
 * Namespace: Person
 * Signature: void ControlSpeed(Person * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Person::ControlSpeed(Person *this,float param_1)

{
  float fVar1;
  
  if (param_1 <= 0.0) {
    fVar1 = *(float *)(this->_padding_ + 0x34c);
  }
  else {
    fVar1 = *(float *)(this->_padding_ + 0x348);
  }
  fVar1 = Clamp(param_1 / fVar1,-1.0,1.0);
  *(float *)(this->_padding_ + 0xd0) = fVar1;
  return;
}
