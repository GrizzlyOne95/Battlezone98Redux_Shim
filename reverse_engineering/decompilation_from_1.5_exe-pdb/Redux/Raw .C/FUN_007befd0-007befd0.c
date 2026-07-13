
void __fastcall FUN_007befd0(int param_1)

{
  char cVar1;
  void *pvVar2;
  undefined4 local_24;
  undefined4 local_1c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00861bbc;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  cVar1 = FUN_007d3360(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  (**(code **)(**(int **)(param_1 + 0x15c) + 0x24))(cVar1 == '\0');
  cVar1 = FUN_007d3360();
  (**(code **)(**(int **)(param_1 + 0x160) + 0x24))(cVar1 == '\0');
  cVar1 = FUN_007d3360();
  (**(code **)(**(int **)(param_1 + 0x164) + 0x24))(cVar1 == '\0');
  cVar1 = FUN_007d3360();
  (**(code **)(**(int **)(param_1 + 0x168) + 0x24))(cVar1 == '\0');
  cVar1 = FUN_007d3360();
  if (cVar1 == '\x01') {
    FUN_007c2950(*(undefined4 *)(param_1 + 0x170));
  }
  else {
    FUN_007c2950(*(undefined4 *)(param_1 + 0x174));
  }
  DAT_009455dc = FUN_007d3360();
  if (DAT_009455dc == '\0') {
    local_1c = 0xc;
  }
  else {
    local_1c = 0x1b;
  }
  DAT_008e772c = local_1c;
  FUN_004377c0(local_1c,local_1c,local_1c,local_1c);
  FUN_004378f0();
  if (DAT_009455dc == '\0') {
    FUN_007d3e80(0,0x1d,0);
  }
  else if ((DAT_008e8c7f == '\0') || (DAT_008eaab8 == 0)) {
    FUN_007d3e80(0x3c,0x59,0);
  }
  else {
    FUN_007c1580();
    pvVar2 = operator_new(0x144);
    local_8 = 0;
    if (pvVar2 == (void *)0x0) {
      local_24 = 0;
    }
    else {
      local_24 = FUN_007d1cc0("movie1",0,0,0x44f00000,0x44870000,0x101,param_1,0);
    }
    local_8 = 0xffffffff;
    *(undefined4 *)(param_1 + 0x148) = local_24;
    FUN_007d3f20(10);
    FUN_0078c480(1);
    FUN_007d3850("02TRO_Intro.ogv",0);
    FUN_007d3dd0(0);
    FUN_007d2110(*(undefined4 *)(param_1 + 0x148),0);
  }
  ExceptionList = local_10;
  return;
}

