
undefined4 * __thiscall
FUN_004cc620(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5)

{
  undefined4 *local_24;
  int local_20;
  int local_1c;
  void *local_18;
  undefined4 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084762c;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *param_1 = param_2;
  param_1[1] = param_3;
  param_1[2] = param_4;
  param_1[3] = param_5;
  local_14 = param_1;
  if (DAT_00917a5c == 0) {
    local_18 = operator_new(8);
    local_8 = 0;
    if (local_18 == (void *)0x0) {
      local_1c = 0;
    }
    else {
      local_1c = vector<>();
    }
    local_20 = local_1c;
    DAT_00917a5c = local_1c;
  }
  local_8 = 0xffffffff;
  local_24 = local_14;
  FUN_00438be0(&local_24);
  ExceptionList = local_10;
  return local_14;
}

