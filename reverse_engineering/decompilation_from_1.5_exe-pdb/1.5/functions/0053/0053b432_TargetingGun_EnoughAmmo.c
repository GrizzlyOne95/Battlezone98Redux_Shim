/*
 * Entry: 0053b432
 * Name: TargetingGun::EnoughAmmo
 * Namespace: TargetingGun
 * Signature: bool EnoughAmmo(TargetingGun * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall TargetingGun::EnoughAmmo(TargetingGun *this)

{
  OrdnanceClass *pOVar1;
  
  if (this->salvoCount < 1) {
    pOVar1 = this->leaderClass;
  }
  else {
    pOVar1 = (OrdnanceClass *)this->_padding_;
  }
  return pOVar1->ammoCost <= (int)(this->carrier->curAmmo ^ 0x33333333U);
}
