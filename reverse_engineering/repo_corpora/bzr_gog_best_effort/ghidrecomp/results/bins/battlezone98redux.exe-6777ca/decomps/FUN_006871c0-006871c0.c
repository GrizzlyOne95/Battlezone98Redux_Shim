
void FUN_006871c0(undefined4 param_1,undefined4 param_2,uint param_3,undefined4 param_4,
                 undefined4 param_5,uint param_6,undefined4 param_7)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  short *psVar4;
  
  FUN_0067a110(2,2);
  uVar1 = FUN_00684c10();
  puVar2 = (undefined4 *)FUN_0067a150(2);
  puVar3 = (undefined4 *)FUN_00446360(param_1,param_2,param_3 ^ 0x80000000,param_7,0,0);
  *puVar2 = *puVar3;
  puVar2[1] = puVar3[1];
  puVar2[2] = puVar3[2];
  puVar2[3] = puVar3[3];
  puVar2[4] = puVar3[4];
  puVar2[5] = puVar3[5];
  puVar2 = puVar2 + 6;
  puVar3 = (undefined4 *)FUN_00446360(param_4,param_5,param_6 ^ 0x80000000,param_7,0,0);
  *puVar2 = *puVar3;
  puVar2[1] = puVar3[1];
  puVar2[2] = puVar3[2];
  puVar2[3] = puVar3[3];
  puVar2[4] = puVar3[4];
  puVar2[5] = puVar3[5];
  puVar2 = puVar2 + 6;
  psVar4 = (short *)FUN_0067a1e0(2);
  *psVar4 = (short)uVar1;
  psVar4[1] = (short)uVar1 + 1;
  FUN_0083e885(uVar1,puVar2,psVar4 + 2);
  return;
}

