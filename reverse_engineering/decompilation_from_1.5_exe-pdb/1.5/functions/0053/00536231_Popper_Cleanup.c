/*
 * Entry: 00536231
 * Name: Popper::Cleanup
 * Namespace: Popper
 * Signature: void Cleanup(Popper * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Popper::Cleanup(Popper *this)

{
  uint *puVar1;
  
  puVar1 = (uint *)(*(int *)&this->field_0x18 + 0x14);
  *puVar1 = *puVar1 & 0xfffffff7;
  Bullet::Cleanup((Bullet *)this);
  return;
}
