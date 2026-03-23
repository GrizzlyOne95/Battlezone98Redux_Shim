
undefined4 FUN_00489230(void)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_008490b8;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  cVar1 = FUN_00427310(&stack0x00000004,&DAT_0094ffe0,uVar2);
  if (cVar1 == '\0') {
    cVar1 = FUN_00427310(&stack0x00000004,&DAT_0094fea8,uVar2);
    if (cVar1 == '\0') {
      cVar1 = FUN_00427310(&stack0x00000004,&DAT_0094fef8,uVar2);
      if (cVar1 == '\0') {
        cVar1 = FUN_00427310(&stack0x00000004,&DAT_0094fe78,uVar2);
        if (cVar1 == '\0') {
          cVar1 = FUN_00427310(&stack0x00000004,&DAT_0094fe90,uVar2);
          if (cVar1 == '\0') {
            local_8 = 0xffffffff;
            ~basic_string<>();
            uVar3 = 0x25;
          }
          else {
            local_8 = 0xffffffff;
            ~basic_string<>();
            uVar3 = 0x22;
          }
        }
        else {
          local_8 = 0xffffffff;
          ~basic_string<>();
          uVar3 = 0x21;
        }
      }
      else {
        local_8 = 0xffffffff;
        ~basic_string<>();
        uVar3 = 9;
      }
    }
    else {
      local_8 = 0xffffffff;
      ~basic_string<>();
      uVar3 = 8;
    }
  }
  else {
    local_8 = 0xffffffff;
    ~basic_string<>();
    uVar3 = 7;
  }
  ExceptionList = local_10;
  return uVar3;
}

