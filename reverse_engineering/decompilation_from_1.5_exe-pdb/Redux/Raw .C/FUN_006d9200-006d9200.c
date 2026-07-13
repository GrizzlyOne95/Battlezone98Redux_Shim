
int FUN_006d9200(void)

{
  short sVar1;
  short sVar2;
  uint uVar3;
  ushort uVar4;
  
  uVar3 = FUN_006b2540();
  sVar1 = (short)((int)(0xe - (uVar3 & 0xffff)) / 0xc);
  sVar2 = FUN_006b2540();
  uVar4 = (sVar2 + 0x12c0) - sVar1;
  sVar2 = FUN_006b2540();
  uVar3 = FUN_006b2540();
  return (((uVar3 & 0xffff) + ((uint)(ushort)(sVar2 + -3 + sVar1 * 0xc) * 0x99 + 2) / 5 +
           (uint)uVar4 * 0x16d + ((int)(uint)uVar4 >> 2)) - uVar4 / 100) + -0x7d2d + uVar4 / 400;
}

