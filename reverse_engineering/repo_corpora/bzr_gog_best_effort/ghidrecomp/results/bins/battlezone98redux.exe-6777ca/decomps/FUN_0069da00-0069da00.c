
void __fastcall FUN_0069da00(int param_1)

{
  int iVar1;
  bool bVar2;
  
  iVar1 = *(int *)(*(int *)(*(int *)(*(int *)(param_1 + 0x3c) + 0x90) + *(int *)(param_1 + 0x40) * 4
                           ) + *(int *)(param_1 + 0x44) * 4);
  if (iVar1 == 0) {
    if (*(int *)(*(int *)(*(int *)(*(int *)(param_1 + 0x3c) + 0x94) + *(int *)(param_1 + 0x40) * 4)
                + *(int *)(param_1 + 0x44) * 4) < 2) {
      *(undefined4 *)(param_1 + 4) = 4;
    }
    else {
      *(undefined4 *)(param_1 + 4) = 0;
    }
  }
  else {
    bVar2 = *(int *)(*(int *)(*(int *)(*(int *)(param_1 + 0x3c) + 0x88) +
                             *(int *)(param_1 + 0x40) * 4) + *(int *)(param_1 + 0x44) * 4) == 1;
    if (((((*(int *)(param_1 + 0x48) != 0) || (*(float *)(param_1 + 100) != 0.0)) ||
         (*(float *)(param_1 + 0x60) != 0.0)) || ((*(int *)(param_1 + 0x5c) != 0 || (iVar1 != 1))))
       || ((*(int *)(param_1 + 0x68) != 0 || (bVar2)))) {
      if (*(float *)(param_1 + 0x60) <= 0.0) {
        if ((*(int *)(param_1 + 0x48) != 0) || (*(float *)(param_1 + 100) <= 0.0)) {
          if (*(int *)(param_1 + 0x48) < 1) {
            if (*(int *)(param_1 + 0x5c) < 1) {
              if (*(int *)(param_1 + 0x68) < 1) {
                if (bVar2) {
                  *(undefined4 *)(param_1 + 4) = 6;
                }
                else if (iVar1 == 2) {
                  *(undefined4 *)(param_1 + 4) = 7;
                }
                else {
                  *(undefined4 *)(param_1 + 4) = 0;
                }
              }
              else {
                *(undefined4 *)(param_1 + 4) = 5;
              }
            }
            else {
              *(undefined4 *)(param_1 + 4) = 8;
            }
          }
          else {
            *(undefined4 *)(param_1 + 4) = 2;
          }
        }
        else {
          *(undefined4 *)(param_1 + 4) = 1;
        }
      }
      else {
        *(undefined4 *)(param_1 + 4) = 3;
      }
    }
    else {
      *(undefined4 *)(param_1 + 4) = 0;
    }
  }
  return;
}

