
int __thiscall
FUN_00703be0(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 *param_5,undefined4 *param_6)

{
  uint uVar1;
  undefined4 uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00856b70;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  FUN_006ac9a0(FUN_00706480);
  local_8 = CONCAT31(local_8._1_3_,1);
  *(undefined4 *)(param_1 + 0x20) = param_2;
  uVar2 = FUN_006d5810(uVar1);
  *(undefined4 *)(param_1 + 0x24) = uVar2;
  shared_ptr<>(&param_3);
  uVar2 = param_5[1];
  *(undefined4 *)(param_1 + 0x30) = *param_5;
  *(undefined4 *)(param_1 + 0x34) = uVar2;
  uVar2 = param_6[1];
  *(undefined4 *)(param_1 + 0x38) = *param_6;
  *(undefined4 *)(param_1 + 0x3c) = uVar2;
  local_8 = 0xffffffff;
  FUN_006c9420();
  ExceptionList = local_10;
  return param_1;
}

