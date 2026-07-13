; Entry: 004fff35
; Name: Terrain_64PolyDouble
; Signature: void Terrain_64PolyDouble(_GRAPHIC_BUFFER * param_1, POINT_3D * param_2, long param_3, POLYGON_SKIN param_4)
; Stop: 0x00500804
; Reason: Exception while decompiling 004fff35: process: timeout 
; Command: C:\Program Files\LLVM\bin\llvm-objdump.EXE -d --no-show-raw-insn --start-address=0x004fff35 --stop-address=0x00500804 C:\Users\istuart\Downloads\bzone15227\extracted\bzone.exe


C:\Users\istuart\Downloads\bzone15227\extracted\bzone.exe:	file format coff-i386

Disassembly of section .text:

00401000 <.text>:
  4fff35:      	pushl	%ebp
  4fff36:      	movl	%esp, %ebp
  4fff38:      	pushl	%ebx
  4fff39:      	pushl	%esi
  4fff3a:      	pushl	%edi
  4fff3b:      	pushl	%ebp
  4fff3c:      	subl	$0x700, %esp            # imm = 0x700
  4fff42:      	movl	0x14(%ebp), %ebx
  4fff45:      	movl	$0x186a0, %edx          # imm = 0x186A0
  4fff4a:      	movl	0xc(%ebp), %esi
  4fff4d:      	movl	0x10(%ebp), %eax
  4fff50:      	fildl	0x4(%ebx)
  4fff53:      	movl	(%ebx), %ecx
  4fff55:      	movl	%esi, (%esp)
  4fff58:      	shll	$0x3, %eax
  4fff5b:      	leal	0x8(%ebx), %edi
  4fff5e:      	fildl	(%ebx)
  4fff60:      	movl	%ecx, 0x10(%esp)
  4fff64:      	leal	(%eax,%eax,2), %ecx
  4fff67:      	xorl	%eax, %eax
  4fff69:      	movl	%edi, 0x50(%esp)
  4fff6d:      	flds	0x62c808
  4fff73:      	fsubs	0x14(%esi,%eax)
  4fff77:      	flds	0x4(%esi,%eax)
  4fff7b:      	faddl	0x632380
  4fff81:      	fxch	%st(1)
  4fff83:      	flds	0xc(%esi,%eax)
  4fff87:      	fmul	%st(3), %st
  4fff89:      	flds	0x10(%esi,%eax)
  4fff8d:      	fmul	%st(5), %st
  4fff8f:      	fxch	%st(3)
  4fff91:      	fstpl	0x38(%esp)
  4fff95:      	fxch	%st(1)
  4fff97:      	fmuls	0x62c810
  4fff9d:      	fxch	%st(2)
  4fff9f:      	fstps	0x10(%esi,%eax)
  4fffa3:      	fstps	0xc(%esi,%eax)
  4fffa7:      	fstps	0x14(%esi,%eax)
  4fffab:      	movl	0x38(%esp), %edi
  4fffaf:      	movl	%eax, 0x3e4(%esp,%eax)
  4fffb6:      	movl	%eax, 0x114(%esp,%eax)
  4fffbd:      	movl	%edi, 0x400(%esp,%eax)
  4fffc4:      	addl	$0x18, %eax
  4fffc7:      	cmpl	%edx, %edi
  4fffc9:      	jg	0x4fffcf <.text+0xfefcf>
  4fffcb:      	movl	%eax, %ebx
  4fffcd:      	movl	%edi, %edx
  4fffcf:      	cmpl	%ecx, %eax
  4fffd1:      	jne	0x4fff6d <.text+0xfef6d>
  4fffd3:      	subl	$0x18, %ebx
  4fffd6:      	leal	-0x18(%eax), %ecx
  4fffd9:      	fcompp
  4fffdb:      	movl	$0x0, 0x3e4(%esp,%eax)
  4fffe6:      	movl	%ecx, 0xfc(%esp)
  4fffed:      	movl	0x8(%ebp), %edi
  4ffff0:      	movl	%ebx, 0xcc(%esp)
  4ffff7:      	movl	%ebx, 0x9c(%esp)
  4ffffe:      	movl	%ebx, 0xd0(%esp)
  500005:      	movl	%esi, %ebp
  500007:      	movl	0x20(%edi), %eax
  50000a:      	movl	(%edi), %ecx
  50000c:      	addl	%edx, %eax
  50000e:      	movl	0x14(%edi), %esi
  500011:      	movl	0x1c(%edi), %edi
  500014:      	imull	%ecx
  500016:      	addl	%edi, %esi
  500018:      	movl	%ecx, 0xc(%esp)
  50001c:      	addl	%eax, %esi
  50001e:      	movl	0x400(%esp,%ebx), %edi
  500025:      	movl	%esi, 0x98(%esp)
  50002c:      	movl	%ebx, 0xa0(%esp)
  500033:      	movl	0xd0(%esp), %ecx
  50003a:      	movl	0x400(%esp,%ecx), %eax
  500041:      	movl	%edi, 0x4(%esp)
  500045:      	cmpl	%eax, %edi
  500047:      	jl	0x500170 <.text+0xff170>
  50004d:      	movl	0x3fc(%esp,%ecx), %edx
  500054:      	movl	%ecx, %eax
  500056:      	movl	%edx, 0xd0(%esp)
  50005d:      	cmpl	0x9c(%esp), %edx
  500064:      	je	0x5007f8 <.text+0xff7f8>
  50006a:      	movl	0x400(%esp,%edx), %esi
  500071:      	movl	%edx, %ecx
  500073:      	cmpl	%esi, %edi
  500075:      	jge	0x50004d <.text+0xff04d>
  500077:      	flds	0x14(%ebp,%edx)
  50007b:      	fsubs	0x14(%ebp,%eax)
  50007f:      	flds	0x4(%ebp,%edx)
  500083:      	fsubs	0x4(%ebp,%eax)
  500087:      	flds	0x10(%ebp,%edx)
  50008b:      	fsubs	0x10(%ebp,%eax)
  50008f:      	fxch	%st(1)
  500091:      	fdivrs	0x62c808
  500097:      	flds	0xc(%ebp,%edx)
  50009b:      	fsubs	0xc(%ebp,%eax)
  50009f:      	fxch	%st(1)
  5000a1:      	fmul	%st, %st(2)
  5000a3:      	flds	0x8(%ebp,%edx)
  5000a7:      	fsubs	0x8(%ebp,%eax)
  5000ab:      	fxch	%st(2)
  5000ad:      	fmul	%st(1), %st
  5000af:      	flds	(%ebp,%edx)
  5000b3:      	fsubs	(%ebp,%eax)
  5000b7:      	fxch	%st(3)
  5000b9:      	fmul	%st(2), %st
  5000bb:      	fxch	%st(4)
  5000bd:      	fstps	0xec(%esp)
  5000c4:      	fstps	0xe8(%esp)
  5000cb:      	fmul	%st, %st(3)
  5000cd:      	flds	0x4(%ebp,%eax)
  5000d1:      	faddl	0x632380
  5000d7:      	fxch	%st(2)
  5000d9:      	fmulp	%st, %st(1)
  5000db:      	fxch	%st(3)
  5000dd:      	fstps	0xf8(%esp)
  5000e4:      	fstpl	0x38(%esp)
  5000e8:      	fstps	0xf4(%esp)
  5000ef:      	fildl	0x38(%esp)
  5000f3:      	fxch	%st(1)
  5000f5:      	fstps	0xf0(%esp)
  5000fc:      	fsubs	0x4(%ebp,%eax)
  500100:      	flds	0xf0(%esp)
  500107:      	flds	0xf4(%esp)
  50010e:      	fmul	%st(2), %st
  500110:      	flds	0xe8(%esp)
  500117:      	fmul	%st(3), %st
  500119:      	flds	0xf8(%esp)
  500120:      	fmul	%st(4), %st
  500122:      	fxch	%st(2)
  500124:      	fadds	0x8(%ebp,%eax)
  500128:      	flds	0xec(%esp)
  50012f:      	fmul	%st(5), %st
  500131:      	fxch	%st(2)
  500133:      	fadds	0xc(%ebp,%eax)
  500137:      	fxch	%st(4)
  500139:      	fmulp	%st, %st(5)
  50013b:      	fstps	0xd8(%esp)
  500142:      	fadds	0x10(%ebp,%eax)
  500146:      	fxch	%st(3)
  500148:      	fadds	(%ebp,%eax)
  50014c:      	fxch	%st(2)
  50014e:      	fstps	0xdc(%esp)
  500155:      	fadds	0x14(%ebp,%eax)
  500159:      	fxch	%st(2)
  50015b:      	fstps	0xe0(%esp)
  500162:      	fstps	0xd4(%esp)
  500169:      	fstps	0xe4(%esp)
  500170:      	movl	0xa0(%esp), %ecx
  500177:      	cmpl	0x400(%esp,%ecx), %edi
  50017e:      	jl	0x500298 <.text+0xff298>
  500184:      	movl	0xfc(%esp,%ecx), %edx
  50018b:      	movl	%ecx, %eax
  50018d:      	movl	%edx, 0xa0(%esp)
  500194:      	movl	%edx, %ecx
  500196:      	cmpl	0x400(%esp,%edx), %edi
  50019d:      	jge	0x500184 <.text+0xff184>
  50019f:      	flds	0x14(%ebp,%edx)
  5001a3:      	fsubs	0x14(%ebp,%eax)
  5001a7:      	flds	0x4(%ebp,%edx)
  5001ab:      	fsubs	0x4(%ebp,%eax)
  5001af:      	flds	0x10(%ebp,%edx)
  5001b3:      	fsubs	0x10(%ebp,%eax)
  5001b7:      	fxch	%st(1)
  5001b9:      	fdivrs	0x62c808
  5001bf:      	flds	0xc(%ebp,%edx)
  5001c3:      	fsubs	0xc(%ebp,%eax)
  5001c7:      	fxch	%st(1)
  5001c9:      	fmul	%st, %st(2)
  5001cb:      	flds	0x8(%ebp,%edx)
  5001cf:      	fsubs	0x8(%ebp,%eax)
  5001d3:      	fxch	%st(2)
  5001d5:      	fmul	%st(1), %st
  5001d7:      	flds	(%ebp,%edx)
  5001db:      	fsubs	(%ebp,%eax)
  5001df:      	fxch	%st(3)
  5001e1:      	fmul	%st(2), %st
  5001e3:      	fxch	%st(4)
  5001e5:      	fstps	0xbc(%esp)
  5001ec:      	fstps	0xb8(%esp)
  5001f3:      	fmul	%st, %st(3)
  5001f5:      	flds	0x4(%ebp,%eax)
  5001f9:      	faddl	0x632380
  5001ff:      	fxch	%st(2)
  500201:      	fmulp	%st, %st(1)
  500203:      	fxch	%st(3)
  500205:      	fstps	0xc8(%esp)
  50020c:      	fstpl	0x38(%esp)
  500210:      	fstps	0xc4(%esp)
  500217:      	fildl	0x38(%esp)
  50021b:      	fxch	%st(1)
  50021d:      	fstps	0xc0(%esp)
  500224:      	fsubs	0x4(%ebp,%eax)
  500228:      	flds	0xc0(%esp)
  50022f:      	flds	0xc4(%esp)
  500236:      	fmul	%st(2), %st
  500238:      	flds	0xb8(%esp)
  50023f:      	fmul	%st(3), %st
  500241:      	flds	0xc8(%esp)
  500248:      	fmul	%st(4), %st
  50024a:      	fxch	%st(2)
  50024c:      	fadds	0x8(%ebp,%eax)
  500250:      	flds	0xbc(%esp)
  500257:      	fmul	%st(5), %st
  500259:      	fxch	%st(2)
  50025b:      	fadds	0xc(%ebp,%eax)
  50025f:      	fxch	%st(4)
  500261:      	fmulp	%st, %st(5)
  500263:      	fstps	0xa8(%esp)
  50026a:      	fadds	0x10(%ebp,%eax)
  50026e:      	fxch	%st(3)
  500270:      	fadds	(%ebp,%eax)
  500274:      	fxch	%st(2)
  500276:      	fstps	0xac(%esp)
  50027d:      	fadds	0x14(%ebp,%eax)
  500281:      	fxch	%st(2)
  500283:      	fstps	0xb0(%esp)
  50028a:      	fstps	0xa4(%esp)
  500291:      	fstps	0xb4(%esp)
  500298:      	flds	0xd4(%esp)
  50029f:      	faddl	0x632380
  5002a5:      	flds	0xa4(%esp)
  5002ac:      	faddl	0x632380
  5002b2:      	fxch	%st(1)
  5002b4:      	fstpl	0x48(%esp)
  5002b8:      	fstpl	0x40(%esp)
  5002bc:      	movl	0x48(%esp), %edx
  5002c0:      	movl	0x40(%esp), %ebx
  5002c4:      	cmpl	%edx, %ebx
  5002c6:      	je	0x500701 <.text+0xff701>
  5002cc:      	jl	0x5003ab <.text+0xff3ab>
  5002d2:      	flds	0xb4(%esp)
  5002d9:      	fsubs	0xe4(%esp)
  5002e0:      	flds	0xa4(%esp)
  5002e7:      	fsubs	0xd4(%esp)
  5002ee:      	flds	0xb0(%esp)
  5002f5:      	fsubs	0xe0(%esp)
  5002fc:      	fxch	%st(1)
  5002fe:      	fdivrs	0x62c808
  500304:      	flds	0xac(%esp)
  50030b:      	fsubs	0xdc(%esp)
  500312:      	fxch	%st(2)
  500314:      	fmul	%st(1), %st
  500316:      	flds	0xa8(%esp)
  50031d:      	fsubs	0xd8(%esp)
  500324:      	fxch	%st(3)
  500326:      	fmul	%st(2), %st
  500328:      	fxch	%st(1)
  50032a:      	fstps	0x1c(%esp)
  50032e:      	fxch	%st(1)
  500330:      	fmul	%st, %st(2)
  500332:      	fxch	%st(1)
  500334:      	fstps	0x18(%esp)
  500338:      	fmulp	%st, %st(2)
  50033a:      	fildl	0x48(%esp)
  50033e:      	fxch	%st(1)
  500340:      	fstps	0x20(%esp)
  500344:      	fsubs	0xd4(%esp)
  50034b:      	fld	%st(1)
  50034d:      	faddl	0x632380
  500353:      	fxch	%st(2)
  500355:      	fmul	%st(1), %st
  500357:      	flds	0x1c(%esp)
  50035b:      	fxch	%st(3)
  50035d:      	fstpl	0x68(%esp)
  500361:      	fadds	0xe4(%esp)
  500368:      	fxch	%st(2)
  50036a:      	flds	0x18(%esp)
  50036e:      	fmul	%st(2), %st
  500370:      	fxch	%st(3)
  500372:      	faddl	0x632380
  500378:      	fxch	%st(3)
  50037a:      	flds	0x20(%esp)
  50037e:      	fmul	%st(3), %st
  500380:      	fxch	%st(4)
  500382:      	fstpl	0x90(%esp)
  500389:      	fadds	0xdc(%esp)
  500390:      	fxch	%st(2)
  500392:      	fmulp	%st, %st(1)
  500394:      	fxch	%st(2)
  500396:      	fadds	0xd8(%esp)
  50039d:      	fxch	%st(2)
  50039f:      	fadds	0xe0(%esp)
  5003a6:      	jmp	0x500489 <.text+0xff489>
  5003ab:      	movl	%ebx, 0x48(%esp)
  5003af:      	movl	%edx, %ebx
  5003b1:      	movl	0x48(%esp), %edx
  5003b5:      	flds	0xe4(%esp)
  5003bc:      	fsubs	0xb4(%esp)
  5003c3:      	flds	0xd4(%esp)
  5003ca:      	fsubs	0xa4(%esp)
  5003d1:      	flds	0xe0(%esp)
  5003d8:      	fsubs	0xb0(%esp)
  5003df:      	fxch	%st(1)
  5003e1:      	fdivrs	0x62c808
  5003e7:      	flds	0xdc(%esp)
  5003ee:      	fsubs	0xac(%esp)
  5003f5:      	fxch	%st(2)
  5003f7:      	fmul	%st(1), %st
  5003f9:      	flds	0xd8(%esp)
  500400:      	fsubs	0xa8(%esp)
  500407:      	fxch	%st(3)
  500409:      	fmul	%st(2), %st
  50040b:      	fxch	%st(1)
  50040d:      	fstps	0x1c(%esp)
  500411:      	fxch	%st(1)
  500413:      	fmul	%st, %st(2)
  500415:      	fxch	%st(1)
  500417:      	fstps	0x18(%esp)
  50041b:      	fmulp	%st, %st(2)
  50041d:      	fildl	0x48(%esp)
  500421:      	fxch	%st(1)
  500423:      	fstps	0x20(%esp)
  500427:      	fsubs	0xa4(%esp)
  50042e:      	fld	%st(1)
  500430:      	faddl	0x632380
  500436:      	fxch	%st(2)
  500438:      	fmul	%st(1), %st
  50043a:      	flds	0x1c(%esp)
  50043e:      	fxch	%st(3)
  500440:      	fstpl	0x68(%esp)
  500444:      	fadds	0xb4(%esp)
  50044b:      	fxch	%st(2)
  50044d:      	flds	0x18(%esp)
  500451:      	fmul	%st(2), %st
  500453:      	fxch	%st(3)
  500455:      	faddl	0x632380
  50045b:      	fxch	%st(3)
  50045d:      	flds	0x20(%esp)
  500461:      	fmul	%st(3), %st
  500463:      	fxch	%st(4)
  500465:      	fstpl	0x90(%esp)
  50046c:      	fadds	0xac(%esp)
  500473:      	fxch	%st(2)
  500475:      	fmulp	%st, %st(1)
  500477:      	fxch	%st(2)
  500479:      	fadds	0xa8(%esp)
  500480:      	fxch	%st(2)
  500482:      	fadds	0xb0(%esp)
  500489:      	movl	0x68(%esp), %eax
  50048d:      	movl	0x98(%esp), %edi
  500494:      	andl	$0xffff, %eax           # imm = 0xFFFF
  500499:      	subl	%edx, %ebx
  50049b:      	orl	$0xfffe0000, %eax       # imm = 0xFFFE0000
  5004a0:      	addl	%edx, %edi
  5004a2:      	movl	%eax, 0x68(%esp)
  5004a6:      	flds	0x18(%esp)
  5004aa:      	fmuls	0x62c814
  5004b0:      	flds	0x1c(%esp)
  5004b4:      	fmuls	0x62c814
  5004ba:      	flds	0x20(%esp)
  5004be:      	fmuls	0x62c814
  5004c4:      	fxch	%st(2)
  5004c6:      	fstps	0x24(%esp)
  5004ca:      	fstps	0x28(%esp)
  5004ce:      	fstps	0x2c(%esp)
  5004d2:      	fxch	%st(2)
  5004d4:      	flds	0x62c80c
  5004da:      	fdiv	%st(1), %st
  5004dc:      	fld	%st(3)
  5004de:      	fmul	%st(1), %st
  5004e0:      	fld	%st(3)
  5004e2:      	fmulp	%st, %st(2)
  5004e4:      	faddl	0x632380
  5004ea:      	fxch	%st(1)
  5004ec:      	faddl	0x632380
  5004f2:      	fxch	%st(2)
  5004f4:      	fadds	0x2c(%esp)
  5004f8:      	fxch	%st(1)
  5004fa:      	fstpl	0x78(%esp)
  5004fe:      	fxch	%st(1)
  500500:      	fstpl	0x70(%esp)
  500504:      	flds	0x62c80c
  50050a:      	fdiv	%st(1), %st
  50050c:      	decl	%ebx
  50050d:      	jmp	0x500603 <.text+0xff603>
  500512:      	flds	0x24(%esp)
  500516:      	faddp	%st, %st(3)
  500518:      	flds	0x28(%esp)
  50051c:      	faddp	%st, %st(4)
  50051e:      	fld	%st(2)
  500520:      	fmul	%st(1), %st
  500522:      	flds	0x2c(%esp)
  500526:      	fxch	%st(2)
  500528:      	fmul	%st(5), %st
  50052a:      	fxch	%st(2)
  50052c:      	faddp	%st, %st(3)
  50052e:      	faddl	0x632380
  500534:      	fxch	%st(1)
  500536:      	faddl	0x632380
  50053c:      	fld	%st(2)
  50053e:      	fxch	%st(2)
  500540:      	fstpl	0x80(%esp)
  500547:      	fstpl	0x88(%esp)
  50054e:      	fdivrs	0x62c80c
  500554:      	movl	0x78(%esp), %ebp
  500558:      	movl	0x70(%esp), %esi
  50055c:      	movl	0x88(%esp), %eax
  500563:      	movl	0x80(%esp), %edx
  50056a:      	subl	%ebp, %eax
  50056c:      	subl	%esi, %edx
  50056e:      	sarl	$0x4, %eax
  500571:      	movl	%ebx, 0x8(%esp)
  500575:      	sarl	$0x4, %edx
  500578:      	movl	0x90(%esp), %ebx
  50057f:      	movl	%edx, 0x58(%esp)
  500583:      	andl	$0xffff, %ebx           # imm = 0xFFFF
  500589:      	movl	%eax, 0x60(%esp)
  50058d:      	orl	$0x1e0000, %ebx         # imm = 0x1E0000
  500593:      	movl	%ebp, %eax
  500595:      	movl	%esi, %edx
  500597:      	sarl	$0xa, %eax
  50059a:      	movl	0x50(%esp), %ecx
  50059e:      	sarl	$0x10, %edx
  5005a1:      	andb	$-0x40, %al
  5005a3:      	addl	0x60(%esp), %ebp
  5005a7:      	addl	0x58(%esp), %esi
  5005ab:      	addl	%ecx, %eax
  5005ad:      	movl	0x68(%esp), %ecx
  5005b1:      	addl	0x60(%esp), %ebp
  5005b5:      	addl	0x58(%esp), %esi
  5005b9:      	movb	(%eax,%edx), %dl
  5005bc:      	addl	$0x2, %edi
  5005bf:      	movb	%bh, %dh
  5005c1:      	andl	$0xfffeffff, %ebx       # imm = 0xFFFEFFFF
  5005c7:      	movb	0xd1e480(%edx), %al
  5005cd:      	addl	%ecx, %ebx
  5005cf:      	movb	%al, %ah
  5005d1:      	andl	$0xfffeffff, %ebx       # imm = 0xFFFEFFFF
  5005d7:      	movw	%ax, -0x2(%edi)
  5005db:      	addl	%ecx, %ebx
  5005dd:      	jge	0x500593 <.text+0xff593>
  5005df:      	movl	%ebx, 0x90(%esp)
  5005e6:      	movl	0x8(%esp), %ebx
  5005ea:      	movl	0x80(%esp), %eax
  5005f1:      	movl	0x88(%esp), %edx
  5005f8:      	movl	%eax, 0x70(%esp)
  5005fc:      	movl	%edx, 0x78(%esp)
  500600:      	subl	$0x10, %ebx
  500603:      	cmpl	$0x10, %ebx
  500606:      	jge	0x500512 <.text+0xff512>
  50060c:      	movl	0x90(%esp), %eax
  500613:      	movl	%ebx, %ecx
  500615:      	decl	%ebx
  500616:      	movl	0x78(%esp), %ebp
  50061a:      	shll	$0x11, %ebx
  50061d:      	andl	$0xffff, %eax           # imm = 0xFFFF
  500622:      	movl	0x70(%esp), %esi
  500626:      	orl	%eax, %ebx
  500628:      	cmpl	$0x0, %ecx
  50062b:      	je	0x5006df <.text+0xff6df>
  500631:      	fxch	%st(1)
  500633:      	fsubs	0x2c(%esp)
  500637:      	flds	0x20(%esp)
  50063b:      	fmuls	0x62c810(,%ecx,8)
  500642:      	flds	0x18(%esp)
  500646:      	fmuls	0x62c810(,%ecx,8)
  50064d:      	flds	0x1c(%esp)
  500651:      	fmuls	0x62c810(,%ecx,8)
  500658:      	fxch	%st(2)
  50065a:      	faddp	%st, %st(3)
  50065c:      	faddp	%st, %st(4)
  50065e:      	faddp	%st, %st(4)
  500660:      	fdivrs	0x62c80c
  500666:      	fmul	%st, %st(2)
  500668:      	fildl	0x70(%esp)
  50066c:      	fxch	%st(1)
  50066e:      	fmul	%st(4), %st
  500670:      	fildl	0x78(%esp)
  500674:      	fxch	%st(2)
  500676:      	fsubrp	%st, %st(4)
  500678:      	fsubp	%st, %st(1)
  50067a:      	fxch	%st(2)
  50067c:      	fmuls	0x62c814(,%ecx,8)
  500683:      	fxch	%st(2)
  500685:      	fmuls	0x62c814(,%ecx,8)
  50068c:      	fxch	%st(2)
  50068e:      	faddl	0x632380
  500694:      	fxch	%st(2)
  500696:      	faddl	0x632380
  50069c:      	fxch	%st(2)
  50069e:      	fstl	0x58(%esp)
  5006a2:      	fxch	%st(2)
  5006a4:      	fstl	0x60(%esp)
  5006a8:      	movl	%ebp, %eax
  5006aa:      	movl	%esi, %edx
  5006ac:      	sarl	$0xa, %eax
  5006af:      	movl	0x50(%esp), %ecx
  5006b3:      	sarl	$0x10, %edx
  5006b6:      	andb	$-0x40, %al
  5006b8:      	addl	%ecx, %eax
  5006ba:      	movl	0x68(%esp), %ecx
  5006be:      	addl	0x60(%esp), %ebp
  5006c2:      	addl	0x58(%esp), %esi
  5006c6:      	movb	(%eax,%edx), %dl
  5006c9:      	incl	%edi
  5006ca:      	movb	%bh, %dh
  5006cc:      	andl	$0xfffeffff, %ebx       # imm = 0xFFFEFFFF
  5006d2:      	movb	0xd1e480(%edx), %al
  5006d8:      	addl	%ecx, %ebx
  5006da:      	movb	%al, -0x1(%edi)
  5006dd:      	jge	0x5006a8 <.text+0xff6a8>
  5006df:      	sarl	$0xa, %ebp
  5006e2:      	xorl	%edx, %edx
  5006e4:      	sarl	$0x10, %esi
  5006e7:      	movl	0x50(%esp), %eax
  5006eb:      	andl	$-0x40, %ebp
  5006ee:      	movb	%bh, %dh
  5006f0:      	addl	%ebp, %eax
  5006f2:      	fcompp
  5006f4:      	movb	(%eax,%esi), %dl
  5006f7:      	fcompp
  5006f9:      	movb	0xd1e480(%edx), %al
  5006ff:      	movb	%al, (%edi)
  500701:      	flds	0xb4(%esp)
  500708:      	fadds	0xc8(%esp)
  50070f:      	flds	0xa8(%esp)
  500716:      	fadds	0xc4(%esp)
  50071d:      	flds	0xb0(%esp)
  500724:      	fadds	0xbc(%esp)
  50072b:      	flds	0xac(%esp)
  500732:      	fadds	0xb8(%esp)
  500739:      	flds	0xa4(%esp)
  500740:      	fadds	0xc0(%esp)
  500747:      	fxch	%st(3)
  500749:      	fstps	0xa8(%esp)
  500750:      	fstps	0xac(%esp)
  500757:      	fstps	0xb0(%esp)
  50075e:      	fstps	0xa4(%esp)
  500765:      	fstps	0xb4(%esp)
  50076c:      	flds	0xe4(%esp)
  500773:      	fadds	0xf8(%esp)
  50077a:      	flds	0xd8(%esp)
  500781:      	fadds	0xf4(%esp)
  500788:      	flds	0xe0(%esp)
  50078f:      	fadds	0xec(%esp)
  500796:      	flds	0xdc(%esp)
  50079d:      	fadds	0xe8(%esp)
  5007a4:      	flds	0xd4(%esp)
  5007ab:      	fadds	0xf0(%esp)
  5007b2:      	fxch	%st(3)
  5007b4:      	fstps	0xd8(%esp)
  5007bb:      	fstps	0xdc(%esp)
  5007c2:      	fstps	0xe0(%esp)
  5007c9:      	fstps	0xd4(%esp)
  5007d0:      	fstps	0xe4(%esp)
  5007d7:      	movl	0x98(%esp), %esi
  5007de:      	movl	0xc(%esp), %eax
  5007e2:      	movl	(%esp), %ebp
  5007e5:      	addl	%eax, %esi
  5007e7:      	movl	0x4(%esp), %edi
  5007eb:      	movl	%esi, 0x98(%esp)
  5007f2:      	incl	%edi
  5007f3:      	jmp	0x500033 <.text+0xff033>
  5007f8:      	addl	$0x700, %esp            # imm = 0x700
  5007fe:      	popl	%ebp
  5007ff:      	popl	%edi
  500800:      	popl	%esi
  500801:      	popl	%ebx
  500802:      	popl	%ebp
  500803:      	retl
