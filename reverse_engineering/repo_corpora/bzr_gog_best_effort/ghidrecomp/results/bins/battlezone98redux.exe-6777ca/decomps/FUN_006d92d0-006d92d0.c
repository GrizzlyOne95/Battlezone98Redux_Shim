
undefined4 FUN_006d92d0(undefined4 param_1,int param_2)

{
  undefined2 uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  
  uVar2 = ((param_2 + 0x7d2c) * 4 + 3U) / 0x23ab1;
  iVar3 = (param_2 + 0x7d2c) - (uVar2 * 0x23ab1 >> 2);
  uVar4 = (iVar3 * 4 + 3U) / 0x5b5;
  iVar3 = iVar3 - (uVar4 * 0x5b5 >> 2);
  uVar5 = (iVar3 * 5 + 2U) / 0x99;
  FUN_006b25f0(uVar2 * 100 + uVar4 + -0x12c0 + uVar5 / 10);
  uVar8 = extraout_ECX;
  FUN_006b2520(((short)iVar3 - (short)((ulonglong)(uVar5 * 0x99 + 2) / 5)) + 1);
  uVar7 = extraout_ECX_00;
  FUN_006b26a0((short)uVar5 + 3 + (short)((ulonglong)uVar5 / 10) * -0xc);
  uVar1 = FUN_006b2540(uVar7,uVar8);
  uVar6 = extraout_ECX_01;
  FUN_006b25f0(uVar1);
  FUN_006d9100(uVar6,uVar7,uVar8);
  return param_1;
}

