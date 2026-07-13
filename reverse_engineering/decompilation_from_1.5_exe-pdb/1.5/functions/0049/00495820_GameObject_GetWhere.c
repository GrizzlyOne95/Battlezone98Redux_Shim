/*
 * Entry: 00495820
 * Name: GameObject::GetWhere
 * Namespace: GameObject
 * Signature: VECTOR_3D * GetWhere(GameObject * this, VECTOR_3D * __return_storage_ptr__)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __thiscall GameObject::GetWhere(GameObject *this,VECTOR_3D *__return_storage_ptr__)

{
  VECTOR_2D *pVVar1;
  
  pVVar1 = ((this->curCmd).where)->points;
  __return_storage_ptr__->x = pVVar1->x;
  __return_storage_ptr__->y = 0.0;
  __return_storage_ptr__->z = pVVar1->z;
  return __return_storage_ptr__;
}
