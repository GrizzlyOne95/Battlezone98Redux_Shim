
undefined4 FUN_0082f739(int param_1,int param_2)

{
  if (*(ushort *)(param_1 + 0x36) < *(ushort *)(param_1 + 0x34)) {
    FUN_0082df5b(param_1,"attempt to yield across metamethod/C-call boundary");
  }
  *(undefined1 *)(param_1 + 6) = 1;
  *(int *)(param_1 + 0xc) = *(int *)(param_1 + 8) + param_2 * -0x10;
  return 0xffffffff;
}

