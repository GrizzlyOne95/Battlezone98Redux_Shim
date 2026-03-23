
void FUN_00840000(void)

{
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_008655ee;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  if ((DAT_009150c0 & 1) == 0) {
    DAT_009150c0 = DAT_009150c0 | 1;
    local_4 = 0;
    ExceptionList = &local_c;
    FUN_008401c0(&DAT_009150bc,DAT_008e7000 ^ (uint)&local_c);
    FUN_0083e979(&LAB_00868310);
  }
  local_4 = 0xffffffff;
  FUN_0083f7e0(&DAT_009150bc);
  ExceptionList = local_c;
  return;
}

