
void FUN_007ae5b0(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  
  uVar1 = FUN_0081cb40("option_box",&DAT_0089e9fc);
  uVar2 = FUN_0081cb40("vehicle_shadows",&DAT_00892b00);
  uVar3 = FUN_0081cb40("vehicle_shadows","medium");
  uVar4 = FUN_0081cb40("vehicle_shadows",&DAT_00892af0);
  uVar5 = FUN_0081cb40("vehicle_shadows","very_high");
  uVar6 = FUN_0081cb40("vehicle_shadows","ultra");
  FUN_007c3ba0();
  if (-2 < DAT_008f0684) {
    FUN_007c3ac0(uVar1,0xffffffff);
  }
  if (-1 < DAT_008f0684) {
    FUN_007c3ac0(uVar2,0);
  }
  if (0 < DAT_008f0684) {
    FUN_007c3ac0(uVar3,1);
  }
  if (1 < DAT_008f0684) {
    FUN_007c3ac0(uVar4,2);
  }
  if (2 < DAT_008f0684) {
    FUN_007c3ac0(uVar5,3);
  }
  if (3 < DAT_008f0684) {
    FUN_007c3ac0(uVar6,4);
  }
  FUN_007c3c10((int)*(char *)(DAT_0094672c + 0x25));
  uVar1 = FUN_0081cb40("detail_level",&DAT_00892af0);
  uVar2 = FUN_0081cb40("detail_level",&DAT_0089f7d4,uVar1);
  uVar3 = FUN_0081cb40("detail_level",&DAT_00892b00,uVar1,uVar2);
  uVar4 = FUN_0081cb40("detail_level","very_low",uVar1,uVar2,uVar3);
  FUN_007c3ba0();
  if (DAT_009455a8 < 4) {
    FUN_007c3ac0(uVar4,3);
  }
  if (DAT_009455a8 < 3) {
    FUN_007c3ac0(uVar3,2);
  }
  if (DAT_009455a8 < 2) {
    FUN_007c3ac0(uVar2,1);
  }
  if (DAT_009455a8 < 1) {
    FUN_007c3ac0(uVar1,0);
  }
  FUN_007c3c10(*(undefined1 *)(DAT_0094672c + 0x27));
  return;
}

