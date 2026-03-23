
undefined4 * __thiscall
FUN_007c3150(undefined4 *param_1,undefined4 param_2,float param_3,undefined4 param_4,float param_5,
            undefined4 param_6,uint param_7,undefined4 param_8)

{
  uint uVar1;
  void *pvVar2;
  undefined4 local_1c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00861e7e;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_007d1cc0(param_2,param_3,param_4,param_5,param_6,param_7 | 0x20,param_8,0);
  local_8 = 0;
  *param_1 = cUI_Checklist::vftable;
  *(undefined1 *)(param_1 + 0x51) = 0;
  *(undefined1 *)((int)param_1 + 0x145) = 0;
  Concurrency::details::QuickBitSet::QuickBitSet((QuickBitSet *)(param_1 + 0x52));
  local_8._0_1_ = 1;
  Concurrency::details::QuickBitSet::QuickBitSet((QuickBitSet *)(param_1 + 0x54));
  local_8._0_1_ = 2;
  param_1[0x76] = 0;
  param_1[0x77] = 0;
  *(undefined1 *)(param_1 + 0x78) = 1;
  vector<>(uVar1);
  local_8._0_1_ = 3;
  pvVar2 = operator_new(0x930);
  local_8._0_1_ = 4;
  if (pvVar2 == (void *)0x0) {
    local_1c = 0;
  }
  else {
    local_1c = FUN_007cc390(param_2,param_3 + param_5,param_4,param_5,param_6,param_7 | 0x8000,
                            param_8,0);
  }
  local_8 = CONCAT31(local_8._1_3_,3);
  param_1[0x7c] = local_1c;
  memset(param_1 + 0x56,0,0x40);
  memset(param_1 + 0x66,0,0x40);
  FUN_007d2870("optnoff.png");
  FUN_007c3900("optnclick.png");
  FUN_007c3990("optnon.png");
  FUN_007c3a20("cfigclk.wav");
  FUN_007c3a70("cfigon.wav");
  (**(code **)(*(int *)param_1[0x7c] + 0x28))((float)param_1[1] + (float)param_1[3],0xbf800000,1);
  ExceptionList = local_10;
  return param_1;
}

