/*
 * Entry: 00460be6
 * Name: SetCurAmmo
 * Namespace: Global
 * Signature: void SetCurAmmo(int param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SetCurAmmo(int param_1,long param_2)

{
  GameObject *this;
  
  this = GameObjectHandle::GetObj(param_1);
  if (this != (GameObject *)0x0) {
    GameObject::SetCurAmmo(this,param_2);
  }
  return;
}
