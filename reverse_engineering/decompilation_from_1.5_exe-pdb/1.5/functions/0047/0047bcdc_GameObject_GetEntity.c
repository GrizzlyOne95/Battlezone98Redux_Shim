/*
 * Entry: 0047bcdc
 * Name: GameObject::GetEntity
 * Namespace: GameObject
 * Signature: tagENTITY * GetEntity(GameObject * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

tagENTITY * __thiscall GameObject::GetEntity(GameObject *this)

{
  return (tagENTITY *)(this->nextCmd).priority;
}
