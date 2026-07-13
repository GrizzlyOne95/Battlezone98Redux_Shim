/*
 * Entry: 0053a1f5
 * Name: SpecialItem::Deselect
 * Namespace: SpecialItem
 * Signature: void Deselect(SpecialItem * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SpecialItem::Deselect(SpecialItem *this)

{
  if (((this->carrier != (GameObject *)0x0) && (this->carrier == GameObject::userObject)) &&
     ((UserProfilePtr->playOption & 0x400U) == 0)) {
    this->triggered = false;
  }
  return;
}
