/*
 * Entry: 004b2ff6
 * Name: Tug::GetAmmoGauge
 * Namespace: Tug
 * Signature: float GetAmmoGauge(Tug * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __thiscall Tug::GetAmmoGauge(Tug *this)

{
  if (this->cargo != (GameObject *)0x0) {
    return 1.0;
  }
  return 0.0;
}
