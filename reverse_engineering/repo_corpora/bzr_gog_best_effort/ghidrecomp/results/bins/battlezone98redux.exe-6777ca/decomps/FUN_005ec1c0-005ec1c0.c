
void FUN_005ec1c0(int param_1,int *param_2)

{
  while( true ) {
    if (param_1 == 0) {
      return;
    }
    if (*(int *)(param_1 + 0x84) == 0x4a) break;
    if ((*(int *)(param_1 + 0x80) != 0) &&
       (FUN_005ec1c0(*(undefined4 *)(param_1 + 0x80),param_2), *param_2 != 0)) {
      return;
    }
    param_1 = *(int *)(param_1 + 0x7c);
  }
  *param_2 = param_1;
  return;
}

