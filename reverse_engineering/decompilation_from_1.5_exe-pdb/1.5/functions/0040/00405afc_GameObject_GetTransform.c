/*
 * Entry: 00405afc
 * Name: GameObject::GetTransform
 * Namespace: GameObject
 * Signature: MAT_3D * GetTransform(GameObject * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

MAT_3D * __thiscall GameObject::GetTransform(GameObject *this)

{
  return &this->obj->transform;
}
