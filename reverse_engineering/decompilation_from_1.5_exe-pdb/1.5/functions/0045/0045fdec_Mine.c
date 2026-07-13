/*
 * Entry: 0045fdec
 * Name: Mine
 * Namespace: Global
 * Signature: void Mine(int param_1, VECTOR_3D * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Mine(int param_1,VECTOR_3D *param_2,int param_3)

{
  GameObject *this;
  AiPath *this_00;
  VECTOR_3D *pVVar1;
  AiCmdInfo local_1c;
  
  this = GameObjectHandle::GetObj(param_1);
  if (this != (GameObject *)0x0) {
    local_1c.who = 0;
    local_1c.priority = param_3;
    local_1c.what = CMD_LAY_MINES;
    this_00 = operator_new(0x1c);
    if (this_00 == (AiPath *)0x0) {
      local_1c.where = (AiPath *)0x0;
    }
    else {
      pVVar1 = (VECTOR_3D *)(**(code **)(this->_padding_ + 0xc))();
      local_1c.where = AiPath::AiPath(this_00,pVVar1,param_2);
    }
    local_1c.param = 0;
    GameObject::SetCommand(this,&local_1c);
  }
  return;
}
