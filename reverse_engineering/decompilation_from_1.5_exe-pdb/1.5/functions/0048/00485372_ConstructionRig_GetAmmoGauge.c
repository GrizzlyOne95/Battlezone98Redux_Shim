/*
 * Entry: 00485372
 * Name: ConstructionRig::GetAmmoGauge
 * Namespace: ConstructionRig
 * Signature: float GetAmmoGauge(ConstructionRig * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __thiscall ConstructionRig::GetAmmoGauge(ConstructionRig *this)

{
  float fVar1;
  
  if (this->unbuildHandle != 0) {
    return 1.0 - (float)this->_padding_ / this->dropClass->buildTime;
  }
  fVar1 = Producer::GetAmmoGauge((Producer *)this);
  return fVar1;
}
