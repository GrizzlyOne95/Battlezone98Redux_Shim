/*
 * Entry: 0046007d
 * Name: Dropoff
 * Namespace: Global
 * Signature: void Dropoff(GameObject * param_1, AiPath * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Dropoff(GameObject *param_1,AiPath *param_2,int param_3)

{
  int iVar1;
  int unaff_EBX;
  AiPath *local_34;
  AiCommand local_30;
  int local_2c;
  VECTOR_3D local_10;
  
  iVar1 = (**(code **)param_1->_padding_)();
  if (*(int *)(iVar1 + 0x20) == 0x434e5354) {
    local_10.x = *(float *)(*(int *)(unaff_EBX + 8) + -8 + *(int *)(unaff_EBX + 4) * 8);
    local_10.z = *(float *)(*(int *)(unaff_EBX + 8) + -4 + *(int *)(unaff_EBX + 4) * 8);
    local_10.y = 0.0;
    ConstructionRig::SetConstructionMatrix
              ((ConstructionRig *)param_1,&local_10,(VECTOR_3D *)&(param_1->obj->transform).front_x)
    ;
  }
  local_2c = 0;
  local_34 = param_2;
  local_30 = CMD_DROPOFF;
  GameObject::SetCommand(param_1,(AiCmdInfo *)&local_34);
  return;
}
