
undefined4 __thiscall FUN_006bb8b0(undefined4 param_1,undefined4 param_2)

{
  undefined1 auStack_38 [20];
  undefined4 uStack_24;
  uint uStack_20;
  undefined4 local_1c;
  undefined1 *local_18;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00851368;
  local_10 = ExceptionList;
  uStack_20 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  local_18 = auStack_38;
  local_14 = param_1;
  local_1c = function<>(param_1);
  FUN_00421ec0();
  FUN_006bb260();
  uStack_24 = 0x6bb90a;
  FUN_006ab750();
  local_8 = 0xffffffff;
  uStack_24 = 0x6bb919;
  FUN_006ca8c0();
  ExceptionList = local_10;
  return param_2;
}

