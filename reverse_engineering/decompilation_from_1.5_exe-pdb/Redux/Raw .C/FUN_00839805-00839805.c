
void FUN_00839805(int param_1,int param_2,int param_3)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  int local_40 [2];
  int local_38 [6];
  undefined4 local_20 [2];
  int local_18;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  piVar1 = (int *)(param_2 + 8);
  if ((*piVar1 < 6) || (9 < *piVar1)) {
    FUN_008390b7(param_1,"syntax error");
  }
  iVar3 = FUN_0083b6c3(param_1,0x2c);
  if (iVar3 == 0) {
    FUN_00839bb2(param_1,0x3d);
    iVar3 = FUN_0083a118(param_1,local_20);
    if (iVar3 == param_3) {
      FUN_0083ce20(*(undefined4 *)(param_1 + 0x30),local_20);
      FUN_0083cef1(*(undefined4 *)(param_1 + 0x30),piVar1,local_20);
      goto LAB_00839923;
    }
    FUN_0083975c(param_1,param_3,iVar3);
    if (param_3 < iVar3) {
      piVar2 = (int *)(*(int *)(param_1 + 0x30) + 0x24);
      *piVar2 = *piVar2 + (param_3 - iVar3);
    }
  }
  else {
    local_40[0] = param_2;
    FUN_0083ad61(param_1,local_38);
    if (local_38[0] == 6) {
      FUN_00839ad3(param_1,param_2,local_38);
    }
    iVar3 = 200 - (uint)*(ushort *)(*(int *)(param_1 + 0x34) + 0x34);
    if (iVar3 < param_3) {
      FUN_0083a089(*(undefined4 *)(param_1 + 0x30),iVar3,"variables in assignment");
    }
    FUN_00839805(param_1,local_40,param_3 + 1);
  }
  local_10 = 0xffffffff;
  local_18 = *(int *)(*(int *)(param_1 + 0x30) + 0x24) + -1;
  local_c = 0xffffffff;
  local_20[0] = 0xc;
  FUN_0083cef1(*(int *)(param_1 + 0x30),piVar1,local_20);
LAB_00839923:
  FUN_0083e885();
  return;
}

