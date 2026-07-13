/*
 * Entry: 0053c63e
 * Name: ThermalMissileClass::Build
 * Namespace: ThermalMissileClass
 * Signature: Ordnance * Build(ThermalMissileClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Ordnance * __thiscall ThermalMissileClass::Build(ThermalMissileClass *this,_OBJ76 *param_1)

{
  ThermalMissile *pTVar1;
  
  pTVar1 = operator_new(0xf8);
  if (pTVar1 == (ThermalMissile *)0x0) {
    pTVar1 = (ThermalMissile *)0x0;
  }
  else {
    pTVar1 = ThermalMissile::ThermalMissile(pTVar1,param_1,this);
  }
  return (Ordnance *)pTVar1;
}
