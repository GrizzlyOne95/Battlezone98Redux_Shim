/*
 * Entry: 0045f3e5
 * Name: SetObjectiveOn
 * Namespace: Global
 * Signature: void SetObjectiveOn(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SetObjectiveOn(int param_1)

{
  GameObject *this;
  
  this = GameObject::GetObj(param_1);
  if (this != (GameObject *)0x0) {
    GameObject::SetObjective(this,true);
  }
  return;
}
