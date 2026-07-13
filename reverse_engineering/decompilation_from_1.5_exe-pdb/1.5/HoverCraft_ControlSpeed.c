
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall HoverCraft::ControlSpeed(HoverCraft *this,float param_1)

{
  int iVar1;
  float fVar2;
  
  if (this->hi != (HoverInterface *)0x0) {
    this->hi->desiredSpeed = param_1;
  }
  iVar1 = this->_padding_;
  fVar2 = Clamp((param_1 -
                ((float)this->_padding_ * *(float *)(iVar1 + 0x38) +
                (float)this->_padding_ * *(float *)(iVar1 + 0x40) +
                (float)this->_padding_ * *(float *)(iVar1 + 0x3c))) * ___real_3e4ccccd,
                ___real_bf800000,1.0);
  *(float *)(this->_padding_ + 0xd0) = fVar2;
  *(undefined4 *)(this->_padding_ + 0xcc) = 0;
  return;
}


