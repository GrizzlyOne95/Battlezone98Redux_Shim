/*
 * Entry: 004ae741
 * Name: Scavenger::SetActiveMode
 * Namespace: Scavenger
 * Signature: bool SetActiveMode(Scavenger * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Scavenger::SetActiveMode(Scavenger *this,int param_1)

{
  bool bVar1;
  
  if (param_1 == 0xc) {
    GameObject::SetCommand((GameObject *)this,CMD_SCAVENGE);
    return true;
  }
  bVar1 = Craft::SetActiveMode((Craft *)this,param_1);
  return bVar1;
}
