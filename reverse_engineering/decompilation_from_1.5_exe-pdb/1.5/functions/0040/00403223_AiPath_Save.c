/*
 * Entry: 00403223
 * Name: AiPath::Save
 * Namespace: AiPath
 * Signature: bool Save(AiPath * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall AiPath::Save(AiPath *this,_iobuf *param_1)

{
  char *pcVar1;
  char cVar2;
  bool bVar3;
  bool bVar4;
  char *pcVar5;
  AiPath *local_c;
  uint local_8;
  
  pcVar5 = this->label;
  if (pcVar5 == (char *)0x0) {
    local_8 = 0;
  }
  else {
    pcVar1 = pcVar5 + 1;
    do {
      cVar2 = *pcVar5;
      pcVar5 = pcVar5 + 1;
    } while (cVar2 != '\0');
    local_8 = (int)pcVar5 - (int)pcVar1;
  }
  local_c = this;
  bVar3 = ::out(param_1,"[AiPath]");
  if ((bVar3) && (bVar3 = ::out(param_1,&local_c,4,"old_ptr"), bVar3)) {
    bVar4 = ::out(param_1,(int *)&local_8,4,"size");
    bVar3 = false;
    if (bVar4) {
      bVar4 = true;
      if (0 < (int)local_8) {
        bVar4 = ::out(param_1,this->label,local_8,"label");
      }
      bVar3 = false;
      if (bVar4 != false) {
        bVar3 = ::out(param_1,&this->pointCount,4,"pointCount");
        if (((bVar3) && (bVar3 = ::out(param_1,this->points,this->pointCount << 3,"points"), bVar3))
           && (bVar3 = ::out(param_1,&this->pathType,4,"pathType"), bVar3)) {
          bVar3 = true;
        }
        else {
          bVar3 = false;
        }
      }
    }
  }
  else {
    bVar3 = false;
  }
  return bVar3;
}
