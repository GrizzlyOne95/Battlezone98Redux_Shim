/*
 * Entry: 0053c36f
 * Name: ThermalMissile::~ThermalMissile
 * Namespace: ThermalMissile
 * Signature: void ~ThermalMissile(ThermalMissile * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ThermalMissile::~ThermalMissile(ThermalMissile *this)

{
  this->_padding_ = (int)&_vftable_;
  Missile::~Missile((Missile *)this);
  return;
}
