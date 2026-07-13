/*
 * Entry: 0045fe51
 * Name: Mine
 * Namespace: Global
 * Signature: void Mine(int param_1, char * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Mine(int param_1,char *param_2,int param_3)

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
      local_1c.what = CMD_LAY_MINES;
      GameObject::SetCommand(this,&local_1c);
    }
  }
  return;
}
