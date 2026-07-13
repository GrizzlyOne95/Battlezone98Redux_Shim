/*
 * Entry: 0045f3fd
 * Name: SetObjectiveOff
 * Namespace: Global
 * Signature: void SetObjectiveOff(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SetObjectiveOff(int param_1)

{
  GameObject *this;
  
  this = GameObject::GetObj(param_1);
  if (this != (GameObject *)0x0) {
    GameObject::SetObjective(this,false);
  }
  return;
}
