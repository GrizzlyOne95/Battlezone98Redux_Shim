
undefined4 * __thiscall
FUN_004e6cf0(undefined4 *param_1,undefined4 param_2,int param_3,undefined4 param_4,float param_5)

{
  uint uVar1;
  undefined4 uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00849568;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_004e54c0(param_2,param_4,0);
  local_8 = 0;
  *param_1 = GoNear::vftable;
  if (param_3 == 0) {
    param_1[3] = 0xd;
  }
  else {
    uVar2 = FUN_00477590(param_3,uVar1);
    param_1[5] = uVar2;
    *(undefined1 *)((int)param_1 + 0x13e) = 1;
    param_1[0x53] = param_5 * param_5;
    *(undefined1 *)(param_1 + 0x54) = 0;
    param_1[0x55] = 0;
  }
  ExceptionList = local_10;
  return param_1;
}

