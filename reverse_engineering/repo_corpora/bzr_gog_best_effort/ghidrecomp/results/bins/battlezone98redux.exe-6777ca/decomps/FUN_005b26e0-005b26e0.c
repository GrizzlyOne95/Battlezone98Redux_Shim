
void __fastcall FUN_005b26e0(char *param_1)

{
  if (*param_1 == '\0') {
    *(undefined4 *)(param_1 + 0xc) = *(undefined4 *)(param_1 + 4);
    *(undefined4 *)(param_1 + 0x18) = *(undefined4 *)(param_1 + 0x10);
    *(undefined4 *)(param_1 + 0x28) =
         *(undefined4 *)
          (*(int *)(param_1 + 0x24) +
          (*(int *)(param_1 + 0x18) * *(int *)(param_1 + 0x1c) + *(int *)(param_1 + 0xc)) * 4);
  }
  return;
}

