
undefined4 FUN_0068bdd0(void)

{
  int local_8;
  
  memset(&DAT_00920f08,0,0x10000);
  for (local_8 = 0; local_8 < DAT_00920f00; local_8 = local_8 + 1) {
    FUN_004c85d0();
    *(undefined2 *)(&DAT_025f8f40 + local_8 * 0x24) = 0;
    *(undefined2 *)(&DAT_025f8f42 + local_8 * 0x24) = 0;
    *(undefined2 *)(&DAT_025f8f44 + local_8 * 0x24) = 0;
    *(undefined2 *)(&DAT_025f8f46 + local_8 * 0x24) = 0;
    *(undefined4 *)(&DAT_025f8f48 + local_8 * 0x24) = 0;
    *(undefined4 *)(&DAT_025f8f4c + local_8 * 0x24) = 0;
    *(undefined4 *)(&DAT_025f8f50 + local_8 * 0x24) = 0;
    *(undefined4 *)(&DAT_025f8f54 + local_8 * 0x24) = 0;
    *(undefined4 *)(&DAT_025f8f58 + local_8 * 0x24) = 0;
  }
  DAT_00920f00 = 0;
  return 1;
}

