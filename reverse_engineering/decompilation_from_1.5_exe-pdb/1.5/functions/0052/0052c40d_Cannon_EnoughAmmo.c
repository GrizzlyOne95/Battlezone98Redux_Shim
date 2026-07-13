/*
 * Entry: 0052c40d
 * Name: Cannon::EnoughAmmo
 * Namespace: Cannon
 * Signature: bool EnoughAmmo(Cannon * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Cannon::EnoughAmmo(Cannon *this)

{
  if ((this->_padding_ != 0) &&
     (*(int *)(this->_padding_ + 0x48) <= (int)(this->carrier->curAmmo ^ 0x33333333U))) {
    return true;
  }
  return false;
}
