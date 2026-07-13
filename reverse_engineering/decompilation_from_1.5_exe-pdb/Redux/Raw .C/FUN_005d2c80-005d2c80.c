
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_005d2c80(undefined4 *param_1,undefined4 *param_2)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = DAT_009182e8;
  DAT_009182ac = 0;
  piVar2 = (int *)(DAT_009182e8 + 0x10);
  FUN_005d2c00(*piVar2 + _DAT_00918308,*(undefined4 *)(DAT_009182e8 + 0x14));
  FUN_005d2c00(*piVar2,*(int *)(iVar1 + 0x14) + _DAT_009182f0);
  FUN_005d2c00(*piVar2 + _DAT_00918308,*(int *)(iVar1 + 0x14) + _DAT_009182f0);
  *param_1 = DAT_009182ac;
  *param_2 = &DAT_009182b0;
  return;
}

