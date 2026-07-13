/*
 * Entry: 00405b06
 * Name: GameObject::GetVelocity
 * Namespace: GameObject
 * Signature: VECTOR_3D * GetVelocity(GameObject * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __thiscall GameObject::GetVelocity(GameObject *this)

{
  return &(this->euler).v;
}
