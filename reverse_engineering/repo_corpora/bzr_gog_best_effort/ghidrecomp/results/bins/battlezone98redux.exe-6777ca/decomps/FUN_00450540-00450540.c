
void FUN_00450540(void)

{
  char cVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  undefined1 local_20 [8];
  undefined1 local_18 [4];
  undefined4 local_14;
  undefined1 local_10 [11];
  char local_5;
  
  FUN_0044ef90(local_10);
  puVar3 = local_10;
  FUN_0044fd20(local_18);
  cVar1 = FUN_00420f10(puVar3);
  if (cVar1 != '\0') {
    FUN_0044f170();
    do {
      FUN_0044fd20(&local_14);
      local_5 = FUN_004221b0(local_10);
      uVar2 = FUN_0042de50(local_14);
      FUN_0044fdc0(local_20,uVar2);
    } while (local_5 == '\0');
  }
  return;
}

