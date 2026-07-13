/*
 * Entry: 00478a92
 * Name: Debug_ExceptionFilter
 * Namespace: Global
 * Signature: long Debug_ExceptionFilter(_EXCEPTION_POINTERS * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl Debug_ExceptionFilter(_EXCEPTION_POINTERS *param_1)

{
  float fVar1;
  int iVar2;
  char_0_ *pcVar3;
  
  pcVar3 = &msn_filename;
  iVar2 = useD3D;
  fVar1 = Get_Time();
  sprintf(line,"t%f D3D%x msn(%s)",(double)fVar1,iVar2,pcVar3);
  dpReportCrashEx(param_1,line);
  return (uint)(param_1->ExceptionRecord->ExceptionCode != 0xe0000002) * 2 + -1;
}
