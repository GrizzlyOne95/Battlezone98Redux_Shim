
undefined4 * __thiscall
FUN_007c2480(undefined4 *param_1,undefined4 param_2,float param_3,float param_4,undefined4 param_5,
            undefined4 param_6,undefined4 param_7,undefined4 param_8,float param_9,float param_10)

{
  void *pvVar1;
  uint uVar2;
  undefined4 local_1c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00861de0;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_007d1cc0(param_2,param_3,param_4,param_5,param_6,param_7,param_8,0);
  local_8 = 0;
  *param_1 = cUI_Button::vftable;
  *(undefined1 *)(param_1 + 0x52) = 1;
  *(undefined1 *)((int)param_1 + 0x149) = 0;
  *(undefined1 *)((int)param_1 + 0x14a) = 0;
  *(undefined1 *)((int)param_1 + 0x14b) = 0;
  param_1[0x53] = 0;
  param_1[0x54] = 0;
  param_1[0x55] = 0;
  param_1[0x56] = 0;
  Concurrency::details::QuickBitSet::QuickBitSet((QuickBitSet *)(param_1 + 0x57));
  local_8._0_1_ = 1;
  Concurrency::details::QuickBitSet::QuickBitSet((QuickBitSet *)(param_1 + 0x59));
  local_8._0_1_ = 2;
  pvVar1 = operator_new(0x930);
  local_8._0_1_ = 3;
  if (pvVar1 == (void *)0x0) {
    local_1c = 0;
  }
  else {
    local_1c = FUN_007cc390(param_1 + 8,param_3 + param_9,param_4 + param_10,param_5,param_6,
                            param_1[5] | 0x9000,param_8,param_9);
  }
  local_8 = CONCAT31(local_8._1_3_,2);
  param_1[0x51] = local_1c;
  uVar2 = FUN_007c19b0();
  FUN_007d3f20((uVar2 & 0xff) + 2);
  memset(param_1 + 0x5b,0,0x40);
  memset(param_1 + 0x6b,0,0x40);
  FUN_007c2ff0("cornron.wav");
  FUN_007c2fa0("cornrclk.wav");
  ExceptionList = local_10;
  return param_1;
}

