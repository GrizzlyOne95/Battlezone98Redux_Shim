
bool __fastcall FUN_004e6360(int param_1)

{
  undefined4 uVar1;
  bool bVar2;
  
  bVar2 = *(int *)(param_1 + 8) != 0xd;
  if (bVar2) {
    *(undefined4 *)(param_1 + 0x18) = 0;
    uVar1 = FUN_00462630(*(undefined4 *)(param_1 + 0x78));
    *(undefined4 *)(param_1 + 0x80) = uVar1;
    uVar1 = FUN_004643e0(*(undefined4 *)(param_1 + 0x10),*(undefined4 *)(param_1 + 0x80));
    *(undefined4 *)(param_1 + 0x7c) = uVar1;
  }
  return bVar2;
}

