/*
 * Entry: 0045f02c
 * Name: SetTransform
 * Namespace: Global
 * Signature: void SetTransform(int param_1, MAT_3D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SetTransform(int param_1,MAT_3D *param_2)

{
  GameObject *this;
  
  this = GameObjectHandle::GetObj(param_1);
  if (this != (GameObject *)0x0) {
    GameObject::SetTransform(this,param_2);
  }
  return;
}
