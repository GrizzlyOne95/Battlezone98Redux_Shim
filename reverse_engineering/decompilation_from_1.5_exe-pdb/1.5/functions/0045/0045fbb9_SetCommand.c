/*
 * Entry: 0045fbb9
 * Name: SetCommand
 * Namespace: Global
 * Signature: void SetCommand(int param_1, AiCommand param_2, int param_3, int param_4, VECTOR_3D * param_5, float param_6, long param_7)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
SetCommand(int param_1,AiCommand param_2,int param_3,int param_4,VECTOR_3D *param_5,float param_6,
          long param_7)

{
  GameObject *this;
  AiPath *this_00;
  VECTOR_3D *pVVar1;
  AiCmdInfo local_1c;
  
  this = GameObjectHandle::GetObj(param_1);
  if (this != (GameObject *)0x0) {
    local_1c.priority = param_3;
    local_1c.what = param_2;
    local_1c.who = param_4;
    this_00 = operator_new(0x1c);
    if (this_00 == (AiPath *)0x0) {
      local_1c.where = (AiPath *)0x0;
    }
    else {
      pVVar1 = (VECTOR_3D *)(**(code **)(this->_padding_ + 0xc))();
      local_1c.where = AiPath::AiPath(this_00,pVVar1,param_5);
    }
    local_1c.param = param_7;
    local_1c.when = param_6;
    GameObject::SetCommand(this,&local_1c);
  }
  return;
}
