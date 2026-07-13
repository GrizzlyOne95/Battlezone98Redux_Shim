
void __fastcall FUN_004ae330(int param_1)

{
  if ((*(int *)(param_1 + 0x228) == 2) || (*(int *)(param_1 + 0x228) == 1)) {
    *(undefined4 *)(*(int *)(param_1 + 0x230) + 0xe0) = 1;
  }
  else {
    *(undefined4 *)(*(int *)(param_1 + 0x230) + 0xe0) = 0;
  }
  return;
}

