/*
 * Entry: 0045e456
 * Name: GameObject::GetOrigin
 * Namespace: GameObject
 * Signature: VECTOR_3D * GetOrigin(GameObject * this, VECTOR_3D * __return_storage_ptr__)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __thiscall GameObject::GetOrigin(GameObject *this,VECTOR_3D *__return_storage_ptr__)

{
  _OBJ76 *p_Var1;
  
  p_Var1 = this->obj;
  __return_storage_ptr__->x = (float)(p_Var1->transform).posit_x;
  __return_storage_ptr__->y = (float)(p_Var1->transform).posit_y;
  __return_storage_ptr__->z = (float)(p_Var1->transform).posit_z;
  return __return_storage_ptr__;
}
