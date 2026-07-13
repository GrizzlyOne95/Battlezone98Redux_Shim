
void FUN_00822f40(int param_1,int param_2)

{
  char cVar1;
  float10 fVar2;
  double dVar3;
  float fVar4;
  char *local_10;
  uint local_c;
  
  local_c = 0;
  *(undefined4 *)(param_1 + 0x118) = 0;
  for (local_10 = (char *)(param_1 + 0x10 + *(int *)(param_1 + 0x114));
      local_10 <= (char *)(param_1 + 0x10 + param_2); local_10 = local_10 + 1) {
    fVar2 = (float10)FUN_00689a20(DAT_0091552c,(short)*local_10);
    fVar4 = (float)fVar2;
    dVar3 = (double)(int)local_c + (double)(&DAT_008a2fd0)[-((int)local_c >> 0x1f)];
    local_c = FUN_008445c0();
    if (*(uint *)(param_1 + 8) < local_c) {
      cVar1 = *(char *)(param_1 + 0x10 + *(int *)(param_1 + 0x114));
      *(int *)(param_1 + 0x114) = *(int *)(param_1 + 0x114) + 1;
      fVar2 = (float10)FUN_00689a20(DAT_0091552c,(short)cVar1);
      local_c = FUN_008445c0((double)(int)local_c + (double)(&DAT_008a2fd0)[-((int)local_c >> 0x1f)]
                             ,dVar3,(float)fVar2,fVar4);
      *(uint *)(param_1 + 0x118) = *(int *)(param_1 + 8) - local_c;
    }
  }
  return;
}

