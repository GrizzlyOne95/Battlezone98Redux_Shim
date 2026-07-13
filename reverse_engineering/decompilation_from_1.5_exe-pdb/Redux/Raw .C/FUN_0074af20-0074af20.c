
undefined4 *
FUN_0074af20(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  undefined4 uVar2;
  byte *pbVar3;
  undefined4 *puVar4;
  uint uVar5;
  undefined4 uVar6;
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  undefined1 local_10 [8];
  undefined1 local_8;
  undefined1 local_7;
  byte local_6;
  byte local_5;
  
  FID_conflict__Make_iter(local_10,param_2);
  uVar2 = FUN_0042d8c0(local_14);
  cVar1 = FUN_004221b0(uVar2);
  if (cVar1 == '\0') {
    FUN_0044f170();
    pbVar3 = (byte *)_Iter_cat<>(&local_8,&param_3);
    local_6 = *pbVar3;
    uVar5 = (uint)local_6;
    uVar2 = param_3;
    uVar6 = param_4;
    puVar4 = (undefined4 *)FUN_00461400(local_1c);
    FUN_0074b1b0(*puVar4,uVar2,uVar6,uVar5);
    puVar4 = (undefined4 *)FUN_0042da80();
    *param_1 = *puVar4;
  }
  else {
    pbVar3 = (byte *)_Iter_cat<>(&local_7,&param_3);
    local_5 = *pbVar3;
    uVar5 = (uint)local_5;
    uVar2 = param_3;
    uVar6 = param_4;
    puVar4 = (undefined4 *)FUN_00461400(local_18);
    FUN_0074b1b0(*puVar4,uVar2,uVar6,uVar5);
    FUN_0042d8c0(param_1);
  }
  return param_1;
}

