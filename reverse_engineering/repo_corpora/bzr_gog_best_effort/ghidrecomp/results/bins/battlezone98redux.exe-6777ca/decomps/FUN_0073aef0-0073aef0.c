
void __fastcall FUN_0073aef0(int param_1)

{
  undefined4 uVar1;
  undefined4 uStack_1c;
  char *pcStack_18;
  int local_14;
  int *local_10;
  int *local_c;
  int *local_8;
  
  *(undefined4 *)(param_1 + 8) = 3;
  pcStack_18 = "gogInitState = 3;\n";
  uStack_1c = 0x73af0d;
  local_14 = param_1;
  FUN_007d6a70();
  pcStack_18 = (char *)0x73af15;
  local_8 = (int *)FUN_007647a0();
  pcStack_18 = (char *)0x73af25;
  (**(code **)(*local_8 + 0x1c))();
  pcStack_18 = (char *)0x73af2a;
  local_c = (int *)FUN_0073add0();
  pcStack_18 = (char *)0x73af32;
  local_10 = (int *)FUN_0073ae00();
  (**(code **)(*local_c + 8))(&uStack_1c);
  uVar1 = (**(code **)(*local_10 + 0x14))();
  FUN_00764b80(0,0,uVar1);
  FUN_00764f30();
  return;
}

