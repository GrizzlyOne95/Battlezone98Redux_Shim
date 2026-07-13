/*
 * Entry: 0045fd25
 * Name: Goto
 * Namespace: Global
 * Signature: void Goto(int param_1, char * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Goto(int param_1,char *param_2,int param_3)

{
  GameObject *this;
  AiCmdInfo local_1c;
  
  this = GameObjectHandle::GetObj(param_1);
  if (this != (GameObject *)0x0) {
    local_1c.where = AiPath::Find(param_2);
    if (local_1c.where != (AiPath *)0x0) {
      local_1c.who = 0;
      local_1c.param = 0;
      local_1c.priority = param_3;
      local_1c.what = CMD_GO;
      GameObject::SetCommand(this,&local_1c);
    }
  }
  return;
}
