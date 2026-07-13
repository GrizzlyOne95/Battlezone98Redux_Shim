/*
 * Entry: 004b9581
 * Name: Wingman::SetActiveMode
 * Namespace: Wingman
 * Signature: bool SetActiveMode(Wingman * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Wingman::SetActiveMode(Wingman *this,int param_1)

{
  bool bVar1;
  
  if (param_1 == 0xd) {
    GameObject::SetCommand((GameObject *)this,CMD_HUNT);
  }
  else {
    if (param_1 != 0x10) {
      bVar1 = Craft::SetActiveMode((Craft *)this,param_1);
      return bVar1;
    }
    GameObject::SetCommand((GameObject *)this,CMD_FORMATION,GameObject::userObject);
  }
  return true;
}
