/*
 * Entry: 0040330b
 * Name: AiPath::SetLabel
 * Namespace: AiPath
 * Signature: void SetLabel(AiPath * this, char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall AiPath::SetLabel(AiPath *this,char *param_1)

{
  char cVar1;
  char *pcVar2;
  
  if (this->label != (char *)0x0) {
    operator_delete__(this->label);
  }
  pcVar2 = param_1;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  pcVar2 = operator_new__((uint)(pcVar2 + (1 - (int)(param_1 + 1))));
  this->label = pcVar2;
  do {
    cVar1 = *param_1;
    param_1 = param_1 + 1;
    *pcVar2 = cVar1;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  return;
}
