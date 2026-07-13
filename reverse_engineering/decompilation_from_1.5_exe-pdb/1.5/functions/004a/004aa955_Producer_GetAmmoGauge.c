/*
 * Entry: 004aa955
 * Name: Producer::GetAmmoGauge
 * Namespace: Producer
 * Signature: float GetAmmoGauge(Producer * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __thiscall Producer::GetAmmoGauge(Producer *this)

{
  if (this->buildClass != (GameObjectClass *)0x0) {
    return 1.0 - this->buildDoneTime / this->buildClass->buildTime;
  }
  return 0.0;
}
