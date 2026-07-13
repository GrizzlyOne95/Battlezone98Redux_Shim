
void __thiscall FUN_007517a0(undefined4 param_1,char param_2,undefined4 param_3,undefined4 param_4)

{
  int *piVar1;
  undefined8 uVar2;
  undefined4 local_c;
  
  FUN_007427f0(param_2,param_3,param_4);
  if (param_2 == '\0') {
    local_c = 2;
  }
  else {
    local_c = 1;
  }
  piVar1 = (int *)FUN_007508c0();
  uVar2 = (**(code **)(*piVar1 + 0x34))(local_c,8);
  FUN_00752250(uVar2,param_1,FUN_00750f30);
  return;
}

