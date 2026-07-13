/*
 * Entry: 004aa812
 * Name: Producer::SetActiveMode
 * Namespace: Producer
 * Signature: bool SetActiveMode(Producer * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Producer::SetActiveMode(Producer *this,int param_1)

{
  bool bVar1;
  AiCommand AVar2;
  
  if (param_1 == 0xb) {
    AVar2 = CMD_GO_TO_GEYSER;
  }
  else if (param_1 == 3) {
    AVar2 = CMD_PICKUP;
  }
  else {
    if (param_1 != 0x17) {
      if (0x18 < param_1) {
        GameObject::SetCommand((GameObject *)this,CMD_BUILD,param_1);
        return true;
      }
      bVar1 = Craft::SetActiveMode((Craft *)this,param_1);
      return bVar1;
    }
    AVar2 = CMD_STOP;
  }
  GameObject::SetCommand((GameObject *)this,AVar2);
  return true;
}
