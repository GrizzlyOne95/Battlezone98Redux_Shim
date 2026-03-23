
void FUN_008438a0(undefined4 *param_1,LPCWSTR param_2,undefined4 *param_3)

{
  char cVar1;
  uint uVar2;
  LPCWSTR pWVar3;
  LPCWSTR ***lpFileName;
  HANDLE hObject;
  undefined4 uVar4;
  HANDLE local_34;
  undefined4 local_30;
  DWORD local_2c;
  LPCWSTR **local_28 [4];
  undefined4 local_18;
  uint local_14;
  uint local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00865da0;
  local_c = ExceptionList;
  local_10 = DAT_008e7000 ^ (uint)&local_34;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xffffffbc;
  ExceptionList = &local_c;
  pWVar3 = param_2;
  if (7 < *(uint *)(param_2 + 10)) {
    pWVar3 = *(LPCWSTR *)param_2;
  }
  local_2c = GetFileAttributesW(pWVar3);
  if (local_2c == 0xffffffff) {
LAB_008438fa:
    FUN_00843490(param_1,param_2,param_3);
  }
  else {
    if ((local_2c & 0x400) != 0) {
      pWVar3 = param_2;
      if (7 < *(uint *)(param_2 + 10)) {
        pWVar3 = *(LPCWSTR *)param_2;
      }
      FUN_0083f930(pWVar3);
      lpFileName = local_28;
      if (7 < local_14) {
        lpFileName = (LPCWSTR ***)local_28[0];
      }
      local_4 = 0;
      hObject = CreateFileW((LPCWSTR)lpFileName,0,7,(LPSECURITY_ATTRIBUTES)0x0,3,0x2000000,
                            (HANDLE)0x0);
      local_4 = CONCAT31(local_4._1_3_,2);
      local_34 = hObject;
      if (7 < local_14) {
        operator_delete(local_28[0]);
      }
      local_14 = 7;
      local_18 = 0;
      local_28[0] = (LPCWSTR **)((uint)local_28[0] & 0xffff0000);
      if (hObject == (HANDLE)0xffffffff) goto LAB_008438fa;
      cVar1 = FUN_00842ef0(param_2,uVar2);
      if (cVar1 == '\0') {
        uVar4 = FUN_008430e0(param_2,local_2c);
        *param_1 = 9;
        param_1[1] = uVar4;
        local_4 = 0xffffffff;
        CloseHandle(hObject);
        goto LAB_00843a20;
      }
      local_4 = 0xffffffff;
      CloseHandle(hObject);
    }
    if (param_3 != (undefined4 *)0x0) {
      *param_3 = 0;
      uVar4 = FUN_0083e820();
      param_3[1] = uVar4;
    }
    local_34 = (HANDLE)0x3;
    if ((local_2c & 0x10) == 0) {
      local_34 = (HANDLE)0x2;
    }
    local_30 = FUN_008430e0(param_2,local_2c);
    *param_1 = local_34;
    param_1[1] = local_30;
  }
LAB_00843a20:
  ExceptionList = local_c;
  FUN_0083e885();
  return;
}

