
void FUN_004ce120(void)

{
  char cVar1;
  char *pcVar2;
  
  do {
    cVar1 = *DAT_0260db08;
    pcVar2 = DAT_0260db08 + 1;
    if (pcVar2 == DAT_0260db00) {
      return;
    }
    DAT_0260db08 = pcVar2;
  } while (cVar1 != '=');
  return;
}

