
void __fastcall FUN_00605350(int param_1)

{
  int iVar1;
  bool bVar2;
  char cVar3;
  int iVar4;
  uint uVar5;
  int local_18;
  int local_14;
  
  if ((*(int *)(param_1 + 0xb8) != 0) &&
     (iVar4 = FUN_00462630(*(undefined4 *)(param_1 + 0x14)), iVar4 != 0)) {
    if (*(float *)(param_1 + 0x98) <= 3.0 && *(float *)(param_1 + 0x98) != 3.0) {
      (**(code **)(**(int **)(param_1 + 0xb8) + 0xc))();
    }
    else {
      bVar2 = false;
      iVar1 = *(int *)(*(int *)(*(int *)(param_1 + 0xb8) + 8) + 0xc);
      if (iVar1 == 0x49524546) {
        if ((*(float *)(param_1 + 0x98) < 4.0) || (uVar5 = FUN_0045c4b0(), (uVar5 & 0x30) == 0)) {
          iVar4 = FUN_00417ca0();
          if (iVar4 != 0) {
            for (local_18 = 0; local_18 < 5; local_18 = local_18 + 1) {
              iVar4 = FUN_00417f60(local_18);
              if ((iVar4 != 0) &&
                 ((*(int *)(*(int *)(iVar4 + 8) + 0xc) == 0x494d474c ||
                  (*(int *)(*(int *)(iVar4 + 8) + 0xc) == 0x54484d4c)))) {
                bVar2 = true;
                break;
              }
            }
          }
        }
        else {
          bVar2 = true;
        }
      }
      else if (iVar1 == 0x52444d50) {
        if ((*(float *)(param_1 + 0x98) < 4.0) || (uVar5 = FUN_0045c4b0(), (uVar5 & 0x30) == 0)) {
          iVar4 = (*(code *)**(undefined4 **)(iVar4 + 0x18))();
          if (*(int *)(iVar4 + 0x14) == 0x544f5250) {
            bVar2 = true;
          }
          else {
            iVar4 = FUN_00417ca0();
            if (iVar4 != 0) {
              for (local_14 = 0; local_14 < 5; local_14 = local_14 + 1) {
                iVar4 = FUN_00417f60(local_14);
                if ((iVar4 != 0) && (*(int *)(*(int *)(iVar4 + 8) + 0xc) == 0x5244524c)) {
                  bVar2 = true;
                  break;
                }
              }
            }
          }
        }
        else {
          bVar2 = true;
        }
      }
      if ((bVar2) && (cVar3 = (**(code **)(**(int **)(param_1 + 0xb8) + 0x10))(), cVar3 == '\0')) {
        (**(code **)(**(int **)(param_1 + 0xb8) + 8))();
      }
    }
  }
  return;
}

