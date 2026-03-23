
undefined4 * __thiscall
FUN_006ad2a0(int param_1,undefined4 *param_2,HANDLE param_3,undefined4 *param_4)

{
  HANDLE pvVar1;
  DWORD DVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  
  pvVar1 = CreateIoCompletionPort(param_3,*(HANDLE *)(param_1 + 0x14),0,0);
  if (pvVar1 == (HANDLE)0x0) {
    DVar2 = GetLastError();
    uVar3 = FUN_006abbb0();
    puVar4 = (undefined4 *)FUN_00416430(DVar2,uVar3);
    uVar3 = puVar4[1];
    *param_4 = *puVar4;
    param_4[1] = uVar3;
  }
  else {
    puVar4 = (undefined4 *)FUN_004fbb60();
    uVar3 = puVar4[1];
    *param_4 = *puVar4;
    param_4[1] = uVar3;
  }
  uVar3 = param_4[1];
  *param_2 = *param_4;
  param_2[1] = uVar3;
  return param_2;
}

