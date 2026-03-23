
undefined4 * __thiscall FUN_006a1820(undefined4 *param_1,int param_2)

{
  undefined4 uVar1;
  undefined4 *_Dst;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084fb48;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_006a0de0(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  *param_1 = BuildAttachment::vftable;
  _Dst = param_1 + 1;
  memset(_Dst,0,0x34);
  param_1[3] = param_2;
  uVar1 = (*(code *)**(undefined4 **)(param_2 + 0x18))();
  uVar1 = FUN_006a12b0(uVar1,0);
  param_1[6] = uVar1;
  uVar1 = (**(code **)(*(int *)(param_2 + 0x18) + 4))();
  *_Dst = uVar1;
  param_1[8] = 0;
  *(undefined1 *)(param_1 + 7) = 0x14;
  FUN_0069fff0(*(undefined2 *)param_1[6],*(undefined1 *)_Dst);
  ExceptionList = local_10;
  return param_1;
}

