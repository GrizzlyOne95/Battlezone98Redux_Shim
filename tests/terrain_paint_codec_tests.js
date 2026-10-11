"use strict";
const assert=require('node:assert/strict');
const codec=require('../scripts/terrain-paint-codec.js');
(async()=>{
 const weights=new Uint8ClampedArray([255,0,0,0, 0,255,0,0, 0,0,255,0, 0,0,0,255]);
 const encoded=await codec.encode(2,weights);
 assert.deepEqual(await codec.decode(encoded,2),weights,'zero-alpha RGB weights were lost');
 await assert.rejects(codec.decode(encoded,4),/dimensions/);
 const damaged=encoded.slice();damaged[42]^=1;await assert.rejects(codec.decode(damaged,2),/checksum/);
 assert.deepEqual(codec.normalize([255,255,0,0]),[128,127,0,0]);
 assert.deepEqual(codec.normalize([0,0,0,0]),[255,0,0,0]);
 for(let i=0;i<1000;i++){const value=codec.normalize([i%256,(i*3)%256,(i*7)%256,(i*13)%256]);assert.equal(value.reduce((a,b)=>a+b,0),255);}
 console.log('PASS: raw four-channel PNG, transparent RGB preservation, identity dimensions, checksum and normalized weights');
})().catch(error=>{console.error(error);process.exitCode=1;});
