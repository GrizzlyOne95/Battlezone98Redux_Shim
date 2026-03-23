
void __thiscall
FUN_007cbd60(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6,uint param_7,undefined4 param_8)

{
  uint uVar1;
  void *pvVar2;
  undefined4 local_80;
  char local_78 [100];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008625c4;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  FUN_007d1cc0(param_2,param_3,param_4,param_5,param_6,param_7 | 0x20,param_8,0);
  local_8 = 0;
  *param_1 = cUI_Slider::vftable;
  *(undefined1 *)(param_1 + 0x51) = 0;
  param_1[0x52] = 0;
  param_1[0x53] = 0x41200000;
  param_1[0x54] = 0;
  *(undefined1 *)(param_1 + 0x55) = 1;
  param_1[0x56] = 0;
  param_1[0x57] = 0;
  param_1[0x58] = 0;
  FUN_007d2870("arrows.png");
  param_1[0x56] = (float)param_1[3] / 9.0;
  _snprintf(local_78,100,"%s_Bar",param_2,uVar1);
  param_1[0x57] = (float)param_1[4] / 5.0;
  pvVar2 = operator_new(0x144);
  local_8._0_1_ = 1;
  if (pvVar2 == (void *)0x0) {
    local_80 = 0;
  }
  else {
    local_80 = FUN_007d1cc0(local_78,(float)param_1[1] + (float)param_1[0x56],
                            ((float)param_1[4] - (float)param_1[0x57]) / 2.0 + (float)param_1[2],
                            (float)param_1[3] - (float)param_1[0x56] * 2.0,param_1[0x57],param_7 | 8
                            ,0,0);
  }
  local_8 = (uint)local_8._1_3_ << 8;
  param_1[0x52] = local_80;
  uVar1 = FUN_007d3ee0();
  FUN_007d3f20((uVar1 & 0xff) + 3);
  FUN_007d2870("kickclk.png");
  FUN_007d2110(param_1[0x52],0);
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

