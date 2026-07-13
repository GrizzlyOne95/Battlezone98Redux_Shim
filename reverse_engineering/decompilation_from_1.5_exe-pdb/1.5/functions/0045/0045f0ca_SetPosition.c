/*
 * Entry: 0045f0ca
 * Name: SetPosition
 * Namespace: Global
 * Signature: void SetPosition(int param_1, VECTOR_3D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SetPosition(int param_1,VECTOR_3D *param_2)

{
  GameObject *this;
  
  this = GameObjectHandle::GetObj(param_1);
  if (this != (GameObject *)0x0) {
    GameObject::SetOrigin(this,param_2);
  }
  return;
}
