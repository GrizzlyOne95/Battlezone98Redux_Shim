
void __thiscall FUN_0049f300(int param_1,char param_2)

{
  int local_8;
  
  if ((param_2 == '\0') || (*(char *)(param_1 + 0x189) != '\0')) {
    if ((param_2 == '\0') && (*(char *)(param_1 + 0x189) != '\0')) {
      for (local_8 = 0; local_8 < DAT_00917af8; local_8 = local_8 + 1) {
        if (*(int *)(&DAT_00917a78 + local_8 * 4) == param_1) {
          DAT_00917af8 = DAT_00917af8 + -1;
          *(undefined4 *)(&DAT_00917a78 + local_8 * 4) =
               *(undefined4 *)(&DAT_00917a78 + DAT_00917af8 * 4);
          break;
        }
      }
    }
  }
  else {
    *(int *)(&DAT_00917a78 + DAT_00917af8 * 4) = param_1;
    DAT_00917af8 = DAT_00917af8 + 1;
  }
  *(char *)(param_1 + 0x189) = param_2;
  return;
}

