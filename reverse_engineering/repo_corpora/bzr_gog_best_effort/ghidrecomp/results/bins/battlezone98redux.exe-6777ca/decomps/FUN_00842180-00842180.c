
void FUN_00842180(LPCWSTR param_1,DWORD *param_2)

{
  uint uVar1;
  LPCWSTR lpPathName;
  BOOL BVar2;
  DWORD DVar3;
  DWORD DVar4;
  undefined4 uVar5;
  undefined4 local_6c;
  undefined4 local_68;
  int local_64 [2];
  undefined1 local_5c [8];
  undefined1 auStack_54 [68];
  uint local_10;
  void *local_c;
  undefined1 *puStack_8;
  DWORD *local_4;
  
  local_4 = (DWORD *)0xffffffff;
  puStack_8 = &LAB_00865a58;
  local_c = ExceptionList;
  local_10 = DAT_008e7000 ^ (uint)&local_6c;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xffffff88;
  ExceptionList = &local_c;
  lpPathName = param_1;
  if (7 < *(uint *)(param_1 + 10)) {
    lpPathName = *(LPCWSTR *)param_1;
  }
  BVar2 = CreateDirectoryW(lpPathName,(LPSECURITY_ATTRIBUTES)0x0);
  if (BVar2 == 0) {
    DVar3 = GetLastError();
    local_6c = 0;
    local_68 = FUN_0083e820(uVar1);
    if ((DVar3 == 0xb7) && (FUN_008438a0(local_64,param_1,&local_6c), local_64[0] == 3)) {
      if (param_2 == (DWORD *)0x0) goto LAB_00842284;
      *param_2 = 0;
      DVar4 = FUN_0083e820(uVar1);
    }
    else {
      if (param_2 == (DWORD *)0x0) {
        basic_string<>("boost::filesystem::create_directory");
        local_4 = param_2;
        uVar5 = FUN_0083e820();
        FUN_00841dd0(local_5c,param_1,DVar3,uVar5);
                    /* WARNING: Subroutine does not return */
        _CxxThrowException(auStack_54,(ThrowInfo *)&DAT_008d8618);
      }
      DVar4 = FUN_0083e820(uVar1);
      *param_2 = DVar3;
    }
    param_2[1] = DVar4;
  }
  else if (param_2 != (DWORD *)0x0) {
    *param_2 = 0;
    DVar3 = FUN_0083e820(uVar1);
    param_2[1] = DVar3;
  }
LAB_00842284:
  ExceptionList = local_c;
  FUN_0083e885();
  return;
}

