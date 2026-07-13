/*
 * Entry: 0045fc27
 * Name: SetCommand
 * Namespace: Global
 * Signature: void SetCommand(int param_1, AiCommand param_2, int param_3, int param_4, char * param_5, float param_6, long param_7)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
SetCommand(int param_1,AiCommand param_2,int param_3,int param_4,char *param_5,float param_6,
          long param_7)

{
  GameObject *this;
  AiCmdInfo local_1c;
  
  this = GameObjectHandle::GetObj(param_1);
  if (this != (GameObject *)0x0) {
    local_1c.priority = param_3;
    local_1c.what = param_2;
    local_1c.who = param_4;
    if (param_5 == (char *)0x0) {
      local_1c.where = (AiPath *)0x0;
    }
    else {
      local_1c.where = AiPath::Find(param_5);
      if (local_1c.where == (AiPath *)0x0) {
        return;
      }
    }
    local_1c.param = param_7;
    local_1c.when = param_6;
    GameObject::SetCommand(this,&local_1c);
  }
  return;
}
