/*
 * Entry: 00405af2
 * Name: GameObject::GetFrontVector
 * Namespace: GameObject
 * Signature: VECTOR_3D * GetFrontVector(GameObject * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __thiscall GameObject::GetFrontVector(GameObject *this)

{
  return (VECTOR_3D *)&(this->obj->transform).front_x;
}
