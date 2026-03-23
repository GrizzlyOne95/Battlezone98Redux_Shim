
void FUN_0046a020(int param_1,undefined2 param_2,undefined2 param_3)

{
  ushort uVar1;
  ushort uVar2;
  
  uVar1 = FUN_00469fd0(param_1,param_2);
  uVar2 = FUN_00469fd0(param_1,param_3);
  if (uVar1 != uVar2) {
    if (uVar1 < uVar2) {
      *(ushort *)(param_1 + (uint)uVar2 * 2) = uVar1;
    }
    else {
      *(ushort *)(param_1 + (uint)uVar1 * 2) = uVar2;
    }
  }
  return;
}

