
undefined4 FUN_007236a6(void)

{
  undefined4 uVar1;
  int unaff_EBP;
  undefined4 uStack_24;
  undefined1 *puStack_20;
  int iStack_1c;
  undefined1 auStack_18 [4];
  undefined4 uStack_14;
  undefined1 *puStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  int iStack_4;
  
  *(undefined4 *)(unaff_EBP + -4) = 0;
  puStack_10 = (undefined1 *)&uStack_c;
  *(undefined4 **)(unaff_EBP + -0xb0) = &uStack_c;
  uStack_14 = 0x7236ca;
  uVar1 = FUN_004bb570();
  *(undefined4 *)(unaff_EBP + -0x44) = uVar1;
  *(undefined4 *)(unaff_EBP + -0xc0) = *(undefined4 *)(unaff_EBP + -0x44);
  *(undefined1 *)(unaff_EBP + -4) = 0xc;
  puStack_10 = (undefined1 *)(unaff_EBP + -0x124);
  uStack_14 = 0x7236e9;
  uVar1 = FUN_004bb540();
  *(undefined4 *)(unaff_EBP + -0x4c) = uVar1;
  *(undefined4 *)(unaff_EBP + -0x54) = *(undefined4 *)(unaff_EBP + -0x4c);
  *(undefined1 *)(unaff_EBP + -4) = 0xd;
  puStack_20 = auStack_18;
  *(undefined1 **)(unaff_EBP + -0xa4) = auStack_18;
  iStack_1c = *(undefined4 *)(unaff_EBP + -0x1c);
  uStack_24 = 0x72370e;
  uVar1 = FID_conflict_operator_();
  *(undefined4 *)(unaff_EBP + -0x5c) = uVar1;
  *(undefined4 *)(unaff_EBP + -0x84) = *(undefined4 *)(unaff_EBP + -0x5c);
  *(undefined1 *)(unaff_EBP + -4) = 0xe;
  iStack_1c = unaff_EBP + -0x10c;
  puStack_20 = (undefined1 *)0x72372d;
  uVar1 = FUN_004bb540();
  *(undefined4 *)(unaff_EBP + -100) = uVar1;
  *(undefined4 *)(unaff_EBP + -0x6c) = *(undefined4 *)(unaff_EBP + -100);
  *(undefined1 *)(unaff_EBP + -4) = 0xf;
  *(undefined4 **)(unaff_EBP + -0x8c) = &uStack_24;
  uVar1 = FID_conflict_operator_(&uStack_24,*(undefined4 *)(unaff_EBP + -0x20));
  *(undefined4 *)(unaff_EBP + -0x94) = uVar1;
  *(undefined1 *)(unaff_EBP + -4) = 0x11;
  uVar1 = FUN_00728820(unaff_EBP + -0xf4);
  *(undefined4 *)(unaff_EBP + -0x9c) = uVar1;
  iStack_4 = 0x72377c;
  FUN_004bb3b0();
  *(undefined1 *)(unaff_EBP + -4) = 0x10;
  iStack_4 = 0x72378b;
  FUN_004bb3b0();
  *(undefined1 *)(unaff_EBP + -4) = 0;
  iStack_4 = 0x72379a;
  FUN_004bb3b0();
  iStack_4 = unaff_EBP + -0x13c;
  uStack_8 = 0x7237a9;
  uVar1 = FUN_004bb540();
  *(undefined4 *)(unaff_EBP + -0x74) = uVar1;
  *(undefined4 *)(unaff_EBP + -0x2c) = *(undefined4 *)(unaff_EBP + -0x74);
  *(undefined1 *)(unaff_EBP + -4) = 0x12;
  iStack_4 = *(undefined4 *)(unaff_EBP + -0x20);
  uStack_8 = *(undefined4 *)(unaff_EBP + 8);
  uStack_c = 0x7237c6;
  FID_conflict_operator_();
  *(uint *)(unaff_EBP + -0x28) = *(uint *)(unaff_EBP + -0x28) | 1;
  *(undefined1 *)(unaff_EBP + -4) = 0;
  iStack_4 = 0x7237de;
  FUN_004bb3b0();
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  iStack_4 = 0x7237ed;
  FUN_004bb3d0();
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return *(undefined4 *)(unaff_EBP + 8);
}

