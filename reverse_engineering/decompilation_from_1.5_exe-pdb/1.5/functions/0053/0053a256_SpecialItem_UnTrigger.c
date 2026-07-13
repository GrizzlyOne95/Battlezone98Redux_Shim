/*
 * Entry: 0053a256
 * Name: SpecialItem::UnTrigger
 * Namespace: SpecialItem
 * Signature: void UnTrigger(SpecialItem * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SpecialItem::UnTrigger(SpecialItem *this)

{
  if ((this->carrier != GameObject::userObject) || ((UserProfilePtr->playOption & 0x400U) != 0)) {
    this->triggered = false;
    this->held = '\0';
  }
  return;
}
