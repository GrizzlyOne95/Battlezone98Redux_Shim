/*
 * Entry: 004dd990
 * Name: Net_CreateMission
 * Namespace: Global
 * Signature: void Net_CreateMission(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Unable to track spacebase fully for stack */

void __cdecl Net_CreateMission(void)

{
  char cVar1;
  code *pcVar2;
  int iVar3;
  char *pcVar4;
  char *pcVar5;
  AiMission *pAVar6;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  int iStack_14;
  
  pcVar5 = Net::MissionFileName;
  do {
    pcVar4 = pcVar5;
    pcVar5 = pcVar4 + 1;
  } while (*pcVar4 != '\0');
  iStack_14 = 0x4dd9b9;
  iVar3 = -(int)(pcVar4 + -0xba7287);
  pcVar5 = Net::MissionFileName;
  do {
    cVar1 = *pcVar5;
    pcVar5[(int)(&stack0xff458d68 + iVar3)] = cVar1;
    pcVar5 = pcVar5 + 1;
  } while (cVar1 != '\0');
  *(undefined4 *)((int)&iStack_14 + iVar3) = 0x2e;
  *(undefined1 **)((int)&uStack_18 + iVar3) = &stack0xfffffff0 + iVar3;
  *(undefined4 *)((int)&uStack_1c + iVar3) = 0x4dd9d4;
  pcVar5 = strchr(*(char **)((int)&uStack_18 + iVar3),*(int *)((int)&iStack_14 + iVar3));
  if (pcVar5 != (char *)0x0) {
    *pcVar5 = '\0';
  }
  *(undefined4 *)((int)&iStack_14 + iVar3) = 0x4dd9e2;
  pAVar6 = AiMission::GetCurrent();
  if (pAVar6 == (AiMission *)0x0) {
    *(undefined1 **)((int)&iStack_14 + iVar3) = &stack0xfffffff0 + iVar3;
    *(undefined4 *)((int)&uStack_18 + iVar3) = 0x4dd9f5;
    AiMission::Create(*(char **)((int)&iStack_14 + iVar3));
  }
  else {
    pcVar2 = *(code **)(pAVar6->_padding_ + 0x38);
    *(undefined4 *)((int)&iStack_14 + iVar3) = 0x4dd9ed;
    (*pcVar2)();
  }
  return;
}
