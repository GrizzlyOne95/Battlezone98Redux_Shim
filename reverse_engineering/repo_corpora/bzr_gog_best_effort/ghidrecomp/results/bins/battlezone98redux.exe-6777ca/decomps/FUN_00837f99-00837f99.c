
void FUN_00837f99(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  uVar1 = FUN_0082d377(param_1,0xffffffff,0);
  uVar1 = FUN_0082d377(param_1,1,0,param_2,uVar1);
  FUN_0082bc39(param_1,"error loading module \'%s\' from file \'%s\':\n\t%s",uVar1);
  return;
}

