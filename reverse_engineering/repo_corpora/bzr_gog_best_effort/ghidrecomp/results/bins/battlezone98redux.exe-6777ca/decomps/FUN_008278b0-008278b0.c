
bool FUN_008278b0(ushort *param_1,ushort param_2)

{
  ushort uVar1;
  ushort uVar2;
  
  uVar1 = *param_1;
  if (uVar1 < 7) {
    uVar2 = *param_1;
    *param_1 = uVar2 + 1;
    param_1[(ushort)(uVar2 + 1)] = param_2;
  }
  return uVar1 < 7;
}

