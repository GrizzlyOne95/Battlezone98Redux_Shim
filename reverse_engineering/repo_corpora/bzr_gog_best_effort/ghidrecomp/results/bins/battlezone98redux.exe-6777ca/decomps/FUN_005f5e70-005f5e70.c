
void __thiscall FUN_005f5e70(int param_1,byte *param_2,int *param_3)

{
  uint uVar1;
  CMetaFileDC *this;
  undefined4 uVar2;
  int iVar3;
  int *local_28;
  int local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084d08c;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  if ((param_2[2] & 0x40) == 0) {
    *(uint *)(*(int *)(param_1 + 0x218) + 0x114) =
         *(uint *)(*(int *)(param_1 + 0x218) + 0x114) & 0xffffefff;
  }
  else {
    *(uint *)(*(int *)(param_1 + 0x218) + 0x114) =
         *(uint *)(*(int *)(param_1 + 0x218) + 0x114) | 0x1000;
  }
  if ((param_2[2] & 0x80) == 0) {
    *(undefined4 *)(param_1 + 0xd4) = 0;
    if (*(int *)(param_1 + 0xe4) != 0) {
      if (*(undefined4 **)(param_1 + 0xe4) != (undefined4 *)0x0) {
        (**(code **)**(undefined4 **)(param_1 + 0xe4))(1,uVar1);
      }
      *(undefined4 *)(param_1 + 0xe4) = 0;
    }
  }
  else {
    *(undefined4 *)(param_1 + 0xd4) = *(undefined4 *)(param_1 + 0xe0);
    if (*(int *)(param_1 + 0xe4) == 0) {
      this = operator_new(0x18);
      local_8 = 0;
      if (this == (CMetaFileDC *)0x0) {
        local_28 = (int *)0x0;
      }
      else {
        local_28 = (int *)CMetaFileDC::CMetaFileDC(this);
      }
      local_8 = 0xffffffff;
      uVar2 = FUN_0045ca50(param_1 + -0x18);
      (**(code **)(*local_28 + 0x18))(uVar2);
    }
  }
  param_2[2] = param_2[2] & 3;
  switch(param_2[2]) {
  case 0:
    local_18 = 3;
    break;
  case 1:
    local_18 = 1;
    break;
  case 2:
    local_18 = 2;
    break;
  case 3:
    local_18 = 0;
  }
  if (*(int *)(param_1 + 0x210) != local_18) {
    switch(*(undefined4 *)(param_1 + 0x210)) {
    case 0:
      if (local_18 != 3) {
        *(undefined4 *)(param_1 + 0x2e8) = 1;
      }
      break;
    case 1:
      if (local_18 == 2) {
        *(undefined4 *)(param_1 + 0x2f0) = 0;
      }
      else {
        *(undefined4 *)(param_1 + 0x2e8) = 1;
      }
      break;
    case 2:
      if (local_18 != 1) {
        *(undefined4 *)(param_1 + 0x2e8) = 1;
      }
      break;
    case 3:
      if (local_18 == 0) {
        *(undefined4 *)(param_1 + 0x2f0) = 0;
      }
      else {
        *(undefined4 *)(param_1 + 0x2e8) = 1;
      }
    }
  }
  *(float *)(param_1 + 0x1e8) = (float)*param_2 / 255.0;
  FUN_004a76a0(*(float *)(param_1 + 0x1f0) * *(float *)(param_1 + 0x1e8));
  (**(code **)(*(int *)(param_1 + -0x18) + 0xa4))(*(undefined4 *)(param_1 + 0x1e8));
  *(float *)(param_1 + 500) = (float)param_2[1] / 255.0;
  iVar3 = FUN_0046d060();
  FUN_004a7700((int)((float)iVar3 * *(float *)(param_1 + 500)));
  *param_3 = *param_3 + -3;
  if (local_18 == 0) {
    FUN_004ef240(param_2 + 3,param_3);
  }
  ExceptionList = local_10;
  return;
}

