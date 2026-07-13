
undefined4
FUN_007ff830(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined1 *param_4)

{
  undefined4 uVar1;
  undefined1 *puVar2;
  undefined1 local_94 [44];
  undefined1 local_68 [40];
  undefined1 local_40 [52];
  undefined1 *local_c;
  undefined1 local_7;
  undefined1 local_6;
  undefined1 local_5;
  
  uVar1 = FUN_007e3040(param_2);
  local_c = (undefined1 *)max_size(uVar1);
  local_7 = 0;
  FUN_007e3060(&local_5,*local_c,*param_4);
  puVar2 = &local_5;
  uVar1 = FUN_007e3090(param_2,param_3,puVar2);
  uVar1 = FUN_008010e0(local_68,uVar1,param_3,puVar2);
  uVar1 = FUN_00801110(local_94,uVar1);
  FUN_00801130(local_40,local_c,uVar1);
  local_6 = 0;
  FUN_00801150(param_1,local_40,param_4);
  return param_1;
}

