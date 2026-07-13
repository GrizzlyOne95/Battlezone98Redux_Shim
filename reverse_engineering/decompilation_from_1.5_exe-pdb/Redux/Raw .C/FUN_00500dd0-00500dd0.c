
void FUN_00500dd0(undefined4 param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  float10 fVar3;
  undefined1 local_98 [12];
  undefined1 local_8c [12];
  undefined1 local_80 [12];
  undefined1 local_74 [12];
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  fVar3 = (float10)FUN_0082c276(param_1,1,0);
  local_5c = (float)fVar3;
  fVar3 = (float10)FUN_0082c276(param_1,2,0);
  local_60 = (float)fVar3;
  fVar3 = (float10)FUN_0082c276(param_1,3,0);
  local_3c = (float)fVar3;
  fVar3 = (float10)FUN_0082c276(param_1,4,0);
  local_64 = (float)fVar3;
  fVar3 = (float10)FUN_0082c276(param_1,5,0);
  local_4c = (float)fVar3;
  fVar3 = (float10)FUN_0082c276(param_1,6,0);
  local_68 = (float)fVar3;
  fVar3 = (float10)FUN_0082c276(param_1,7,0);
  local_44 = (float)fVar3;
  fVar3 = (float10)FUN_0082c276(param_1,8,0);
  local_58 = (float)fVar3;
  fVar3 = (float10)FUN_0082c276(param_1,9,0);
  local_50 = (float)fVar3;
  fVar3 = (float10)FUN_0082c276(param_1,10,0);
  local_48 = (float)fVar3;
  fVar3 = (float10)FUN_0082c276(param_1,0xb,0);
  local_40 = (float)fVar3;
  fVar3 = (float10)FUN_0082c276(param_1,0xc,0);
  local_54 = (float)fVar3;
  puVar1 = (undefined4 *)FUN_00440000(local_74,local_48,local_40,local_54);
  local_14 = *puVar1;
  local_10 = puVar1[1];
  local_c = puVar1[2];
  puVar1 = (undefined4 *)FUN_00440000(local_8c,local_44,local_58,local_50);
  local_20 = *puVar1;
  local_1c = puVar1[1];
  local_18 = puVar1[2];
  puVar1 = (undefined4 *)FUN_00440000(local_80,local_64,local_4c,local_68);
  local_38 = *puVar1;
  local_34 = puVar1[1];
  local_30 = puVar1[2];
  puVar1 = (undefined4 *)FUN_00440000(local_98,local_5c,local_60,local_3c);
  local_2c = *puVar1;
  local_28 = puVar1[1];
  local_24 = puVar1[2];
  uVar2 = FUN_004ff840(param_1,local_2c,local_28,local_24,local_38,local_34,local_30,local_20,
                       local_1c,local_18,local_14,local_10,local_c);
  FUN_004fefc0(uVar2);
  FUN_0083e885();
  return;
}

