/*
 * Entry: 0046014f
 * Name: Dropoff
 * Namespace: Global
 * Signature: void Dropoff(int param_1, MAT_3D * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Dropoff(int param_1,MAT_3D *param_2,int param_3)

{
  int iVar1;
  VECTOR_3D *pVVar2;
  VECTOR_3D *pVVar3;
  AiCmdInfo local_48;
  VECTOR_3D local_30;
  VECTOR_3D local_24;
  float local_18;
  float local_14;
  float local_10;
  AiPath *local_c;
  ConstructionRig *local_8;
  
  local_8 = (ConstructionRig *)GameObjectHandle::GetObj(param_1);
  if (local_8 != (ConstructionRig *)0x0) {
    iVar1 = (**(code **)local_8->_padding_)();
    if (*(int *)(iVar1 + 0x20) == 0x434e5354) {
      local_24.x = param_2->front_x;
      local_24.y = param_2->front_y;
      local_24.z = param_2->front_z;
      local_30.x = (float)param_2->posit_x;
      local_30.y = (float)param_2->posit_y;
      local_30.z = (float)param_2->posit_z;
      local_18 = local_30.x;
      local_14 = local_30.y;
      local_10 = local_30.z;
      ConstructionRig::SetConstructionMatrix(local_8,&local_30,&local_24);
    }
    local_48.who = 0;
    local_48.priority = param_3;
    local_48.what = CMD_DROPOFF;
    local_c = operator_new(0x1c);
    if (local_c == (AiPath *)0x0) {
      local_48.where = (AiPath *)0x0;
    }
    else {
      local_30.x = (float)param_2->posit_x;
      local_30.y = (float)param_2->posit_y;
      pVVar3 = &local_30;
      local_30.z = (float)param_2->posit_z;
      local_18 = local_30.x;
      local_14 = local_30.y;
      local_10 = local_30.z;
      pVVar2 = (VECTOR_3D *)(**(code **)(local_8->_padding_ + 0xc))();
      local_48.where = AiPath::AiPath(local_c,pVVar2,pVVar3);
    }
    local_48.param = 0;
    GameObject::SetCommand((GameObject *)local_8,&local_48);
  }
  return;
}
