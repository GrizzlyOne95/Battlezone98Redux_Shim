
uint __thiscall FUN_0049d0e0(int param_1,uint param_2)

{
  undefined4 uVar1;
  uint uVar2;
  
  if (param_2 < 0x1b) {
    uVar2 = FUN_005aeab0(param_2);
  }
  else {
    FUN_004dbf90(0x15,param_2,0);
    *(uint *)(param_1 + 0x370) = param_2;
    uVar1 = FUN_00472370(param_2);
    uVar2 = FUN_004723b0(uVar1);
    uVar2 = uVar2 & 0xffffff00;
  }
  return uVar2;
}

