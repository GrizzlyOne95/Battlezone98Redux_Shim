/*
 * Entry: 005c7726
 * Name: __report_gsfailure
 * Namespace: Global
 * Signature: void __report_gsfailure(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl __report_gsfailure(void)

{
  ulong in_EAX;
  HANDLE hProcess;
  ulong in_ECX;
  ulong in_EDX;
  ulong unaff_EBX;
  ulong unaff_EBP;
  ulong unaff_ESI;
  ulong unaff_EDI;
  undefined2 in_ES;
  undefined2 in_CS;
  undefined2 in_SS;
  undefined2 in_DS;
  undefined2 in_FS;
  undefined2 in_GS;
  byte in_AF;
  byte in_TF;
  byte in_IF;
  byte in_NT;
  byte in_AC;
  byte in_VIF;
  byte in_VIP;
  byte in_ID;
  void *unaff_retaddr;
  UINT uExitCode;
  uint local_32c;
  uint local_328;
  
  GS_ContextRecord.EFlags =
       (uint)(in_NT & 1) * 0x4000 | (uint)SBORROW4((int)&stack0xfffffffc,0x328) * 0x800 |
       (uint)(in_IF & 1) * 0x200 | (uint)(in_TF & 1) * 0x100 | (uint)((int)&local_32c < 0) * 0x80 |
       (uint)(&stack0x00000000 == (undefined1 *)0x32c) * 0x40 | (uint)(in_AF & 1) * 0x10 |
       (uint)((POPCOUNT((uint)&local_32c & 0xff) & 1U) == 0) * 4 |
       (uint)(&stack0xfffffffc < (undefined1 *)0x328) | (uint)(in_ID & 1) * 0x200000 |
       (uint)(in_VIP & 1) * 0x100000 | (uint)(in_VIF & 1) * 0x80000 | (uint)(in_AC & 1) * 0x40000;
  GS_ContextRecord.Esp = (ulong)&stack0x00000004;
  GS_ContextRecord.ContextFlags = 0x10001;
  GS_ExceptionRecord.ExceptionCode = 0xc0000409;
  GS_ExceptionRecord.ExceptionFlags = 1;
  local_32c = __security_cookie;
  local_328 = __security_cookie_complement;
  GS_ExceptionRecord.ExceptionAddress = unaff_retaddr;
  GS_ContextRecord.SegGs._0_2_ = in_GS;
  GS_ContextRecord.SegFs._0_2_ = in_FS;
  GS_ContextRecord.SegEs._0_2_ = in_ES;
  GS_ContextRecord.SegDs._0_2_ = in_DS;
  GS_ContextRecord.Edi = unaff_EDI;
  GS_ContextRecord.Esi = unaff_ESI;
  GS_ContextRecord.Ebx = unaff_EBX;
  GS_ContextRecord.Edx = in_EDX;
  GS_ContextRecord.Ecx = in_ECX;
  GS_ContextRecord.Eax = in_EAX;
  GS_ContextRecord.Ebp = unaff_EBP;
  GS_ContextRecord.Eip = (ulong)unaff_retaddr;
  GS_ContextRecord.SegCs._0_2_ = in_CS;
  GS_ContextRecord.SegSs._0_2_ = in_SS;
  DebuggerWasPresent = IsDebuggerPresent();
  crt_debugger_hook(1);
  SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)0x0);
  UnhandledExceptionFilter((_EXCEPTION_POINTERS *)&GS_ExceptionPointers);
  if (DebuggerWasPresent == 0) {
    crt_debugger_hook(1);
  }
  uExitCode = 0xc0000409;
  hProcess = GetCurrentProcess();
  TerminateProcess(hProcess,uExitCode);
  return;
}
