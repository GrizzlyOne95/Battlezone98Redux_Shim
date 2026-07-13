
u_short FUN_006bbb00(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                     *param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  char cVar2;
  undefined4 *puVar3;
  int iVar4;
  char *pcVar5;
  undefined1 local_2c [8];
  undefined1 local_24 [8];
  undefined1 local_1c [16];
  undefined2 local_c;
  u_short local_8;
  
  puVar3 = (undefined4 *)FUN_006ab750();
  uVar1 = puVar3[1];
  *param_2 = *puVar3;
  param_2[1] = uVar1;
  iVar4 = FUN_004170c0();
  if (iVar4 == 0) {
    local_8 = 0x3ed;
  }
  else {
    iVar4 = FUN_004170c0();
    if (iVar4 == 1) {
      puVar3 = (undefined4 *)make_error_code(local_1c,10);
      uVar1 = puVar3[1];
      *param_2 = *puVar3;
      param_2[1] = uVar1;
      local_8 = 0x3ea;
    }
    else {
      pcVar5 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
               operator[](param_1,0);
      local_c = CONCAT11(local_c._1_1_,*pcVar5);
      pcVar5 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
               operator[](param_1,1);
      local_c = CONCAT11(*pcVar5,(undefined1)local_c);
      local_8 = ntohs(local_c);
      cVar2 = FUN_006bba40(local_8);
      if (cVar2 != '\0') {
        puVar3 = (undefined4 *)make_error_code(local_24,0xc);
        uVar1 = puVar3[1];
        *param_2 = *puVar3;
        param_2[1] = uVar1;
      }
      cVar2 = FUN_006bb9f0(local_8);
      if (cVar2 != '\0') {
        puVar3 = (undefined4 *)make_error_code(local_2c,0xb);
        uVar1 = puVar3[1];
        *param_2 = *puVar3;
        param_2[1] = uVar1;
      }
    }
  }
  return local_8;
}

