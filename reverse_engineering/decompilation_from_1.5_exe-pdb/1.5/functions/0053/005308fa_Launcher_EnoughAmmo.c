/*
 * Entry: 005308fa
 * Name: Launcher::EnoughAmmo
 * Namespace: Launcher
 * Signature: bool EnoughAmmo(Launcher * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Launcher::EnoughAmmo(Launcher *this)

{
  bool bVar1;
  
  bVar1 = false;
  if ((this->_padding_ != 0) &&
     (*(int *)(this->_padding_ + 0x78) <= (int)(this->carrier->curAmmo ^ 0x33333333U))) {
    bVar1 = true;
  }
  return bVar1;
}
