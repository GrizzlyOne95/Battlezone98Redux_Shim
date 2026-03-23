
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_005d42e0(void)

{
  bool bVar1;
  char cVar2;
  undefined4 uVar3;
  int iVar4;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar5;
  int iVar6;
  char *local_34;
  int local_30;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_20 [24];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_0081e820("Starting do_smain UI wrapper\n");
  uVar3 = FUN_0081e660();
  FUN_004bc590(uVar3);
  iVar4 = FUN_00764760();
  DAT_00918324 = 1;
  if (iVar4 != 0) {
    FUN_00740a90(0);
    FUN_0073ddf0();
  }
  if (DAT_0091812a != '\0') {
    FUN_00572a00(0);
  }
  _DAT_008fe6c0 = 0;
  FUN_00623ff0();
  FUN_00434600();
  DAT_00918133 = 0;
  if ((DAT_0091830c != 0) && (DAT_0091812a == '\0')) {
    pbVar5 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             FUN_00482850();
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_20,pbVar5);
    if (DAT_00918314 == 0) {
      DAT_0091831c = FUN_004888b0(local_20);
      if (DAT_0091831c < 0) {
        DAT_0091831c = 0;
      }
      else if (DAT_0091830c == 2) {
        DAT_0091831c = DAT_0091831c + 1;
      }
      FUN_004897d0(&DAT_0091831c,&DAT_00918330);
      FUN_00820b90();
    }
    else {
      DAT_0091831c = FUN_004888b0(local_20);
      cVar2 = FUN_00427310(local_20,&DAT_0094ffe0);
      if (cVar2 == '\0') {
        cVar2 = FUN_00427310(local_20,&DAT_0094fea8);
        if (cVar2 == '\0') {
          cVar2 = FUN_00427310(local_20,&DAT_0094fef8);
          if (cVar2 == '\0') {
            cVar2 = FUN_00427310(local_20,&DAT_0094fe78);
            if (cVar2 == '\0') {
              cVar2 = FUN_00427310(local_20,&DAT_0094fe90);
              if (cVar2 == '\0') {
                DAT_00918328 = 0x26;
              }
              else {
                DAT_00918328 = 0x24;
              }
            }
            else {
              DAT_00918328 = 0x23;
            }
          }
          else {
            DAT_00918328 = 0x19;
          }
        }
        else {
          DAT_00918328 = 0x1a;
        }
      }
      else {
        DAT_00918328 = 0x18;
      }
    }
    ~basic_string<>();
  }
  FUN_00764790();
  FUN_0076a030();
  bVar1 = true;
  if (DAT_009183ec == 1) {
    iVar4 = FUN_00822e60();
    local_30 = FUN_00822e60();
    while ((uint)(local_30 - iVar4) < 15000) {
      iVar6 = FUN_00764870();
      if (iVar6 != 0) {
        DAT_00918328 = 0xf;
        FUN_00764760();
        FUN_00741840();
        DAT_008e8c7e = 0;
        bVar1 = false;
        break;
      }
      local_30 = FUN_00822e60();
      FUN_00764a10();
    }
    DAT_009183ec = 0;
  }
  if (bVar1) {
    if (DAT_0091812a == '\0') {
      if (DAT_0091830c == 0) {
        DAT_00918328 = 1;
      }
    }
    else {
      DAT_00918328 = 0xe;
    }
  }
  FUN_00682450();
  DAT_0091812a = 0;
  FUN_005d50f0();
  if ((DAT_008eaaa8 == 0) || (DAT_00918328 != 1)) {
    FUN_004fdc20();
  }
  else {
    iVar4 = FUN_004fdab0();
    if (iVar4 != 0) {
      DAT_008e8c7e = 0;
      DAT_00918328 = 0;
    }
  }
  while (DAT_00918328 != 0) {
    DAT_009455de = 0;
    DAT_009455df = 0;
    FUN_005d5150(DAT_00918328);
  }
  iVar4 = FUN_00572a70();
  DAT_0091812a = iVar4 != 0;
  FUN_00434600();
  FUN_00623eb0();
  DAT_00918324 = 0;
  if (DAT_00918320 == 0) {
    local_34 = "\n";
  }
  else {
    local_34 = " (parent still set)\n";
  }
  FUN_0081e820("Ending do_smain UI wrapper",local_34);
  uVar3 = FUN_0081e660();
  uVar3 = FUN_004bc590(uVar3);
  FUN_004bc590(uVar3);
  FUN_0083e885();
  return;
}

