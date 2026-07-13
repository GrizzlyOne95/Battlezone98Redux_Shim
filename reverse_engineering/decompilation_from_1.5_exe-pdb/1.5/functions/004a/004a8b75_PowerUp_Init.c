/*
 * Entry: 004a8b75
 * Name: PowerUp::Init
 * Namespace: PowerUp
 * Signature: void Init(PowerUp * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PowerUp::Init(PowerUp *this,int param_1)

{
  int iVar1;
  Team *this_00;
  int iVar2;
  
  *(uint *)(this->_padding_ + 0x14) =
       *(uint *)(this->_padding_ + 0x14) & 0xfff0ffff | param_1 << 0x10;
  this->_padding_ = param_1;
  this_00 = Team::GetTeam(param_1);
  this->_padding_ = (int)this_00;
  if ((this == (PowerUp *)GameObject::userObject) || ((char)this->_padding_ != '\0')) {
    this->_padding_ = 0;
  }
  else {
    iVar2 = *(int *)(this->_padding_ + 0x144);
    if ((iVar2 < 0) || (iVar1 = *(int *)(this->_padding_ + 0x148), iVar1 < 0)) {
      this->_padding_ = -1;
    }
    else {
      iVar2 = Team::FirstEmptySlot(this_00,iVar2,iVar1);
      this->_padding_ = iVar2;
    }
  }
  if (((Team *)this->_padding_ != (Team *)0x0) && (this->_padding_ != -1)) {
    Team::SetSlot((Team *)this->_padding_,this->_padding_,(GameObject *)this);
  }
  GameObject::AssignColor((GameObject *)this);
  (**(code **)(this->_padding_ + 0x58))();
  this->_padding_ = 0;
  return;
}
