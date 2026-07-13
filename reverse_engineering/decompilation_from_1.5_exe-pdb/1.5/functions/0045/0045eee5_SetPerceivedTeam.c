/*
 * Entry: 0045eee5
 * Name: SetPerceivedTeam
 * Namespace: Global
 * Signature: void SetPerceivedTeam(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SetPerceivedTeam(int param_1,int param_2)

{
  GameObject *this;
  
  this = GameObjectHandle::GetObj(param_1);
  if (this != (GameObject *)0x0) {
    GameObject::SetPerceivedTeam(this,param_2);
  }
  return;
}
