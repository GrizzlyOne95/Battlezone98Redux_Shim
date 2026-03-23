
undefined4 * __fastcall FUN_007d0fa0(undefined4 *param_1)

{
  void *pvVar1;
  char *pcVar2;
  undefined4 local_4c;
  undefined4 local_44;
  undefined4 local_3c;
  undefined4 local_34;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00862a42;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_007c5400(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  *param_1 = cUI_View::vftable;
  param_1[5] = 1;
  *(undefined1 *)(param_1 + 0x3a) = 0;
  *(undefined1 *)((int)param_1 + 0xe9) = 1;
  param_1[0x3f] = 0;
  Ogre::ColourValue::ColourValue((ColourValue *)(param_1 + 0x41),1.0,1.0,1.0,1.0);
  Concurrency::details::QuickBitSet::QuickBitSet((QuickBitSet *)(param_1 + 0x45));
  local_8._0_1_ = 1;
  param_1[0x47] = 0;
  param_1[0x48] = 0;
  Concurrency::details::QuickBitSet::QuickBitSet((QuickBitSet *)(param_1 + 0x49));
  local_8._0_1_ = 2;
  vector<>();
  local_8._0_1_ = 3;
  param_1[0x4e] = 0;
  param_1[0x4f] = 0;
  param_1[0x50] = 0;
  DAT_009456d4 = DAT_009456d4 + 1;
  pcVar2 = (char *)(param_1 + 8);
  pcVar2[0] = 'T';
  pcVar2[1] = 'o';
  pcVar2[2] = 'p';
  pcVar2[3] = ' ';
  pcVar2 = (char *)(param_1 + 9);
  pcVar2[0] = 'S';
  pcVar2[1] = 'c';
  pcVar2[2] = 'r';
  pcVar2[3] = 'e';
  *(undefined2 *)(param_1 + 10) = 0x6e65;
  *(undefined1 *)((int)param_1 + 0x2a) = 0;
  FUN_007d14b0(0,0,0,0);
  FUN_007d3f20(0);
  FUN_007d2870("bckground_1920x1080.png");
  pvVar1 = operator_new(0x144);
  local_8._0_1_ = 4;
  if (pvVar1 == (void *)0x0) {
    local_34 = 0;
  }
  else {
    local_34 = FUN_007d1cc0("Border_Top",0,0,0x44b40000,0x42880000,0,0,0);
  }
  local_8._0_1_ = 3;
  FUN_007d3f20(1);
  FUN_007d2870("topEdge.png");
  FUN_007d2110(local_34,0);
  pvVar1 = operator_new(0x144);
  local_8._0_1_ = 5;
  if (pvVar1 == (void *)0x0) {
    local_3c = 0;
  }
  else {
    local_3c = FUN_007d1cc0("Border_Bot",0,0x447d0000,0x44b40000,0x42880000,4,0,0);
  }
  local_8._0_1_ = 3;
  FUN_007d3f20(1);
  FUN_007d2870("topEdge.png");
  FUN_007d2110(local_3c,0);
  pvVar1 = operator_new(0x144);
  local_8._0_1_ = 6;
  if (pvVar1 == (void *)0x0) {
    local_44 = 0;
  }
  else {
    local_44 = FUN_007d1cc0("Border_Left",0,0x42880000,0x42540000,0x446c0000,0,0,0);
  }
  local_8._0_1_ = 3;
  FUN_007d3f20(1);
  FUN_007d2870("EdgeBorder.png");
  FUN_007d2110(local_44,0);
  pvVar1 = operator_new(0x144);
  local_8._0_1_ = 7;
  if (pvVar1 == (void *)0x0) {
    local_4c = 0;
  }
  else {
    local_4c = FUN_007d1cc0("Border_Right",0x44ad6000,0x42880000,0x42540000,0x446c0000,2,0,0);
  }
  local_8 = CONCAT31(local_8._1_3_,3);
  FUN_007d3f20(1);
  FUN_007d2870("EdgeBorder.png");
  FUN_007d2110(local_4c,0);
  ExceptionList = local_10;
  return param_1;
}

