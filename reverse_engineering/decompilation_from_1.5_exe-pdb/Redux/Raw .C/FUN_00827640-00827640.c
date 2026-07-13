
void FUN_00827640(int param_1,int param_2)

{
  int iVar1;
  int local_8;
  
  for (local_8 = 0; (local_8 < 0x10 && (*(char *)(param_2 + local_8) != '\0'));
      local_8 = local_8 + 1) {
    iVar1 = tolower((int)*(char *)(param_2 + local_8));
    *(char *)(param_1 + local_8) = (char)iVar1;
  }
  for (; local_8 < 0x10; local_8 = local_8 + 1) {
    *(undefined1 *)(param_1 + local_8) = 0;
  }
  return;
}

