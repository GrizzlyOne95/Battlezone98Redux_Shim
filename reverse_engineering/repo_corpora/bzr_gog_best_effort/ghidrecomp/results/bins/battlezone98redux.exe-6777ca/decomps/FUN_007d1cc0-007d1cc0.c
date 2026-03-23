
undefined4 * __thiscall
FUN_007d1cc0(undefined4 *param_1,char *param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,
            undefined4 param_9)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00862a92;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_007c5400(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  *param_1 = cUI_View::vftable;
  param_1[5] = param_7;
  *(undefined1 *)(param_1 + 0x3a) = 2;
  *(undefined1 *)((int)param_1 + 0xe9) = 1;
  param_1[0x3b] = param_3;
  param_1[0x3c] = param_4;
  param_1[0x3d] = param_5;
  param_1[0x3e] = param_6;
  param_1[0x3f] = param_9;
  Ogre::ColourValue::ColourValue((ColourValue *)(param_1 + 0x41),1.0,1.0,1.0,1.0);
  Concurrency::details::QuickBitSet::QuickBitSet((QuickBitSet *)(param_1 + 0x45));
  local_8._0_1_ = 1;
  param_1[0x47] = 0;
  param_1[0x48] = 0;
  Concurrency::details::QuickBitSet::QuickBitSet((QuickBitSet *)(param_1 + 0x49));
  local_8._0_1_ = 2;
  vector<>();
  local_8 = CONCAT31(local_8._1_3_,3);
  param_1[0x4e] = 0;
  param_1[0x4f] = param_8;
  param_1[0x50] = 0;
  DAT_009456d4 = DAT_009456d4 + 1;
  strncpy((char *)(param_1 + 8),param_2,200);
  FUN_007d14b0(param_3,param_4,param_5,param_6);
  FUN_0041ff50();
  ExceptionList = local_10;
  return param_1;
}

