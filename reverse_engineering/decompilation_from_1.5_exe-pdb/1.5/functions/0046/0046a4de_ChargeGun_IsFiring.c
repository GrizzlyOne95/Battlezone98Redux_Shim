/*
 * Entry: 0046a4de
 * Name: ChargeGun::IsFiring
 * Namespace: ChargeGun
 * Signature: bool IsFiring(ChargeGun * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall ChargeGun::IsFiring(ChargeGun *this)

{
  return 0 < this->salvoCount;
}
