/*
 * Entry: 0052fde1
 * Name: Grenade::Cleanup
 * Namespace: Grenade
 * Signature: void Cleanup(Grenade * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Grenade::Cleanup(Grenade *this)

{
  uint *puVar1;
  
  puVar1 = (uint *)(*(int *)&this->field_0x18 + 0x14);
  *puVar1 = *puVar1 & 0xfffffff7;
  Bullet::Cleanup((Bullet *)this);
  return;
}
