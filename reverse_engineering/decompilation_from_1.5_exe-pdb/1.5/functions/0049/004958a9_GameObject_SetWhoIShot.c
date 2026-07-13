/*
 * Entry: 004958a9
 * Name: GameObject::SetWhoIShot
 * Namespace: GameObject
 * Signature: void SetWhoIShot(GameObject * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GameObject::SetWhoIShot(GameObject *this,int param_1)

{
  float fVar1;
  
  this->who_i_shot = param_1;
  fVar1 = Get_TimeLocal();
  this->when_i_shot = fVar1;
  return;
}
