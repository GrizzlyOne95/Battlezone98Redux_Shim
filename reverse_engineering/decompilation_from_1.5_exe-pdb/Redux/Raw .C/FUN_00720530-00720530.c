
void __thiscall FUN_00720530(int param_1,undefined4 param_2)

{
  uint uVar1;
  undefined4 *puVar2;
  undefined1 local_64 [8];
  int local_5c;
  undefined1 local_58 [44];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00858b58;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_5c = param_1;
  local_14 = uVar1;
  if (*(int *)(param_1 + 0xa24) != 6) {
    basic_string<>("Call to set_status from invalid state");
    local_8 = 0;
    puVar2 = (undefined4 *)make_error_code(local_64,9,uVar1);
    FUN_006b4ff0(local_2c,*puVar2,puVar2[1]);
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_58,(ThrowInfo *)&DAT_008d8184);
  }
  FUN_006b9910(param_2);
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

