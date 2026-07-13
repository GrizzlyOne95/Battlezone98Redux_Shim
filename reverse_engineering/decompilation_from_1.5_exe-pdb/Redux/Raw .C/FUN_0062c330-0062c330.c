
void FUN_0062c330(void)

{
  int local_8;
  
  for (local_8 = 0x13ff; -1 < local_8; local_8 = local_8 + -1) {
    if (*(int *)(&DAT_02a1f570 + local_8 * 0xe4) != 0) {
      FUN_0062c460(&DAT_02a1f570 + local_8 * 0xe4);
      FUN_0062d200(*(undefined4 *)(&DAT_02a1f570 + local_8 * 0xe4),"Obj76\\Entities.c");
    }
    FUN_0062c240(&DAT_02a1f570 + local_8 * 0xe4);
  }
  DAT_00920c7c = 0;
  return;
}

