/*
 * Entry: 00460558
 * Name: BuildAt
 * Namespace: Global
 * Signature: void BuildAt(int param_1, char * param_2, int param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl BuildAt(int param_1,char *param_2,int param_3,int param_4)

{
  ConstructionRig *this;
  GameObject *pGVar1;
  int iVar2;
  VECTOR_3D *pVVar3;
  AiPath *this_00;
  VECTOR_3D *pVVar4;
  AiCmdInfo local_24;
  ConstructionRig *local_c;
  GameObjectClass *local_8;
  
  this = (ConstructionRig *)GameObjectHandle::GetObj(param_1);
  if (((this != (ConstructionRig *)0x0) &&
      (local_c = this, local_8 = GameObjectClass::Find(param_2), local_8 != (GameObjectClass *)0x0))
     && (pGVar1 = GameObjectHandle::GetObj(param_3), pGVar1 != (GameObject *)0x0)) {
    iVar2 = (**(code **)this->_padding_)();
    if (*(int *)(iVar2 + 0x20) == 0x434e5354) {
      pVVar4 = (VECTOR_3D *)&(pGVar1->obj->transform).front_x;
      pVVar3 = (VECTOR_3D *)(**(code **)(pGVar1->_padding_ + 0xc))();
      ConstructionRig::SetConstructionMatrix(this,pVVar3,pVVar4);
    }
    local_24.priority = param_4;
    local_24.what = CMD_BUILD;
    local_24.who = param_3;
    this_00 = operator_new(0x1c);
    if (this_00 == (AiPath *)0x0) {
      local_24.where = (AiPath *)0x0;
    }
    else {
      pVVar4 = (VECTOR_3D *)(**(code **)(pGVar1->_padding_ + 0xc))();
      pVVar3 = (VECTOR_3D *)(**(code **)(this->_padding_ + 0xc))();
      local_24.where = AiPath::AiPath(this_00,pVVar3,pVVar4);
    }
    local_24.param = (long)local_8;
    GameObject::SetCommand((GameObject *)local_c,&local_24);
  }
  return;
}
