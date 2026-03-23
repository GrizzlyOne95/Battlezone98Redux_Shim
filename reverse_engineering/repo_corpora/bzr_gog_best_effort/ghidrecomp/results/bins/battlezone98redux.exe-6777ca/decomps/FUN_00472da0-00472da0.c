
undefined4 __thiscall FUN_00472da0(int param_1,int param_2)

{
  uint uVar1;
  char cVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  float10 fVar7;
  float10 fVar8;
  int local_14;
  
  if (param_2 == 0) {
    uVar3 = 0;
  }
  else {
    uVar4 = FUN_0046fc10();
    if ((uVar4 == 0) || (uVar4 == 9)) {
      uVar3 = 0;
    }
    else if (uVar4 == 1) {
      if (param_2 == param_1) {
        uVar3 = 0;
      }
      else {
        iVar5 = (*(code *)**(undefined4 **)(param_2 + 0x18))();
        if (*(int *)(iVar5 + 0x14) == 0x53435250) {
          uVar3 = 0;
        }
        else {
          iVar5 = (*(code *)**(undefined4 **)(param_2 + 0x18))();
          if (*(int *)(iVar5 + 0x14) == 0x4745495a) {
            if (*(char *)(param_2 + 0x239) == '\0') {
              uVar3 = 3;
            }
            else {
              uVar3 = 0;
            }
          }
          else {
            iVar5 = (*(code *)**(undefined4 **)(param_2 + 0x18))();
            if (*(int *)(iVar5 + 0x1c) == 3) {
              uVar3 = 3;
            }
            else {
              iVar5 = (**(code **)(*(int *)(param_2 + 0x18) + 4))();
              if ((iVar5 == 0) && (cVar2 = FUN_0046fbf0(), cVar2 == '\0')) {
                uVar3 = 0;
              }
              else {
                cVar2 = FUN_004db5b0(param_2);
                if (cVar2 == '\0') {
                  iVar5 = (*(code *)**(undefined4 **)(param_2 + 0x18))();
                  if ((*(int *)(iVar5 + 0x1c) == 1) ||
                     (iVar5 = (*(code *)**(undefined4 **)(param_2 + 0x18))(),
                     *(int *)(iVar5 + 0x1c) == 6)) {
                    uVar3 = 5;
                  }
                  else {
                    iVar5 = (*(code *)**(undefined4 **)(param_2 + 0x18))();
                    if (*(int *)(iVar5 + 0x1c) == 5) {
                      uVar3 = 0;
                    }
                    else {
                      uVar3 = 3;
                    }
                  }
                }
                else {
                  uVar3 = 0;
                }
              }
            }
          }
        }
      }
    }
    else if (uVar4 < 0x1b) {
      uVar3 = 0;
    }
    else {
      iVar5 = (*(code *)**(undefined4 **)(param_2 + 0x18))();
      if (((*(int *)(iVar5 + 0x1c) == 1) ||
          (iVar5 = (*(code *)**(undefined4 **)(param_2 + 0x18))(), *(int *)(iVar5 + 0x1c) == 6)) ||
         (iVar5 = (*(code *)**(undefined4 **)(param_2 + 0x18))(), *(int *)(iVar5 + 0x1c) == 2)) {
        uVar1 = *(uint *)(uVar4 + 0x14);
        if (uVar1 < 0x524b4955) {
          if (uVar1 == 0x524b4954) {
            fVar7 = (float10)FUN_0046fbd0();
            fVar8 = (float10)FUN_004624f0();
            if ((float)fVar7 < (float)fVar8) {
              return 10;
            }
            return 0;
          }
          if (uVar1 == 0x414d4d4f) {
            iVar5 = FUN_00417c80();
            iVar6 = FUN_0046d060();
            if ((iVar5 < iVar6) && (iVar5 = FUN_00417ca0(), iVar5 != 0)) {
              return 0xb;
            }
            return 0;
          }
          if (uVar1 == 0x43504f44) {
            iVar5 = (*(code *)**(undefined4 **)(param_2 + 0x18))();
            if (*(int *)(iVar5 + 0x1c) != 2) {
              return 0xd;
            }
            return 0;
          }
        }
        else {
          if (uVar1 == 0x5745504e) {
            iVar5 = FUN_00417ca0();
            if (iVar5 == 0) {
              return 0;
            }
            FUN_00417ca0();
            iVar5 = *(int *)(*(int *)(uVar4 + 0x170) + 0x74);
            local_14 = 0;
            while( true ) {
              if (4 < local_14) {
                return 0;
              }
              iVar6 = FUN_00417f40(local_14);
              if ((iVar6 != 0) && (*(int *)(iVar6 + 0x84) == iVar5)) break;
              local_14 = local_14 + 1;
            }
            return 0xc;
          }
          if (uVar1 == 0x5752434b) {
            iVar5 = (*(code *)**(undefined4 **)(param_2 + 0x18))();
            if ((*(int *)(iVar5 + 0x14) == 0x4745495a) && (*(char *)(param_2 + 0x239) != '\0')) {
              return 0;
            }
            return 0xe;
          }
        }
        uVar3 = 0;
      }
      else {
        uVar4 = *(uint *)(uVar4 + 0x14);
        if (uVar4 < 0x5745504f) {
          if (uVar4 == 0x5745504e) {
            iVar5 = (*(code *)**(undefined4 **)(param_2 + 0x18))();
            if (*(int *)(iVar5 + 0x14) == 0x43504f44) {
              return 0xc;
            }
            return 0;
          }
          if (uVar4 == 0x414d4d4f) {
            iVar5 = (*(code *)**(undefined4 **)(param_2 + 0x18))();
            if (*(int *)(iVar5 + 0x14) == 0x43504f44) {
              return 0xb;
            }
            return 0;
          }
          if (uVar4 == 0x524b4954) {
            iVar5 = (*(code *)**(undefined4 **)(param_2 + 0x18))();
            if (*(int *)(iVar5 + 0x14) == 0x43504f44) {
              return 10;
            }
            return 0;
          }
        }
        else if (uVar4 == 0x5752434b) {
          return 0xe;
        }
        uVar3 = 0;
      }
    }
  }
  return uVar3;
}

