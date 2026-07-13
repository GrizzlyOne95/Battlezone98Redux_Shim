/*
 * Entry: 0052b599
 * Name: BounceBomb::Cleanup
 * Namespace: BounceBomb
 * Signature: void Cleanup(BounceBomb * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall BounceBomb::Cleanup(BounceBomb *this)

{
  uint *puVar1;
  
  puVar1 = (uint *)(*(int *)&this->field_0x18 + 0x14);
  *puVar1 = *puVar1 & 0xfffffff7;
  Bullet::Cleanup((Bullet *)this);
  return;
}
