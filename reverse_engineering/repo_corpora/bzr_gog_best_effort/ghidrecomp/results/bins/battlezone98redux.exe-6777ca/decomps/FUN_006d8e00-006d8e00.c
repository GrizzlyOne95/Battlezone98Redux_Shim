
undefined4 * FUN_006d8e00(undefined4 param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined1 local_10 [8];
  undefined4 *local_8;
  
  puVar2 = (undefined4 *)make_error_code(local_10,param_1);
  uVar1 = puVar2[1];
  *local_8 = *puVar2;
  local_8[1] = uVar1;
  return local_8;
}

