
undefined4 * __thiscall FUN_006de390(undefined4 *param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined1 local_10 [8];
  undefined4 *local_8;
  
  *param_1 = 0;
  param_1[1] = 0;
  local_8 = param_1;
  puVar2 = (undefined4 *)make_error_code(local_10,param_2);
  uVar1 = puVar2[1];
  *local_8 = *puVar2;
  local_8[1] = uVar1;
  return local_8;
}

