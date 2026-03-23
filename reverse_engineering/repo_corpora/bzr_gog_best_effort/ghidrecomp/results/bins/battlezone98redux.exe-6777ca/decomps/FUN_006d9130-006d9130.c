
undefined4 FUN_006d9130(void)

{
  short sVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  ushort uVar5;
  
  uVar3 = FUN_006b2540();
  sVar1 = (short)((int)(0xe - (uVar3 & 0xffff)) / 0xc);
  sVar2 = FUN_006b2540();
  uVar5 = sVar2 - sVar1;
  sVar2 = FUN_006b2540();
  uVar3 = FUN_006b2540();
  iVar4 = ((uint)(ushort)(sVar2 + -2 + sVar1 * 0xc) * 0x1f) / 0xc +
          (((uVar3 & 0xffff) + (uint)uVar5 + ((int)(uint)uVar5 >> 2)) - uVar5 / 100) + uVar5 / 400;
  return CONCAT22((short)((uint)(iVar4 / 7) >> 0x10),(short)(iVar4 % 7));
}

