/*
 * Entry: 0046035d
 * Name: BuildAt
 * Namespace: Global
 * Signature: void BuildAt(int param_1, char * param_2, MAT_3D * param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl BuildAt(int param_1,char *param_2,MAT_3D *param_3,int param_4)

{
  ConstructionRig *pCVar1;
  int iVar2;
  VECTOR_3D *pVVar3;
  VECTOR_3D *pVVar4;
  AiCmdInfo local_4c;
  VECTOR_3D local_34;
  VECTOR_3D local_28;
  float local_1c;
  float local_18;
  float local_14;
  GameObjectClass *local_10;
  AiPath *local_c;
  ConstructionRig *local_8;
  
  pCVar1 = (ConstructionRig *)GameObjectHandle::GetObj(param_1);
  if (pCVar1 != (ConstructionRig *)0x0) {
    local_8 = pCVar1;
    local_10 = GameObjectClass::Find(param_2);
    if (local_10 != (GameObjectClass *)0x0) {
      iVar2 = (**(code **)pCVar1->_padding_)();
      if (*(int *)(iVar2 + 0x20) == 0x434e5354) {
        local_28.x = param_3->front_x;
        local_28.y = param_3->front_y;
        local_28.z = param_3->front_z;
        local_34.x = (float)param_3->posit_x;
        local_34.y = (float)param_3->posit_y;
        local_34.z = (float)param_3->posit_z;
        local_1c = local_34.x;
        local_18 = local_34.y;
        local_14 = local_34.z;
        ConstructionRig::SetConstructionMatrix(local_8,&local_34,&local_28);
      }
      local_4c.who = 0;
      local_4c.priority = param_4;
      local_4c.what = CMD_BUILD;
      local_c = operator_new(0x1c);
      if (local_c == (AiPath *)0x0) {
        local_4c.where = (AiPath *)0x0;
      }
      else {
        local_34.x = (float)param_3->posit_x;
        local_34.y = (float)param_3->posit_y;
        pVVar4 = &local_34;
        local_34.z = (float)param_3->posit_z;
        local_1c = local_34.x;
        local_18 = local_34.y;
        local_14 = local_34.z;
        pVVar3 = (VECTOR_3D *)(**(code **)(local_8->_padding_ + 0xc))();
        local_4c.where = AiPath::AiPath(local_c,pVVar3,pVVar4);
      }
      local_4c.param = (long)local_10;
      GameObject::SetCommand((GameObject *)local_8,&local_4c);
    }
  }
  return;
}
