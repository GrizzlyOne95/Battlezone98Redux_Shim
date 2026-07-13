/*
 * Entry: 004607b1
 * Name: SetMaxHealth
 * Namespace: Global
 * Signature: void SetMaxHealth(int param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SetMaxHealth(int param_1,float param_2)

{
  GameObject *this;
  
  this = GameObjectHandle::GetObj(param_1);
  if (this != (GameObject *)0x0) {
    GameObject::SetMaxHealth(this,param_2);
  }
  return;
}
