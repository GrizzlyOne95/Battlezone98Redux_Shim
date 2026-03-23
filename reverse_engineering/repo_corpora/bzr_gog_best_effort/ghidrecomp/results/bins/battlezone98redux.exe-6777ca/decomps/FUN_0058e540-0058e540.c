
int FUN_0058e540(float *param_1,int param_2)

{
  float fVar1;
  int iVar2;
  int iVar3;
  float local_28;
  float local_24;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  
  fVar1 = param_1[0xc];
  iVar2 = FUN_0058e040(param_1,param_2);
  iVar3 = FUN_0058e040(param_1,fVar1);
  if (iVar3 == iVar2) {
    local_28 = param_1[9];
    local_24 = param_1[10];
    local_18 = *(float *)(param_2 + 0x24);
    local_14 = *(float *)(param_2 + 0x28);
    local_c = 0.0;
    local_10 = 0.0;
    switch(iVar2) {
    case 0:
    case 2:
      if (param_1[2] - *param_1 < 3.0) {
        if (param_1[2] - *param_1 < 2.0) {
          local_10 = 0.5;
        }
        else {
          local_10 = 1.0;
        }
      }
      else {
        local_10 = 1.5;
      }
      break;
    case 1:
    case 3:
      if (param_1[3] - param_1[1] < 3.0) {
        if (param_1[3] - param_1[1] < 2.0) {
          local_c = 0.5;
        }
        else {
          local_c = 1.0;
        }
      }
      else {
        local_c = 1.5;
      }
    }
    switch(iVar2) {
    case 0:
      local_28 = *param_1 + local_10;
      local_18 = local_28;
      break;
    case 1:
      local_24 = param_1[1] + local_c;
      local_14 = local_24;
      break;
    case 2:
      local_28 = param_1[2] - local_10;
      local_18 = local_28;
      break;
    case 3:
      local_24 = param_1[3] - local_c;
      local_14 = local_24;
    }
    iVar2 = FUN_0058dbb0(local_28,local_24,param_1);
    DAT_02a13c74 = FUN_0058dbb0(local_18,local_14,param_1);
    *(int *)(param_2 + 0x30) = DAT_02a13c74;
    *(int *)(DAT_02a13c74 + 0x30) = iVar2;
    *(float **)(iVar2 + 0x30) = param_1;
    param_2 = iVar2;
    DAT_0091815c = iVar2;
  }
  return param_2;
}

