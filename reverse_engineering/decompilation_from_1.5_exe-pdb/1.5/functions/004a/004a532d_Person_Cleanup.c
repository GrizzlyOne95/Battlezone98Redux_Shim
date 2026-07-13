/*
 * Entry: 004a532d
 * Name: Person::Cleanup
 * Namespace: Person
 * Signature: void Cleanup(Person * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Person::Cleanup(Person *this)

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
