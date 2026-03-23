
void FUN_00743cb0(void)

{
  char cVar1;
  undefined1 uVar2;
  int iVar3;
  char *_Source;
  undefined1 *puVar4;
  undefined4 uVar5;
  int *piVar6;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> abStack_474 [16];
  undefined4 uStack_464;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> abStack_45c [8];
  undefined4 uStack_454;
  size_t _Count;
  char local_414 [1024];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085b3a6;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_00795cb0();
  iVar3 = FUN_0056f900();
  if (iVar3 == 0) goto LAB_00743f26;
  FUN_00743f40();
  cVar1 = FUN_00742d50();
  if ((cVar1 == '\0') || (*(char *)(iVar3 + 0xb0) != '\0')) goto LAB_00743f26;
  cVar1 = FUN_0041f890();
  if (cVar1 != '\0') goto LAB_00743f26;
  cVar1 = FUN_0041f890();
  if (cVar1 != '\0') goto LAB_00743f26;
  _Count = 0x400;
  _Source = (char *)FUN_0041f870();
  uStack_454 = 0x743da9;
  strncpy(local_414,_Source,_Count);
  puVar4 = (undefined1 *)FUN_004fbaf0();
  if (puVar4 != (undefined1 *)0x0) {
    *puVar4 = 0;
  }
  uStack_464 = 0x743df4;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            (abStack_45c,
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (iVar3 + 0xdc));
  local_8 = 0;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            (abStack_474,
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (iVar3 + 0xfc));
  local_8 = CONCAT31(local_8._1_3_,1);
  FUN_00764790();
  local_8 = 0xffffffff;
  FUN_0076b7a0();
  FUN_004afeb0();
  uVar5 = FUN_004b0190();
  FUN_004afe80();
  FUN_00764790();
  FUN_0076ba00();
  *(undefined4 *)(iVar3 + 0xf8) = uVar5;
  cVar1 = operator!=<>();
  if (cVar1 == '\0') {
LAB_00743f0e:
    *(undefined1 *)(iVar3 + 0xf4) = 1;
  }
  else {
    cVar1 = FUN_0041f890();
    if (cVar1 != '\0') goto LAB_00743f0e;
    piVar6 = (int *)FUN_00764790();
    uVar2 = (**(code **)(*piVar6 + 4))();
    *(undefined1 *)(iVar3 + 0xf4) = uVar2;
  }
  FUN_0073d020();
LAB_00743f26:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

