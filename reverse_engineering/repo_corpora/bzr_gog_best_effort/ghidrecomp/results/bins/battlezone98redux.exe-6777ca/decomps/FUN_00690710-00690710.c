
undefined4 * __thiscall FUN_00690710(undefined4 param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)FUN_0069d590(param_2 + 0x93,0,param_1);
  if (puVar1 == (undefined4 *)0x0) {
    FUN_006a5fd0("UnassignedCCGet team %d no cc\n",*param_2);
  }
  else {
    FUN_006a5fd0("UnassignedCCGet team %d cc %p\n",*param_2,*puVar1);
  }
  return puVar1;
}

