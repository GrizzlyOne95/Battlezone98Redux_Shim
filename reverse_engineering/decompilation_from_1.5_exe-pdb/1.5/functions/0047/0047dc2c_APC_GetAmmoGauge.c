/*
 * Entry: 0047dc2c
 * Name: APC::GetAmmoGauge
 * Namespace: APC
 * Signature: float GetAmmoGauge(APC * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __thiscall APC::GetAmmoGauge(APC *this)

{
  return (float)this->soldierCount / (float)*(int *)(this->_padding_ + 0x3cc);
}
