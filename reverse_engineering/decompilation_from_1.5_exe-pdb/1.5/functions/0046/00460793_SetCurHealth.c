/*
 * Entry: 00460793
 * Name: SetCurHealth
 * Namespace: Global
 * Signature: void SetCurHealth(int param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SetCurHealth(int param_1,float param_2)

{
  GameObject *this;
  
  this = GameObjectHandle::GetObj(param_1);
  if (this != (GameObject *)0x0) {
    GameObject::SetCurHealth(this,param_2);
  }
  return;
}
