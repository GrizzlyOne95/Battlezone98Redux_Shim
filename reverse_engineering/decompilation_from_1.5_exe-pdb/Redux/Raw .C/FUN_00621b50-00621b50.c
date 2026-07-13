
undefined4 FUN_00621b50(int param_1,int param_2,int param_3)

{
  return *(undefined4 *)
          (&DAT_02a14610 +
          (((param_1 - param_2) * 0xfe) / (param_3 - param_2)) * 4 +
          *(int *)(DAT_0094672c + 0x3c) * 0x400);
}

