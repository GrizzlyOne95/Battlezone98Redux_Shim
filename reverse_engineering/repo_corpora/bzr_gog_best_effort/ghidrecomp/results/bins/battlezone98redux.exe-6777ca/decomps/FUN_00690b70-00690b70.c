
void FUN_00690b70(void)

{
  void *_Memory;
  int local_c;
  int local_8;
  
  FUN_006a5fd0("in RLD\n");
  for (local_8 = 0; local_8 < 2; local_8 = local_8 + 1) {
    for (local_c = 0; local_c < *(int *)((&DAT_02bfdff0)[local_8] + 8); local_c = local_c + 1) {
      _Memory = (void *)FUN_0069d590((&DAT_02bfdff0)[local_8],local_c);
      FUN_006a5fd0("RLD about to free resource %d node %d ptr %08x\n",local_8,local_c,_Memory);
      free(_Memory);
    }
    FUN_006a5fd0("About to free list resource %d\n",local_8);
    FUN_0069d310((&DAT_02bfdff0)[local_8]);
  }
  FUN_006a5fd0("leaving RLD\n");
  return;
}

