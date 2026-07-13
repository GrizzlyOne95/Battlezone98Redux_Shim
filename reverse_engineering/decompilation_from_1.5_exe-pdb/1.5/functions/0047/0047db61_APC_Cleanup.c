/*
 * Entry: 0047db61
 * Name: APC::Cleanup
 * Namespace: APC
 * Signature: void Cleanup(APC * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall APC::Cleanup(APC *this)

{
  int iVar1;
  
  if (((Team *)this->_padding_ != (Team *)0x0) && (this->_padding_ != -1)) {
    Team::SetSlot((Team *)this->_padding_,this->_padding_,(GameObject *)0x0);
  }
  this->_padding_ = 0;
  this->_padding_ = -1;
  this->_padding_ = -1;
  iVar1 = GameObject::GetHandle((GameObject *)this);
  ControlPanel::FlushLists(&controlPanel,iVar1);
  return;
}
