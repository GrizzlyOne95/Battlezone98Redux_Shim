
undefined4 FUN_007ef280(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined1 auStack_44 [20];
  undefined4 uStack_30;
  undefined1 *puStack_2c;
  undefined1 auStack_28 [20];
  undefined4 uStack_14;
  undefined4 uStack_10;
  
  FUN_007ee650(&stack0x00000010);
  FUN_007efe00(auStack_44);
  uVar1 = FUN_0042eee0(param_3);
  uVar1 = FUN_0042eee0(param_2,uVar1);
  FUN_007efe20(auStack_28,uVar1);
  puStack_2c = &stack0x00000010;
  uStack_30 = 0x7ef2d2;
  uStack_10 = FUN_007efe70();
  uStack_14 = 0x7ef2de;
  FUN_007ee650();
  return param_1;
}

