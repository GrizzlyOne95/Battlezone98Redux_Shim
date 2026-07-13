
void __thiscall FUN_00480470(int *param_1,float param_2)

{
  undefined4 uVar1;
  int iVar2;
  float10 fVar3;
  float local_54;
  int local_50;
  bool local_49;
  int *local_48;
  double local_44;
  double local_3c;
  double local_34;
  undefined1 local_2c [12];
  undefined8 local_20;
  undefined8 local_18;
  undefined8 local_10;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if ((float)param_1[0x1e] <= param_2 && param_2 != (float)param_1[0x1e]) {
    param_2 = (float)param_1[0x1e];
  }
  param_1[0x1e] = (int)((float)param_1[0x1e] - param_2);
  local_20 = *(double *)(param_1[5] + 0x48);
  local_18 = *(double *)(param_1[5] + 0x50);
  local_10 = *(double *)(param_1[5] + 0x58);
  local_48 = param_1;
  FUN_00785730(local_20,local_10,&local_54,local_2c);
  if (((double)local_54 <= local_18) ||
     (fVar3 = (float10)FUN_004428b0(local_48 + 0xc,local_2c), 0.0 <= (float)fVar3)) {
    iVar2 = FUN_00784620((undefined4)local_20,local_20._4_4_,(undefined4)local_18,local_18._4_4_,
                         (undefined4)local_10,local_10._4_4_,local_48[0xc],local_48[0xd],
                         local_48[0xe],&param_2,local_2c);
    local_49 = iVar2 != 0;
  }
  else {
    local_49 = true;
    param_2 = 0.0;
    local_18 = (double)local_54;
  }
  local_44 = (double)(param_2 * (float)local_48[0xc]) + local_20;
  local_3c = (double)(param_2 * (float)local_48[0xd]) + local_18;
  local_34 = (double)(param_2 * (float)local_48[0xe]) + local_10;
  local_50 = FUN_00480f40();
  *(double *)(local_48[5] + 0x48) = local_44;
  *(double *)(local_48[5] + 0x50) = local_3c;
  *(double *)(local_48[5] + 0x58) = local_34;
  if (local_50 == 0) {
    if (local_49 == false) {
      iVar2 = FUN_0077d560(local_44,local_34);
      if (iVar2 == 0) {
        *(uint *)(local_48[5] + 0x14) = *(uint *)(local_48[5] + 0x14) | 0x200;
      }
      else if (((float)local_48[0x1e] <= 0.0) &&
              (*(uint *)(local_48[5] + 0x14) = *(uint *)(local_48[5] + 0x14) | 0x200,
              *(int *)(local_48[3] + 0x48) != 0)) {
        FUN_004cb7b0(local_48[5] + 0x20,local_48[0x36]);
      }
    }
    else {
      (**(code **)(*local_48 + 0x14))(0,local_2c);
    }
  }
  else {
    uVar1 = FUN_00479f30(local_50,local_2c);
    (**(code **)(*local_48 + 0x14))(uVar1);
  }
  FUN_0083e885();
  return;
}

