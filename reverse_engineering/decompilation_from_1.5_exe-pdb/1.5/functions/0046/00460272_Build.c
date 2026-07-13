/*
 * Entry: 00460272
 * Name: Build
 * Namespace: Global
 * Signature: void Build(int param_1, char * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Build(int param_1,char *param_2,int param_3)

{
  GameObject *this;
  AiCmdInfo local_1c;
  
  this = GameObjectHandle::GetObj(param_1);
  if (this != (GameObject *)0x0) {
    local_1c.param = (long)GameObjectClass::Find(param_2);
    if ((GameObjectClass *)local_1c.param != (GameObjectClass *)0x0) {
      local_1c.who = 0;
      local_1c.where = (AiPath *)0x0;
      local_1c.priority = param_3;
      local_1c.what = CMD_BUILD;
      GameObject::SetCommand(this,&local_1c);
    }
  }
  return;
}
