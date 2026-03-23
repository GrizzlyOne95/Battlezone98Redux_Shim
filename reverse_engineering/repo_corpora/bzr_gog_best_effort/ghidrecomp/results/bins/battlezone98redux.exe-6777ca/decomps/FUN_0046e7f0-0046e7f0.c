
void FUN_0046e7f0(undefined4 param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined1 local_10 [4];
  undefined1 local_c [4];
  undefined1 local_8 [4];
  
  FID_conflict_begin(local_8);
  while( true ) {
    uVar2 = FID_conflict_end(local_c);
    cVar1 = FID_conflict_operator__(uVar2);
    if (cVar1 == '\0') break;
    uVar2 = param_1;
    FUN_0046b260(local_10,0);
    FUN_00421ec0(uVar2);
    FUN_0046e1e0(uVar2);
  }
  return;
}

