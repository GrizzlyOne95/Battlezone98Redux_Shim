
int FUN_00690950(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  int local_c;
  int local_8;
  
  local_c = 0;
  local_8 = 0;
  do {
    if (((((&DAT_02bfddb0)[local_8 + param_1 * 0x20] != '\0') &&
         ((int)*(short *)(&DAT_02bfdff8 + local_8 * 8 + param_1 * 0x100) <= param_2 + -1 + param_4))
        && ((int)*(short *)(&DAT_02bfdffa + local_8 * 8 + param_1 * 0x100) <= param_3 + -1 + param_5
           )) && ((param_2 < (int)*(short *)(&DAT_02bfdff8 + local_8 * 8 + param_1 * 0x100) +
                             (int)*(short *)(&DAT_02bfdffc + local_8 * 8 + param_1 * 0x100) &&
                  (param_3 < (int)*(short *)(&DAT_02bfdffa + local_8 * 8 + param_1 * 0x100) +
                             (int)*(short *)(&DAT_02bfdffe + local_8 * 8 + param_1 * 0x100))))) {
      local_c = 1;
    }
    local_8 = local_8 + 1;
  } while ((local_c == 0) && (local_8 < 0x20));
  return local_c;
}

