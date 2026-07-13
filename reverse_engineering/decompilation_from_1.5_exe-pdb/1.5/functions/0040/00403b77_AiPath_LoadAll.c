/*
 * Entry: 00403b77
 * Name: AiPath::LoadAll
 * Namespace: AiPath
 * Signature: bool LoadAll(_iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl AiPath::LoadAll(_iobuf *param_1)

{
  bool bVar1;
  bool bVar2;
  AiPath *pAVar3;
  int iVar4;
  int iVar5;
  int local_8;
  
  bVar1 = ::in(param_1,"[AiPaths]");
  bVar2 = false;
  if (bVar1) {
    bVar2 = ::in(param_1,&local_8,4);
    if (bVar2) {
      if (missionSave != false) {
        do_load_bar(shell_hwnd,0x55);
      }
      iVar5 = 0;
      iVar4 = 0;
      do {
        if (local_8 <= iVar5) break;
        if (missionSave != false) {
          do_load_bar(shell_hwnd,iVar4 / local_8 + 0x55);
        }
        pAVar3 = operator_new(0x1c);
        if (pAVar3 == (AiPath *)0x0) {
          pAVar3 = (AiPath *)0x0;
        }
        else {
          pAVar3 = AiPath(pAVar3);
        }
        bVar2 = Load(pAVar3,param_1);
        iVar5 = iVar5 + 1;
        iVar4 = iVar4 + 0xf;
      } while (bVar2);
      if (missionSave != false) {
        do_load_bar(shell_hwnd,100);
      }
    }
  }
  return bVar2;
}
