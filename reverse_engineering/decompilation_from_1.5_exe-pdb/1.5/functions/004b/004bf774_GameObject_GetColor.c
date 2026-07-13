/*
 * Entry: 004bf774
 * Name: GameObject::GetColor
 * Namespace: GameObject
 * Signature: long GetColor(GameObject * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __thiscall GameObject::GetColor(GameObject *this)

{
  if ((this->obj->flags & 0x200) != 0) {
    return this->deadColor;
  }
  return this->liveColor;
}
