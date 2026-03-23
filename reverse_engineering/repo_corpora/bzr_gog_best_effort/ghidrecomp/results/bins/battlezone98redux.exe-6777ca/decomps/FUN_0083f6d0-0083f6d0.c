
void __thiscall FUN_0083f6d0(undefined4 *param_1,int param_2,int param_3)

{
  int *piVar1;
  undefined4 *puVar2;
  undefined4 ****ppppuVar3;
  undefined4 *local_2c;
  undefined4 ***local_28 [4];
  int local_18;
  uint local_14;
  uint local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_00865500;
  local_c = ExceptionList;
  local_10 = DAT_008e7000 ^ (uint)&local_2c;
  ExceptionList = &local_c;
  param_1[5] = 7;
  param_1[4] = 0;
  *(undefined2 *)param_1 = 0;
  local_4 = 0;
  local_2c = param_1;
  if (param_2 != param_3) {
    local_14 = 7;
    local_18 = 0;
    local_28[0] = (undefined4 ***)((uint)local_28[0] & 0xffff0000);
    FUN_0083fdc0(param_2,param_3 - param_2 >> 1);
    ppppuVar3 = local_28;
    if (7 < local_14) {
      ppppuVar3 = (undefined4 ****)local_28[0];
    }
    local_4 = CONCAT31(local_4._1_3_,1);
    puVar2 = param_1;
    if (7 < (uint)param_1[5]) {
      puVar2 = (undefined4 *)*param_1;
    }
    piVar1 = param_1 + 4;
    if (7 < (uint)param_1[5]) {
      param_1 = (undefined4 *)*param_1;
    }
    FUN_008412a0(*piVar1 * 2 + (int)param_1,(undefined2 *)((int)puVar2 + *piVar1 * 2),ppppuVar3,
                 (int)ppppuVar3 + local_18 * 2);
    if (7 < local_14) {
      operator_delete(local_28[0]);
    }
  }
  ExceptionList = local_c;
  FUN_0083e885();
  return;
}

