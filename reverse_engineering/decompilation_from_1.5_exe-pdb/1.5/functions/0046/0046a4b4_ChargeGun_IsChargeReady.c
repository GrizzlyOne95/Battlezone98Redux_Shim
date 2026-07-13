/*
 * Entry: 0046a4b4
 * Name: ChargeGun::IsChargeReady
 * Namespace: ChargeGun
 * Signature: bool IsChargeReady(ChargeGun * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall ChargeGun::IsChargeReady(ChargeGun *this)

{
  return this->chargeLevel->ordnanceClass != (OrdnanceClass *)0x0;
}
