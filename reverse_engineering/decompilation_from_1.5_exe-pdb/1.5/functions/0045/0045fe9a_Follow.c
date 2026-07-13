/*
 * Entry: 0045fe9a
 * Name: Follow
 * Namespace: Global
 * Signature: void Follow(int param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Follow(int param_1,int param_2,int param_3)

{
  GameObject *this;
  AiCmdInfo local_1c;
  
  this = GameObjectHandle::GetObj(param_1);
  if (this != (GameObject *)0x0) {
    local_1c.where = (AiPath *)0x0;
    local_1c.param = 0;
    local_1c.priority = param_3;
    local_1c.who = param_2;
    local_1c.what = CMD_FOLLOW;
    GameObject::SetCommand(this,&local_1c);
  }
  return;
}
