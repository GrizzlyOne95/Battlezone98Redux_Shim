/*
 * Entry: 004a5617
 * Name: Person::ControlHeading
 * Namespace: Person
 * Signature: void ControlHeading(Person * this, VECTOR_2D param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Person::ControlHeading(Person *this,VECTOR_2D param_1)

{
  VECTOR_2D VVar1;
  float fVar2;
  
  VVar1 = Vec2D_Normalize(param_1);
  fVar2 = Clamp((*(float *)(this->_padding_ + 0x28) * VVar1.z +
                *(float *)(this->_padding_ + 0x20) * VVar1.x) * -5.0,-1.0,1.0);
  *(float *)(this->_padding_ + 0xc4) = fVar2;
  fVar2 = Clamp((*(float *)(this->_padding_ + 0x38) * VVar1.x +
                *(float *)(this->_padding_ + 0x40) * VVar1.z) * 5.0,-1.0,1.0);
  *(float *)(this->_padding_ + 0xd0) = fVar2;
  return;
}
