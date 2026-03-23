
void __fastcall FUN_007ba370(int param_1)

{
  char *_Str2;
  char *_Str1;
  int iVar1;
  void *pvVar2;
  undefined4 uVar3;
  undefined4 local_1c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0086167c;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  if (*(int *)(param_1 + 0x14c) != 0) {
    FUN_007ba270(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  }
  _Str2 = (char *)FUN_0081cb40("multi_error","empty");
  _Str1 = (char *)FUN_007c2980();
  iVar1 = _stricmp(_Str1,_Str2);
  if (iVar1 == 0) {
    FUN_007ba2e0();
    FUN_007c79a0();
  }
  else {
    pvVar2 = operator_new(0x15c);
    local_8 = 0;
    if (pvVar2 == (void *)0x0) {
      local_1c = 0;
    }
    else {
      local_1c = FUN_007c1ef0("Alert",0x44548000,0x42c80000,0x43e10000,0x43610000,0x120,
                              *(undefined4 *)(param_1 + 0x144));
    }
    local_8 = 0xffffffff;
    *(undefined4 *)(param_1 + 0x14c) = local_1c;
    uVar3 = FUN_0081cb40("save_load","overwrite");
    FUN_007c2400(uVar3);
    FUN_007c23c0(FUN_007ba220);
    FUN_007c23e0(FUN_007ba210);
    FUN_007d2110(*(undefined4 *)(param_1 + 0x14c),0);
  }
  ExceptionList = local_10;
  return;
}

