
undefined2 FUN_00469fd0(int param_1,ushort param_2)

{
  undefined2 uVar1;
  
  if (*(ushort *)(param_1 + (uint)param_2 * 2) != param_2) {
    uVar1 = FUN_00469fd0(param_1,*(undefined2 *)(param_1 + (uint)param_2 * 2));
    *(undefined2 *)(param_1 + (uint)param_2 * 2) = uVar1;
  }
  return *(undefined2 *)(param_1 + (uint)param_2 * 2);
}

