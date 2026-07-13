/*
 * Entry: 0047ec4f
 * Name: Armory::SetActiveMode
 * Namespace: Armory
 * Signature: bool SetActiveMode(Armory * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Armory::SetActiveMode(Armory *this,int param_1)

{
  bool bVar1;
  int iVar2;
  
  if (param_1 == 0x16) {
    this->menu = MENU_NORMAL;
  }
  else if (param_1 == 0x12) {
    this->menu = MENU_CANNONS;
  }
  else if (param_1 == 0x13) {
    this->menu = MENU_ROCKETS;
  }
  else if (param_1 == 0x14) {
    this->menu = MENU_MORTARS;
  }
  else if (param_1 == 0x15) {
    this->menu = MENU_SPECIALS;
  }
  else {
    if (param_1 < 0x19) {
      bVar1 = Producer::SetActiveMode((Producer *)this,param_1);
      return bVar1;
    }
    GameObject::SetCommand((GameObject *)this,CMD_BUILD,param_1);
    iVar2 = ModeList::FindMode((ModeList *)&this->_padding_,param_1);
    this->_padding_ = iVar2;
  }
  return false;
}
