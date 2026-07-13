/*
 * Entry: 0047bcd5
 * Name: GameObject::GetOBJ76
 * Namespace: GameObject
 * Signature: _OBJ76 * GetOBJ76(GameObject * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_OBJ76 * __thiscall GameObject::GetOBJ76(GameObject *this)

{
  return (_OBJ76 *)(this->nextCmd).what;
}
