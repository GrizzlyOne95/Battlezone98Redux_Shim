
void __fastcall FUN_004e2ce0(int param_1)

{
  if ((*(int *)(*(int *)(param_1 + 0xf8) + 0x160) != 0) && (*(char *)(param_1 + 0x238) == '\0')) {
    (**(code **)(**(int **)(*(int *)(param_1 + 0xf8) + 0x160) + 8))
              (param_1 + 0x23c,*(int *)(param_1 + 0xf4) + 0x20);
  }
  *(uint *)(*(int *)(param_1 + 0xf4) + 0x14) =
       *(uint *)(*(int *)(param_1 + 0xf4) + 0x14) & 0xfffffbfe;
  *(undefined4 *)(*(int *)(param_1 + 0xf4) + 0xd0) = 0;
  *(undefined1 *)(param_1 + 0x238) = 1;
  return;
}

