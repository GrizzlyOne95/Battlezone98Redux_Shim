
void FUN_004879f0(void)

{
  char cVar1;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  undefined4 uVar6;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> abStack_58 [16];
  undefined4 uStack_48;
  undefined1 *puStack_44;
  undefined1 local_c [4];
  undefined1 local_8 [4];
  
  puStack_44 = local_8;
  uStack_48 = 0x487a05;
  FUN_00424640();
  puStack_44 = local_c;
  uStack_48 = 0x487a13;
  FID_conflict_begin();
  while( true ) {
    puStack_44 = local_c;
    uStack_48 = 0x487a1f;
    cVar1 = FUN_00420f10();
    if (cVar1 == '\0') break;
    puStack_44 = (undefined1 *)0x487a32;
    pbVar2 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             FUN_004237d0();
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(abStack_58,pbVar2);
    iVar3 = FUN_004885d0();
    puStack_44 = (undefined1 *)0x487a56;
    puStack_44 = (undefined1 *)FUN_004237d0();
    uStack_48 = 0x487a61;
    piVar4 = (int *)FUN_0048a3b0();
    if (iVar3 <= *piVar4) {
      puStack_44 = (undefined1 *)0x487a70;
      pbVar2 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               FUN_004237d0();
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                (abStack_58,pbVar2);
      iVar3 = FUN_004885d0();
      puStack_44 = (undefined1 *)0x487a9a;
      puStack_44 = (undefined1 *)FUN_004237d0();
      uStack_48 = 0x487aa5;
      piVar4 = (int *)FUN_0048a3b0();
      *piVar4 = iVar3 + -1;
    }
    puStack_44 = (undefined1 *)0x487aaf;
    pbVar2 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             FUN_004237d0();
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(abStack_58,pbVar2);
    iVar3 = FUN_004885d0();
    puStack_44 = (undefined1 *)0x487ad3;
    puStack_44 = (undefined1 *)FUN_004237d0();
    uStack_48 = 0x487ade;
    iVar5 = FUN_0048a3b0();
    if (iVar3 < *(int *)(iVar5 + 4)) {
      puStack_44 = (undefined1 *)0x487aee;
      pbVar2 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               FUN_004237d0();
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                (abStack_58,pbVar2);
      uVar6 = FUN_004885d0();
      puStack_44 = (undefined1 *)0x487b12;
      puStack_44 = (undefined1 *)FUN_004237d0();
      uStack_48 = 0x487b1d;
      iVar3 = FUN_0048a3b0();
      *(undefined4 *)(iVar3 + 4) = uVar6;
    }
    puStack_44 = (undefined1 *)0x487b2b;
    FUN_00422190();
  }
  return;
}

