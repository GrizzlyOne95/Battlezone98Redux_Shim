/*
 * Entry: 004ec0ac
 * Name: InitObjectives
 * Namespace: Global
 * Signature: int InitObjectives(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl InitObjectives(void)

{
  OBJECTIVE_DATA *pOVar1;
  long *plVar2;
  long lVar3;
  
  lVar3 = 0x7c;
  plVar2 = (long *)0x0;
  pOVar1 = &od;
  memset();
  od.FailMessageNum = -1;
  lVar3 = GetObjectiveText((char **)0x6,0xd3fee0,(long *)0x10,(char **)od.ObjState,0x100,
                           &pOVar1->NumObjs,plVar2,lVar3);
  if (lVar3 < 1) {
    if (lVar3 == 0) {
      DEBUG_systemWarning("No objective text found. The Notepad is unavailable");
    }
    else {
      od.NumObjs = -1;
    }
    return 0;
  }
  return 1;
}
