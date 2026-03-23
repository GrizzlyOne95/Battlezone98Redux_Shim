
uint FUN_00609980(float *param_1,float *param_2,undefined4 *param_3,
                 _Order_node_base<enum_Concurrency::agent_status> *param_4,undefined4 param_5,
                 float param_6,undefined4 *param_7,
                 _Order_node_base<enum_Concurrency::agent_status> *param_8)

{
  char cVar1;
  bool bVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  float10 fVar7;
  undefined4 local_2c;
  _Order_node_base<enum_Concurrency::agent_status> *local_28;
  undefined4 local_24;
  float local_20;
  undefined4 local_18;
  float local_14;
  float local_10;
  float local_c;
  int local_8;
  
  *param_1 = 0.0;
  if (param_4 == (_Order_node_base<enum_Concurrency::agent_status> *)0x0) {
    uVar3 = 0;
  }
  else {
    uVar3 = FUN_0045c4b0();
    uVar3 = uVar3 & 0x200;
    if (uVar3 == 0) {
      if (param_4 == *(_Order_node_base<enum_Concurrency::agent_status> **)(local_8 + 0xc)) {
        uVar3 = 0;
      }
      else {
        uVar4 = (**(code **)(*(int *)(param_4 + 0x18) + 4))();
        cVar1 = FUN_004db600(uVar4);
        if (cVar1 == '\0') {
          uVar3 = 0;
        }
        else {
          fVar7 = (float10)FUN_004624f0();
          local_20 = (float)fVar7;
          uVar3 = 0;
          if (local_20 != 0.0) {
            iVar5 = FUN_0045bdf0();
            if ((iVar5 == 0) && (param_4 != param_8)) {
              uVar3 = 0;
            }
            else {
              iVar5 = (**(code **)(*(int *)(*(int *)(local_8 + 0xc) + 0x18) + 4))();
              iVar6 = (**(code **)(*(int *)(param_4 + 0x18) + 4))();
              if (iVar5 != iVar6) {
                local_24 = (**(code **)(*(int *)(param_4 + 0x18) + 0x30))();
                iVar5 = FUN_00417e20(local_24);
                if (iVar5 != 0) {
                  local_28 = param_4;
                  bVar2 = Concurrency::_Order_node_base<enum_Concurrency::agent_status>::has_value
                                    (param_4);
                  if (bVar2) {
                    return 0;
                  }
                }
              }
              FUN_00609380(param_2,param_3,param_4);
              if (param_2[2] <= 0.0001 && param_2[2] != 0.0001) {
                uVar3 = 0;
              }
              else if (*(float *)(local_8 + 0x74) <= param_2[2] &&
                       param_2[2] != *(float *)(local_8 + 0x74)) {
                uVar3 = 0;
              }
              else {
                iVar5 = FUN_00462400();
                local_c = *(float *)(iVar5 + 0xc) * 0.75;
                local_c = local_c * local_c;
                local_10 = *param_2 * *param_2;
                local_14 = param_2[2] * param_2[2] + local_10;
                if ((local_10 <= local_c) || (local_10 <= local_14 * 0.066987)) {
                  *param_1 = 1.0 - (*(float *)(local_8 + 0x74) * *(float *)(local_8 + 0x74)) /
                                   local_14;
                  *param_1 = *param_1 * *param_1;
                  *param_1 = *param_1 * *param_1;
                  *param_1 = *param_1 * *param_1;
                  *param_1 = *param_1 * *param_1;
                  *param_1 = *param_1 * *param_1;
                  local_2c = 0x3f800000;
                  iVar5 = FUN_00784620(*param_7,param_7[1],param_7[2],param_7[3],param_7[4],
                                       param_7[5],*param_3,param_3[1],param_3[2],&local_2c,0);
                  if (iVar5 == 0) {
                    *param_1 = *param_1 + 1.0;
                  }
                  local_18 = (**(code **)(*(int *)(param_4 + 0x18) + 0x30))();
                  iVar5 = FUN_00417e20(local_18);
                  if ((iVar5 == 0) || (iVar5 = FUN_0045bdf0(), iVar5 == 0)) {
                    iVar5 = FUN_00462340(local_18);
                    if (iVar5 != 0) {
                      *param_1 = *param_1 + 1.0;
                    }
                  }
                  else {
                    *param_1 = *param_1 + 2.0;
                  }
                  uVar3 = (uint)(param_6 < *param_1);
                }
                else {
                  uVar3 = 0;
                }
              }
            }
          }
        }
      }
    }
  }
  return uVar3;
}

