/*
 * Entry: 00403f39
 * Name: AiTask::LoadAll
 * Namespace: AiTask
 * Signature: bool LoadAll(_iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl AiTask::LoadAll(_iobuf *param_1)

{
  bool bVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  int local_8;
  
  bVar1 = ::in(param_1,"[AiTasks]");
  bVar2 = false;
  if (bVar1) {
    bVar2 = ::in(param_1,&local_8,4);
    do_load_bar(shell_hwnd,0x5a);
    iVar3 = 0;
    if (bVar2) {
      iVar4 = 0;
      for (; iVar3 < local_8; iVar3 = iVar3 + 1) {
        do_load_bar(shell_hwnd,iVar4 / local_8 + 0x5a);
        RtimeClass::Load(param_1);
        iVar4 = iVar4 + 10;
      }
    }
    do_load_bar(shell_hwnd,100);
  }
  return bVar2;
}
