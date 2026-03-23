
void FUN_007fb090(undefined4 param_1,int param_2)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 *puVar4;
  undefined1 *puVar5;
  undefined1 local_280 [4];
  undefined1 local_27c [6];
  char local_276;
  char local_275;
  undefined1 local_274 [512];
  undefined1 local_74 [96];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008641b3;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_007fb340(local_14);
  local_8 = 0;
  FUN_007fb4d0(param_2);
  local_8 = CONCAT31(local_8._1_3_,1);
  puVar5 = local_74;
  puVar4 = local_274;
  puVar1 = (undefined4 *)FUN_004fee40(local_27c);
  uVar3 = *puVar1;
  uVar2 = FID_conflict_begin(local_280);
  local_275 = FUN_007fc280(uVar2,uVar3,puVar4,puVar5,param_1);
  if (local_275 != '\0') {
    FUN_007bb040();
    FUN_0041f830();
    *(undefined4 *)(param_2 + 0x18) = 0;
  }
  local_276 = local_275;
  local_8 = local_8 & 0xffffff00;
  FUN_007fb190();
  local_8 = 0xffffffff;
  FUN_007d7860();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

