/*
 * Entry: 0045fd6e
 * Name: Goto
 * Namespace: Global
 * Signature: void Goto(int param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Goto(int param_1,int param_2,int param_3)

{
  GameObject *this;
  GameObject *pGVar1;
  AiPath *this_00;
  VECTOR_3D *pVVar2;
  VECTOR_3D *pVVar3;
  AiCmdInfo local_1c;
  
  this = GameObjectHandle::GetObj(param_1);
  if ((this != (GameObject *)0x0) &&
     (pGVar1 = GameObjectHandle::GetObj(param_2), pGVar1 != (GameObject *)0x0)) {
    local_1c.priority = param_3;
    local_1c.what = CMD_GO;
    local_1c.who = param_2;
    this_00 = operator_new(0x1c);
    if (this_00 == (AiPath *)0x0) {
      local_1c.where = (AiPath *)0x0;
    }
    else {
      pVVar2 = (VECTOR_3D *)(**(code **)(pGVar1->_padding_ + 0xc))();
      pVVar3 = (VECTOR_3D *)(**(code **)(this->_padding_ + 0xc))();
      local_1c.where = AiPath::AiPath(this_00,pVVar3,pVVar2);
    }
    local_1c.param = 0;
    GameObject::SetCommand(this,&local_1c);
  }
  return;
}
