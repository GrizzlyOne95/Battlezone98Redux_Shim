/*
 * Entry: 0045f415
 * Name: SetObjectiveName
 * Namespace: Global
 * Signature: void SetObjectiveName(int param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SetObjectiveName(int param_1,char *param_2)

{
  GameObject *this;
  
  this = GameObject::GetObj(param_1);
  if (this != (GameObject *)0x0) {
    GameObject::SetName(this,param_2);
  }
  return;
}
