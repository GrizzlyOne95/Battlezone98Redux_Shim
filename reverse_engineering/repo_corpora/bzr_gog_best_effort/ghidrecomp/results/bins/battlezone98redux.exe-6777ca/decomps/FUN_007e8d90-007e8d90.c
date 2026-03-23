
bool __thiscall FUN_007e8d90(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  undefined4 uVar2;
  
  uVar2 = FUN_0066eeb0(&param_2,param_1);
  cVar1 = FUN_006dc8e0(uVar2);
  if (cVar1 == '\0') {
    FUN_007ea480(param_2,param_3,0);
  }
  return cVar1 == '\0';
}

