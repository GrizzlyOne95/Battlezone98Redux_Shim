/*
 * Entry: 0053678c
 * Name: PopperGun::EnoughAmmo
 * Namespace: PopperGun
 * Signature: bool EnoughAmmo(PopperGun * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall PopperGun::EnoughAmmo(PopperGun *this)

{
  if ((this->_padding_ != 0) &&
     (*(int *)(this->_padding_ + 0x48) <= (int)(this->carrier->curAmmo ^ 0x33333333U))) {
    return true;
  }
  return false;
}
