
void __fastcall FUN_004f2d20(int param_1)

{
  FUN_0062de40(*(undefined4 *)(param_1 + 0x18),1);
  *(uint *)(*(int *)(param_1 + 0x18) + 0x14) =
       *(uint *)(*(int *)(param_1 + 0x18) + 0x14) & 0xfffffffe;
  *(uint *)(*(int *)(param_1 + 0x18) + 0x14) =
       *(uint *)(*(int *)(param_1 + 0x18) + 0x14) | 0x40000400;
  return;
}

