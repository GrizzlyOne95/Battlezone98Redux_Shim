/*
 * Entry: 0053a1cd
 * Name: SpecialItem::Select
 * Namespace: SpecialItem
 * Signature: void Select(SpecialItem * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SpecialItem::Select(SpecialItem *this)

{
  if (((this->carrier != (GameObject *)0x0) && (this->carrier == GameObject::userObject)) &&
     ((UserProfilePtr->playOption & 0x400U) == 0)) {
    this->triggered = true;
  }
  return;
}
