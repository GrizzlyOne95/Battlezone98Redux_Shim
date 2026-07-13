/*
 * Entry: 00531f5e
 * Name: Missile::Cleanup
 * Namespace: Missile
 * Signature: void Cleanup(Missile * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Missile::Cleanup(Missile *this)

{
  if (userMissile == (_OBJ76 *)this->_padding_) {
    userMissile = (_OBJ76 *)0x0;
  }
  Rocket::Cleanup((Rocket *)this);
  return;
}
