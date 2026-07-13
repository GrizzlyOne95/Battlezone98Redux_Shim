
undefined1 FUN_00433730(undefined4 *param_1,undefined4 *param_2)

{
  undefined1 uVar1;
  undefined1 local_28 [12];
  undefined1 local_1c [24];
  
  if (param_1[2] == param_2[2]) {
    FUN_004282e0(*param_2,0);
    FUN_004282e0(*param_1,0);
    uVar1 = FUN_00428770(local_28,local_1c);
  }
  else {
    uVar1 = (int)param_1[2] < (int)param_2[2];
  }
  return uVar1;
}

