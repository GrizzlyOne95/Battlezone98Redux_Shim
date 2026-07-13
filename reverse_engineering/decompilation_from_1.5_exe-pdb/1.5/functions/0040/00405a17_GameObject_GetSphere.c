/*
 * Entry: 00405a17
 * Name: GameObject::GetSphere
 * Namespace: GameObject
 * Signature: SPHERE * GetSphere(GameObject * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SPHERE * __thiscall GameObject::GetSphere(GameObject *this)

{
  if (this->ent != (tagENTITY *)0x0) {
    return &this->ent->bSphere;
  }
  return &this->obj->bSphere;
}
