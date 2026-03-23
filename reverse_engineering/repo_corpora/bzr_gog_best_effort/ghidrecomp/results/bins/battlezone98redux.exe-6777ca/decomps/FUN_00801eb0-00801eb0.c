
undefined4
FUN_00801eb0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined1 *param_4)

{
  undefined4 uVar1;
  undefined1 *puVar2;
  undefined1 local_28 [12];
  undefined1 local_1c [8];
  undefined1 local_14 [8];
  undefined1 *local_c;
  undefined1 local_7;
  undefined1 local_6;
  undefined1 local_5;
  
  uVar1 = FUN_007e3040(param_2);
  local_c = (undefined1 *)max_size(uVar1);
  local_5 = 0;
  FUN_007e3060(&local_6,*local_c,*param_4);
  puVar2 = &local_6;
  uVar1 = FUN_007e3090(param_2,param_3,puVar2);
  uVar1 = FUN_007e2fc0(local_14,uVar1,param_3,puVar2);
  uVar1 = FUN_007e2ff0(local_1c,uVar1);
  FUN_00801320(local_28,local_c,uVar1);
  local_7 = 0;
  FUN_00803c30(param_1,local_28,param_4);
  return param_1;
}

