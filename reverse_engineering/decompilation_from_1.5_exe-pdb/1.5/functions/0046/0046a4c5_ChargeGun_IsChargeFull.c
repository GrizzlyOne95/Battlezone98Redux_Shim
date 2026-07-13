/*
 * Entry: 0046a4c5
 * Name: ChargeGun::IsChargeFull
 * Namespace: ChargeGun
 * Signature: bool IsChargeFull(ChargeGun * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall ChargeGun::IsChargeFull(ChargeGun *this)

{
  return (bool)('\x01' - (this->chargeLevel != this->fullLevel));
}
