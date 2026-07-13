
void FUN_00575570(undefined4 param_1,int param_2,int param_3)

{
  uint uVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined1 local_80 [4];
  undefined1 local_7c [4];
  undefined1 local_78 [4];
  undefined1 local_74 [4];
  undefined1 local_70 [4];
  undefined1 local_6c [4];
  undefined1 local_68 [4];
  undefined1 local_64 [4];
  undefined1 local_60 [4];
  undefined1 local_5c [4];
  undefined1 local_58 [4];
  undefined1 local_54 [4];
  undefined1 local_50 [4];
  undefined1 local_4c [4];
  undefined1 local_48 [4];
  undefined1 local_44 [4];
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  int local_20;
  undefined1 local_1c;
  undefined1 local_1b;
  undefined1 uStack_1a;
  undefined1 local_19;
  undefined4 local_18;
  undefined1 local_12;
  undefined1 local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084b8ab;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_18 = FUN_00578e00(&param_1);
  FUN_0041ff50(uVar1);
  FUN_00579020(param_3);
  puVar2 = (undefined4 *)FID_conflict_begin(local_44);
  local_28 = *puVar2;
  FUN_0057b140(local_48,local_28,param_2,param_2 + param_3);
  vector<>();
  local_8 = 0;
  FUN_00579020(param_3 + 4);
  local_11 = 0x7a;
  puVar2 = (undefined4 *)FID_conflict_end(local_4c);
  local_2c = *puVar2;
  FUN_00578fd0(local_50,local_2c,&local_11);
  local_12 = 0x75;
  puVar2 = (undefined4 *)FID_conflict_end(local_54);
  local_30 = *puVar2;
  FUN_00578fd0(local_58,local_30,&local_12);
  puVar2 = (undefined4 *)FID_conflict_end(local_5c);
  local_34 = *puVar2;
  FUN_0057b140(local_60,local_34,local_20 + 0x28,local_20 + 0x2a);
  puVar2 = (undefined4 *)FID_conflict_end(local_64);
  local_38 = *puVar2;
  FUN_0057b140(local_68,local_38,&param_1,&param_2);
  local_24 = FUN_004bb390();
  local_1c = (undefined1)((uint)local_24 >> 0x10);
  local_1b = (undefined1)((uint)local_24 >> 8);
  uStack_1a = (undefined1)local_24;
  puVar2 = (undefined4 *)FID_conflict_end(local_6c);
  local_3c = *puVar2;
  FUN_0057b140(local_70,local_3c,&local_1c,&local_19);
  puVar2 = (undefined4 *)FID_conflict_end(local_74);
  local_40 = *puVar2;
  puVar2 = (undefined4 *)FID_conflict_end(local_78);
  uVar3 = *puVar2;
  puVar2 = (undefined4 *)FID_conflict_begin(local_7c);
  FUN_0057b1b0(local_80,local_40,*puVar2,uVar3);
  uVar3 = FUN_004bb390(1,0);
  uVar3 = get(uVar3);
  FUN_00575890(uVar3);
  local_8 = 0xffffffff;
  FUN_00579000();
  ExceptionList = local_10;
  return;
}

