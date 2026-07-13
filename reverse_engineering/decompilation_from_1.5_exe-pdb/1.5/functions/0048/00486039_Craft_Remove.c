/*
 * Entry: 00486039
 * Name: Craft::Remove
 * Namespace: Craft
 * Signature: void Remove(Craft * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Craft::Remove(Craft *this)

{
  if ((char)this->_padding_ != '\0') {
    Tug::SetCargo((Tug *)this->_padding_,(GameObject *)0x0);
  }
  GameObject::Remove((GameObject *)this);
  return;
}
