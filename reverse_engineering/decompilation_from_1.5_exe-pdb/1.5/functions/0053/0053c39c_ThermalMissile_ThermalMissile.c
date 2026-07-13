/*
 * Entry: 0053c39c
 * Name: ThermalMissile::ThermalMissile
 * Namespace: ThermalMissile
 * Signature: ThermalMissile * ThermalMissile(ThermalMissile * this, _OBJ76 * param_1, ThermalMissileClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ThermalMissile * __thiscall
ThermalMissile::ThermalMissile(ThermalMissile *this,_OBJ76 *param_1,ThermalMissileClass *param_2)

{
  float10 fVar1;
  
  Missile::Missile((Missile *)this,param_1,(MissileClass *)param_2);
  this->_padding_ = (int)&_vftable_;
  fVar1 = (float10)fcos((float10)param_2->coneAngle);
  this->coneCosSq = (float)(fVar1 * fVar1);
  return this;
}
