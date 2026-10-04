/* Raw RGBA weight PNGs: canvas premultiplication destroys RGB when A=0.
 * Keep all four channels as data, including fully transparent PNG pixels. */
"use strict";
const TerrainPaintCodec = (() => {
 function normalize(values) {
  const total=values.reduce((a,b)=>a+b,0);
  if(!total)return [255,0,0,0];
  const exact=values.map(v=>v*255/total), result=exact.map(Math.floor);
  const order=[0,1,2,3].sort((a,b)=>(exact[b]-result[b])-(exact[a]-result[a])||a-b);
  const missing=255-result.reduce((a,b)=>a+b,0);
  for(let i=0;i<missing;i++)result[order[i]]++;
  return result;
 }
 function u32(out,at,value){new DataView(out.buffer,out.byteOffset,out.byteLength).setUint32(at,value);}
 function crc(bytes){let value=0xffffffff;for(const byte of bytes){value^=byte;for(let i=0;i<8;i++)value=(value>>>1)^((value&1)?0xedb88320:0);}return (value^0xffffffff)>>>0;}
 function chunk(type,data){const bytes=new Uint8Array(data.length+12);u32(bytes,0,data.length);bytes.set(new TextEncoder().encode(type),4);bytes.set(data,8);u32(bytes,bytes.length-4,crc(bytes.subarray(4,bytes.length-4)));return bytes;}
 function join(parts){const out=new Uint8Array(parts.reduce((n,p)=>n+p.length,0));let at=0;for(const p of parts){out.set(p,at);at+=p.length;}return out;}
 async function encode(size,weights){
  if(!Number.isInteger(size)||size<1||size>2048||weights.length!==size*size*4)throw Error('Invalid weight dimensions.');
  const rows=new Uint8Array(size*(size*4+1));
  for(let y=0;y<size;y++)rows.set(weights.subarray(y*size*4,(y+1)*size*4),y*(size*4+1)+1);
  const compressed=new Uint8Array(await new Response(new Blob([rows]).stream().pipeThrough(new CompressionStream('deflate'))).arrayBuffer());
  const header=new Uint8Array(13);u32(header,0,size);u32(header,4,size);header[8]=8;header[9]=6;
  return join([new Uint8Array([137,80,78,71,13,10,26,10]),chunk('IHDR',header),chunk('IDAT',compressed),chunk('IEND',new Uint8Array())]);
 }
 async function decode(bytes,expectedSize){
  const view=new DataView(bytes.buffer,bytes.byteOffset,bytes.byteLength);
  if(bytes.length<33||view.getUint32(0)!==0x89504e47||view.getUint32(4)!==0x0d0a1a0a)throw Error('Choose an RGBA weights PNG.');
  let size=0,ended=false,parts=[];
  for(let at=8;at+12<=bytes.length;){
   const length=view.getUint32(at),end=at+12+length;if(end>bytes.length)throw Error('Truncated PNG.');
   const type=new TextDecoder().decode(bytes.subarray(at+4,at+8)),data=bytes.subarray(at+8,at+8+length);
   if(crc(bytes.subarray(at+4,at+8+length))!==view.getUint32(at+8+length))throw Error('PNG checksum failed.');
   if(type==='IHDR'){
    if(at!==8||length!==13||view.getUint32(at+8)!==expectedSize||view.getUint32(at+12)!==expectedSize||data[8]!==8||data[9]!==6||data[10]!==0||data[11]!==0||data[12]!==0)throw Error('Weights must be non-interlaced RGBA8 at the project dimensions.');
    size=expectedSize;
   }else if(type==='IDAT')parts.push(data);
   else if(type==='IEND'){ended=true;break;}
   at=end;
  }
  if(!size||!parts.length||!ended)throw Error('Incomplete weights PNG.');
  const reader=new Blob(parts).stream().pipeThrough(new DecompressionStream('deflate')).getReader();
  const maximum=size*(size*4+1),decoded=[];let count=0;
  for(;;){const result=await reader.read();if(result.done)break;count+=result.value.length;if(count>maximum){await reader.cancel();throw Error('PNG data exceeds the expected dimensions.');}decoded.push(result.value);}
  const rows=join(decoded);if(rows.length!==maximum)throw Error('Incorrect PNG row data.');
  const out=new Uint8ClampedArray(size*size*4),stride=size*4;
  const paeth=(a,b,c)=>{const p=a+b-c,pa=Math.abs(p-a),pb=Math.abs(p-b),pc=Math.abs(p-c);return pa<=pb&&pa<=pc?a:pb<=pc?b:c;};
  for(let y=0;y<size;y++){
   const filter=rows[y*(stride+1)];if(filter>4)throw Error('Unknown PNG filter.');
   for(let x=0;x<stride;x++){
    const p=y*stride+x,a=x>=4?out[p-4]:0,b=y?out[p-stride]:0,c=y&&x>=4?out[p-stride-4]:0;
    const prediction=filter===0?0:filter===1?a:filter===2?b:filter===3?Math.floor((a+b)/2):paeth(a,b,c);
    out[p]=(rows[y*(stride+1)+1+x]+prediction)&255;
   }
  }
  return out;
 }
 return {normalize,encode,decode};
})();
if(typeof module!=='undefined')module.exports=TerrainPaintCodec;
