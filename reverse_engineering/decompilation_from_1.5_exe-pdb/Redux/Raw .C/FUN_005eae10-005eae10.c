
void __thiscall FUN_005eae10(int param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  float10 fVar3;
  
  iVar2 = FUN_005c8800(param_2);
  if (iVar2 == 1) {
    cVar1 = FUN_005c8410(param_2,"avscav");
    if ((cVar1 != '\0') && (*(int *)(param_1 + 0xb4) == 0)) {
      *(undefined1 *)(param_1 + 0x57) = 1;
      *(undefined4 *)(param_1 + 0xb4) = param_2;
      FUN_005caff0(*(undefined4 *)(param_1 + 0xb4),1);
    }
  }
  iVar2 = FUN_005c8800(param_2);
  if (iVar2 == 2) {
    cVar1 = FUN_005c8410(param_2,"svfigh");
    if (cVar1 != '\0') {
      if (*(char *)(param_1 + 0x58) == '\0') {
        *(undefined1 *)(param_1 + 0x58) = 1;
        *(undefined4 *)(param_1 + 0xc4) = param_2;
        FUN_005cb960(*(undefined4 *)(param_1 + 0xc4),"patrol1",0);
        FUN_005c95e0(*(undefined4 *)(param_1 + 0xc4));
      }
      else {
        fVar3 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xb4),
                                      *(undefined4 *)(param_1 + 0xc0));
        if (200.0 <= (float)fVar3) {
          FUN_005cb960(param_2,"patrol2",0);
        }
        else {
          FUN_005cb820(param_2,*(undefined4 *)(param_1 + 0xb4),1);
        }
      }
    }
  }
  return;
}

