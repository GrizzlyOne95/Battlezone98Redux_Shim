
void FUN_0083a3ff(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  
  iVar1 = *(int *)(param_1 + 0x30);
  uVar2 = *(undefined4 *)(iVar1 + 0x24);
  uVar3 = FUN_00838fac(param_1,"(for index)",0xb,0);
  FUN_0083abae(param_1,uVar3);
  uVar3 = FUN_00838fac(param_1,"(for limit)",0xb,1);
  FUN_0083abae(param_1,uVar3);
  uVar3 = FUN_00838fac(param_1,"(for step)",10,2);
  FUN_0083abae(param_1,uVar3);
  FUN_0083abae(param_1,param_2,3);
  FUN_00839bb2(param_1,0x3d);
  FUN_0083a0d3(param_1);
  FUN_00839bb2(param_1,0x2c);
  FUN_0083a0d3(param_1);
  iVar4 = FUN_0083b6c3(param_1,0x2c);
  if (iVar4 == 0) {
    uVar3 = FUN_0083ca81(iVar1,0x3ff0000000000000);
    FUN_0083c5ff(iVar1,1,*(undefined4 *)(iVar1 + 0x24),uVar3);
    FUN_0083cd31(iVar1,1);
  }
  else {
    FUN_0083a0d3();
  }
  FUN_0083a220(param_1,uVar2,param_3,1,1);
  return;
}

