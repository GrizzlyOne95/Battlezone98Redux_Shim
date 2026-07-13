; Entry: 005010d3
; Name: Terrain256PolyDouble
; Signature: void Terrain256PolyDouble(_GRAPHIC_BUFFER * param_1, POINT_3D * param_2, long param_3, POLYGON_SKIN param_4)
; Stop: 0x005019f5
; Reason: Exception while decompiling 005010d3: process: timeout 
; Command: C:\Program Files\LLVM\bin\llvm-objdump.EXE -d --no-show-raw-insn --start-address=0x005010d3 --stop-address=0x005019f5 C:\Users\istuart\Downloads\bzone15227\extracted\bzone.exe


C:\Users\istuart\Downloads\bzone15227\extracted\bzone.exe:	file format coff-i386

Disassembly of section .text:

00401000 <.text>:
  5010d3:      	pushl	%ebp
  5010d4:      	movl	%esp, %ebp
  5010d6:      	movl	0x14(%ebp), %ecx
  5010d9:      	movzwl	(%ecx), %eax
  5010dc:      	pushl	%ebx
  5010dd:      	movl	$0x100, %edx            # imm = 0x100
  5010e2:      	pushl	%esi
  5010e3:      	pushl	%edi
  5010e4:      	cmpw	%dx, %ax
  5010e7:      	je	0x501129 <.text+0x100129>
  5010e9:      	pushl	%ecx
  5010ea:      	pushl	0x10(%ebp)
  5010ed:      	addl	$-0x80, %edx
  5010f0:      	pushl	0xc(%ebp)
  5010f3:      	pushl	0x8(%ebp)
  5010f6:      	cmpw	%dx, %ax
  5010f9:      	jne	0x501102 <.text+0x100102>
  5010fb:      	calll	0x4ff666 <.text+0xfe666>
  501100:      	jmp	0x501121 <.text+0x100121>
  501102:      	cmpw	$0x40, %ax
  501106:      	jne	0x50110f <.text+0x10010f>
  501108:      	calll	0x4fff35 <.text+0xfef35>
  50110d:      	jmp	0x501121 <.text+0x100121>
  50110f:      	cmpw	$0x20, %ax
  501113:      	jne	0x50111c <.text+0x10011c>
  501115:      	calll	0x500804 <.text+0xff804>
  50111a:      	jmp	0x501121 <.text+0x100121>
  50111c:      	calll	0x4f5020 <.text+0xf4020>
  501121:      	addl	$0x10, %esp
  501124:      	jmp	0x5019f0 <.text+0x1009f0>
  501129:      	pushl	%ebp
  50112a:      	subl	$0x700, %esp            # imm = 0x700
  501130:      	movl	0x14(%ebp), %ebx
  501133:      	movl	$0x186a0, %edx          # imm = 0x186A0
  501138:      	movl	0xc(%ebp), %esi
  50113b:      	movl	0x10(%ebp), %eax
  50113e:      	fildl	0x4(%ebx)
  501141:      	movl	(%ebx), %ecx
  501143:      	movl	%esi, (%esp)
  501146:      	shll	$0x3, %eax
  501149:      	leal	0x8(%ebx), %edi
  50114c:      	fildl	(%ebx)
  50114e:      	movl	%ecx, 0x10(%esp)
  501152:      	leal	(%eax,%eax,2), %ecx
  501155:      	xorl	%eax, %eax
  501157:      	movl	%edi, 0x50(%esp)
  50115b:      	flds	0x62c808
  501161:      	fsubs	0x14(%esi,%eax)
  501165:      	flds	0x4(%esi,%eax)
  501169:      	faddl	0x632380
  50116f:      	fxch	%st(1)
  501171:      	flds	0xc(%esi,%eax)
  501175:      	fmul	%st(3), %st
  501177:      	flds	0x10(%esi,%eax)
  50117b:      	fmul	%st(5), %st
  50117d:      	fxch	%st(3)
  50117f:      	fstpl	0x38(%esp)
  501183:      	fxch	%st(1)
  501185:      	fmuls	0x62c810
  50118b:      	fxch	%st(2)
  50118d:      	fstps	0x10(%esi,%eax)
  501191:      	fstps	0xc(%esi,%eax)
  501195:      	fstps	0x14(%esi,%eax)
  501199:      	movl	0x38(%esp), %edi
  50119d:      	movl	%eax, 0x3e4(%esp,%eax)
  5011a4:      	movl	%eax, 0x114(%esp,%eax)
  5011ab:      	movl	%edi, 0x400(%esp,%eax)
  5011b2:      	addl	$0x18, %eax
  5011b5:      	cmpl	%edx, %edi
  5011b7:      	jg	0x5011bd <.text+0x1001bd>
  5011b9:      	movl	%eax, %ebx
  5011bb:      	movl	%edi, %edx
  5011bd:      	cmpl	%ecx, %eax
  5011bf:      	jne	0x50115b <.text+0x10015b>
  5011c1:      	subl	$0x18, %ebx
  5011c4:      	leal	-0x18(%eax), %ecx
  5011c7:      	fcompp
  5011c9:      	movl	$0x0, 0x3e4(%esp,%eax)
  5011d4:      	movl	%ecx, 0xfc(%esp)
  5011db:      	movl	0x8(%ebp), %edi
  5011de:      	movl	%ebx, 0xcc(%esp)
  5011e5:      	movl	%ebx, 0x9c(%esp)
  5011ec:      	movl	%ebx, 0xd0(%esp)
  5011f3:      	movl	%esi, %ebp
  5011f5:      	movl	0x20(%edi), %eax
  5011f8:      	movl	(%edi), %ecx
  5011fa:      	addl	%edx, %eax
  5011fc:      	movl	0x14(%edi), %esi
  5011ff:      	movl	0x1c(%edi), %edi
  501202:      	imull	%ecx
  501204:      	addl	%edi, %esi
  501206:      	movl	%ecx, 0xc(%esp)
  50120a:      	addl	%eax, %esi
  50120c:      	movl	0x400(%esp,%ebx), %edi
  501213:      	movl	%esi, 0x98(%esp)
  50121a:      	movl	%ebx, 0xa0(%esp)
  501221:      	movl	0xd0(%esp), %ecx
  501228:      	movl	0x400(%esp,%ecx), %eax
  50122f:      	movl	%edi, 0x4(%esp)
  501233:      	cmpl	%eax, %edi
  501235:      	jl	0x50135e <.text+0x10035e>
  50123b:      	movl	0x3fc(%esp,%ecx), %edx
  501242:      	movl	%ecx, %eax
  501244:      	movl	%edx, 0xd0(%esp)
  50124b:      	cmpl	0x9c(%esp), %edx
  501252:      	je	0x5019e9 <.text+0x1009e9>
  501258:      	movl	0x400(%esp,%edx), %esi
  50125f:      	movl	%edx, %ecx
  501261:      	cmpl	%esi, %edi
  501263:      	jge	0x50123b <.text+0x10023b>
  501265:      	flds	0x14(%ebp,%edx)
  501269:      	fsubs	0x14(%ebp,%eax)
  50126d:      	flds	0x4(%ebp,%edx)
  501271:      	fsubs	0x4(%ebp,%eax)
  501275:      	flds	0x10(%ebp,%edx)
  501279:      	fsubs	0x10(%ebp,%eax)
  50127d:      	fxch	%st(1)
  50127f:      	fdivrs	0x62c808
  501285:      	flds	0xc(%ebp,%edx)
  501289:      	fsubs	0xc(%ebp,%eax)
  50128d:      	fxch	%st(1)
  50128f:      	fmul	%st, %st(2)
  501291:      	flds	0x8(%ebp,%edx)
  501295:      	fsubs	0x8(%ebp,%eax)
  501299:      	fxch	%st(2)
  50129b:      	fmul	%st(1), %st
  50129d:      	flds	(%ebp,%edx)
  5012a1:      	fsubs	(%ebp,%eax)
  5012a5:      	fxch	%st(3)
  5012a7:      	fmul	%st(2), %st
  5012a9:      	fxch	%st(4)
  5012ab:      	fstps	0xec(%esp)
  5012b2:      	fstps	0xe8(%esp)
  5012b9:      	fmul	%st, %st(3)
  5012bb:      	flds	0x4(%ebp,%eax)
  5012bf:      	faddl	0x632380
  5012c5:      	fxch	%st(2)
  5012c7:      	fmulp	%st, %st(1)
  5012c9:      	fxch	%st(3)
  5012cb:      	fstps	0xf8(%esp)
  5012d2:      	fstpl	0x38(%esp)
  5012d6:      	fstps	0xf4(%esp)
  5012dd:      	fildl	0x38(%esp)
  5012e1:      	fxch	%st(1)
  5012e3:      	fstps	0xf0(%esp)
  5012ea:      	fsubs	0x4(%ebp,%eax)
  5012ee:      	flds	0xf0(%esp)
  5012f5:      	flds	0xf4(%esp)
  5012fc:      	fmul	%st(2), %st
  5012fe:      	flds	0xe8(%esp)
  501305:      	fmul	%st(3), %st
  501307:      	flds	0xf8(%esp)
  50130e:      	fmul	%st(4), %st
  501310:      	fxch	%st(2)
  501312:      	fadds	0x8(%ebp,%eax)
  501316:      	flds	0xec(%esp)
  50131d:      	fmul	%st(5), %st
  50131f:      	fxch	%st(2)
  501321:      	fadds	0xc(%ebp,%eax)
  501325:      	fxch	%st(4)
  501327:      	fmulp	%st, %st(5)
  501329:      	fstps	0xd8(%esp)
  501330:      	fadds	0x10(%ebp,%eax)
  501334:      	fxch	%st(3)
  501336:      	fadds	(%ebp,%eax)
  50133a:      	fxch	%st(2)
  50133c:      	fstps	0xdc(%esp)
  501343:      	fadds	0x14(%ebp,%eax)
  501347:      	fxch	%st(2)
  501349:      	fstps	0xe0(%esp)
  501350:      	fstps	0xd4(%esp)
  501357:      	fstps	0xe4(%esp)
  50135e:      	movl	0xa0(%esp), %ecx
  501365:      	cmpl	0x400(%esp,%ecx), %edi
  50136c:      	jl	0x501486 <.text+0x100486>
  501372:      	movl	0xfc(%esp,%ecx), %edx
  501379:      	movl	%ecx, %eax
  50137b:      	movl	%edx, 0xa0(%esp)
  501382:      	movl	%edx, %ecx
  501384:      	cmpl	0x400(%esp,%edx), %edi
  50138b:      	jge	0x501372 <.text+0x100372>
  50138d:      	flds	0x14(%ebp,%edx)
  501391:      	fsubs	0x14(%ebp,%eax)
  501395:      	flds	0x4(%ebp,%edx)
  501399:      	fsubs	0x4(%ebp,%eax)
  50139d:      	flds	0x10(%ebp,%edx)
  5013a1:      	fsubs	0x10(%ebp,%eax)
  5013a5:      	fxch	%st(1)
  5013a7:      	fdivrs	0x62c808
  5013ad:      	flds	0xc(%ebp,%edx)
  5013b1:      	fsubs	0xc(%ebp,%eax)
  5013b5:      	fxch	%st(1)
  5013b7:      	fmul	%st, %st(2)
  5013b9:      	flds	0x8(%ebp,%edx)
  5013bd:      	fsubs	0x8(%ebp,%eax)
  5013c1:      	fxch	%st(2)
  5013c3:      	fmul	%st(1), %st
  5013c5:      	flds	(%ebp,%edx)
  5013c9:      	fsubs	(%ebp,%eax)
  5013cd:      	fxch	%st(3)
  5013cf:      	fmul	%st(2), %st
  5013d1:      	fxch	%st(4)
  5013d3:      	fstps	0xbc(%esp)
  5013da:      	fstps	0xb8(%esp)
  5013e1:      	fmul	%st, %st(3)
  5013e3:      	flds	0x4(%ebp,%eax)
  5013e7:      	faddl	0x632380
  5013ed:      	fxch	%st(2)
  5013ef:      	fmulp	%st, %st(1)
  5013f1:      	fxch	%st(3)
  5013f3:      	fstps	0xc8(%esp)
  5013fa:      	fstpl	0x38(%esp)
  5013fe:      	fstps	0xc4(%esp)
  501405:      	fildl	0x38(%esp)
  501409:      	fxch	%st(1)
  50140b:      	fstps	0xc0(%esp)
  501412:      	fsubs	0x4(%ebp,%eax)
  501416:      	flds	0xc0(%esp)
  50141d:      	flds	0xc4(%esp)
  501424:      	fmul	%st(2), %st
  501426:      	flds	0xb8(%esp)
  50142d:      	fmul	%st(3), %st
  50142f:      	flds	0xc8(%esp)
  501436:      	fmul	%st(4), %st
  501438:      	fxch	%st(2)
  50143a:      	fadds	0x8(%ebp,%eax)
  50143e:      	flds	0xbc(%esp)
  501445:      	fmul	%st(5), %st
  501447:      	fxch	%st(2)
  501449:      	fadds	0xc(%ebp,%eax)
  50144d:      	fxch	%st(4)
  50144f:      	fmulp	%st, %st(5)
  501451:      	fstps	0xa8(%esp)
  501458:      	fadds	0x10(%ebp,%eax)
  50145c:      	fxch	%st(3)
  50145e:      	fadds	(%ebp,%eax)
  501462:      	fxch	%st(2)
  501464:      	fstps	0xac(%esp)
  50146b:      	fadds	0x14(%ebp,%eax)
  50146f:      	fxch	%st(2)
  501471:      	fstps	0xb0(%esp)
  501478:      	fstps	0xa4(%esp)
  50147f:      	fstps	0xb4(%esp)
  501486:      	flds	0xd4(%esp)
  50148d:      	faddl	0x632380
  501493:      	flds	0xa4(%esp)
  50149a:      	faddl	0x632380
  5014a0:      	fxch	%st(1)
  5014a2:      	fstpl	0x48(%esp)
  5014a6:      	fstpl	0x40(%esp)
  5014aa:      	movl	0x48(%esp), %edx
  5014ae:      	movl	0x40(%esp), %ebx
  5014b2:      	cmpl	%edx, %ebx
  5014b4:      	je	0x5018f2 <.text+0x1008f2>
  5014ba:      	jl	0x501599 <.text+0x100599>
  5014c0:      	flds	0xb4(%esp)
  5014c7:      	fsubs	0xe4(%esp)
  5014ce:      	flds	0xa4(%esp)
  5014d5:      	fsubs	0xd4(%esp)
  5014dc:      	flds	0xb0(%esp)
  5014e3:      	fsubs	0xe0(%esp)
  5014ea:      	fxch	%st(1)
  5014ec:      	fdivrs	0x62c808
  5014f2:      	flds	0xac(%esp)
  5014f9:      	fsubs	0xdc(%esp)
  501500:      	fxch	%st(2)
  501502:      	fmul	%st(1), %st
  501504:      	flds	0xa8(%esp)
  50150b:      	fsubs	0xd8(%esp)
  501512:      	fxch	%st(3)
  501514:      	fmul	%st(2), %st
  501516:      	fxch	%st(1)
  501518:      	fstps	0x1c(%esp)
  50151c:      	fxch	%st(1)
  50151e:      	fmul	%st, %st(2)
  501520:      	fxch	%st(1)
  501522:      	fstps	0x18(%esp)
  501526:      	fmulp	%st, %st(2)
  501528:      	fildl	0x48(%esp)
  50152c:      	fxch	%st(1)
  50152e:      	fstps	0x20(%esp)
  501532:      	fsubs	0xd4(%esp)
  501539:      	fld	%st(1)
  50153b:      	faddl	0x632380
  501541:      	fxch	%st(2)
  501543:      	fmul	%st(1), %st
  501545:      	flds	0x1c(%esp)
  501549:      	fxch	%st(3)
  50154b:      	fstpl	0x68(%esp)
  50154f:      	fadds	0xe4(%esp)
  501556:      	fxch	%st(2)
  501558:      	flds	0x18(%esp)
  50155c:      	fmul	%st(2), %st
  50155e:      	fxch	%st(3)
  501560:      	faddl	0x632380
  501566:      	fxch	%st(3)
  501568:      	flds	0x20(%esp)
  50156c:      	fmul	%st(3), %st
  50156e:      	fxch	%st(4)
  501570:      	fstpl	0x90(%esp)
  501577:      	fadds	0xdc(%esp)
  50157e:      	fxch	%st(2)
  501580:      	fmulp	%st, %st(1)
  501582:      	fxch	%st(2)
  501584:      	fadds	0xd8(%esp)
  50158b:      	fxch	%st(2)
  50158d:      	fadds	0xe0(%esp)
  501594:      	jmp	0x501677 <.text+0x100677>
  501599:      	movl	%ebx, 0x48(%esp)
  50159d:      	movl	%edx, %ebx
  50159f:      	movl	0x48(%esp), %edx
  5015a3:      	flds	0xe4(%esp)
  5015aa:      	fsubs	0xb4(%esp)
  5015b1:      	flds	0xd4(%esp)
  5015b8:      	fsubs	0xa4(%esp)
  5015bf:      	flds	0xe0(%esp)
  5015c6:      	fsubs	0xb0(%esp)
  5015cd:      	fxch	%st(1)
  5015cf:      	fdivrs	0x62c808
  5015d5:      	flds	0xdc(%esp)
  5015dc:      	fsubs	0xac(%esp)
  5015e3:      	fxch	%st(2)
  5015e5:      	fmul	%st(1), %st
  5015e7:      	flds	0xd8(%esp)
  5015ee:      	fsubs	0xa8(%esp)
  5015f5:      	fxch	%st(3)
  5015f7:      	fmul	%st(2), %st
  5015f9:      	fxch	%st(1)
  5015fb:      	fstps	0x1c(%esp)
  5015ff:      	fxch	%st(1)
  501601:      	fmul	%st, %st(2)
  501603:      	fxch	%st(1)
  501605:      	fstps	0x18(%esp)
  501609:      	fmulp	%st, %st(2)
  50160b:      	fildl	0x48(%esp)
  50160f:      	fxch	%st(1)
  501611:      	fstps	0x20(%esp)
  501615:      	fsubs	0xa4(%esp)
  50161c:      	fld	%st(1)
  50161e:      	faddl	0x632380
  501624:      	fxch	%st(2)
  501626:      	fmul	%st(1), %st
  501628:      	flds	0x1c(%esp)
  50162c:      	fxch	%st(3)
  50162e:      	fstpl	0x68(%esp)
  501632:      	fadds	0xb4(%esp)
  501639:      	fxch	%st(2)
  50163b:      	flds	0x18(%esp)
  50163f:      	fmul	%st(2), %st
  501641:      	fxch	%st(3)
  501643:      	faddl	0x632380
  501649:      	fxch	%st(3)
  50164b:      	flds	0x20(%esp)
  50164f:      	fmul	%st(3), %st
  501651:      	fxch	%st(4)
  501653:      	fstpl	0x90(%esp)
  50165a:      	fadds	0xac(%esp)
  501661:      	fxch	%st(2)
  501663:      	fmulp	%st, %st(1)
  501665:      	fxch	%st(2)
  501667:      	fadds	0xa8(%esp)
  50166e:      	fxch	%st(2)
  501670:      	fadds	0xb0(%esp)
  501677:      	movl	0x68(%esp), %eax
  50167b:      	movl	0x98(%esp), %edi
  501682:      	andl	$0xffff, %eax           # imm = 0xFFFF
  501687:      	subl	%edx, %ebx
  501689:      	orl	$0xfffe0000, %eax       # imm = 0xFFFE0000
  50168e:      	addl	%edx, %edi
  501690:      	movl	%eax, 0x68(%esp)
  501694:      	flds	0x18(%esp)
  501698:      	fmuls	0x62c814
  50169e:      	flds	0x1c(%esp)
  5016a2:      	fmuls	0x62c814
  5016a8:      	flds	0x20(%esp)
  5016ac:      	fmuls	0x62c814
  5016b2:      	fxch	%st(2)
  5016b4:      	fstps	0x24(%esp)
  5016b8:      	fstps	0x28(%esp)
  5016bc:      	fstps	0x2c(%esp)
  5016c0:      	fxch	%st(2)
  5016c2:      	flds	0x62c80c
  5016c8:      	fdiv	%st(1), %st
  5016ca:      	fld	%st(3)
  5016cc:      	fmul	%st(1), %st
  5016ce:      	fld	%st(3)
  5016d0:      	fmulp	%st, %st(2)
  5016d2:      	faddl	0x632380
  5016d8:      	fxch	%st(1)
  5016da:      	faddl	0x632380
  5016e0:      	fxch	%st(2)
  5016e2:      	fadds	0x2c(%esp)
  5016e6:      	fxch	%st(1)
  5016e8:      	fstpl	0x78(%esp)
  5016ec:      	fxch	%st(1)
  5016ee:      	fstpl	0x70(%esp)
  5016f2:      	flds	0x62c80c
  5016f8:      	fdiv	%st(1), %st
  5016fa:      	decl	%ebx
  5016fb:      	jmp	0x5017f1 <.text+0x1007f1>
  501700:      	flds	0x24(%esp)
  501704:      	faddp	%st, %st(3)
  501706:      	flds	0x28(%esp)
  50170a:      	faddp	%st, %st(4)
  50170c:      	fld	%st(2)
  50170e:      	fmul	%st(1), %st
  501710:      	flds	0x2c(%esp)
  501714:      	fxch	%st(2)
  501716:      	fmul	%st(5), %st
  501718:      	fxch	%st(2)
  50171a:      	faddp	%st, %st(3)
  50171c:      	faddl	0x632380
  501722:      	fxch	%st(1)
  501724:      	faddl	0x632380
  50172a:      	fld	%st(2)
  50172c:      	fxch	%st(2)
  50172e:      	fstpl	0x80(%esp)
  501735:      	fstpl	0x88(%esp)
  50173c:      	fdivrs	0x62c80c
  501742:      	movl	0x78(%esp), %ebp
  501746:      	movl	0x70(%esp), %esi
  50174a:      	movl	0x88(%esp), %eax
  501751:      	movl	0x80(%esp), %edx
  501758:      	subl	%ebp, %eax
  50175a:      	subl	%esi, %edx
  50175c:      	sarl	$0x4, %eax
  50175f:      	movl	%ebx, 0x8(%esp)
  501763:      	sarl	$0x4, %edx
  501766:      	movl	0x90(%esp), %ebx
  50176d:      	movl	%edx, 0x58(%esp)
  501771:      	andl	$0xffff, %ebx           # imm = 0xFFFF
  501777:      	movl	%eax, 0x60(%esp)
  50177b:      	orl	$0x1e0000, %ebx         # imm = 0x1E0000
  501781:      	movl	%ebp, %eax
  501783:      	movl	%esi, %edx
  501785:      	sarl	$0x8, %eax
  501788:      	movl	0x50(%esp), %ecx
  50178c:      	sarl	$0x10, %edx
  50178f:      	xorb	%al, %al
  501791:      	addl	0x60(%esp), %ebp
  501795:      	addl	0x58(%esp), %esi
  501799:      	addl	%ecx, %eax
  50179b:      	movl	0x68(%esp), %ecx
  50179f:      	addl	0x60(%esp), %ebp
  5017a3:      	addl	0x58(%esp), %esi
  5017a7:      	movb	(%eax,%edx), %dl
  5017aa:      	addl	$0x2, %edi
  5017ad:      	movb	%bh, %dh
  5017af:      	andl	$0xfffeffff, %ebx       # imm = 0xFFFEFFFF
  5017b5:      	movb	0xd1e480(%edx), %al
  5017bb:      	addl	%ecx, %ebx
  5017bd:      	movb	%al, %ah
  5017bf:      	andl	$0xfffeffff, %ebx       # imm = 0xFFFEFFFF
  5017c5:      	movw	%ax, -0x2(%edi)
  5017c9:      	addl	%ecx, %ebx
  5017cb:      	jge	0x501781 <.text+0x100781>
  5017cd:      	movl	%ebx, 0x90(%esp)
  5017d4:      	movl	0x8(%esp), %ebx
  5017d8:      	movl	0x80(%esp), %eax
  5017df:      	movl	0x88(%esp), %edx
  5017e6:      	movl	%eax, 0x70(%esp)
  5017ea:      	movl	%edx, 0x78(%esp)
  5017ee:      	subl	$0x10, %ebx
  5017f1:      	cmpl	$0x10, %ebx
  5017f4:      	jge	0x501700 <.text+0x100700>
  5017fa:      	movl	0x90(%esp), %eax
  501801:      	movl	%ebx, %ecx
  501803:      	decl	%ebx
  501804:      	movl	0x78(%esp), %ebp
  501808:      	shll	$0x11, %ebx
  50180b:      	andl	$0xffff, %eax           # imm = 0xFFFF
  501810:      	movl	0x70(%esp), %esi
  501814:      	orl	%eax, %ebx
  501816:      	cmpl	$0x0, %ecx
  501819:      	je	0x5018cd <.text+0x1008cd>
  50181f:      	fxch	%st(1)
  501821:      	fsubs	0x2c(%esp)
  501825:      	flds	0x20(%esp)
  501829:      	fmuls	0x62c810(,%ecx,8)
  501830:      	flds	0x18(%esp)
  501834:      	fmuls	0x62c810(,%ecx,8)
  50183b:      	flds	0x1c(%esp)
  50183f:      	fmuls	0x62c810(,%ecx,8)
  501846:      	fxch	%st(2)
  501848:      	faddp	%st, %st(3)
  50184a:      	faddp	%st, %st(4)
  50184c:      	faddp	%st, %st(4)
  50184e:      	fdivrs	0x62c80c
  501854:      	fmul	%st, %st(2)
  501856:      	fildl	0x70(%esp)
  50185a:      	fxch	%st(1)
  50185c:      	fmul	%st(4), %st
  50185e:      	fildl	0x78(%esp)
  501862:      	fxch	%st(2)
  501864:      	fsubrp	%st, %st(4)
  501866:      	fsubp	%st, %st(1)
  501868:      	fxch	%st(2)
  50186a:      	fmuls	0x62c814(,%ecx,8)
  501871:      	fxch	%st(2)
  501873:      	fmuls	0x62c814(,%ecx,8)
  50187a:      	fxch	%st(2)
  50187c:      	faddl	0x632380
  501882:      	fxch	%st(2)
  501884:      	faddl	0x632380
  50188a:      	fxch	%st(2)
  50188c:      	fstl	0x58(%esp)
  501890:      	fxch	%st(2)
  501892:      	fstl	0x60(%esp)
  501896:      	movl	%ebp, %eax
  501898:      	movl	%esi, %edx
  50189a:      	sarl	$0x8, %eax
  50189d:      	movl	0x50(%esp), %ecx
  5018a1:      	sarl	$0x10, %edx
  5018a4:      	xorb	%al, %al
  5018a6:      	addl	%ecx, %eax
  5018a8:      	movl	0x68(%esp), %ecx
  5018ac:      	addl	0x60(%esp), %ebp
  5018b0:      	addl	0x58(%esp), %esi
  5018b4:      	movb	(%eax,%edx), %dl
  5018b7:      	incl	%edi
  5018b8:      	movb	%bh, %dh
  5018ba:      	andl	$0xfffeffff, %ebx       # imm = 0xFFFEFFFF
  5018c0:      	movb	0xd1e480(%edx), %al
  5018c6:      	addl	%ecx, %ebx
  5018c8:      	movb	%al, -0x1(%edi)
  5018cb:      	jge	0x501896 <.text+0x100896>
  5018cd:      	sarl	$0x8, %ebp
  5018d0:      	xorl	%edx, %edx
  5018d2:      	sarl	$0x10, %esi
  5018d5:      	movl	0x50(%esp), %eax
  5018d9:      	andl	$0xffffff00, %ebp       # imm = 0xFFFFFF00
  5018df:      	movb	%bh, %dh
  5018e1:      	addl	%ebp, %eax
  5018e3:      	fcompp
  5018e5:      	movb	(%eax,%esi), %dl
  5018e8:      	fcompp
  5018ea:      	movb	0xd1e480(%edx), %al
  5018f0:      	movb	%al, (%edi)
  5018f2:      	flds	0xb4(%esp)
  5018f9:      	fadds	0xc8(%esp)
  501900:      	flds	0xa8(%esp)
  501907:      	fadds	0xc4(%esp)
  50190e:      	flds	0xb0(%esp)
  501915:      	fadds	0xbc(%esp)
  50191c:      	flds	0xac(%esp)
  501923:      	fadds	0xb8(%esp)
  50192a:      	flds	0xa4(%esp)
  501931:      	fadds	0xc0(%esp)
  501938:      	fxch	%st(3)
  50193a:      	fstps	0xa8(%esp)
  501941:      	fstps	0xac(%esp)
  501948:      	fstps	0xb0(%esp)
  50194f:      	fstps	0xa4(%esp)
  501956:      	fstps	0xb4(%esp)
  50195d:      	flds	0xe4(%esp)
  501964:      	fadds	0xf8(%esp)
  50196b:      	flds	0xd8(%esp)
  501972:      	fadds	0xf4(%esp)
  501979:      	flds	0xe0(%esp)
  501980:      	fadds	0xec(%esp)
  501987:      	flds	0xdc(%esp)
  50198e:      	fadds	0xe8(%esp)
  501995:      	flds	0xd4(%esp)
  50199c:      	fadds	0xf0(%esp)
  5019a3:      	fxch	%st(3)
  5019a5:      	fstps	0xd8(%esp)
  5019ac:      	fstps	0xdc(%esp)
  5019b3:      	fstps	0xe0(%esp)
  5019ba:      	fstps	0xd4(%esp)
  5019c1:      	fstps	0xe4(%esp)
  5019c8:      	movl	0x98(%esp), %esi
  5019cf:      	movl	0xc(%esp), %eax
  5019d3:      	movl	(%esp), %ebp
  5019d6:      	addl	%eax, %esi
  5019d8:      	movl	0x4(%esp), %edi
  5019dc:      	movl	%esi, 0x98(%esp)
  5019e3:      	incl	%edi
  5019e4:      	jmp	0x501221 <.text+0x100221>
  5019e9:      	addl	$0x700, %esp            # imm = 0x700
  5019ef:      	popl	%ebp
  5019f0:      	popl	%edi
  5019f1:      	popl	%esi
  5019f2:      	popl	%ebx
  5019f3:      	popl	%ebp
  5019f4:      	retl
