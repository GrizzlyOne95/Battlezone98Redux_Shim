
void __thiscall FUN_0074f080(int param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  undefined1 local_18 [16];
  int local_8;
  
  if (*(char *)(param_1 + 0x30) == '\0') {
    local_8 = param_1;
    cVar1 = FUN_0074db10(param_2,param_1 + -200);
    if (cVar1 != '\0') {
      uVar2 = (**(code **)(*(int *)(local_8 + -0xf0) + 0x38))(local_18,0);
      FUN_00578640(uVar2);
      FUN_0056f7e0();
      FUN_007659f0();
      FUN_0073bb30();
      FUN_00740a90(1);
      FUN_007476a0();
    }
  }
  return;
}

