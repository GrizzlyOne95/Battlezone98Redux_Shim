/*
 * Entry: 0045f194
 * Name: SetVelocity
 * Namespace: Global
 * Signature: void SetVelocity(int param_1, VECTOR_3D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SetVelocity(int param_1,VECTOR_3D *param_2)

{
  GameObject *this;
  
  this = GameObjectHandle::GetObj(param_1);
  if (this != (GameObject *)0x0) {
    GameObject::SetVelocity(this,param_2);
  }
  return;
}
