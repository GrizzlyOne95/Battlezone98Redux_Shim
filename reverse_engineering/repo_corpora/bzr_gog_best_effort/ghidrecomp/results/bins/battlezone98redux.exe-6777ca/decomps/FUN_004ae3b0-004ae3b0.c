
void __thiscall FUN_004ae3b0(int param_1,byte *param_2,int *param_3)

{
  uint uVar1;
  CMetaFileDC *this;
  undefined4 uVar2;
  int iVar3;
  int *local_28;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008496ac;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_0049f300((param_2[2] & 0x20) != 0);
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
  *(float *)(param_1 + 500) = (float)param_2[1] / 255.0;
  iVar3 = FUN_0046d060();
  FUN_004a7700((int)((float)iVar3 * *(float *)(param_1 + 500)));
  *(float *)(param_1 + 0x1e8) = (float)*param_2 / 255.0;
  FUN_004a76a0(*(float *)(param_1 + 0x1f0) * *(float *)(param_1 + 0x1e8));
  (**(code **)(*(int *)(param_1 + -0x18) + 0xa4))(*(undefined4 *)(param_1 + 0x1e8));
  if ((param_2[2] & 0x10) != 0) {
    FUN_0062de40(*(undefined4 *)(param_1 + 0xdc),0x280);
    FUN_004b8460();
  }
  if ((param_2[2] & 1) == 0) {
    FUN_0062de80(*(undefined4 *)(param_1 + 0xdc),0x10000000);
  }
  else {
    FUN_0062de40(*(undefined4 *)(param_1 + 0xdc),0x10000000);
  }
  if ((param_2[2] & 2) == 0) {
    FUN_0062de80(*(undefined4 *)(param_1 + 0xdc),0x20000000);
  }
  else {
    FUN_0062de40(*(undefined4 *)(param_1 + 0xdc),0x20000000);
  }
  if ((param_2[2] & 4) == 0) {
    FUN_0062de80(*(undefined4 *)(param_1 + 0xdc),0x40000000);
  }
  else {
    FUN_0062de40(*(undefined4 *)(param_1 + 0xdc),0x40000000);
  }
  if (*(uint *)(param_1 + 0x280) != (uint)param_2[3]) {
    if ((param_2[3] == 0) || (param_2[3] == 3)) {
      FUN_004ae9f0();
    }
    else if ((param_2[3] == 2) || (param_2[3] == 1)) {
      FUN_004ae900();
    }
  }
  *param_3 = *param_3 + -4;
  ExceptionList = local_10;
  return;
}

