
void __thiscall FUN_006ce030(ushort *param_1,ushort param_2)

{
  ushort uVar1;
  uint uVar2;
  
  uVar2 = FUN_006ce020();
  if (param_2 + 1 < (uVar2 & 0xffff) + 1) {
    FUN_006d1c80(*param_1,param_2,0);
  }
  else {
    uVar1 = FUN_006d1c60();
    if (uVar1 < param_2) {
      FUN_006d1c80(*param_1,param_2,1);
    }
    else {
      *param_1 = param_2;
    }
  }
  return;
}

