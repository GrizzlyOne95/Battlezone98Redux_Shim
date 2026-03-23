
void FUN_004897d0(int *param_1,int *param_2)

{
  char cVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> abStack_d8 [12];
  undefined4 uStack_cc;
  undefined *puStack_c8;
  undefined *puStack_c4;
  
  puStack_c4 = &DAT_0094fef8;
  puStack_c8 = &DAT_0094fee0;
  uStack_cc = 0x4897e9;
  cVar1 = FUN_00427310();
  if (cVar1 == '\0') {
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
              (abStack_d8,
               (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               &DAT_0094fee0);
    iVar2 = FUN_004885d0();
    if (*param_1 < iVar2) {
      if (*param_2 == 0) {
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
        basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  (abStack_d8,
                   (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                   &DAT_0094fee0);
        DAT_00918328 = FUN_00489230();
      }
      else {
        *param_2 = 0;
        DAT_00918328 = 1;
      }
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                (abStack_d8,
                 (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 &DAT_0094fee0);
      iVar2 = FUN_00488ec0();
      if (iVar2 < *param_1) {
        puStack_c4 = &DAT_0094fee0;
        puStack_c8 = (undefined *)0x489a3e;
        piVar3 = (int *)FUN_0048a3b0();
        *piVar3 = *param_1;
      }
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                (abStack_d8,
                 (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 &DAT_0094fee0);
      iVar2 = FUN_00488ec0();
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                (abStack_d8,
                 (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 &DAT_0094fee0);
      iVar4 = FUN_00488f70();
      if (iVar2 < iVar4) {
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
        basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  (abStack_d8,
                   (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                   &DAT_0094fee0);
        uVar6 = FUN_00488f70();
        puStack_c4 = &DAT_0094fee0;
        puStack_c8 = (undefined *)0x489abf;
        puVar5 = (undefined4 *)FUN_0048a3b0();
        *puVar5 = uVar6;
      }
    }
    else {
      DAT_00918328 = 1;
      *param_1 = 0;
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                (abStack_d8,
                 (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 &DAT_0094fee0);
      iVar2 = FUN_00488f70();
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                (abStack_d8,
                 (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 &DAT_0094fee0);
      iVar4 = FUN_00488ec0();
      if (iVar2 < iVar4 + 1) {
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
        basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  (abStack_d8,
                   (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                   &DAT_0094fee0);
        iVar2 = FUN_00488ec0();
        puStack_c4 = &DAT_0094fee0;
        puStack_c8 = (undefined *)0x4899b5;
        iVar4 = FUN_0048a3b0();
        *(int *)(iVar4 + 4) = iVar2 + 1;
      }
    }
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
              (abStack_d8,
               (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               &DAT_0094fee0);
    iVar2 = FUN_00488f70();
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
              (abStack_d8,
               (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               &DAT_0094fee0);
    iVar4 = FUN_00488ec0();
    if (iVar2 < iVar4) {
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                (abStack_d8,
                 (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 &DAT_0094fee0);
      uVar6 = FUN_00488ec0();
      puStack_c4 = &DAT_0094fee0;
      puStack_c8 = (undefined *)0x489b4d;
      iVar2 = FUN_0048a3b0();
      *(undefined4 *)(iVar2 + 4) = uVar6;
    }
  }
  else {
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
              (abStack_d8,
               (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               &DAT_0094fee0);
    iVar2 = FUN_004885d0();
    if (*param_1 < iVar2) {
      if (*param_2 == 0) {
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
        basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  (abStack_d8,
                   (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                   &DAT_0094fee0);
        DAT_00918328 = FUN_00489230();
      }
      else {
        *param_2 = 0;
        DAT_00918328 = 1;
      }
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                (abStack_d8,
                 (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 &DAT_0094fee0);
      iVar2 = FUN_00488ec0();
      if (iVar2 < *param_1) {
        puStack_c4 = &DAT_0094fee0;
        puStack_c8 = (undefined *)0x4898df;
        piVar3 = (int *)FUN_0048a3b0();
        *piVar3 = *param_1;
      }
    }
    else {
      DAT_00918328 = 1;
      *param_1 = 0;
      puStack_c4 = &DAT_0094fee0;
      puStack_c8 = (undefined *)0x489846;
      piVar3 = (int *)FUN_0048a3b0();
      *piVar3 = *piVar3 + 1;
    }
  }
  puStack_c4 = (undefined *)0x489b58;
  FUN_00487f30();
  return;
}

