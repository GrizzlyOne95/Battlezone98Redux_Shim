
int __thiscall FUN_00449910(int param_1,int param_2)

{
  uint uVar1;
  undefined1 local_20 [8];
  int local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008462a8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_18 = param_1;
  if (*(int *)(param_1 + 4) != *(int *)(param_2 + 4)) {
    local_14 = param_1;
    FUN_004498d0(param_2);
    local_8 = 0;
    Swap(local_20);
    local_18 = local_14;
    local_8 = 0xffffffff;
    FUN_004499a0(uVar1);
  }
  ExceptionList = local_10;
  return local_18;
}

