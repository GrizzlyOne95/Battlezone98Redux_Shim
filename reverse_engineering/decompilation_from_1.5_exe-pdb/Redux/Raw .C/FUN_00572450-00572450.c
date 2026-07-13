
void FUN_00572450(undefined4 param_1)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar4;
  code *pcVar5;
  code *pcVar6;
  undefined *puVar7;
  undefined1 auStack_ec [160];
  undefined1 *local_4c;
  undefined1 *local_48;
  undefined *local_44;
  undefined1 *local_40;
  char local_39;
  undefined1 local_38 [24];
  undefined1 local_20 [24];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_00574400(3,1);
  if (&stack0x00000000 == (undefined1 *)0xfc) {
    local_48 = (undefined1 *)0x0;
  }
  else {
    local_48 = auStack_ec;
  }
  uVar1 = FUN_00572790();
  uVar1 = FUN_004bc590(local_48,param_1,", State : ",uVar1);
  uVar1 = FUN_004bc590(uVar1);
  FUN_004bc590(uVar1);
  if (DAT_00917f78 == '\0') {
    local_44 = &DAT_00884008;
  }
  else {
    local_44 = &DAT_00884010;
  }
  if (&stack0x00000000 == (undefined1 *)0xfc) {
    local_40 = (undefined1 *)0x0;
  }
  else {
    local_40 = auStack_ec;
  }
  pcVar6 = FUN_004bc8c0;
  uVar2 = FUN_004b75b0();
  iVar3 = FUN_005726f0(" Players: ");
  pcVar5 = FUN_0056f740;
  uVar1 = FUN_004bc590(local_40,&DAT_00883ec4,"Host: ",local_44," TimeOut: ");
  uVar1 = FUN_004bc590(uVar1);
  uVar1 = FUN_004bc590(uVar1);
  pbVar4 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(uVar1);
  pbVar4 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar4,pcVar5);
  pbVar4 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar4,iVar3);
  pbVar4 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(pbVar4);
  pbVar4 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar4,uVar2);
  std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar4,pcVar6);
  if (&stack0x00000000 == (undefined1 *)0xfc) {
    local_4c = (undefined1 *)0x0;
  }
  else {
    local_4c = auStack_ec;
  }
  FUN_00577eb0(&DAT_0087bd08,local_4c);
  puVar7 = &DAT_009c8f70;
  uVar1 = GetPolicy(local_20);
  local_39 = operator!=<>(uVar1,puVar7);
  ~basic_string<>();
  if (local_39 != '\0') {
    uVar1 = GetPolicy(local_38);
    FUN_0045e0f0(uVar1);
    ~basic_string<>();
    pcVar5 = FUN_004bc8c0;
    FUN_0081e820(&DAT_009c8f70);
    uVar1 = FUN_0081e660();
    pbVar4 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_00574730(uVar1);
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar4,pcVar5);
  }
  FUN_00417f10();
  FUN_0083e885();
  return;
}

