
undefined4 FUN_00821190(undefined4 *param_1)

{
  uint uVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  
  puVar2 = (undefined4 *)FUN_00821aa0();
  *puVar2 = *param_1;
  puVar2[1] = param_1[1];
  puVar2[2] = param_1[2];
  if ((param_1[0x10] & 0x10) == 0) {
    puVar2[3] = param_1[3];
  }
  else {
    puVar2[3] = DAT_02cc1b08;
  }
  puVar2[0xb] = param_1[0xe];
  puVar2[0xc] = 0xffffffff;
  puVar2[0x15] = param_1[0xf];
  puVar2[0x16] = 0xbf800000;
  puVar2[0x17] = param_1[0x10];
  puVar2[0xb] = param_1[0xe];
  uVar3 = DAT_02cc1b18;
  uVar1 = DAT_02cc1b08;
  puVar2[5] = 0x4f;
  if ((puVar2[0x17] & 0x10) == 0) {
    puVar2[4] = (uint)puVar2[3] / uVar1;
  }
  else {
    puVar2[4] = 1;
  }
  puVar2[6] = uVar1;
  puVar2[7] = 0;
  if ((puVar2[0x17] & 8) == 0) {
    puVar2[8] = puVar2[4];
  }
  else {
    puVar2[8] = 0;
  }
  puVar2[9] = 0;
  uVar3 = FUN_00821ad0(puVar2[4] + 5,uVar3);
  puVar2[10] = uVar3;
  memset((void *)puVar2[10],0,(puVar2[4] + 5) * 0x58);
  DAT_02cc1b0c = FUN_00824540(DAT_02cc1b0c,0,puVar2);
  return DAT_02cc1b0c;
}

