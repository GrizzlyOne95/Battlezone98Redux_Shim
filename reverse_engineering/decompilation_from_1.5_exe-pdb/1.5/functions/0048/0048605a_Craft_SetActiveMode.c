/*
 * Entry: 0048605a
 * Name: Craft::SetActiveMode
 * Namespace: Craft
 * Signature: bool SetActiveMode(Craft * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Craft::SetActiveMode(Craft *this,int param_1)

{
  AiCommand AVar1;
  Craft *pCVar2;
  
  if (param_1 == 1) {
    return false;
  }
  pCVar2 = (Craft *)GameObject::userObject;
  if (param_1 == 2) {
    AVar1 = CMD_FOLLOW;
LAB_00486096:
    GameObject::SetCommand((GameObject *)this,AVar1,(GameObject *)pCVar2);
  }
  else {
    if (param_1 == 5) {
      AVar1 = CMD_GET_REPAIR;
    }
    else {
      if (param_1 != 6) {
        if (param_1 == 7) {
          AVar1 = CMD_RESCUE;
        }
        else {
          if (param_1 != 8) {
            return true;
          }
          AVar1 = CMD_RECYCLE;
          pCVar2 = this;
        }
        goto LAB_00486096;
      }
      AVar1 = CMD_GET_RELOAD;
    }
    GameObject::SetCommand((GameObject *)this,AVar1);
  }
  return true;
}
