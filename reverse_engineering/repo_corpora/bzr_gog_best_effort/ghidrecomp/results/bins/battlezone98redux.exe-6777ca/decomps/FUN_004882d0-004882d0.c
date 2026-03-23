
undefined1 FUN_004882d0(void)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined4 in_stack_0000001c;
  undefined1 local_1c [4];
  undefined1 local_18 [6];
  undefined1 local_12;
  undefined1 local_11;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_00848f20;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  uVar3 = FUN_0048a2b0(&stack0x00000004);
  FUN_0048a5b0(uVar3,uVar2);
  local_8 = CONCAT31(local_8._1_3_,1);
  FID_conflict_begin(local_18);
  while( true ) {
    uVar3 = FID_conflict_end(local_1c);
    cVar1 = FID_conflict_operator__(uVar3);
    if (cVar1 == '\0') {
      local_12 = 0;
      local_8 = local_8 & 0xffffff00;
      FUN_0041fe20();
      local_8 = 0xffffffff;
      ~basic_string<>();
      ExceptionList = local_10;
      return local_12;
    }
    puVar4 = (undefined4 *)FUN_00421ec0(in_stack_0000001c);
    cVar1 = FUN_00427310(*puVar4);
    if (cVar1 != '\0') break;
    FUN_00421ee0();
  }
  local_11 = 1;
  local_8 = local_8 & 0xffffff00;
  FUN_0041fe20();
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  return local_11;
}

