/*
 * Entry: 00486b48
 * Name: Craft::ControlHeading
 * Namespace: Craft
 * Signature: void ControlHeading(Craft * this, VECTOR_2D param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Craft::ControlHeading(Craft *this,VECTOR_2D param_1)

{
  VECTOR_2D VVar1;
  VECTOR_2D VVar2;
  float fVar3;
  float local_c;
  float local_8;
  
  VVar1.z = *(float *)(this->_padding_ + 0x40);
  VVar1.x = *(float *)(this->_padding_ + 0x38);
  VVar1 = Vec2D_Normalize(VVar1);
  VVar2 = Vec2D_Normalize(param_1);
  local_8 = VVar1.z;
  local_c = VVar1.x;
  param_1.z = VVar2.z;
  param_1.x = VVar2.x;
  fVar3 = local_c * param_1.z - param_1.x * local_8;
  if (local_8 * param_1.z + param_1.x * local_c <= 0.0) {
    if (0.0 <= fVar3) {
      fVar3 = 1.0;
    }
    else {
      fVar3 = -1.0;
    }
  }
  else {
    fVar3 = Clamp(fVar3 * 3.0 - (float)this->_padding_ * 0.5,-1.0,1.0);
  }
  (this->vhcl->control).steer = fVar3;
  return;
}
