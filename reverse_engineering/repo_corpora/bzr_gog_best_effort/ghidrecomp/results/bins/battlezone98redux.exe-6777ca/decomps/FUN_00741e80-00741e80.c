
undefined4
FUN_00741e80(undefined4 param_1,
            basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_2)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  char *pcVar4;
  undefined1 auStack_dc [160];
  uint local_3c;
  undefined1 *local_38;
  undefined1 *local_34;
  uint local_30;
  char *local_2c;
  undefined1 *local_28;
  undefined1 *local_24;
  undefined1 *local_20;
  int local_1c;
  uint local_18;
  char local_12;
  char local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085b10b;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_30 = 0;
  FUN_00574400(3,1);
  local_8 = 0;
  if (*(char *)(local_1c + 0x61) == '\0') {
    local_2c = "chat~";
  }
  else {
    local_2c = "game~";
  }
  if (&stack0x00000000 == (undefined1 *)0xec) {
    local_24 = (undefined1 *)0x0;
  }
  else {
    local_24 = auStack_dc;
  }
  uVar3 = FUN_004bc590(local_24,&DAT_0089ace0,local_2c,uVar2);
  FUN_004bc590(uVar3);
  if (&stack0x00000000 == (undefined1 *)0xec) {
    local_34 = (undefined1 *)0x0;
  }
  else {
    local_34 = auStack_dc;
  }
  FUN_004bc590(local_34,&DAT_0089a8b8);
  cVar1 = FUN_0041f890();
  if (cVar1 == '\0') {
    if (&stack0x00000000 == (undefined1 *)0xec) {
      local_38 = (undefined1 *)0x0;
    }
    else {
      local_38 = auStack_dc;
    }
    FUN_004bc590(local_38,&DAT_008922f0);
  }
  if (&stack0x00000000 == (undefined1 *)0xec) {
    local_20 = (undefined1 *)0x0;
  }
  else {
    local_20 = auStack_dc;
  }
  FUN_004bc590(local_20,&DAT_0089ace0);
  local_3c = FUN_004170c0();
  for (local_18 = 0; local_18 < local_3c; local_18 = local_18 + 1) {
    pcVar4 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
             operator[](param_2,local_18);
    if (*pcVar4 < '\0') {
      local_11 = '?';
    }
    else {
      pcVar4 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
               operator[](param_2,local_18);
      local_11 = *pcVar4;
    }
    local_12 = local_11;
    if (&stack0x00000000 == (undefined1 *)0xec) {
      local_28 = (undefined1 *)0x0;
    }
    else {
      local_28 = auStack_dc;
    }
    FUN_006d9650(local_28,local_11);
  }
  GetPolicy(param_1);
  local_30 = local_30 | 1;
  local_8 = 0xffffffff;
  FUN_00417f10();
  ExceptionList = local_10;
  return param_1;
}

