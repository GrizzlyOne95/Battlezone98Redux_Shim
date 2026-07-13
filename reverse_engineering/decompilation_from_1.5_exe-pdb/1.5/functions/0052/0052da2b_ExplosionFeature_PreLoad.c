/*
 * Entry: 0052da2b
 * Name: ExplosionFeature::PreLoad
 * Namespace: ExplosionFeature
 * Signature: void PreLoad(ExplosionFeature * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ExplosionFeature::PreLoad(ExplosionFeature *this)

{
  if (((byte)useD3D & 4) == 0) {
    xplBuilding = ExplosionClass::Find(0x6c7078646c6278);
    xplVehicle = ExplosionClass::Find(0x6c707872616378);
    xplSecondary = ExplosionClass::Find(0x6c707863657378);
    xplDetonate = ExplosionClass::Find(0x6c707872616378);
    xplGround = (ExplosionClass *)0x0;
  }
  else {
    xplBuilding = ExplosionClass::Find(0x616c7078646c6278);
    xplVehicle = ExplosionClass::Find(0x616c707872616378);
    xplSecondary = ExplosionClass::Find(0x616c707863657378);
    xplDetonate = ExplosionClass::Find(0x626c707872616378);
    xplGround = ExplosionClass::Find(0x6b6873646e6778);
  }
  return;
}
