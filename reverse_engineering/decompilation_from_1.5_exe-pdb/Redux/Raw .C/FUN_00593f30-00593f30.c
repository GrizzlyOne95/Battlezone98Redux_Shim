
void __fastcall FUN_00593f30(int param_1)

{
  uint uVar1;
  void *pvVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084b95c;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  if (*(char *)(param_1 + 0x35) == '\0') {
    if (*(char *)(param_1 + 0x34) == '\0') {
      *(int *)(param_1 + 0x30) = *(int *)(param_1 + 0x30) + 100;
    }
    FUN_00460de0(param_1);
    if ((DAT_02a13cbc == 0) && (*(char *)(param_1 + 0x28) != '\0')) {
      pvVar2 = operator_new(0x18);
      local_8 = 0;
      if (pvVar2 != (void *)0x0) {
        FUN_0046f190(*(undefined4 *)(param_1 + 0x38),2,*(undefined1 *)(param_1 + 0x29),
                     *(undefined1 *)(param_1 + 0x2a),*(undefined4 *)(param_1 + 0x2c),
                     *(undefined4 *)(param_1 + 0x30));
      }
      local_8 = 0xffffffff;
    }
    else if ((DAT_02a13cbc != 0) && (*(char *)(param_1 + 0x28) == '\0')) {
      if (DAT_02a13cbc != 0) {
        FUN_0046f0c0(1);
      }
      DAT_02a13cbc = 0;
    }
    if (DAT_02a13cbc != 0) {
      *(undefined1 *)(DAT_02a13cbc + 8) = *(undefined1 *)(param_1 + 0x29);
      *(undefined1 *)(DAT_02a13cbc + 9) = *(undefined1 *)(param_1 + 0x2a);
      if (*(char *)(param_1 + 0x29) == '\0') {
        *(undefined4 *)(param_1 + 0x2c) = 0xffffffff;
        *(undefined4 *)(param_1 + 0x30) = 0;
      }
      *(undefined4 *)(DAT_02a13cbc + 0xc) = *(undefined4 *)(param_1 + 0x2c);
      *(undefined4 *)(DAT_02a13cbc + 0x10) = *(undefined4 *)(param_1 + 0x30);
    }
    FUN_0046f160(uVar1);
  }
  ExceptionList = local_10;
  return;
}

