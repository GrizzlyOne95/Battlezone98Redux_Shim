/*
 * Entry: 00537e76
 * Name: Rocket::Cleanup
 * Namespace: Rocket
 * Signature: void Cleanup(Rocket * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Rocket::Cleanup(Rocket *this)

{
  uint *puVar1;
  
  puVar1 = (uint *)(this->_padding_ + 0x14);
  *puVar1 = *puVar1 & 0xfffffff7;
  Bullet::Cleanup((Bullet *)this);
  return;
}
