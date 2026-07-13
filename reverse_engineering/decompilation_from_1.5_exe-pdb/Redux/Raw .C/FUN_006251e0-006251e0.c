
uint __thiscall
FUN_006251e0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  
  uVar1 = FUN_00625160(param_2,param_3,param_4,param_1);
  return -((int)uVar1 >> ((byte)param_4 - 1 & 0x1f) & 1U) << ((byte)param_4 & 0x1f) | uVar1;
}

