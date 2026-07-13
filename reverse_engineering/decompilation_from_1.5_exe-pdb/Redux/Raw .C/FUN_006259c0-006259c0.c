
undefined4 *
FUN_006259c0(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined2 uVar1;
  undefined2 uVar2;
  undefined4 local_c;
  
  uVar1 = FUN_00625830(param_2);
  uVar2 = FUN_00625830(param_3);
  local_c = CONCAT22(uVar2,uVar1);
  uVar1 = FUN_00625830(param_4);
  *param_1 = local_c;
  *(undefined2 *)(param_1 + 1) = uVar1;
  return param_1;
}

