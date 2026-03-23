
undefined4 FUN_00435190(void)

{
  BOOL BVar1;
  undefined4 uVar2;
  tagCURSORINFO local_18;
  
  local_18.flags = 0;
  local_18.hCursor = (HCURSOR)0x0;
  local_18.ptScreenPos.x = 0;
  local_18.ptScreenPos.y = 0;
  local_18.cbSize = 0x14;
  BVar1 = GetCursorInfo(&local_18);
  if (BVar1 == 0) {
    uVar2 = 0;
  }
  else if ((local_18.flags & 1) == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
}

