
undefined4 FUN_007fa670(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined1 local_c [8];
  
  uVar1 = FUN_006d0d10();
  uVar2 = select_on_container_copy_construction(local_c,param_2,uVar1);
  uVar1 = FUN_007d9fe0(uVar2,uVar1);
  FUN_007dac70(param_1,uVar1);
  return param_1;
}

