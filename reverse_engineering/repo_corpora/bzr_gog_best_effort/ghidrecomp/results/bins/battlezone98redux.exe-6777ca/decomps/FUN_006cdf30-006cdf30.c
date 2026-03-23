
void __thiscall FUN_006cdf30(ushort *param_1,ushort param_2)

{
  ushort uVar1;
  uint uVar2;
  
  uVar2 = FUN_006cdf20();
  if (param_2 + 1 < (uVar2 & 0xffff) + 1) {
    FUN_006d1b70(*param_1,param_2,0);
  }
  else {
    uVar1 = FUN_006d1b60();
    if (uVar1 < param_2) {
      FUN_006d1b70(*param_1,param_2,1);
    }
    else {
      *param_1 = param_2;
    }
  }
  return;
}

