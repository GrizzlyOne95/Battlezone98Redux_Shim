
void FUN_006da360(int *param_1)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  char *pcVar5;
  undefined1 local_70 [8];
  undefined1 local_68 [4];
  undefined1 local_64 [56];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00853818;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uVar2 = FUN_006cac60(local_14);
  uVar2 = uVar2 & 0xffff;
  uVar3 = FUN_006cac80(local_64);
  FUN_006b3570(uVar3,uVar2);
  FUN_004fbb60();
  FUN_006b38c0(local_2c,local_70);
  local_8 = 0;
  iVar4 = FUN_00667170();
  if (iVar4 == 0) {
    FID_conflict_begin(local_68);
    while( true ) {
      uVar3 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::end
                        (local_2c);
      cVar1 = FID_conflict_operator__(uVar3);
      if (cVar1 == '\0') break;
      pcVar5 = (char *)FUN_00421ec0();
      cVar1 = std::basic_ios<char,struct_std::char_traits<char>_>::widen
                        ((basic_ios<char,struct_std::char_traits<char>_> *)
                         ((int)param_1 + *(int *)(*param_1 + 4)),*pcVar5);
      FUN_006d9650(param_1,cVar1);
      FUN_004f5330();
    }
  }
  else {
    uVar2 = std::ios_base::exceptions((ios_base *)((int)param_1 + *(int *)(*param_1 + 4)));
    if ((uVar2 & 2) == 0) {
      std::basic_ios<char,struct_std::char_traits<char>_>::setstate
                ((basic_ios<char,struct_std::char_traits<char>_> *)
                 ((int)param_1 + *(int *)(*param_1 + 4)),2,false);
    }
    else {
      FUN_006ab9e0(local_70);
    }
  }
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

