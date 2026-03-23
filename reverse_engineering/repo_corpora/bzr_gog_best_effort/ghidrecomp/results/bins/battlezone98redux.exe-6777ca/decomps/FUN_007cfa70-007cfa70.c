
void __thiscall FUN_007cfa70(int param_1,char param_2)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  float10 fVar4;
  float10 fVar5;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> abStack_ac [8];
  undefined4 uStack_a4;
  undefined1 *puStack_a0;
  int iStack_9c;
  char *local_6c;
  char *local_68;
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008628e8;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  if (param_2 != '\t') {
    if (*(char *)(param_1 + 0x960) == '\x01') {
      FUN_00764760();
      iVar2 = FUN_006cc050();
      if (iVar2 != 4) goto LAB_007cfd24;
    }
    if ((param_2 == '\n') || (param_2 == '\r')) {
      if ((*(char *)(param_1 + 0x950) != '\0') && (*(int *)(param_1 + 0x94c) != 0)) {
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
        basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  (abStack_ac,
                   (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                   (param_1 + 0x930));
        (**(code **)(param_1 + 0x94c))();
      }
    }
    else if (param_2 == '\b') {
      iVar2 = FUN_004170c0();
      if (iVar2 != 0) {
        FUN_004170c0();
        iStack_9c = 0;
        puStack_a0 = local_44;
        uStack_a4 = 0x7cfb7c;
        FUN_0045e1d0();
        iStack_9c = 0x7cfb91;
        FUN_0045e0f0();
        ~basic_string<>();
      }
    }
    else if ((*(int *)(param_1 + 0x964) < 0) ||
            (uVar3 = FUN_004170c0(), uVar3 < *(uint *)(param_1 + 0x964))) {
      iStack_9c = 0x7cfbd3;
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator+=
                ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 (param_1 + 0x930),param_2);
    }
    iStack_9c = 0x7cfbe4;
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
              (local_2c,(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                         *)(param_1 + 0x930));
    local_8 = 0;
    uVar3 = FUN_004170c0();
    if (*(uint *)(param_1 + 0x948) < uVar3) {
      iStack_9c = FUN_004170c0();
      iStack_9c = iStack_9c - *(int *)(param_1 + 0x948);
      puStack_a0 = local_5c;
      uStack_a4 = 0x7cfc28;
      FUN_0045e1d0();
      iStack_9c = 0x7cfc37;
      FUN_0045e0f0();
      ~basic_string<>();
    }
    FUN_0041f870();
    iStack_9c = DAT_0091552c;
    puStack_a0 = (undefined1 *)0x7cfc54;
    fVar4 = (float10)FUN_00689cb0();
    *(undefined4 *)(param_1 + 0x91c) = 0xff00ff00;
    *(undefined4 *)(param_1 + 0x920) = 0x3f800000;
    local_6c = (char *)FUN_0041f870();
    local_68 = (char *)(param_1 + 0x144);
    do {
      cVar1 = *local_6c;
      *local_68 = cVar1;
      local_6c = local_6c + 1;
      local_68 = local_68 + 1;
    } while (cVar1 != '\0');
    FUN_007cc750();
    iStack_9c = 0xbf800000;
    puStack_a0 = (undefined1 *)0x7cfce2;
    fVar5 = (float10)FUN_007d37b0();
    puStack_a0 = (undefined1 *)((float)fVar5 + (float)fVar4);
    uStack_a4 = 0x7cfd0e;
    (**(code **)(**(int **)(param_1 + 0x954) + 0x28))();
    local_8 = 0xffffffff;
    ~basic_string<>();
  }
LAB_007cfd24:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

