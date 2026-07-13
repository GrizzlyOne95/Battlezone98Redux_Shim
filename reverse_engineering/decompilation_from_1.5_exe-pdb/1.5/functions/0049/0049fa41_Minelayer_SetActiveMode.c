/*
 * Entry: 0049fa41
 * Name: Minelayer::SetActiveMode
 * Namespace: Minelayer
 * Signature: bool SetActiveMode(Minelayer * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Minelayer::SetActiveMode(Minelayer *this,int param_1)

{
  bool bVar1;
  
  if (param_1 == 0xf) {
    GameObject::SetCommand((GameObject *)this,CMD_LAY_MINES);
    return true;
  }
  bVar1 = Craft::SetActiveMode((Craft *)this,param_1);
  return bVar1;
}
