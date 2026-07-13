
undefined1 FUN_00780e80(uint param_1,uint param_2,undefined4 *param_3,undefined4 *param_4)

{
  undefined1 uVar1;
  ushort uVar2;
  ushort *puVar3;
  undefined4 *puVar4;
  
  puVar3 = (ushort *)FUN_004c0fe0(param_1,param_2);
  uVar2 = *puVar3;
  uVar1 = (&DAT_02c06778)
          [((int)(uVar2 & 0x80) >> 7) +
           (uVar2 & 3) * 2 + ((int)(uVar2 & 0xf00) >> 8) * 8 + ((int)(uVar2 & 0xf000) >> 0xc) * 0x40
          ];
  puVar4 = (undefined4 *)
           (&DAT_02c079d0 +
           (param_1 & 3) * 0x20 + (param_2 & 3) * 0x100 + ((int)(uVar2 & 0xf0) >> 4) * 0x800);
  *param_3 = *puVar4;
  *param_4 = puVar4[1];
  param_3[1] = puVar4[2];
  param_4[1] = puVar4[3];
  param_3[2] = puVar4[4];
  param_4[2] = puVar4[5];
  param_3[3] = puVar4[6];
  param_4[3] = puVar4[7];
  return uVar1;
}

