
void __fastcall FUN_004c7320(int param_1)

{
  int iVar1;
  undefined2 *puVar2;
  
  *(uint *)(param_1 + 0x4150) = *(int *)(param_1 + 0x4150) + 0x7fU & 0x7f;
  *(int *)(param_1 + 0x4148) = *(int *)(param_1 + 0x4148) + -1;
  iVar1 = *(int *)(param_1 + 0x4150);
  puVar2 = (undefined2 *)
           FUN_004c0fe0((int)*(short *)(param_1 + 0x4160 + *(int *)(param_1 + 0x4150) * 6),
                        (int)*(short *)(param_1 + 0x4162 + *(int *)(param_1 + 0x4150) * 6));
  *puVar2 = *(undefined2 *)(param_1 + 0x4164 + iVar1 * 6);
  return;
}

