
void __fastcall FUN_00844020(HCRYPTPROV *param_1)

{
  uint uVar1;
  BOOL BVar2;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_00865edb;
  local_c = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xffffffec;
  ExceptionList = &local_c;
  local_4 = 0;
  BVar2 = CryptReleaseContext(*param_1,0);
  if (BVar2 == 0) {
    FUN_008440f0("Could not release CSP context",uVar1);
  }
  if (0xf < param_1[6]) {
    operator_delete((void *)param_1[1]);
  }
  param_1[6] = 0xf;
  param_1[5] = 0;
  *(undefined1 *)(param_1 + 1) = 0;
  ExceptionList = local_c;
  return;
}

