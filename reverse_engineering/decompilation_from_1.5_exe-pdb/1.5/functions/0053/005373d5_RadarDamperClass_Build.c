/*
 * Entry: 005373d5
 * Name: RadarDamperClass::Build
 * Namespace: RadarDamperClass
 * Signature: Weapon * Build(RadarDamperClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Weapon * __thiscall RadarDamperClass::Build(RadarDamperClass *this,_OBJ76 *param_1)

{
  RadarDamper *pRVar1;
  
  pRVar1 = operator_new(0xc0);
  if (pRVar1 == (RadarDamper *)0x0) {
    pRVar1 = (RadarDamper *)0x0;
  }
  else {
    pRVar1 = RadarDamper::RadarDamper(pRVar1,param_1,this);
  }
  return (Weapon *)pRVar1;
}
