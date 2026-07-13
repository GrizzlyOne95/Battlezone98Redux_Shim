
void FUN_00818cf0(undefined4 param_1,ushort param_2,undefined1 param_3,undefined1 param_4)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  uint uVar4;
  undefined1 *puVar5;
  undefined1 local_64 [8];
  undefined1 local_5c [4];
  undefined1 local_58 [4];
  undefined1 local_54 [8];
  undefined1 local_4c [4];
  undefined1 local_48 [8];
  undefined4 local_40;
  uint local_3c;
  undefined1 local_38 [4];
  undefined4 local_34;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00864e00;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_3c = 0;
  FUN_00421c40(local_14);
  local_8 = 0;
  FUN_008187a0(local_48,param_3,param_4);
  local_8 = CONCAT31(local_8._1_3_,1);
  puVar2 = (undefined4 *)FUN_00420260(local_58);
  local_34 = *puVar2;
  puVar2 = (undefined4 *)FID_conflict_begin(local_5c);
  local_40 = *puVar2;
  while( true ) {
    cVar1 = FUN_00420f10(&local_40);
    if (cVar1 == '\0') break;
    puVar5 = local_38;
    FUN_00421ea0(puVar5);
    FUN_0041fc00(puVar5);
    puVar5 = local_4c;
    FUN_00421ea0(puVar5);
    FUN_0041fc60(puVar5);
    cVar1 = FID_conflict_operator__(local_4c);
    if (cVar1 != '\0') {
      uVar4 = (uint)param_2;
      uVar3 = FUN_00422220(uVar4);
      uVar3 = FUN_006cb490(uVar3,uVar4);
      FUN_0075f880(local_64,uVar3);
      FUN_006cc780();
    }
    FUN_00422190();
  }
  FUN_00819110(local_54);
  local_3c = local_3c | 1;
  local_8 = local_8 & 0xffffff00;
  FUN_00818cb0();
  local_8 = 0xffffffff;
  FUN_0045c7d0();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

