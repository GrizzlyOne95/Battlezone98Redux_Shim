
void FUN_007b1f50(void)

{
  char cVar1;
  char *_Src;
  undefined4 uVar2;
  undefined4 *puVar3;
  char *_Format;
  undefined4 uVar4;
  undefined4 *puVar5;
  undefined1 local_58 [4];
  undefined1 local_54 [4];
  undefined1 local_50 [4];
  undefined1 local_4c [4];
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  int local_1c;
  int local_18 [2];
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00861078;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_007c3ba0(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_24 = FUN_0081cb40("hud_size",&DAT_0089f83c);
  local_2c = FUN_0081cb40("hud_size",&DAT_0089f850);
  local_34 = FUN_0081cb40("hud_size",&DAT_0089f834);
  local_3c = FUN_0081cb40("hud_size",&DAT_0089f830);
  local_44 = FUN_0081cb40("hud_size",&DAT_0089f838);
  _Format = "%d x %d";
  _Src = (char *)FUN_007c3d10("%d x %d",local_18,&local_1c);
  sscanf(_Src,_Format);
  vector<>();
  local_8 = 0;
  FUN_007c3ac0(local_24,0);
  local_28 = 0;
  FUN_0041ff90(&local_28);
  FUN_007c3ac0(local_2c,1);
  local_30 = 1;
  FUN_0041ff90(&local_30);
  if ((0x63f < local_18[0]) && (899 < local_1c)) {
    FUN_007c3ac0(local_34,2);
    local_38 = 2;
    FUN_0041ff90(&local_38);
  }
  if ((0x77f < local_18[0]) && (0x4af < local_1c)) {
    FUN_007c3ac0(local_3c,3);
    local_40 = 3;
    FUN_0041ff90(&local_40);
  }
  if ((0x9ff < local_18[0]) && (0x59f < local_1c)) {
    FUN_007c3ac0(local_44,4);
    local_48 = 4;
    FUN_0041ff90(&local_48);
  }
  local_20 = FUN_007c3cc0();
  uVar2 = FID_conflict_end(local_4c);
  puVar5 = &local_20;
  puVar3 = (undefined4 *)FID_conflict_end(local_50);
  uVar4 = *puVar3;
  puVar3 = (undefined4 *)FID_conflict_begin(local_54);
  FUN_0046e9c0(local_58,*puVar3,uVar4,puVar5,uVar2);
  cVar1 = FID_conflict_operator__(uVar2);
  if (cVar1 == '\0') {
    FUN_007c3c10(local_20);
  }
  else {
    FUN_007c3c10(0);
  }
  local_8 = 0xffffffff;
  FUN_0041fe20();
  ExceptionList = local_10;
  return;
}

