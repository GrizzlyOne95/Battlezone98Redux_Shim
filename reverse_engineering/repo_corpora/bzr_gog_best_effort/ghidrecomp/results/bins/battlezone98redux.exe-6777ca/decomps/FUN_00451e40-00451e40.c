
void __fastcall FUN_00451e40(int param_1)

{
  FUN_00451dc0(1);
  FUN_00451dd0(1);
  *(byte *)(param_1 + 0x25) = *(byte *)(param_1 + 0x25) & 0xfe;
  *(byte *)(param_1 + 0x25) = *(byte *)(param_1 + 0x25) & 0xfd;
  *(byte *)(param_1 + 0x25) = *(byte *)(param_1 + 0x25) | 4;
  *(byte *)(param_1 + 0x25) = *(byte *)(param_1 + 0x25) & 0xf7;
  return;
}

