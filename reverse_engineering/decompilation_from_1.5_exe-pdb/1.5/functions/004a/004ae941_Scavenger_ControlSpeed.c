/*
 * Entry: 004ae941
 * Name: Scavenger::ControlSpeed
 * Namespace: Scavenger
 * Signature: void ControlSpeed(Scavenger * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Scavenger::ControlSpeed(Scavenger *this,float param_1)

{
  int iVar1;
  float fVar2;
  
  iVar1 = this->_padding_;
  if ((*(uint *)(iVar1 + 0x14) & 0x200) == 0) {
    fVar2 = Clamp((param_1 -
                  (*(float *)(iVar1 + 0x40) * (float)this->_padding_ +
                   (float)this->_padding_ * *(float *)(iVar1 + 0x3c) +
                  (float)this->_padding_ * *(float *)(iVar1 + 0x38))) * 0.09,-1.0,1.0);
    *(float *)(this->_padding_ + 0xd0) = fVar2;
    *(undefined4 *)(this->_padding_ + 0xcc) = 0;
  }
  return;
}
