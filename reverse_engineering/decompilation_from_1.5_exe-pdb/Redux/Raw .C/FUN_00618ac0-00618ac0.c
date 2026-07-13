
void FUN_00618ac0(void)

{
  DWORD DVar1;
  undefined4 uVar2;
  basic_ostream<char,struct_std::char_traits<char>_> *this;
  HANDLE hThread;
  code *pcVar3;
  
  DVar1 = GetCurrentThreadId();
  if (DAT_02a13e88 == DVar1) {
    pcVar3 = FUN_004bc8c0;
    FUN_0081e820("std::terminate called from main thread, forced to abort application");
    uVar2 = FUN_0081e660();
    this = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(uVar2);
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(this,pcVar3);
                    /* WARNING: Subroutine does not return */
    abort();
  }
  DVar1 = 0x69;
  hThread = GetCurrentThread();
  TerminateThread(hThread,DVar1);
  return;
}

