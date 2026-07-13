/*
 * Entry: 0053a281
 * Name: SpecialItem::Control
 * Namespace: SpecialItem
 * Signature: void Control(SpecialItem * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SpecialItem::Control(SpecialItem *this,float param_1)

{
  Weapon::Control((Weapon *)this,param_1);
  if ((float)(int)(this->carrier->curAmmo ^ 0x33333333) <
      (float)*(int *)(this->_padding_ + 0x78) * param_1) {
    this->triggered = false;
  }
  return;
}
