
void FUN_00772860(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,byte param_7)

{
  int iVar1;
  undefined4 *puVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined1 local_48 [8];
  undefined1 local_40 [8];
  undefined1 local_38 [8];
  undefined1 local_30 [8];
  undefined1 local_28 [8];
  undefined1 local_20 [8];
  undefined1 local_18 [8];
  undefined1 local_10 [8];
  int local_8;
  
  iVar1 = FUN_00732ef0(&param_1);
  if (iVar1 < 0x29) {
    FUN_007730c0(param_1,param_2,param_3,param_4,param_5,param_6,param_7);
  }
  else {
    iVar1 = FUN_00732ef0(&param_1);
    local_8 = (int)(iVar1 + 1 + (iVar1 + 1 >> 0x1f & 7U)) >> 3;
    uVar3 = (uint)param_7;
    puVar2 = (undefined4 *)FUN_00732eb0(local_10,local_8 << 1);
    uVar7 = puVar2[1];
    uVar5 = *puVar2;
    puVar2 = (undefined4 *)FUN_00732eb0(local_18,local_8);
    FUN_007730c0(param_1,param_2,*puVar2,puVar2[1],uVar5,uVar7,uVar3);
    uVar3 = (uint)param_7;
    puVar2 = (undefined4 *)FUN_00732eb0(local_20,local_8);
    uVar7 = puVar2[1];
    uVar5 = *puVar2;
    uVar4 = param_3;
    uVar6 = param_4;
    puVar2 = (undefined4 *)FUN_007721c0(local_28,local_8);
    FUN_007730c0(*puVar2,puVar2[1],uVar4,uVar6,uVar5,uVar7,uVar3);
    uVar3 = (uint)param_7;
    uVar4 = param_5;
    uVar6 = param_6;
    puVar2 = (undefined4 *)FUN_007721c0(local_30,local_8);
    uVar7 = puVar2[1];
    uVar5 = *puVar2;
    puVar2 = (undefined4 *)FUN_007721c0(local_38,local_8 << 1);
    FUN_007730c0(*puVar2,puVar2[1],uVar5,uVar7,uVar4,uVar6,uVar3);
    uVar3 = (uint)param_7;
    puVar2 = (undefined4 *)FUN_007721c0(local_40,local_8);
    uVar7 = puVar2[1];
    uVar5 = *puVar2;
    uVar4 = param_3;
    uVar6 = param_4;
    puVar2 = (undefined4 *)FUN_00732eb0(local_48,local_8);
    FUN_007730c0(*puVar2,puVar2[1],uVar4,uVar6,uVar5,uVar7,uVar3);
  }
  return;
}

