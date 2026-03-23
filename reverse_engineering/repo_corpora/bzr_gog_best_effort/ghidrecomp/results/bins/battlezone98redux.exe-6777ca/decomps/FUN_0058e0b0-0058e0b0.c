
void FUN_0058e0b0(undefined4 *param_1,undefined4 *param_2,int param_3)

{
  float fVar1;
  undefined4 uVar2;
  float10 fVar3;
  float local_28;
  int local_24;
  float local_20;
  undefined4 local_1c;
  undefined4 *local_18;
  undefined4 local_14;
  float local_10;
  undefined4 local_c;
  undefined4 *local_8;
  
  local_24 = 0;
  if (param_3 == DAT_0091815c) {
    local_24 = param_3;
    param_3 = DAT_02a13c74;
  }
  local_18 = param_1;
  local_8 = param_2;
  uVar2 = FUN_0058e040(param_2,param_1);
  local_14 = 0;
  local_1c = 0;
  switch(uVar2) {
  case 0:
    FUN_0058dd20(*(undefined4 *)(param_3 + 0x24),*(undefined4 *)(param_3 + 0x28),param_1[9],
                 param_1[10],*local_8,local_8[1],*local_8,local_8[3],&local_1c,&local_14);
    break;
  case 1:
    FUN_0058dd20(*(undefined4 *)(param_3 + 0x24),*(undefined4 *)(param_3 + 0x28),param_1[9],
                 param_1[10],*local_8,local_8[1],local_8[2],local_8[1],&local_1c,&local_14);
    break;
  case 2:
    FUN_0058dd20(*(undefined4 *)(param_3 + 0x24),*(undefined4 *)(param_3 + 0x28),param_1[9],
                 param_1[10],local_8[2],local_8[1],local_8[2],local_8[3],&local_1c,&local_14);
    break;
  case 3:
    FUN_0058dd20(*(undefined4 *)(param_3 + 0x24),*(undefined4 *)(param_3 + 0x28),param_1[9],
                 param_1[10],*local_8,local_8[3],local_8[2],local_8[3],&local_1c,&local_14);
  }
  local_c = 0;
  local_20 = 0.0;
  local_28 = 0.0;
  switch(uVar2) {
  case 0:
  case 2:
    fVar3 = (float10)FUN_0044fb20(local_8[1],local_18[1]);
    local_28 = (float)fVar3;
    fVar3 = (float10)FUN_0047b6f0(local_8[3],local_18[3]);
    local_20 = (float)fVar3;
    local_c = local_14;
    break;
  case 1:
  case 3:
    fVar3 = (float10)FUN_0044fb20(*local_8,*local_18);
    local_28 = (float)fVar3;
    fVar3 = (float10)FUN_0047b6f0(local_8[2],local_18[2]);
    local_20 = (float)fVar3;
    local_c = local_1c;
  }
  if (local_20 - local_28 < 3.0) {
    if (local_20 - local_28 < 2.0) {
      local_10 = 0.5;
    }
    else {
      local_10 = 1.0;
    }
  }
  else {
    local_10 = 1.5;
  }
  fVar3 = (float10)FUN_00447ed0(local_c,local_28 + local_10,local_20 - local_10);
  fVar1 = (float)fVar3;
  switch(uVar2) {
  case 0:
  case 2:
    param_2[10] = fVar1;
    if (local_24 != 0) {
      *(float *)(local_24 + 0x28) = fVar1;
    }
    break;
  case 1:
  case 3:
    param_2[9] = fVar1;
    if (local_24 != 0) {
      *(float *)(local_24 + 0x24) = fVar1;
    }
  }
  return;
}

