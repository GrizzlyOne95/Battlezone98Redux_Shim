/*
 * Entry: 00527751
 * Name: LoadMission
 * Namespace: Global
 * Signature: int LoadMission(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl LoadMission(char *param_1)

{
  char cVar1;
  undefined4 *puVar2;
  char *pcVar3;
  int iVar4;
  undefined4 *puVar5;
  char local_31c [4];
  char local_318 [256];
  char local_218 [256];
  char local_118 [255];
  undefined4 uStack_19;
  undefined1 auStack_14 [12];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  ObjLoadInit();
  strncpy((char *)((int)&uStack_19 + 1),param_1,0xf);
  _splitpath((char *)((int)&uStack_19 + 1),local_31c,local_318,local_118,local_218);
  pcVar3 = local_118;
  msnType = 0;
  do {
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  if ((int)pcVar3 - (int)(local_118 + 1) == 3) {
    msnNum = atol(local_118 + 1);
    if (0 < msnNum) {
      if (local_118[0] == 'm') {
        msnType = 1;
      }
      else if (local_118[0] == 't') {
        msnType = 2;
      }
      else if (local_118[0] == 's') {
        msnType = 3;
      }
    }
  }
  if (local_218[0] == '\0') {
    puVar2 = &uStack_19;
    do {
      puVar5 = puVar2;
      puVar2 = (undefined4 *)((int)puVar5 + 1);
    } while (*(char *)((int)puVar5 + 1) != '\0');
    *(undefined4 *)((int)puVar5 + 1) = 0x6e736d2e;
    *(undefined1 *)((int)puVar5 + 5) = 0;
  }
  iVar4 = ReadBWD2File((char *)((int)&uStack_19 + 1),TopLevelChunkDefs,7,(void *)0x0);
  if (iVar4 == 0) {
    DEBUG_systemError("Mission file %s not found. Exiting");
  }
  return 1;
}
