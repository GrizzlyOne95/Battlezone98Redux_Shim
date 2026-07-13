
void __thiscall FUN_0073b470(int param_1,char param_2)

{
  int *piVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085a8c3;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *(undefined4 *)(param_1 + 8) = 2;
  FUN_007d6a70("gogInitState = 2;\n");
  if (param_2 != '\0') {
    FUN_00764920();
    FUN_007d6a70("getSteamAuthTicket\n");
    FUN_0073b61f();
    return;
  }
  local_8 = 0;
  piVar1 = (int *)FUN_0073add0();
  (**(code **)(*piVar1 + 0x18))(0);
  FUN_007d6a70("galaxy::api::User()->SignIn()\n");
  FUN_0073b60f();
  return;
}

