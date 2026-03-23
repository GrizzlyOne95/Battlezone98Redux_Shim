
void FUN_00843490(undefined4 *param_1,undefined4 param_2,DWORD *param_3)

{
  uint uVar1;
  DWORD DVar2;
  DWORD DVar3;
  undefined4 uVar4;
  undefined1 local_5c [8];
  undefined1 auStack_54 [68];
  uint local_10;
  void *local_c;
  undefined1 *puStack_8;
  DWORD *local_4;
  
  local_4 = (DWORD *)0xffffffff;
  puStack_8 = &LAB_00865bc8;
  local_c = ExceptionList;
  local_10 = DAT_008e7000 ^ (uint)local_5c;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xffffff94;
  ExceptionList = &local_c;
  DVar2 = GetLastError();
  if (param_3 != (DWORD *)0x0) {
    DVar3 = FUN_0083e820(uVar1);
    *param_3 = DVar2;
    param_3[1] = DVar3;
  }
  if (((((DVar2 == 2) || (DVar2 == 3)) || (DVar2 == 0x7b)) || ((DVar2 == 0xf || (DVar2 == 0x15))))
     || ((DVar2 == 0x57 || ((DVar2 == 0xa1 || (DVar2 == 0x35)))))) {
    *param_1 = 1;
    param_1[1] = 0;
  }
  else if (DVar2 == 0x20) {
    *param_1 = 10;
    param_1[1] = 0xffff;
  }
  else {
    if (param_3 == (DWORD *)0x0) {
      basic_string<>("boost::filesystem::status");
      local_4 = param_3;
      uVar4 = FUN_0083e820(uVar1);
      FUN_00841dd0(local_5c,param_2,DVar2,uVar4);
                    /* WARNING: Subroutine does not return */
      _CxxThrowException(auStack_54,(ThrowInfo *)&DAT_008d8618);
    }
    *param_1 = 0;
    param_1[1] = 0xffff;
  }
  ExceptionList = local_c;
  FUN_0083e885();
  return;
}

