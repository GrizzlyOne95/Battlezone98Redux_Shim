
undefined4 * __thiscall
FUN_006b16a0(int param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4)

{
  char cVar1;
  HMODULE hModule;
  FARPROC pFVar2;
  int iVar3;
  DWORD DVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  char *lpProcName;
  
  cVar1 = FUN_006b1390(param_3);
  if (cVar1 == '\0') {
    FUN_006d8cf0(0x2719);
    uVar6 = param_4[1];
    *param_2 = *param_4;
    param_2[1] = uVar6;
  }
  else {
    lpProcName = "CancelIoEx";
    hModule = GetModuleHandleA("KERNEL32");
    pFVar2 = GetProcAddress(hModule,lpProcName);
    if (pFVar2 == (FARPROC)0x0) {
      FUN_006d8cf0(0x273d);
    }
    else {
      iVar3 = (*pFVar2)(*param_3,0);
      if (iVar3 == 0) {
        DVar4 = GetLastError();
        if (DVar4 == 0x490) {
          puVar5 = (undefined4 *)FUN_004fbb60();
          uVar6 = puVar5[1];
          *param_4 = *puVar5;
          param_4[1] = uVar6;
        }
        else {
          uVar6 = FUN_006abbb0();
          puVar5 = (undefined4 *)FUN_00416430(DVar4,uVar6);
          uVar6 = puVar5[1];
          *param_4 = *puVar5;
          param_4[1] = uVar6;
        }
      }
      else {
        puVar5 = (undefined4 *)FUN_004fbb60();
        uVar6 = puVar5[1];
        *param_4 = *puVar5;
        param_4[1] = uVar6;
      }
    }
    cVar1 = FUN_004c85a0();
    if ((cVar1 != '\0') && (iVar3 = FUN_006b20f0(param_1 + 8,0,0), iVar3 != 0)) {
      FUN_006b0bb0(*param_3,param_3 + 4);
    }
    uVar6 = param_4[1];
    *param_2 = *param_4;
    param_2[1] = uVar6;
  }
  return param_2;
}

