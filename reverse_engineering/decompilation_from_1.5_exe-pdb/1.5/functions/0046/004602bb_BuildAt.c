/*
 * Entry: 004602bb
 * Name: BuildAt
 * Namespace: Global
 * Signature: void BuildAt(int param_1, char * param_2, VECTOR_3D * param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl BuildAt(int param_1,char *param_2,VECTOR_3D *param_3,int param_4)

{
  ConstructionRig *this;
  int iVar1;
  AiPath *this_00;
  VECTOR_3D *pVVar2;
  AiCmdInfo local_20;
  GameObjectClass *local_8;
  
  this = (ConstructionRig *)GameObjectHandle::GetObj(param_1);
  if (this != (ConstructionRig *)0x0) {
    local_8 = GameObjectClass::Find(param_2);
    if (local_8 != (GameObjectClass *)0x0) {
      iVar1 = (**(code **)this->_padding_)();
      if (*(int *)(iVar1 + 0x20) == 0x434e5354) {
        ConstructionRig::SetConstructionMatrix(this,param_3,(VECTOR_3D *)(this->_padding_ + 0x38));
      }
      local_20.who = 0;
      local_20.priority = param_4;
      local_20.what = CMD_BUILD;
      this_00 = operator_new(0x1c);
      if (this_00 == (AiPath *)0x0) {
        local_20.where = (AiPath *)0x0;
      }
      else {
        pVVar2 = (VECTOR_3D *)(**(code **)(this->_padding_ + 0xc))();
        local_20.where = AiPath::AiPath(this_00,pVVar2,param_3);
      }
      local_20.param = (long)local_8;
      GameObject::SetCommand((GameObject *)this,&local_20);
    }
  }
  return;
}
