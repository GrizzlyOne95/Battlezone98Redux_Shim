/*
 * Entry: 0052a964
 * Name: BeamGun::EnoughAmmo
 * Namespace: BeamGun
 * Signature: bool EnoughAmmo(BeamGun * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall BeamGun::EnoughAmmo(BeamGun *this)

{
  if ((this->_padding_ != 0) &&
     ((*(int *)(this->_padding_ + 0x48) == 0 || (0 < (int)(this->carrier->curAmmo ^ 0x33333333U)))))
  {
    return true;
  }
  return false;
}
