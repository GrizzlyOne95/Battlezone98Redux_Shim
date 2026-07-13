
void FUN_0083a9d0(int param_1)

{
  int *piVar1;
  undefined4 uVar2;
  undefined1 local_38 [24];
  undefined4 local_20 [2];
  int local_18;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  piVar1 = *(int **)(param_1 + 0x30);
  uVar2 = FUN_0083b57b(param_1,0);
  FUN_0083abae(param_1,uVar2);
  local_18 = piVar1[9];
  local_10 = 0xffffffff;
  local_c = 0xffffffff;
  local_20[0] = 6;
  FUN_0083cd31(piVar1,1);
  FUN_008397cc(param_1,1);
  FUN_0083998e(param_1,local_38,0,*(undefined4 *)(param_1 + 4));
  FUN_0083cef1(piVar1,local_20,local_38);
  *(int *)((uint)*(ushort *)((int)piVar1 + (uint)*(byte *)((int)piVar1 + 0x32) * 2 + 0xaa) * 0xc + 4
          + *(int *)(*piVar1 + 0x18)) = piVar1[6];
  FUN_0083e885();
  return;
}

