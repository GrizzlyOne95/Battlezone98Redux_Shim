
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool __thiscall HoverCraft::ControlForward(HoverCraft *this)

{
  int iVar1;
  
  iVar1 = this->_padding_;
  if ((float)this->_padding_ * *(float *)(iVar1 + 0x38) +
      (float)this->_padding_ * *(float *)(iVar1 + 0x40) +
      (float)this->_padding_ * *(float *)(iVar1 + 0x3c) < ___real_bdcccccd) {
    *(undefined4 *)(this->_padding_ + 0xd0) = 0x3f800000;
    *(undefined4 *)(this->_padding_ + 0xc4) = 0;
    return true;
  }
  return false;
}


