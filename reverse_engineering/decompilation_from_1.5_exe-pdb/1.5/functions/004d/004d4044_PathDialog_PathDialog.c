/*
 * Entry: 004d4044
 * Name: PathDialog::PathDialog
 * Namespace: PathDialog
 * Signature: PathDialog * PathDialog(PathDialog * this, AiPath * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PathDialog * __thiscall PathDialog::PathDialog(PathDialog *this,AiPath *param_1)

{
  char cVar1;
  AOI *pAVar2;
  char *pcVar3;
  char *pcVar4;
  
  aiPath = param_1;
  pAVar2 = AOI::Find(param_1);
  pcVar4 = param_1->label;
  pcVar3 = pathName;
  area = pAVar2;
  do {
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    *pcVar3 = cVar1;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  if (pAVar2 != (AOI *)0x0) {
    isInteresting = pAVar2->interesting;
    isInside = pAVar2->inside;
    areaValue = pAVar2->value;
    defendArea = pAVar2->force < 100;
    areaForce = pAVar2->force - (defendArea - 1 & 100);
  }
  else {
    areaValue = 0;
    areaForce = 0;
    isInteresting = false;
    isInside = true;
    defendArea = true;
  }
  isArea = pAVar2 != (AOI *)0x0;
  cancelled = true;
  return this;
}
