
void FUN_0083a2fd(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  undefined1 local_20 [24];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar1 = *(int *)(param_1 + 0x30);
  uVar2 = *(undefined4 *)(iVar1 + 0x24);
  uVar3 = FUN_00838fac(param_1,"(for generator)",0xf,0);
  FUN_0083abae(param_1,uVar3);
  uVar3 = FUN_00838fac(param_1,"(for state)",0xb,1);
  FUN_0083abae(param_1,uVar3);
  uVar3 = FUN_00838fac(param_1,"(for control)",0xd,2);
  FUN_0083abae(param_1,uVar3);
  FUN_0083abae(param_1,param_2,3);
  iVar6 = 4;
  iVar4 = FUN_0083b6c3(param_1,0x2c);
  while (iVar4 != 0) {
    uVar3 = FUN_0083b57b(param_1,iVar6);
    FUN_0083abae(param_1,uVar3);
    iVar6 = iVar6 + 1;
    iVar4 = FUN_0083b6c3(param_1,0x2c);
  }
  FUN_00839bb2(param_1,0x10b);
  uVar3 = *(undefined4 *)(param_1 + 4);
  uVar5 = FUN_0083a118(param_1,local_20,local_20);
  FUN_0083975c(param_1,3,uVar5);
  FUN_0083c4ff(iVar1,3);
  FUN_0083a220(param_1,uVar2,uVar3,iVar6 + -3,0);
  FUN_0083e885();
  return;
}

