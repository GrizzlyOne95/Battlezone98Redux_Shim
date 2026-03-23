
undefined4 FUN_00729476(void)

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
  *(undefined4 **)(unaff_EBP + -0xa4) = &uStack_c;
  uStack_14 = 0x72949a;
  uVar1 = FUN_004bb570();
  *(undefined4 *)(unaff_EBP + -0x38) = uVar1;
  *(undefined4 *)(unaff_EBP + -0xb4) = *(undefined4 *)(unaff_EBP + -0x38);
  *(undefined1 *)(unaff_EBP + -4) = 0xc;
  puStack_10 = (undefined1 *)(unaff_EBP + -0x118);
  uStack_14 = 0x7294b9;
  uVar1 = FUN_004bb540();
  *(undefined4 *)(unaff_EBP + -0x40) = uVar1;
  *(undefined4 *)(unaff_EBP + -0x48) = *(undefined4 *)(unaff_EBP + -0x40);
  *(undefined1 *)(unaff_EBP + -4) = 0xd;
  puStack_20 = auStack_18;
  *(undefined1 **)(unaff_EBP + -0x98) = auStack_18;
  iStack_1c = *(undefined4 *)(unaff_EBP + -0x1c);
  uStack_24 = 0x7294de;
  uVar1 = FID_conflict_operator_();
  *(undefined4 *)(unaff_EBP + -0x50) = uVar1;
  *(undefined4 *)(unaff_EBP + -0x78) = *(undefined4 *)(unaff_EBP + -0x50);
  *(undefined1 *)(unaff_EBP + -4) = 0xe;
  iStack_1c = unaff_EBP + -0x100;
  puStack_20 = (undefined1 *)0x7294fa;
  uVar1 = FUN_004bb540();
  *(undefined4 *)(unaff_EBP + -0x58) = uVar1;
  *(undefined4 *)(unaff_EBP + -0x60) = *(undefined4 *)(unaff_EBP + -0x58);
  *(undefined1 *)(unaff_EBP + -4) = 0xf;
  *(undefined4 **)(unaff_EBP + -0x80) = &uStack_24;
  uVar1 = FID_conflict_operator_(&uStack_24,*(undefined4 *)(unaff_EBP + -0x18));
  *(undefined4 *)(unaff_EBP + -0x88) = uVar1;
  *(undefined1 *)(unaff_EBP + -4) = 0x11;
  uVar1 = FUN_00728820(unaff_EBP + -0xe8);
  *(undefined4 *)(unaff_EBP + -0x90) = uVar1;
  iStack_4 = 0x729546;
  FUN_004bb3b0();
  *(undefined1 *)(unaff_EBP + -4) = 0x10;
  iStack_4 = 0x729555;
  FUN_004bb3b0();
  *(undefined1 *)(unaff_EBP + -4) = 0;
  iStack_4 = 0x729564;
  FUN_004bb3b0();
  iStack_4 = unaff_EBP + -0x130;
  uStack_8 = 0x729573;
  uVar1 = FUN_004bb540();
  *(undefined4 *)(unaff_EBP + -0x68) = uVar1;
  *(undefined4 *)(unaff_EBP + -0x70) = *(undefined4 *)(unaff_EBP + -0x68);
  *(undefined1 *)(unaff_EBP + -4) = 0x12;
  iStack_4 = *(undefined4 *)(unaff_EBP + -0x18);
  uStack_8 = *(undefined4 *)(unaff_EBP + 8);
  uStack_c = 0x729590;
  FID_conflict_operator_();
  *(uint *)(unaff_EBP + -0x24) = *(uint *)(unaff_EBP + -0x24) | 1;
  *(undefined1 *)(unaff_EBP + -4) = 0;
  iStack_4 = 0x7295a8;
  FUN_004bb3b0();
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  iStack_4 = 0x7295b7;
  FUN_004bb3d0();
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return *(undefined4 *)(unaff_EBP + 8);
}

