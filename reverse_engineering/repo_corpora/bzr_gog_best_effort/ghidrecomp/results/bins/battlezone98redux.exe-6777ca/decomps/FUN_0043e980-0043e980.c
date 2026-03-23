
void FUN_0043e980(void)

{
  HANDLE pvVar1;
  uintptr_t uVar2;
  int local_8;
  
  FUN_0081e1e0("Initializing music handler\n");
  if (DAT_00915529 == '\0') {
    FUN_0043e770();
  }
  DAT_0260cacc = CreateEventA((LPSECURITY_ATTRIBUTES)0x0,1,0,(LPCSTR)0x0);
  for (local_8 = 0; local_8 < 2; local_8 = local_8 + 1) {
    (&DAT_0260cdd4)[local_8 * 0x310] = 0;
    InitializeCriticalSection((LPCRITICAL_SECTION)(&DAT_0260cdbc + local_8 * 0x310));
    pvVar1 = CreateEventA((LPSECURITY_ATTRIBUTES)0x0,0,0,(LPCSTR)0x0);
    *(HANDLE *)(&DAT_0260cac8 + local_8 * 0x310) = pvVar1;
    (&DAT_0260cacc)[local_8 * 0xc4] = DAT_0260cacc;
    uVar2 = _beginthreadex((void *)0x0,0,FUN_0043e8a0,&DAT_0260cac8 + local_8 * 0x310,0,
                           (uint *)(&DAT_0260cad0 + local_8 * 0x310));
    *(uintptr_t *)(&DAT_0260cad4 + local_8 * 0x310) = uVar2;
    SetThreadPriority(*(HANDLE *)(&DAT_0260cad4 + local_8 * 0x310),1);
  }
  return;
}

