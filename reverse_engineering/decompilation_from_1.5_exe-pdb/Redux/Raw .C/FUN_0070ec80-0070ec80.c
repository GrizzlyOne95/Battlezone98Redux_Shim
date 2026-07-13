
void FUN_0070ec80(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  input_processor<wchar_t,class___crt_stdio_input::string_input_adapter<wchar_t>_> local_a4 [80];
  undefined1 local_54 [64];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008579a3;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  FUN_007045e0(param_4);
  local_8 = 0;
  FUN_007124b0(param_1,param_2,param_3,local_54);
  local_8._0_1_ = 1;
  uVar4 = 1;
  uVar3 = 0;
  uVar2 = FUN_004fbb60(0,1,uVar1);
  FUN_00712510(uVar2,uVar3,uVar4);
  local_8 = (uint)local_8._1_3_ << 8;
  __crt_stdio_input::
  input_processor<wchar_t,class___crt_stdio_input::string_input_adapter<wchar_t>_>::
  ~input_processor<wchar_t,class___crt_stdio_input::string_input_adapter<wchar_t>_>(local_a4);
  FUN_00417c60();
  local_8 = 0xffffffff;
  FUN_006ff950();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

