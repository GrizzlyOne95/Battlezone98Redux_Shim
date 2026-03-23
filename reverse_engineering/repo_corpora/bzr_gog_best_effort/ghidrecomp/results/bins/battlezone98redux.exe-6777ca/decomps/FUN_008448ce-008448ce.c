
int __fastcall FUN_008448ce(undefined4 param_1,uint param_2)

{
  int iVar1;
  int in_EAX;
  
  if (param_2 == 0) {
    return in_EAX;
  }
  iVar1 = 0x1f;
  if (param_2 != 0) {
    for (; param_2 >> iVar1 == 0; iVar1 = iVar1 + -1) {
    }
  }
  return 0x20 - iVar1;
}

