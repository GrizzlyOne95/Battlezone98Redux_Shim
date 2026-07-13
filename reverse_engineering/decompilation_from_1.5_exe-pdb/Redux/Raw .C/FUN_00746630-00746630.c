
void __thiscall FUN_00746630(int *param_1,int param_2)

{
  char cVar1;
  undefined4 uVar2;
  bool bVar3;
  undefined1 local_1c [16];
  uint local_c;
  int *local_8;
  
  local_8 = param_1;
  uVar2 = (**(code **)(*param_1 + 0x38))(local_1c);
  cVar1 = FUN_0073ba10(uVar2);
  if (cVar1 != '\0') {
    bVar3 = *(char *)(param_2 + 0x44) == '\0';
    local_c = (uint)bVar3;
    *(bool *)(param_2 + 0x44) = bVar3;
    FUN_007476a0();
  }
  return;
}

