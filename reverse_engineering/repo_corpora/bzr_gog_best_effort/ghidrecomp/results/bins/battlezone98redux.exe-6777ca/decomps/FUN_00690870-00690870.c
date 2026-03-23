
int FUN_00690870(int param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4,
                undefined2 param_5)

{
  int local_8;
  
  for (local_8 = 0; ((&DAT_02bfddb0)[local_8 + param_1 * 0x20] != '\0' && (local_8 < 0x20));
      local_8 = local_8 + 1) {
  }
  if (local_8 < 0x20) {
    *(undefined2 *)(&DAT_02bfdff8 + local_8 * 8 + param_1 * 0x100) = param_2;
    *(undefined2 *)(&DAT_02bfdffa + local_8 * 8 + param_1 * 0x100) = param_3;
    *(undefined2 *)(&DAT_02bfdffc + local_8 * 8 + param_1 * 0x100) = param_4;
    *(undefined2 *)(&DAT_02bfdffe + local_8 * 8 + param_1 * 0x100) = param_5;
    (&DAT_02bfddb0)[local_8 + param_1 * 0x20] = 1;
  }
  else {
    local_8 = -1;
  }
  return local_8;
}

