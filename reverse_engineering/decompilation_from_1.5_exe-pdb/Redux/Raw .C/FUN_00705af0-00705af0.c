
uint __thiscall FUN_00705af0(int param_1,char *param_2,uint param_3,undefined4 *param_4)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined1 *puVar5;
  undefined4 uVar6;
  undefined1 local_2c [8];
  undefined1 local_24 [8];
  undefined1 local_1c [4];
  undefined1 local_18 [8];
  undefined4 local_10;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_c;
  int local_8;
  
  local_8 = param_1;
  cVar1 = FUN_006ba440(param_1 + 0xc);
  if (cVar1 != '\0') {
    uVar2 = FUN_006ba820(param_2,param_3,*(undefined4 *)(*(int *)(local_8 + 0x48) + 8));
    *(undefined4 *)(*(int *)(local_8 + 0x48) + 8) = uVar2;
  }
  FUN_00421ec0();
  local_c = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
            FUN_006cc070();
  local_10 = FUN_004170c0();
  cVar1 = FUN_0044bb90();
  if (cVar1 != '\0') {
    FUN_00421ec0();
    cVar1 = FUN_00705180();
    if (cVar1 != '\0') {
      puVar3 = (undefined4 *)FUN_00707f30(local_24,param_2,param_3,local_c);
      uVar2 = puVar3[1];
      *param_4 = *puVar3;
      param_4[1] = uVar2;
      cVar1 = FUN_006ab7d0();
      if (cVar1 != '\0') {
        return 0;
      }
      goto LAB_00705bcd;
    }
  }
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::append
            (local_c,param_2,param_3);
LAB_00705bcd:
  FUN_00421ec0();
  iVar4 = FUN_006cc050();
  if (iVar4 == 1) {
    puVar3 = (undefined4 *)
             std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::end
                       (local_c);
    uVar2 = *puVar3;
    puVar5 = local_18;
    uVar6 = local_10;
    FID_conflict_begin(local_1c);
    puVar3 = (undefined4 *)FID_conflict_operator_(puVar5,uVar6);
    cVar1 = FUN_0070f8a0(*puVar3,uVar2);
    if (cVar1 == '\0') {
      puVar3 = (undefined4 *)make_error_code(local_2c,0x10);
      uVar2 = puVar3[1];
      *param_4 = *puVar3;
      param_4[1] = uVar2;
      return 0;
    }
  }
  *(uint *)(local_8 + 0x18) = *(int *)(local_8 + 0x18) - param_3;
  return param_3;
}

