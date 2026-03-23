
undefined4
FUN_00843b70(undefined4 param_1,LPCWSTR param_2,int param_3,int *param_4,LPSTR param_5,int param_6,
            undefined4 *param_7)

{
  BOOL BVar1;
  int iVar2;
  
  BVar1 = AreFileApisANSI();
  iVar2 = WideCharToMultiByte((uint)(BVar1 == 0),0x400,param_2,param_3 - (int)param_2 >> 1,param_5,
                              param_6 - (int)param_5,(LPCSTR)0x0,(LPBOOL)0x0);
  if (iVar2 == 0) {
    return 2;
  }
  *param_4 = param_3;
  *param_7 = param_5 + iVar2;
  param_5[iVar2] = '\0';
  return 0;
}

