/*
 * Entry: 0053a21d
 * Name: SpecialItem::Trigger
 * Namespace: SpecialItem
 * Signature: void Trigger(SpecialItem * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SpecialItem::Trigger(SpecialItem *this)

{
  if ((this->carrier != GameObject::userObject) || ((UserProfilePtr->playOption & 0x400U) != 0)) {
    if (this->held == '\0') {
      this->triggered = this->triggered == false;
    }
    this->held = '\x02';
  }
  return;
}
