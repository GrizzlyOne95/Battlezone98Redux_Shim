
undefined4 FUN_004895d0(void)

{
  char cVar1;
  int iVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00848fa8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  cVar1 = FUN_00427310(&stack0x00000004,&DAT_0094fef8,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  if ((cVar1 == '\0') && (iVar2 = FUN_0048a3b0(&stack0x00000004), *(int *)(iVar2 + 4) == 0)) {
    local_8 = 0xffffffff;
    ~basic_string<>();
    ExceptionList = local_10;
    return 0;
  }
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  return 1;
}

