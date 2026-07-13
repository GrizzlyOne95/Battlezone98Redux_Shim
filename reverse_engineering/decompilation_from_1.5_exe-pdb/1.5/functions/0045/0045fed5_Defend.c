/*
 * Entry: 0045fed5
 * Name: Defend
 * Namespace: Global
 * Signature: void Defend(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Defend(int param_1,int param_2)

{
  GameObject *this;
  AiCmdInfo local_1c;
  
  this = GameObjectHandle::GetObj(param_1);
  if (this != (GameObject *)0x0) {
    local_1c.who = 0;
    local_1c.where = (AiPath *)0x0;
    local_1c.param = 0;
    local_1c.priority = param_2;
    local_1c.what = CMD_DEFEND;
    GameObject::SetCommand(this,&local_1c);
  }
  return;
}
