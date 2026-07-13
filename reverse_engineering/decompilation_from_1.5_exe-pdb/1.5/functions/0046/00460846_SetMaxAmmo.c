/*
 * Entry: 00460846
 * Name: SetMaxAmmo
 * Namespace: Global
 * Signature: void SetMaxAmmo(int param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SetMaxAmmo(int param_1,long param_2)

{
  GameObject *this;
  
  this = GameObjectHandle::GetObj(param_1);
  if (this != (GameObject *)0x0) {
    GameObject::SetMaxAmmo(this,param_2);
  }
  return;
}
