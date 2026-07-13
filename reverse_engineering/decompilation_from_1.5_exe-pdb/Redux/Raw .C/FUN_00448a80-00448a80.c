
HANDLE FUN_00448a80(LPCSTR param_1,BOOL param_2,BOOL param_3)

{
  HANDLE pvVar1;
  
  pvVar1 = CreateEventA((LPSECURITY_ATTRIBUTES)0x0,param_2,param_3,param_1);
  return pvVar1;
}

