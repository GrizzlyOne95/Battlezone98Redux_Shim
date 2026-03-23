
/* WARNING: Removing unreachable block (ram,0x0081852a) */
/* WARNING: Removing unreachable block (ram,0x00818533) */
/* WARNING: Removing unreachable block (ram,0x00818545) */
/* WARNING: Removing unreachable block (ram,0x0081853c) */
/* WARNING: Removing unreachable block (ram,0x0081854c) */

undefined4 FUN_00818520(char param_1)

{
  undefined1 local_c;
  
  if ((((param_1 < '0') || ('9' < param_1)) && ((param_1 < 'a' || ('f' < param_1)))) &&
     ((param_1 < 'A' || ('F' < param_1)))) {
    local_c = 0;
  }
  else {
    local_c = 1;
  }
  return CONCAT31(param_1 >> 7,local_c);
}

