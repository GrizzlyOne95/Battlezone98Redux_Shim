
void __fastcall FUN_00638e70(int param_1)

{
  undefined4 local_10;
  undefined4 local_8;
  
  FUN_004f6aa0();
  if (*(char *)(param_1 + 0x57) == '\0') {
    local_8 = DAT_0091755c;
  }
  else {
    local_8 = DAT_009175b0;
  }
  FUN_004f6ab0("bd05001.otf",local_8,0x41000000,0);
  if (*(char *)(param_1 + 0x58) == '\0') {
    local_10 = DAT_0091755c;
  }
  else {
    local_10 = DAT_009175b0;
  }
  FUN_004f6ab0("bd05002.otf",local_10,0x41000000,0);
  return;
}

