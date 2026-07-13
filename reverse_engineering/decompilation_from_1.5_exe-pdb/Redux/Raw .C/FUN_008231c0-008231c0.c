
undefined4 FUN_008231c0(undefined4 *param_1)

{
  undefined4 *puVar1;
  uint uVar2;
  undefined4 uVar3;
  ushort in_FPUControlWord;
  float10 fVar4;
  undefined4 uVar5;
  longlong lVar6;
  float fVar7;
  
  puVar1 = (undefined4 *)FUN_00824230();
  *puVar1 = *param_1;
  puVar1[1] = param_1[1];
  puVar1[2] = param_1[2];
  puVar1[0x48] = param_1[0xf] | 0x200;
  puVar1[0x47] = param_1[0xe];
  puVar1[0x49] = param_1[0x10];
  puVar1[0x4a] = param_1[0x11];
  fVar4 = (float10)FUN_00689a70(DAT_0091552c);
  uVar2 = in_FPUControlWord | 0xc00;
  lVar6 = (longlong)ROUND(fVar4);
  uVar5 = (undefined4)lVar6;
  puVar1[3] = uVar5;
  fVar4 = (float10)FUN_00689a20(DAT_0091552c,0x57);
  fVar7 = (float)fVar4;
  uVar3 = FUN_008445c0();
  puVar1[0x40] = uVar5;
  puVar1[0x41] = 0xef;
  memset(puVar1 + 4,0,0xf0);
  puVar1[0x46] = 0;
  puVar1[0x45] = 0;
  puVar1[0x44] = 0;
  puVar1[0x43] = 0;
  puVar1[0x42] = 0;
  DAT_02cc1b40 = FUN_00824540(DAT_02cc1b40,0,puVar1,lVar6,uVar3,fVar7,uVar2);
  return DAT_02cc1b40;
}

