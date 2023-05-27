	.text
	.attribute	4, 16
	.attribute	5, "rv64i2p0"
	.file	"output"
	.globl	quicksort                       # -- Begin function quicksort
	.p2align	2
	.type	quicksort,@function
quicksort:                              # @quicksort
	.cfi_startproc
# %bb.0:                                # %entry_quicksort
	addi	sp, sp, -1888
	.cfi_def_cfa_offset 1888
	sd	ra, 1880(sp)                    # 8-byte Folded Spill
	sd	s0, 1872(sp)                    # 8-byte Folded Spill
	sd	s1, 1864(sp)                    # 8-byte Folded Spill
	sd	s2, 1856(sp)                    # 8-byte Folded Spill
	sd	s3, 1848(sp)                    # 8-byte Folded Spill
	sd	s4, 1840(sp)                    # 8-byte Folded Spill
	sd	s5, 1832(sp)                    # 8-byte Folded Spill
	sd	s6, 1824(sp)                    # 8-byte Folded Spill
	sd	s7, 1816(sp)                    # 8-byte Folded Spill
	sd	s8, 1808(sp)                    # 8-byte Folded Spill
	sd	s9, 1800(sp)                    # 8-byte Folded Spill
	sd	s10, 1792(sp)                   # 8-byte Folded Spill
	sd	s11, 1784(sp)                   # 8-byte Folded Spill
	.cfi_offset ra, -8
	.cfi_offset s0, -16
	.cfi_offset s1, -24
	.cfi_offset s2, -32
	.cfi_offset s3, -40
	.cfi_offset s4, -48
	.cfi_offset s5, -56
	.cfi_offset s6, -64
	.cfi_offset s7, -72
	.cfi_offset s8, -80
	.cfi_offset s9, -88
	.cfi_offset s10, -96
	.cfi_offset s11, -104
	lui	t0, 1
	addiw	t0, t0, -1768
	add	t0, sp, t0
	ld	t0, 0(t0)
	ld	t1, 1896(sp)
	lui	t2, 1
	addiw	t2, t2, -1776
	add	t2, sp, t2
	ld	t2, 0(t2)
	lui	t3, 1
	addiw	t3, t3, -1784
	add	t3, sp, t3
	ld	t3, 0(t3)
	sw	t0, 1636(sp)
	lui	t0, 1
	addiw	t0, t0, -1792
	add	t0, sp, t0
	ld	t0, 0(t0)
	sw	t2, 1632(sp)
	lui	t2, 1
	addiw	t2, t2, -1800
	add	t2, sp, t2
	ld	t2, 0(t2)
	sw	t3, 1628(sp)
	lui	t3, 1
	addiw	t3, t3, -1808
	add	t3, sp, t3
	ld	t3, 0(t3)
	sw	t0, 1624(sp)
	lui	t0, 1
	addiw	t0, t0, -1816
	add	t0, sp, t0
	ld	t0, 0(t0)
	sw	t2, 1620(sp)
	lui	t2, 1
	addiw	t2, t2, -1824
	add	t2, sp, t2
	ld	t2, 0(t2)
	sw	t3, 1616(sp)
	lui	t3, 1
	addiw	t3, t3, -1832
	add	t3, sp, t3
	ld	t3, 0(t3)
	sw	t0, 1612(sp)
	lui	t0, 1
	addiw	t0, t0, -1840
	add	t0, sp, t0
	ld	t0, 0(t0)
	sw	t2, 1608(sp)
	lui	t2, 1
	addiw	t2, t2, -1848
	add	t2, sp, t2
	ld	t2, 0(t2)
	sw	t3, 1604(sp)
	lui	t3, 1
	addiw	t3, t3, -1856
	add	t3, sp, t3
	ld	t3, 0(t3)
	sw	t0, 1600(sp)
	lui	t0, 1
	addiw	t0, t0, -1864
	add	t0, sp, t0
	ld	t0, 0(t0)
	sw	t2, 1596(sp)
	lui	t2, 1
	addiw	t2, t2, -1872
	add	t2, sp, t2
	ld	t2, 0(t2)
	sw	t3, 1592(sp)
	lui	t3, 1
	addiw	t3, t3, -1880
	add	t3, sp, t3
	ld	t3, 0(t3)
	sw	t0, 1588(sp)
	lui	t0, 1
	addiw	t0, t0, -1888
	add	t0, sp, t0
	ld	t0, 0(t0)
	sw	t2, 1584(sp)
	lui	t2, 1
	addiw	t2, t2, -1896
	add	t2, sp, t2
	ld	t2, 0(t2)
	sw	t3, 1580(sp)
	lui	t3, 1
	addiw	t3, t3, -1904
	add	t3, sp, t3
	ld	t3, 0(t3)
	sw	t0, 1576(sp)
	lui	t0, 1
	addiw	t0, t0, -1912
	add	t0, sp, t0
	ld	t0, 0(t0)
	sw	t2, 1572(sp)
	lui	t2, 1
	addiw	t2, t2, -1920
	add	t2, sp, t2
	ld	t2, 0(t2)
	sw	t3, 1568(sp)
	lui	t3, 1
	addiw	t3, t3, -1928
	add	t3, sp, t3
	ld	t3, 0(t3)
	sw	t0, 1564(sp)
	lui	t0, 1
	addiw	t0, t0, -1936
	add	t0, sp, t0
	ld	t0, 0(t0)
	sw	t2, 1560(sp)
	lui	t2, 1
	addiw	t2, t2, -1944
	add	t2, sp, t2
	ld	t2, 0(t2)
	sw	t3, 1556(sp)
	lui	t3, 1
	addiw	t3, t3, -1952
	add	t3, sp, t3
	ld	t3, 0(t3)
	sw	t0, 1552(sp)
	lui	t0, 1
	addiw	t0, t0, -1960
	add	t0, sp, t0
	ld	t0, 0(t0)
	sw	t2, 1548(sp)
	lui	t2, 1
	addiw	t2, t2, -1968
	add	t2, sp, t2
	ld	t2, 0(t2)
	sw	t3, 1544(sp)
	lui	t3, 1
	addiw	t3, t3, -1976
	add	t3, sp, t3
	ld	t3, 0(t3)
	sw	t0, 1540(sp)
	lui	t0, 1
	addiw	t0, t0, -1984
	add	t0, sp, t0
	ld	t0, 0(t0)
	sw	t2, 1536(sp)
	lui	t2, 1
	addiw	t2, t2, -1992
	add	t2, sp, t2
	ld	t2, 0(t2)
	sw	t3, 1532(sp)
	lui	t3, 1
	addiw	t3, t3, -2000
	add	t3, sp, t3
	ld	t3, 0(t3)
	sw	t0, 1528(sp)
	lui	t0, 1
	addiw	t0, t0, -2008
	add	t0, sp, t0
	ld	t0, 0(t0)
	sw	t2, 1524(sp)
	lui	t2, 1
	addiw	t2, t2, -2016
	add	t2, sp, t2
	ld	t2, 0(t2)
	sw	t3, 1520(sp)
	lui	t3, 1
	addiw	t3, t3, -2024
	add	t3, sp, t3
	ld	t3, 0(t3)
	sw	t0, 1516(sp)
	lui	t0, 1
	addiw	t0, t0, -2032
	add	t0, sp, t0
	ld	t0, 0(t0)
	sw	t2, 1512(sp)
	lui	t2, 1
	addiw	t2, t2, -2040
	add	t2, sp, t2
	ld	t2, 0(t2)
	sw	t3, 1508(sp)
	lui	t3, 1
	addiw	t3, t3, -2048
	add	t3, sp, t3
	ld	t3, 0(t3)
	sw	t0, 1504(sp)
	ld	t0, 2040(sp)
	sw	t2, 1500(sp)
	ld	t2, 2032(sp)
	sw	t3, 1496(sp)
	ld	t3, 2024(sp)
	sw	t0, 1492(sp)
	ld	t0, 2016(sp)
	sw	t2, 1488(sp)
	ld	t2, 2008(sp)
	sw	t3, 1484(sp)
	ld	t3, 2000(sp)
	sw	t0, 1480(sp)
	ld	t0, 1992(sp)
	sw	t2, 1476(sp)
	ld	t2, 1984(sp)
	sw	t3, 1472(sp)
	ld	t3, 1976(sp)
	sw	t0, 1468(sp)
	ld	t0, 1968(sp)
	sw	t2, 1464(sp)
	ld	t2, 1960(sp)
	sw	t3, 1460(sp)
	ld	t3, 1952(sp)
	sw	t0, 1456(sp)
	ld	t0, 1944(sp)
	sw	t2, 1452(sp)
	ld	t2, 1936(sp)
	sw	t3, 1448(sp)
	ld	t3, 1928(sp)
	sw	t0, 1444(sp)
	ld	t0, 1920(sp)
	sw	t2, 1440(sp)
	ld	t2, 1912(sp)
	sw	t3, 1436(sp)
	ld	t3, 1904(sp)
	sw	t0, 1432(sp)
	ld	t0, 1888(sp)
	sw	t2, 1428(sp)
	sw	t3, 1424(sp)
	sw	t1, 1420(sp)
	sw	t0, 1416(sp)
	sw	a7, 1412(sp)
	sw	a6, 1408(sp)
	sw	a5, 1404(sp)
	sw	a4, 1400(sp)
	sw	a3, 1396(sp)
	lui	a3, 1
	addiw	a3, a3, -1472
	add	a3, sp, a3
	lw	a3, 0(a3)
	sw	a2, 1392(sp)
	lui	a2, 1
	addiw	a2, a2, -1480
	add	a2, sp, a2
	ld	a2, 0(a2)
	sw	a1, 1388(sp)
	lui	a1, 1
	addiw	a1, a1, -1488
	add	a1, sp, a1
	ld	a1, 0(a1)
	sw	a0, 1384(sp)
	lui	a0, 1
	addiw	a0, a0, -1496
	add	a0, sp, a0
	ld	a0, 0(a0)
	sw	a2, 1780(sp)
	lui	a2, 1
	addiw	a2, a2, -1504
	add	a2, sp, a2
	ld	a2, 0(a2)
	sw	a1, 1776(sp)
	lui	a1, 1
	addiw	a1, a1, -1512
	add	a1, sp, a1
	ld	a1, 0(a1)
	sw	a0, 1772(sp)
	lui	a0, 1
	addiw	a0, a0, -1520
	add	a0, sp, a0
	ld	a0, 0(a0)
	sw	a2, 1768(sp)
	lui	a2, 1
	addiw	a2, a2, -1528
	add	a2, sp, a2
	ld	a2, 0(a2)
	sw	a1, 1764(sp)
	lui	a1, 1
	addiw	a1, a1, -1536
	add	a1, sp, a1
	ld	a1, 0(a1)
	sw	a0, 1760(sp)
	lui	a0, 1
	addiw	a0, a0, -1544
	add	a0, sp, a0
	ld	a0, 0(a0)
	sw	a2, 1756(sp)
	lui	a2, 1
	addiw	a2, a2, -1552
	add	a2, sp, a2
	ld	a2, 0(a2)
	sw	a1, 1752(sp)
	lui	a1, 1
	addiw	a1, a1, -1560
	add	a1, sp, a1
	ld	a1, 0(a1)
	sw	a0, 1748(sp)
	lui	a0, 1
	addiw	a0, a0, -1568
	add	a0, sp, a0
	ld	a0, 0(a0)
	sw	a2, 1744(sp)
	lui	a2, 1
	addiw	a2, a2, -1576
	add	a2, sp, a2
	ld	a2, 0(a2)
	sw	a1, 1740(sp)
	lui	a1, 1
	addiw	a1, a1, -1584
	add	a1, sp, a1
	ld	a1, 0(a1)
	sw	a0, 1736(sp)
	lui	a0, 1
	addiw	a0, a0, -1592
	add	a0, sp, a0
	ld	a0, 0(a0)
	sw	a2, 1732(sp)
	lui	a2, 1
	addiw	a2, a2, -1600
	add	a2, sp, a2
	ld	a2, 0(a2)
	sw	a1, 1728(sp)
	lui	a1, 1
	addiw	a1, a1, -1608
	add	a1, sp, a1
	ld	a1, 0(a1)
	sw	a0, 1724(sp)
	lui	a0, 1
	addiw	a0, a0, -1616
	add	a0, sp, a0
	ld	a0, 0(a0)
	sw	a2, 1720(sp)
	lui	a2, 1
	addiw	a2, a2, -1624
	add	a2, sp, a2
	ld	a2, 0(a2)
	sw	a1, 1716(sp)
	lui	a1, 1
	addiw	a1, a1, -1632
	add	a1, sp, a1
	ld	a1, 0(a1)
	sw	a0, 1712(sp)
	lui	a0, 1
	addiw	a0, a0, -1640
	add	a0, sp, a0
	ld	a0, 0(a0)
	sw	a2, 1708(sp)
	lui	a2, 1
	addiw	a2, a2, -1648
	add	a2, sp, a2
	ld	a2, 0(a2)
	sw	a1, 1704(sp)
	lui	a1, 1
	addiw	a1, a1, -1656
	add	a1, sp, a1
	ld	a1, 0(a1)
	sw	a0, 1700(sp)
	lui	a0, 1
	addiw	a0, a0, -1664
	add	a0, sp, a0
	ld	a0, 0(a0)
	sw	a2, 1696(sp)
	lui	a2, 1
	addiw	a2, a2, -1672
	add	a2, sp, a2
	ld	a2, 0(a2)
	sw	a1, 1692(sp)
	lui	a1, 1
	addiw	a1, a1, -1680
	add	a1, sp, a1
	ld	a1, 0(a1)
	sw	a0, 1688(sp)
	lui	a0, 1
	addiw	a0, a0, -1688
	add	a0, sp, a0
	ld	a0, 0(a0)
	sw	a2, 1684(sp)
	lui	a2, 1
	addiw	a2, a2, -1696
	add	a2, sp, a2
	ld	a2, 0(a2)
	sw	a1, 1680(sp)
	lui	a1, 1
	addiw	a1, a1, -1704
	add	a1, sp, a1
	ld	a1, 0(a1)
	sw	a0, 1676(sp)
	lui	a0, 1
	addiw	a0, a0, -1712
	add	a0, sp, a0
	ld	a0, 0(a0)
	sw	a2, 1672(sp)
	lui	a2, 1
	addiw	a2, a2, -1720
	add	a2, sp, a2
	ld	a2, 0(a2)
	sw	a1, 1668(sp)
	lui	a1, 1
	addiw	a1, a1, -1728
	add	a1, sp, a1
	ld	a1, 0(a1)
	sw	a0, 1664(sp)
	lui	a0, 1
	addiw	a0, a0, -1736
	add	a0, sp, a0
	ld	a0, 0(a0)
	sw	a2, 1660(sp)
	lui	a2, 1
	addiw	a2, a2, -1744
	add	a2, sp, a2
	ld	a2, 0(a2)
	sw	a1, 1656(sp)
	lui	a1, 1
	addiw	a1, a1, -1752
	add	a1, sp, a1
	ld	a1, 0(a1)
	sw	a0, 1652(sp)
	lui	a0, 1
	addiw	a0, a0, -1760
	add	a0, sp, a0
	ld	a0, 0(a0)
	sw	a2, 1648(sp)
	lui	a2, 1
	addiw	a2, a2, -1464
	add	a2, sp, a2
	lw	a2, 0(a2)
	sw	a1, 1644(sp)
	sw	a0, 1640(sp)
	sw	a3, 1380(sp)
	addw	a0, a3, a2
	srliw	a1, a0, 31
	addw	a0, a0, a1
	slli	a0, a0, 1
	andi	a1, a0, -4
	addi	a0, sp, 1384
	add	a1, a0, a1
	lw	a1, 0(a1)
	sw	a3, 1372(sp)
	sw	a2, 1376(sp)
	sw	a2, 1368(sp)
	sw	a1, 1364(sp)
.LBB0_1:                                # %WhileCond
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_2 Depth 2
                                        #     Child Loop BB0_5 Depth 2
	lw	a1, 1372(sp)
	lw	a2, 1368(sp)
	blt	a2, a1, .LBB0_8
.LBB0_2:                                # %WhileCond1
                                        #   Parent Loop BB0_1 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	lw	a1, 1372(sp)
	slli	a1, a1, 2
	add	a1, a0, a1
	lw	a1, 0(a1)
	lw	a2, 1364(sp)
	bge	a1, a2, .LBB0_5
# %bb.3:                                # %WhileLoop2
                                        #   in Loop: Header=BB0_2 Depth=2
	lw	a1, 1372(sp)
	addiw	a1, a1, 1
	sw	a1, 1372(sp)
	j	.LBB0_2
.LBB0_4:                                # %WhileLoop4
                                        #   in Loop: Header=BB0_5 Depth=2
	lw	a1, 1368(sp)
	addiw	a1, a1, -1
	sw	a1, 1368(sp)
.LBB0_5:                                # %WhileCond3
                                        #   Parent Loop BB0_1 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	lw	a1, 1368(sp)
	lw	a2, 1364(sp)
	slli	a1, a1, 2
	add	a1, a0, a1
	lw	a1, 0(a1)
	blt	a2, a1, .LBB0_4
# %bb.6:                                # %WhileEnd5
                                        #   in Loop: Header=BB0_1 Depth=1
	lw	a1, 1372(sp)
	lw	a2, 1368(sp)
	blt	a2, a1, .LBB0_1
# %bb.7:                                #   in Loop: Header=BB0_1 Depth=1
	lw	a1, 1372(sp)
	lw	a2, 1368(sp)
	slli	a3, a1, 2
	add	a3, a0, a3
	lw	a4, 0(a3)
	slli	a5, a2, 2
	add	a5, a0, a5
	lw	a6, 0(a5)
	sw	a4, 1360(sp)
	sw	a6, 0(a3)
	sw	a4, 0(a5)
	addiw	a1, a1, 1
	sw	a1, 1372(sp)
	addiw	a1, a2, -1
	sw	a1, 1368(sp)
	j	.LBB0_1
.LBB0_8:                                # %WhileEnd6
	lw	a0, 1380(sp)
	lw	a1, 1368(sp)
	bge	a0, a1, .LBB0_10
# %bb.9:
	lw	a0, 1412(sp)
	sd	a0, 1352(sp)                    # 8-byte Folded Spill
	lw	a0, 1408(sp)
	sd	a0, 1344(sp)                    # 8-byte Folded Spill
	lw	a0, 1404(sp)
	sd	a0, 1336(sp)                    # 8-byte Folded Spill
	lw	a0, 1400(sp)
	sd	a0, 1328(sp)                    # 8-byte Folded Spill
	lw	a0, 1396(sp)
	sd	a0, 1320(sp)                    # 8-byte Folded Spill
	lw	a0, 1392(sp)
	sd	a0, 1312(sp)                    # 8-byte Folded Spill
	lw	a0, 1388(sp)
	sd	a0, 1304(sp)                    # 8-byte Folded Spill
	lw	a0, 1384(sp)
	sd	a0, 1296(sp)                    # 8-byte Folded Spill
	lw	a0, 1416(sp)
	sd	a0, 1288(sp)                    # 8-byte Folded Spill
	lw	a0, 1420(sp)
	sd	a0, 1280(sp)                    # 8-byte Folded Spill
	lw	a0, 1424(sp)
	sd	a0, 1272(sp)                    # 8-byte Folded Spill
	lw	a0, 1428(sp)
	sd	a0, 1264(sp)                    # 8-byte Folded Spill
	lw	a0, 1432(sp)
	sd	a0, 1256(sp)                    # 8-byte Folded Spill
	lw	a0, 1436(sp)
	sd	a0, 1248(sp)                    # 8-byte Folded Spill
	lw	a0, 1440(sp)
	sd	a0, 1240(sp)                    # 8-byte Folded Spill
	lw	a0, 1444(sp)
	sd	a0, 1232(sp)                    # 8-byte Folded Spill
	lw	a0, 1448(sp)
	sd	a0, 1224(sp)                    # 8-byte Folded Spill
	lw	a0, 1452(sp)
	sd	a0, 1216(sp)                    # 8-byte Folded Spill
	lw	a0, 1456(sp)
	sd	a0, 1208(sp)                    # 8-byte Folded Spill
	lw	a0, 1460(sp)
	sd	a0, 1200(sp)                    # 8-byte Folded Spill
	lw	a0, 1464(sp)
	sd	a0, 1192(sp)                    # 8-byte Folded Spill
	lw	a0, 1468(sp)
	sd	a0, 1184(sp)                    # 8-byte Folded Spill
	lw	a0, 1472(sp)
	sd	a0, 1176(sp)                    # 8-byte Folded Spill
	lw	a0, 1476(sp)
	sd	a0, 1168(sp)                    # 8-byte Folded Spill
	lw	a0, 1480(sp)
	sd	a0, 1160(sp)                    # 8-byte Folded Spill
	lw	a0, 1484(sp)
	sd	a0, 1152(sp)                    # 8-byte Folded Spill
	lw	a0, 1488(sp)
	sd	a0, 1144(sp)                    # 8-byte Folded Spill
	lw	a0, 1492(sp)
	sd	a0, 1136(sp)                    # 8-byte Folded Spill
	lw	a0, 1496(sp)
	sd	a0, 1128(sp)                    # 8-byte Folded Spill
	lw	a0, 1500(sp)
	sd	a0, 1120(sp)                    # 8-byte Folded Spill
	lw	a0, 1504(sp)
	sd	a0, 1112(sp)                    # 8-byte Folded Spill
	lw	a0, 1508(sp)
	sd	a0, 1104(sp)                    # 8-byte Folded Spill
	lw	a0, 1512(sp)
	sd	a0, 1096(sp)                    # 8-byte Folded Spill
	lw	a0, 1516(sp)
	sd	a0, 1088(sp)                    # 8-byte Folded Spill
	lw	a0, 1520(sp)
	sd	a0, 1080(sp)                    # 8-byte Folded Spill
	lw	a0, 1524(sp)
	sd	a0, 1072(sp)                    # 8-byte Folded Spill
	lw	a0, 1528(sp)
	sd	a0, 1064(sp)                    # 8-byte Folded Spill
	lw	a0, 1532(sp)
	sd	a0, 1056(sp)                    # 8-byte Folded Spill
	lw	a0, 1536(sp)
	sd	a0, 1048(sp)                    # 8-byte Folded Spill
	lw	a0, 1540(sp)
	sd	a0, 1040(sp)                    # 8-byte Folded Spill
	lw	a0, 1544(sp)
	sd	a0, 1032(sp)                    # 8-byte Folded Spill
	lw	a0, 1548(sp)
	sd	a0, 1024(sp)                    # 8-byte Folded Spill
	lw	a0, 1552(sp)
	sd	a0, 1016(sp)                    # 8-byte Folded Spill
	lw	a0, 1556(sp)
	sd	a0, 1008(sp)                    # 8-byte Folded Spill
	lw	a0, 1560(sp)
	sd	a0, 1000(sp)                    # 8-byte Folded Spill
	lw	a0, 1564(sp)
	sd	a0, 992(sp)                     # 8-byte Folded Spill
	lw	a0, 1568(sp)
	sd	a0, 984(sp)                     # 8-byte Folded Spill
	lw	a0, 1572(sp)
	sd	a0, 976(sp)                     # 8-byte Folded Spill
	lw	a0, 1576(sp)
	sd	a0, 968(sp)                     # 8-byte Folded Spill
	lw	a0, 1580(sp)
	sd	a0, 960(sp)                     # 8-byte Folded Spill
	lw	a0, 1584(sp)
	sd	a0, 952(sp)                     # 8-byte Folded Spill
	lw	a0, 1588(sp)
	sd	a0, 944(sp)                     # 8-byte Folded Spill
	lw	a0, 1592(sp)
	sd	a0, 936(sp)                     # 8-byte Folded Spill
	lw	a0, 1596(sp)
	sd	a0, 928(sp)                     # 8-byte Folded Spill
	lw	a0, 1600(sp)
	sd	a0, 920(sp)                     # 8-byte Folded Spill
	lw	a0, 1604(sp)
	sd	a0, 912(sp)                     # 8-byte Folded Spill
	lw	a0, 1608(sp)
	sd	a0, 904(sp)                     # 8-byte Folded Spill
	lw	a0, 1612(sp)
	sd	a0, 896(sp)                     # 8-byte Folded Spill
	lw	a0, 1616(sp)
	sd	a0, 888(sp)                     # 8-byte Folded Spill
	lw	a0, 1620(sp)
	sd	a0, 880(sp)                     # 8-byte Folded Spill
	lw	a0, 1624(sp)
	sd	a0, 872(sp)                     # 8-byte Folded Spill
	lw	a0, 1628(sp)
	sd	a0, 864(sp)                     # 8-byte Folded Spill
	lw	a0, 1632(sp)
	sd	a0, 856(sp)                     # 8-byte Folded Spill
	lw	a0, 1636(sp)
	sd	a0, 848(sp)                     # 8-byte Folded Spill
	lw	a0, 1640(sp)
	sd	a0, 840(sp)                     # 8-byte Folded Spill
	lw	a0, 1644(sp)
	sd	a0, 832(sp)                     # 8-byte Folded Spill
	lw	a0, 1648(sp)
	sd	a0, 824(sp)                     # 8-byte Folded Spill
	lw	a0, 1652(sp)
	sd	a0, 816(sp)                     # 8-byte Folded Spill
	lw	a0, 1656(sp)
	sd	a0, 808(sp)                     # 8-byte Folded Spill
	lw	a0, 1660(sp)
	sd	a0, 800(sp)                     # 8-byte Folded Spill
	lw	a0, 1664(sp)
	sd	a0, 792(sp)                     # 8-byte Folded Spill
	lw	a0, 1668(sp)
	sd	a0, 784(sp)                     # 8-byte Folded Spill
	lw	a0, 1672(sp)
	sd	a0, 776(sp)                     # 8-byte Folded Spill
	lw	a0, 1676(sp)
	sd	a0, 768(sp)                     # 8-byte Folded Spill
	lw	ra, 1680(sp)
	lw	s11, 1684(sp)
	lw	s10, 1688(sp)
	lw	s9, 1692(sp)
	lw	s8, 1696(sp)
	lw	s7, 1700(sp)
	lw	s6, 1704(sp)
	lw	s5, 1708(sp)
	lw	s4, 1712(sp)
	lw	s3, 1716(sp)
	lw	s2, 1720(sp)
	lw	s1, 1724(sp)
	lw	s0, 1728(sp)
	lw	t6, 1732(sp)
	lw	t5, 1736(sp)
	lw	t4, 1740(sp)
	lw	t3, 1744(sp)
	lw	t2, 1748(sp)
	lw	t1, 1752(sp)
	lw	t0, 1756(sp)
	lw	a7, 1760(sp)
	lw	a6, 1764(sp)
	lw	a5, 1768(sp)
	lw	a4, 1772(sp)
	lw	a3, 1776(sp)
	lw	a2, 1780(sp)
	lw	a1, 1380(sp)
	lw	a0, 1368(sp)
	sd	a0, 744(sp)
	sd	a1, 736(sp)
	sd	a2, 728(sp)
	sd	a3, 720(sp)
	sd	a4, 712(sp)
	sd	a5, 704(sp)
	sd	a6, 696(sp)
	sd	a7, 688(sp)
	sd	t0, 680(sp)
	sd	t1, 672(sp)
	sd	t2, 664(sp)
	sd	t3, 656(sp)
	sd	t4, 648(sp)
	sd	t5, 640(sp)
	sd	t6, 632(sp)
	sd	s0, 624(sp)
	sd	s1, 616(sp)
	sd	s2, 608(sp)
	sd	s3, 600(sp)
	sd	s4, 592(sp)
	sd	s5, 584(sp)
	sd	s6, 576(sp)
	sd	s7, 568(sp)
	sd	s8, 560(sp)
	sd	s9, 552(sp)
	sd	s10, 544(sp)
	sd	s11, 536(sp)
	sd	ra, 528(sp)
	ld	a0, 768(sp)                     # 8-byte Folded Reload
	sd	a0, 520(sp)
	ld	a0, 776(sp)                     # 8-byte Folded Reload
	sd	a0, 512(sp)
	ld	a0, 784(sp)                     # 8-byte Folded Reload
	sd	a0, 504(sp)
	ld	a0, 792(sp)                     # 8-byte Folded Reload
	sd	a0, 496(sp)
	ld	a0, 800(sp)                     # 8-byte Folded Reload
	sd	a0, 488(sp)
	ld	a0, 808(sp)                     # 8-byte Folded Reload
	sd	a0, 480(sp)
	ld	a0, 816(sp)                     # 8-byte Folded Reload
	sd	a0, 472(sp)
	ld	a0, 824(sp)                     # 8-byte Folded Reload
	sd	a0, 464(sp)
	ld	a0, 832(sp)                     # 8-byte Folded Reload
	sd	a0, 456(sp)
	ld	a0, 840(sp)                     # 8-byte Folded Reload
	sd	a0, 448(sp)
	ld	a0, 848(sp)                     # 8-byte Folded Reload
	sd	a0, 440(sp)
	ld	a0, 856(sp)                     # 8-byte Folded Reload
	sd	a0, 432(sp)
	ld	a0, 864(sp)                     # 8-byte Folded Reload
	sd	a0, 424(sp)
	ld	a0, 872(sp)                     # 8-byte Folded Reload
	sd	a0, 416(sp)
	ld	a0, 880(sp)                     # 8-byte Folded Reload
	sd	a0, 408(sp)
	ld	a0, 888(sp)                     # 8-byte Folded Reload
	sd	a0, 400(sp)
	ld	a0, 896(sp)                     # 8-byte Folded Reload
	sd	a0, 392(sp)
	ld	a0, 904(sp)                     # 8-byte Folded Reload
	sd	a0, 384(sp)
	ld	a0, 912(sp)                     # 8-byte Folded Reload
	sd	a0, 376(sp)
	ld	a0, 920(sp)                     # 8-byte Folded Reload
	sd	a0, 368(sp)
	ld	a0, 928(sp)                     # 8-byte Folded Reload
	sd	a0, 360(sp)
	ld	a0, 936(sp)                     # 8-byte Folded Reload
	sd	a0, 352(sp)
	ld	a0, 944(sp)                     # 8-byte Folded Reload
	sd	a0, 344(sp)
	ld	a0, 952(sp)                     # 8-byte Folded Reload
	sd	a0, 336(sp)
	ld	a0, 960(sp)                     # 8-byte Folded Reload
	sd	a0, 328(sp)
	ld	a0, 968(sp)                     # 8-byte Folded Reload
	sd	a0, 320(sp)
	ld	a0, 976(sp)                     # 8-byte Folded Reload
	sd	a0, 312(sp)
	ld	a0, 984(sp)                     # 8-byte Folded Reload
	sd	a0, 304(sp)
	ld	a0, 992(sp)                     # 8-byte Folded Reload
	sd	a0, 296(sp)
	ld	a0, 1000(sp)                    # 8-byte Folded Reload
	sd	a0, 288(sp)
	ld	a0, 1008(sp)                    # 8-byte Folded Reload
	sd	a0, 280(sp)
	ld	a0, 1016(sp)                    # 8-byte Folded Reload
	sd	a0, 272(sp)
	ld	a0, 1024(sp)                    # 8-byte Folded Reload
	sd	a0, 264(sp)
	ld	a0, 1032(sp)                    # 8-byte Folded Reload
	sd	a0, 256(sp)
	ld	a0, 1040(sp)                    # 8-byte Folded Reload
	sd	a0, 248(sp)
	ld	a0, 1048(sp)                    # 8-byte Folded Reload
	sd	a0, 240(sp)
	ld	a0, 1056(sp)                    # 8-byte Folded Reload
	sd	a0, 232(sp)
	ld	a0, 1064(sp)                    # 8-byte Folded Reload
	sd	a0, 224(sp)
	ld	a0, 1072(sp)                    # 8-byte Folded Reload
	sd	a0, 216(sp)
	ld	a0, 1080(sp)                    # 8-byte Folded Reload
	sd	a0, 208(sp)
	ld	a0, 1088(sp)                    # 8-byte Folded Reload
	sd	a0, 200(sp)
	ld	a0, 1096(sp)                    # 8-byte Folded Reload
	sd	a0, 192(sp)
	ld	a0, 1104(sp)                    # 8-byte Folded Reload
	sd	a0, 184(sp)
	ld	a0, 1112(sp)                    # 8-byte Folded Reload
	sd	a0, 176(sp)
	ld	a0, 1120(sp)                    # 8-byte Folded Reload
	sd	a0, 168(sp)
	ld	a0, 1128(sp)                    # 8-byte Folded Reload
	sd	a0, 160(sp)
	ld	a0, 1136(sp)                    # 8-byte Folded Reload
	sd	a0, 152(sp)
	ld	a0, 1144(sp)                    # 8-byte Folded Reload
	sd	a0, 144(sp)
	ld	a0, 1152(sp)                    # 8-byte Folded Reload
	sd	a0, 136(sp)
	ld	a0, 1160(sp)                    # 8-byte Folded Reload
	sd	a0, 128(sp)
	ld	a0, 1168(sp)                    # 8-byte Folded Reload
	sd	a0, 120(sp)
	ld	a0, 1176(sp)                    # 8-byte Folded Reload
	sd	a0, 112(sp)
	ld	a0, 1184(sp)                    # 8-byte Folded Reload
	sd	a0, 104(sp)
	ld	a0, 1192(sp)                    # 8-byte Folded Reload
	sd	a0, 96(sp)
	ld	a0, 1200(sp)                    # 8-byte Folded Reload
	sd	a0, 88(sp)
	ld	a0, 1208(sp)                    # 8-byte Folded Reload
	sd	a0, 80(sp)
	ld	a0, 1216(sp)                    # 8-byte Folded Reload
	sd	a0, 72(sp)
	ld	a0, 1224(sp)                    # 8-byte Folded Reload
	sd	a0, 64(sp)
	ld	a0, 1232(sp)                    # 8-byte Folded Reload
	sd	a0, 56(sp)
	ld	a0, 1240(sp)                    # 8-byte Folded Reload
	sd	a0, 48(sp)
	ld	a0, 1248(sp)                    # 8-byte Folded Reload
	sd	a0, 40(sp)
	ld	a0, 1256(sp)                    # 8-byte Folded Reload
	sd	a0, 32(sp)
	ld	a0, 1264(sp)                    # 8-byte Folded Reload
	sd	a0, 24(sp)
	ld	a0, 1272(sp)                    # 8-byte Folded Reload
	sd	a0, 16(sp)
	ld	a0, 1280(sp)                    # 8-byte Folded Reload
	sd	a0, 8(sp)
	ld	a0, 1288(sp)                    # 8-byte Folded Reload
	sd	a0, 0(sp)
	ld	a0, 1296(sp)                    # 8-byte Folded Reload
	ld	a1, 1304(sp)                    # 8-byte Folded Reload
	ld	a2, 1312(sp)                    # 8-byte Folded Reload
	ld	a3, 1320(sp)                    # 8-byte Folded Reload
	ld	a4, 1328(sp)                    # 8-byte Folded Reload
	ld	a5, 1336(sp)                    # 8-byte Folded Reload
	ld	a6, 1344(sp)                    # 8-byte Folded Reload
	ld	a7, 1352(sp)                    # 8-byte Folded Reload
	call	quicksort@plt
.LBB0_10:
	lw	a0, 1372(sp)
	lw	a1, 1376(sp)
	bge	a0, a1, .LBB0_12
# %bb.11:
	lw	a0, 1412(sp)
	sd	a0, 1352(sp)                    # 8-byte Folded Spill
	lw	a0, 1408(sp)
	sd	a0, 1344(sp)                    # 8-byte Folded Spill
	lw	a0, 1404(sp)
	sd	a0, 1336(sp)                    # 8-byte Folded Spill
	lw	a0, 1400(sp)
	sd	a0, 1328(sp)                    # 8-byte Folded Spill
	lw	a0, 1396(sp)
	sd	a0, 1320(sp)                    # 8-byte Folded Spill
	lw	a0, 1392(sp)
	sd	a0, 1312(sp)                    # 8-byte Folded Spill
	lw	a0, 1388(sp)
	sd	a0, 1304(sp)                    # 8-byte Folded Spill
	lw	a0, 1384(sp)
	sd	a0, 1296(sp)                    # 8-byte Folded Spill
	lw	a0, 1416(sp)
	sd	a0, 1288(sp)                    # 8-byte Folded Spill
	lw	a0, 1420(sp)
	sd	a0, 1280(sp)                    # 8-byte Folded Spill
	lw	a0, 1424(sp)
	sd	a0, 1272(sp)                    # 8-byte Folded Spill
	lw	a0, 1428(sp)
	sd	a0, 1264(sp)                    # 8-byte Folded Spill
	lw	a0, 1432(sp)
	sd	a0, 1256(sp)                    # 8-byte Folded Spill
	lw	a0, 1436(sp)
	sd	a0, 1248(sp)                    # 8-byte Folded Spill
	lw	a0, 1440(sp)
	sd	a0, 1240(sp)                    # 8-byte Folded Spill
	lw	a0, 1444(sp)
	sd	a0, 1232(sp)                    # 8-byte Folded Spill
	lw	a0, 1448(sp)
	sd	a0, 1224(sp)                    # 8-byte Folded Spill
	lw	a0, 1452(sp)
	sd	a0, 1216(sp)                    # 8-byte Folded Spill
	lw	a0, 1456(sp)
	sd	a0, 1208(sp)                    # 8-byte Folded Spill
	lw	a0, 1460(sp)
	sd	a0, 1200(sp)                    # 8-byte Folded Spill
	lw	a0, 1464(sp)
	sd	a0, 1192(sp)                    # 8-byte Folded Spill
	lw	a0, 1468(sp)
	sd	a0, 1184(sp)                    # 8-byte Folded Spill
	lw	a0, 1472(sp)
	sd	a0, 1176(sp)                    # 8-byte Folded Spill
	lw	a0, 1476(sp)
	sd	a0, 1168(sp)                    # 8-byte Folded Spill
	lw	a0, 1480(sp)
	sd	a0, 1160(sp)                    # 8-byte Folded Spill
	lw	a0, 1484(sp)
	sd	a0, 1152(sp)                    # 8-byte Folded Spill
	lw	a0, 1488(sp)
	sd	a0, 1144(sp)                    # 8-byte Folded Spill
	lw	a0, 1492(sp)
	sd	a0, 1136(sp)                    # 8-byte Folded Spill
	lw	a0, 1496(sp)
	sd	a0, 1128(sp)                    # 8-byte Folded Spill
	lw	a0, 1500(sp)
	sd	a0, 1120(sp)                    # 8-byte Folded Spill
	lw	a0, 1504(sp)
	sd	a0, 1112(sp)                    # 8-byte Folded Spill
	lw	a0, 1508(sp)
	sd	a0, 1104(sp)                    # 8-byte Folded Spill
	lw	a0, 1512(sp)
	sd	a0, 1096(sp)                    # 8-byte Folded Spill
	lw	a0, 1516(sp)
	sd	a0, 1088(sp)                    # 8-byte Folded Spill
	lw	a0, 1520(sp)
	sd	a0, 1080(sp)                    # 8-byte Folded Spill
	lw	a0, 1524(sp)
	sd	a0, 1072(sp)                    # 8-byte Folded Spill
	lw	a0, 1528(sp)
	sd	a0, 1064(sp)                    # 8-byte Folded Spill
	lw	a0, 1532(sp)
	sd	a0, 1056(sp)                    # 8-byte Folded Spill
	lw	a0, 1536(sp)
	sd	a0, 1048(sp)                    # 8-byte Folded Spill
	lw	a0, 1540(sp)
	sd	a0, 1040(sp)                    # 8-byte Folded Spill
	lw	a0, 1544(sp)
	sd	a0, 1032(sp)                    # 8-byte Folded Spill
	lw	a0, 1548(sp)
	sd	a0, 1024(sp)                    # 8-byte Folded Spill
	lw	a0, 1552(sp)
	sd	a0, 1016(sp)                    # 8-byte Folded Spill
	lw	a0, 1556(sp)
	sd	a0, 1008(sp)                    # 8-byte Folded Spill
	lw	a0, 1560(sp)
	sd	a0, 1000(sp)                    # 8-byte Folded Spill
	lw	a0, 1564(sp)
	sd	a0, 992(sp)                     # 8-byte Folded Spill
	lw	a0, 1568(sp)
	sd	a0, 984(sp)                     # 8-byte Folded Spill
	lw	a0, 1572(sp)
	sd	a0, 976(sp)                     # 8-byte Folded Spill
	lw	a0, 1576(sp)
	sd	a0, 968(sp)                     # 8-byte Folded Spill
	lw	a0, 1580(sp)
	sd	a0, 960(sp)                     # 8-byte Folded Spill
	lw	a0, 1584(sp)
	sd	a0, 952(sp)                     # 8-byte Folded Spill
	lw	a0, 1588(sp)
	sd	a0, 944(sp)                     # 8-byte Folded Spill
	lw	a0, 1592(sp)
	sd	a0, 936(sp)                     # 8-byte Folded Spill
	lw	a0, 1596(sp)
	sd	a0, 928(sp)                     # 8-byte Folded Spill
	lw	a0, 1600(sp)
	sd	a0, 920(sp)                     # 8-byte Folded Spill
	lw	a0, 1604(sp)
	sd	a0, 912(sp)                     # 8-byte Folded Spill
	lw	a0, 1608(sp)
	sd	a0, 904(sp)                     # 8-byte Folded Spill
	lw	a0, 1612(sp)
	sd	a0, 896(sp)                     # 8-byte Folded Spill
	lw	a0, 1616(sp)
	sd	a0, 888(sp)                     # 8-byte Folded Spill
	lw	a0, 1620(sp)
	sd	a0, 880(sp)                     # 8-byte Folded Spill
	lw	a0, 1624(sp)
	sd	a0, 872(sp)                     # 8-byte Folded Spill
	lw	a0, 1628(sp)
	sd	a0, 864(sp)                     # 8-byte Folded Spill
	lw	a0, 1632(sp)
	sd	a0, 856(sp)                     # 8-byte Folded Spill
	lw	a0, 1636(sp)
	sd	a0, 848(sp)                     # 8-byte Folded Spill
	lw	a0, 1640(sp)
	sd	a0, 840(sp)                     # 8-byte Folded Spill
	lw	a0, 1644(sp)
	sd	a0, 832(sp)                     # 8-byte Folded Spill
	lw	a0, 1648(sp)
	sd	a0, 824(sp)                     # 8-byte Folded Spill
	lw	a0, 1652(sp)
	sd	a0, 816(sp)                     # 8-byte Folded Spill
	lw	a0, 1656(sp)
	sd	a0, 808(sp)                     # 8-byte Folded Spill
	lw	a0, 1660(sp)
	sd	a0, 800(sp)                     # 8-byte Folded Spill
	lw	a0, 1664(sp)
	sd	a0, 792(sp)                     # 8-byte Folded Spill
	lw	a0, 1668(sp)
	sd	a0, 784(sp)                     # 8-byte Folded Spill
	lw	a0, 1672(sp)
	sd	a0, 776(sp)                     # 8-byte Folded Spill
	lw	a0, 1676(sp)
	sd	a0, 768(sp)                     # 8-byte Folded Spill
	lw	ra, 1680(sp)
	lw	s11, 1684(sp)
	lw	s10, 1688(sp)
	lw	s9, 1692(sp)
	lw	s8, 1696(sp)
	lw	s7, 1700(sp)
	lw	s6, 1704(sp)
	lw	s5, 1708(sp)
	lw	s4, 1712(sp)
	lw	s3, 1716(sp)
	lw	s2, 1720(sp)
	lw	s1, 1724(sp)
	lw	s0, 1728(sp)
	lw	t6, 1732(sp)
	lw	t5, 1736(sp)
	lw	t4, 1740(sp)
	lw	t3, 1744(sp)
	lw	t2, 1748(sp)
	lw	t1, 1752(sp)
	lw	t0, 1756(sp)
	lw	a7, 1760(sp)
	lw	a6, 1764(sp)
	lw	a5, 1768(sp)
	lw	a4, 1772(sp)
	lw	a3, 1776(sp)
	lw	a2, 1780(sp)
	lw	a1, 1372(sp)
	lw	a0, 1376(sp)
	sd	a0, 744(sp)
	sd	a1, 736(sp)
	sd	a2, 728(sp)
	sd	a3, 720(sp)
	sd	a4, 712(sp)
	sd	a5, 704(sp)
	sd	a6, 696(sp)
	sd	a7, 688(sp)
	sd	t0, 680(sp)
	sd	t1, 672(sp)
	sd	t2, 664(sp)
	sd	t3, 656(sp)
	sd	t4, 648(sp)
	sd	t5, 640(sp)
	sd	t6, 632(sp)
	sd	s0, 624(sp)
	sd	s1, 616(sp)
	sd	s2, 608(sp)
	sd	s3, 600(sp)
	sd	s4, 592(sp)
	sd	s5, 584(sp)
	sd	s6, 576(sp)
	sd	s7, 568(sp)
	sd	s8, 560(sp)
	sd	s9, 552(sp)
	sd	s10, 544(sp)
	sd	s11, 536(sp)
	sd	ra, 528(sp)
	ld	a0, 768(sp)                     # 8-byte Folded Reload
	sd	a0, 520(sp)
	ld	a0, 776(sp)                     # 8-byte Folded Reload
	sd	a0, 512(sp)
	ld	a0, 784(sp)                     # 8-byte Folded Reload
	sd	a0, 504(sp)
	ld	a0, 792(sp)                     # 8-byte Folded Reload
	sd	a0, 496(sp)
	ld	a0, 800(sp)                     # 8-byte Folded Reload
	sd	a0, 488(sp)
	ld	a0, 808(sp)                     # 8-byte Folded Reload
	sd	a0, 480(sp)
	ld	a0, 816(sp)                     # 8-byte Folded Reload
	sd	a0, 472(sp)
	ld	a0, 824(sp)                     # 8-byte Folded Reload
	sd	a0, 464(sp)
	ld	a0, 832(sp)                     # 8-byte Folded Reload
	sd	a0, 456(sp)
	ld	a0, 840(sp)                     # 8-byte Folded Reload
	sd	a0, 448(sp)
	ld	a0, 848(sp)                     # 8-byte Folded Reload
	sd	a0, 440(sp)
	ld	a0, 856(sp)                     # 8-byte Folded Reload
	sd	a0, 432(sp)
	ld	a0, 864(sp)                     # 8-byte Folded Reload
	sd	a0, 424(sp)
	ld	a0, 872(sp)                     # 8-byte Folded Reload
	sd	a0, 416(sp)
	ld	a0, 880(sp)                     # 8-byte Folded Reload
	sd	a0, 408(sp)
	ld	a0, 888(sp)                     # 8-byte Folded Reload
	sd	a0, 400(sp)
	ld	a0, 896(sp)                     # 8-byte Folded Reload
	sd	a0, 392(sp)
	ld	a0, 904(sp)                     # 8-byte Folded Reload
	sd	a0, 384(sp)
	ld	a0, 912(sp)                     # 8-byte Folded Reload
	sd	a0, 376(sp)
	ld	a0, 920(sp)                     # 8-byte Folded Reload
	sd	a0, 368(sp)
	ld	a0, 928(sp)                     # 8-byte Folded Reload
	sd	a0, 360(sp)
	ld	a0, 936(sp)                     # 8-byte Folded Reload
	sd	a0, 352(sp)
	ld	a0, 944(sp)                     # 8-byte Folded Reload
	sd	a0, 344(sp)
	ld	a0, 952(sp)                     # 8-byte Folded Reload
	sd	a0, 336(sp)
	ld	a0, 960(sp)                     # 8-byte Folded Reload
	sd	a0, 328(sp)
	ld	a0, 968(sp)                     # 8-byte Folded Reload
	sd	a0, 320(sp)
	ld	a0, 976(sp)                     # 8-byte Folded Reload
	sd	a0, 312(sp)
	ld	a0, 984(sp)                     # 8-byte Folded Reload
	sd	a0, 304(sp)
	ld	a0, 992(sp)                     # 8-byte Folded Reload
	sd	a0, 296(sp)
	ld	a0, 1000(sp)                    # 8-byte Folded Reload
	sd	a0, 288(sp)
	ld	a0, 1008(sp)                    # 8-byte Folded Reload
	sd	a0, 280(sp)
	ld	a0, 1016(sp)                    # 8-byte Folded Reload
	sd	a0, 272(sp)
	ld	a0, 1024(sp)                    # 8-byte Folded Reload
	sd	a0, 264(sp)
	ld	a0, 1032(sp)                    # 8-byte Folded Reload
	sd	a0, 256(sp)
	ld	a0, 1040(sp)                    # 8-byte Folded Reload
	sd	a0, 248(sp)
	ld	a0, 1048(sp)                    # 8-byte Folded Reload
	sd	a0, 240(sp)
	ld	a0, 1056(sp)                    # 8-byte Folded Reload
	sd	a0, 232(sp)
	ld	a0, 1064(sp)                    # 8-byte Folded Reload
	sd	a0, 224(sp)
	ld	a0, 1072(sp)                    # 8-byte Folded Reload
	sd	a0, 216(sp)
	ld	a0, 1080(sp)                    # 8-byte Folded Reload
	sd	a0, 208(sp)
	ld	a0, 1088(sp)                    # 8-byte Folded Reload
	sd	a0, 200(sp)
	ld	a0, 1096(sp)                    # 8-byte Folded Reload
	sd	a0, 192(sp)
	ld	a0, 1104(sp)                    # 8-byte Folded Reload
	sd	a0, 184(sp)
	ld	a0, 1112(sp)                    # 8-byte Folded Reload
	sd	a0, 176(sp)
	ld	a0, 1120(sp)                    # 8-byte Folded Reload
	sd	a0, 168(sp)
	ld	a0, 1128(sp)                    # 8-byte Folded Reload
	sd	a0, 160(sp)
	ld	a0, 1136(sp)                    # 8-byte Folded Reload
	sd	a0, 152(sp)
	ld	a0, 1144(sp)                    # 8-byte Folded Reload
	sd	a0, 144(sp)
	ld	a0, 1152(sp)                    # 8-byte Folded Reload
	sd	a0, 136(sp)
	ld	a0, 1160(sp)                    # 8-byte Folded Reload
	sd	a0, 128(sp)
	ld	a0, 1168(sp)                    # 8-byte Folded Reload
	sd	a0, 120(sp)
	ld	a0, 1176(sp)                    # 8-byte Folded Reload
	sd	a0, 112(sp)
	ld	a0, 1184(sp)                    # 8-byte Folded Reload
	sd	a0, 104(sp)
	ld	a0, 1192(sp)                    # 8-byte Folded Reload
	sd	a0, 96(sp)
	ld	a0, 1200(sp)                    # 8-byte Folded Reload
	sd	a0, 88(sp)
	ld	a0, 1208(sp)                    # 8-byte Folded Reload
	sd	a0, 80(sp)
	ld	a0, 1216(sp)                    # 8-byte Folded Reload
	sd	a0, 72(sp)
	ld	a0, 1224(sp)                    # 8-byte Folded Reload
	sd	a0, 64(sp)
	ld	a0, 1232(sp)                    # 8-byte Folded Reload
	sd	a0, 56(sp)
	ld	a0, 1240(sp)                    # 8-byte Folded Reload
	sd	a0, 48(sp)
	ld	a0, 1248(sp)                    # 8-byte Folded Reload
	sd	a0, 40(sp)
	ld	a0, 1256(sp)                    # 8-byte Folded Reload
	sd	a0, 32(sp)
	ld	a0, 1264(sp)                    # 8-byte Folded Reload
	sd	a0, 24(sp)
	ld	a0, 1272(sp)                    # 8-byte Folded Reload
	sd	a0, 16(sp)
	ld	a0, 1280(sp)                    # 8-byte Folded Reload
	sd	a0, 8(sp)
	ld	a0, 1288(sp)                    # 8-byte Folded Reload
	sd	a0, 0(sp)
	ld	a0, 1296(sp)                    # 8-byte Folded Reload
	ld	a1, 1304(sp)                    # 8-byte Folded Reload
	ld	a2, 1312(sp)                    # 8-byte Folded Reload
	ld	a3, 1320(sp)                    # 8-byte Folded Reload
	ld	a4, 1328(sp)                    # 8-byte Folded Reload
	ld	a5, 1336(sp)                    # 8-byte Folded Reload
	ld	a6, 1344(sp)                    # 8-byte Folded Reload
	ld	a7, 1352(sp)                    # 8-byte Folded Reload
	call	quicksort@plt
.LBB0_12:
	ld	ra, 1880(sp)                    # 8-byte Folded Reload
	ld	s0, 1872(sp)                    # 8-byte Folded Reload
	ld	s1, 1864(sp)                    # 8-byte Folded Reload
	ld	s2, 1856(sp)                    # 8-byte Folded Reload
	ld	s3, 1848(sp)                    # 8-byte Folded Reload
	ld	s4, 1840(sp)                    # 8-byte Folded Reload
	ld	s5, 1832(sp)                    # 8-byte Folded Reload
	ld	s6, 1824(sp)                    # 8-byte Folded Reload
	ld	s7, 1816(sp)                    # 8-byte Folded Reload
	ld	s8, 1808(sp)                    # 8-byte Folded Reload
	ld	s9, 1800(sp)                    # 8-byte Folded Reload
	ld	s10, 1792(sp)                   # 8-byte Folded Reload
	ld	s11, 1784(sp)                   # 8-byte Folded Reload
	addi	sp, sp, 1888
	ret
.Lfunc_end0:
	.size	quicksort, .Lfunc_end0-quicksort
	.cfi_endproc
                                        # -- End function
	.globl	main                            # -- Begin function main
	.p2align	2
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %entry_main
	addi	sp, sp, -1152
	.cfi_def_cfa_offset 1152
	sd	ra, 1144(sp)                    # 8-byte Folded Spill
	sd	s0, 1136(sp)                    # 8-byte Folded Spill
	sd	s1, 1128(sp)                    # 8-byte Folded Spill
	sd	s2, 1120(sp)                    # 8-byte Folded Spill
	sd	s3, 1112(sp)                    # 8-byte Folded Spill
	sd	s4, 1104(sp)                    # 8-byte Folded Spill
	sd	s5, 1096(sp)                    # 8-byte Folded Spill
	sd	s6, 1088(sp)                    # 8-byte Folded Spill
	sd	s7, 1080(sp)                    # 8-byte Folded Spill
	sd	s8, 1072(sp)                    # 8-byte Folded Spill
	sd	s9, 1064(sp)                    # 8-byte Folded Spill
	sd	s10, 1056(sp)                   # 8-byte Folded Spill
	sd	s11, 1048(sp)                   # 8-byte Folded Spill
	.cfi_offset ra, -8
	.cfi_offset s0, -16
	.cfi_offset s1, -24
	.cfi_offset s2, -32
	.cfi_offset s3, -40
	.cfi_offset s4, -48
	.cfi_offset s5, -56
	.cfi_offset s6, -64
	.cfi_offset s7, -72
	.cfi_offset s8, -80
	.cfi_offset s9, -88
	.cfi_offset s10, -96
	.cfi_offset s11, -104
	addi	s0, sp, 1152
	.cfi_def_cfa s0, 0
	lui	a0, %hi(.L__unnamed_1)
	addi	a0, a0, %lo(.L__unnamed_1)
	addi	a1, s0, -516
	call	scanf@plt
	sw	zero, -520(s0)
	addi	s2, s0, -512
	lui	a0, %hi(.L__unnamed_2)
	addi	s1, a0, %lo(.L__unnamed_2)
.LBB1_1:                                # %WhileCond
                                        # =>This Inner Loop Header: Depth=1
	lw	a0, -520(s0)
	lw	a1, -516(s0)
	bge	a0, a1, .LBB1_3
# %bb.2:                                # %WhileLoop
                                        #   in Loop: Header=BB1_1 Depth=1
	lw	a0, -520(s0)
	slli	a0, a0, 2
	add	a1, s2, a0
	mv	a0, s1
	call	scanf@plt
	lw	a0, -520(s0)
	addiw	a0, a0, 1
	sw	a0, -520(s0)
	j	.LBB1_1
.LBB1_3:                                # %WhileEnd
	mv	a0, sp
	addi	sp, a0, -16
	lw	a1, -516(s0)
	sw	zero, -16(a0)
	addiw	a1, a1, -1
	sd	a1, -912(s0)                    # 8-byte Folded Spill
	mv	a1, sp
	sd	a1, -944(s0)                    # 8-byte Folded Spill
	addi	sp, a1, -16
	lw	a0, -16(a0)
	sd	a0, -936(s0)                    # 8-byte Folded Spill
	lw	a0, -484(s0)
	sd	a0, -528(s0)                    # 8-byte Folded Spill
	lw	a0, -488(s0)
	sd	a0, -536(s0)                    # 8-byte Folded Spill
	lw	a0, -492(s0)
	sd	a0, -544(s0)                    # 8-byte Folded Spill
	lw	a0, -496(s0)
	sd	a0, -552(s0)                    # 8-byte Folded Spill
	lw	a0, -500(s0)
	sd	a0, -560(s0)                    # 8-byte Folded Spill
	lw	a0, -504(s0)
	sd	a0, -568(s0)                    # 8-byte Folded Spill
	lw	a0, -508(s0)
	sd	a0, -576(s0)                    # 8-byte Folded Spill
	lw	a0, -512(s0)
	sd	a0, -584(s0)                    # 8-byte Folded Spill
	lw	a0, -480(s0)
	sd	a0, -592(s0)                    # 8-byte Folded Spill
	lw	a0, -476(s0)
	sd	a0, -600(s0)                    # 8-byte Folded Spill
	lw	a0, -472(s0)
	sd	a0, -608(s0)                    # 8-byte Folded Spill
	lw	a0, -468(s0)
	sd	a0, -616(s0)                    # 8-byte Folded Spill
	lw	a0, -464(s0)
	sd	a0, -624(s0)                    # 8-byte Folded Spill
	lw	a0, -460(s0)
	sd	a0, -632(s0)                    # 8-byte Folded Spill
	lw	a0, -456(s0)
	sd	a0, -640(s0)                    # 8-byte Folded Spill
	lw	a0, -452(s0)
	sd	a0, -648(s0)                    # 8-byte Folded Spill
	lw	a0, -448(s0)
	sd	a0, -656(s0)                    # 8-byte Folded Spill
	lw	a0, -444(s0)
	sd	a0, -664(s0)                    # 8-byte Folded Spill
	lw	a0, -440(s0)
	sd	a0, -672(s0)                    # 8-byte Folded Spill
	lw	a0, -436(s0)
	sd	a0, -680(s0)                    # 8-byte Folded Spill
	lw	a0, -432(s0)
	sd	a0, -688(s0)                    # 8-byte Folded Spill
	lw	a0, -428(s0)
	sd	a0, -696(s0)                    # 8-byte Folded Spill
	lw	a0, -424(s0)
	sd	a0, -704(s0)                    # 8-byte Folded Spill
	lw	a0, -420(s0)
	sd	a0, -712(s0)                    # 8-byte Folded Spill
	lw	a0, -416(s0)
	sd	a0, -720(s0)                    # 8-byte Folded Spill
	lw	a0, -412(s0)
	sd	a0, -728(s0)                    # 8-byte Folded Spill
	lw	a0, -408(s0)
	sd	a0, -736(s0)                    # 8-byte Folded Spill
	lw	a0, -404(s0)
	sd	a0, -744(s0)                    # 8-byte Folded Spill
	lw	a0, -400(s0)
	sd	a0, -752(s0)                    # 8-byte Folded Spill
	lw	a0, -396(s0)
	sd	a0, -760(s0)                    # 8-byte Folded Spill
	lw	a0, -392(s0)
	sd	a0, -768(s0)                    # 8-byte Folded Spill
	lw	a0, -388(s0)
	sd	a0, -776(s0)                    # 8-byte Folded Spill
	lw	a0, -384(s0)
	sd	a0, -784(s0)                    # 8-byte Folded Spill
	lw	a0, -380(s0)
	sd	a0, -792(s0)                    # 8-byte Folded Spill
	lw	a0, -376(s0)
	sd	a0, -800(s0)                    # 8-byte Folded Spill
	lw	a0, -372(s0)
	sd	a0, -808(s0)                    # 8-byte Folded Spill
	lw	a0, -368(s0)
	sd	a0, -816(s0)                    # 8-byte Folded Spill
	lw	a0, -364(s0)
	sd	a0, -824(s0)                    # 8-byte Folded Spill
	lw	a0, -360(s0)
	sd	a0, -832(s0)                    # 8-byte Folded Spill
	lw	a0, -356(s0)
	sd	a0, -840(s0)                    # 8-byte Folded Spill
	lw	a0, -352(s0)
	sd	a0, -848(s0)                    # 8-byte Folded Spill
	lw	a0, -348(s0)
	sd	a0, -856(s0)                    # 8-byte Folded Spill
	lw	a0, -344(s0)
	sd	a0, -864(s0)                    # 8-byte Folded Spill
	lw	a0, -340(s0)
	sd	a0, -872(s0)                    # 8-byte Folded Spill
	lw	a0, -336(s0)
	sd	a0, -880(s0)                    # 8-byte Folded Spill
	lw	a0, -332(s0)
	sd	a0, -888(s0)                    # 8-byte Folded Spill
	lw	a0, -328(s0)
	sd	a0, -896(s0)                    # 8-byte Folded Spill
	lw	a0, -324(s0)
	sd	a0, -904(s0)                    # 8-byte Folded Spill
	lw	a0, -320(s0)
	sd	a0, -920(s0)                    # 8-byte Folded Spill
	lw	a0, -316(s0)
	sd	a0, -928(s0)                    # 8-byte Folded Spill
	lw	a0, -312(s0)
	sd	a0, -952(s0)                    # 8-byte Folded Spill
	lw	a0, -308(s0)
	sd	a0, -960(s0)                    # 8-byte Folded Spill
	lw	a0, -304(s0)
	sd	a0, -968(s0)                    # 8-byte Folded Spill
	lw	a0, -300(s0)
	sd	a0, -976(s0)                    # 8-byte Folded Spill
	lw	a0, -296(s0)
	sd	a0, -984(s0)                    # 8-byte Folded Spill
	lw	a0, -292(s0)
	sd	a0, -992(s0)                    # 8-byte Folded Spill
	lw	a0, -288(s0)
	sd	a0, -1000(s0)                   # 8-byte Folded Spill
	lw	a0, -284(s0)
	sd	a0, -1008(s0)                   # 8-byte Folded Spill
	lw	a0, -280(s0)
	sd	a0, -1016(s0)                   # 8-byte Folded Spill
	lw	a0, -276(s0)
	sd	a0, -1024(s0)                   # 8-byte Folded Spill
	lw	a0, -272(s0)
	sd	a0, -1032(s0)                   # 8-byte Folded Spill
	lw	a0, -268(s0)
	sd	a0, -1040(s0)                   # 8-byte Folded Spill
	lw	a0, -264(s0)
	sd	a0, -1048(s0)                   # 8-byte Folded Spill
	lw	a0, -260(s0)
	sd	a0, -1056(s0)                   # 8-byte Folded Spill
	lw	a0, -256(s0)
	sd	a0, -1064(s0)                   # 8-byte Folded Spill
	lw	a0, -252(s0)
	sd	a0, -1072(s0)                   # 8-byte Folded Spill
	lw	a0, -248(s0)
	sd	a0, -1080(s0)                   # 8-byte Folded Spill
	lw	a0, -244(s0)
	sd	a0, -1088(s0)                   # 8-byte Folded Spill
	lw	a0, -240(s0)
	sd	a0, -1096(s0)                   # 8-byte Folded Spill
	lw	a0, -236(s0)
	sd	a0, -1104(s0)                   # 8-byte Folded Spill
	lw	a0, -232(s0)
	sd	a0, -1112(s0)                   # 8-byte Folded Spill
	lw	a0, -228(s0)
	sd	a0, -1120(s0)                   # 8-byte Folded Spill
	lw	a0, -224(s0)
	sd	a0, -1128(s0)                   # 8-byte Folded Spill
	lw	a0, -220(s0)
	sd	a0, -1136(s0)                   # 8-byte Folded Spill
	lw	a0, -216(s0)
	sd	a0, -1144(s0)                   # 8-byte Folded Spill
	lw	s11, -212(s0)
	lw	s10, -208(s0)
	lw	s9, -204(s0)
	lw	s8, -200(s0)
	lw	s7, -196(s0)
	lw	s6, -192(s0)
	lw	s5, -188(s0)
	lw	s4, -184(s0)
	lw	s3, -180(s0)
	lw	s2, -176(s0)
	lw	s1, -172(s0)
	lw	t6, -168(s0)
	lw	t5, -164(s0)
	lw	t4, -160(s0)
	lw	t3, -156(s0)
	lw	t2, -152(s0)
	lw	t1, -148(s0)
	lw	t0, -144(s0)
	lw	a7, -140(s0)
	lw	a6, -136(s0)
	lw	a5, -132(s0)
	lw	a4, -128(s0)
	lw	a3, -124(s0)
	lw	a2, -120(s0)
	lw	a1, -116(s0)
	ld	a0, -912(s0)                    # 8-byte Folded Reload
	ld	ra, -944(s0)                    # 8-byte Folded Reload
	sw	a0, -16(ra)
	addi	sp, sp, -752
	sd	a0, 744(sp)
	ld	a0, -936(s0)                    # 8-byte Folded Reload
	sd	a0, 736(sp)
	sd	a1, 728(sp)
	sd	a2, 720(sp)
	sd	a3, 712(sp)
	sd	a4, 704(sp)
	sd	a5, 696(sp)
	sd	a6, 688(sp)
	sd	a7, 680(sp)
	sd	t0, 672(sp)
	sd	t1, 664(sp)
	sd	t2, 656(sp)
	sd	t3, 648(sp)
	sd	t4, 640(sp)
	sd	t5, 632(sp)
	sd	t6, 624(sp)
	sd	s1, 616(sp)
	sd	s2, 608(sp)
	sd	s3, 600(sp)
	sd	s4, 592(sp)
	sd	s5, 584(sp)
	sd	s6, 576(sp)
	sd	s7, 568(sp)
	sd	s8, 560(sp)
	sd	s9, 552(sp)
	sd	s10, 544(sp)
	sd	s11, 536(sp)
	ld	a0, -1144(s0)                   # 8-byte Folded Reload
	sd	a0, 528(sp)
	ld	a0, -1136(s0)                   # 8-byte Folded Reload
	sd	a0, 520(sp)
	ld	a0, -1128(s0)                   # 8-byte Folded Reload
	sd	a0, 512(sp)
	ld	a0, -1120(s0)                   # 8-byte Folded Reload
	sd	a0, 504(sp)
	ld	a0, -1112(s0)                   # 8-byte Folded Reload
	sd	a0, 496(sp)
	ld	a0, -1104(s0)                   # 8-byte Folded Reload
	sd	a0, 488(sp)
	ld	a0, -1096(s0)                   # 8-byte Folded Reload
	sd	a0, 480(sp)
	ld	a0, -1088(s0)                   # 8-byte Folded Reload
	sd	a0, 472(sp)
	ld	a0, -1080(s0)                   # 8-byte Folded Reload
	sd	a0, 464(sp)
	ld	a0, -1072(s0)                   # 8-byte Folded Reload
	sd	a0, 456(sp)
	ld	a0, -1064(s0)                   # 8-byte Folded Reload
	sd	a0, 448(sp)
	ld	a0, -1056(s0)                   # 8-byte Folded Reload
	sd	a0, 440(sp)
	ld	a0, -1048(s0)                   # 8-byte Folded Reload
	sd	a0, 432(sp)
	ld	a0, -1040(s0)                   # 8-byte Folded Reload
	sd	a0, 424(sp)
	ld	a0, -1032(s0)                   # 8-byte Folded Reload
	sd	a0, 416(sp)
	ld	a0, -1024(s0)                   # 8-byte Folded Reload
	sd	a0, 408(sp)
	ld	a0, -1016(s0)                   # 8-byte Folded Reload
	sd	a0, 400(sp)
	ld	a0, -1008(s0)                   # 8-byte Folded Reload
	sd	a0, 392(sp)
	ld	a0, -1000(s0)                   # 8-byte Folded Reload
	sd	a0, 384(sp)
	ld	a0, -992(s0)                    # 8-byte Folded Reload
	sd	a0, 376(sp)
	ld	a0, -984(s0)                    # 8-byte Folded Reload
	sd	a0, 368(sp)
	ld	a0, -976(s0)                    # 8-byte Folded Reload
	sd	a0, 360(sp)
	ld	a0, -968(s0)                    # 8-byte Folded Reload
	sd	a0, 352(sp)
	ld	a0, -960(s0)                    # 8-byte Folded Reload
	sd	a0, 344(sp)
	ld	a0, -952(s0)                    # 8-byte Folded Reload
	sd	a0, 336(sp)
	ld	a0, -928(s0)                    # 8-byte Folded Reload
	sd	a0, 328(sp)
	ld	a0, -920(s0)                    # 8-byte Folded Reload
	sd	a0, 320(sp)
	ld	a0, -904(s0)                    # 8-byte Folded Reload
	sd	a0, 312(sp)
	ld	a0, -896(s0)                    # 8-byte Folded Reload
	sd	a0, 304(sp)
	ld	a0, -888(s0)                    # 8-byte Folded Reload
	sd	a0, 296(sp)
	ld	a0, -880(s0)                    # 8-byte Folded Reload
	sd	a0, 288(sp)
	ld	a0, -872(s0)                    # 8-byte Folded Reload
	sd	a0, 280(sp)
	ld	a0, -864(s0)                    # 8-byte Folded Reload
	sd	a0, 272(sp)
	ld	a0, -856(s0)                    # 8-byte Folded Reload
	sd	a0, 264(sp)
	ld	a0, -848(s0)                    # 8-byte Folded Reload
	sd	a0, 256(sp)
	ld	a0, -840(s0)                    # 8-byte Folded Reload
	sd	a0, 248(sp)
	ld	a0, -832(s0)                    # 8-byte Folded Reload
	sd	a0, 240(sp)
	ld	a0, -824(s0)                    # 8-byte Folded Reload
	sd	a0, 232(sp)
	ld	a0, -816(s0)                    # 8-byte Folded Reload
	sd	a0, 224(sp)
	ld	a0, -808(s0)                    # 8-byte Folded Reload
	sd	a0, 216(sp)
	ld	a0, -800(s0)                    # 8-byte Folded Reload
	sd	a0, 208(sp)
	ld	a0, -792(s0)                    # 8-byte Folded Reload
	sd	a0, 200(sp)
	ld	a0, -784(s0)                    # 8-byte Folded Reload
	sd	a0, 192(sp)
	ld	a0, -776(s0)                    # 8-byte Folded Reload
	sd	a0, 184(sp)
	ld	a0, -768(s0)                    # 8-byte Folded Reload
	sd	a0, 176(sp)
	ld	a0, -760(s0)                    # 8-byte Folded Reload
	sd	a0, 168(sp)
	ld	a0, -752(s0)                    # 8-byte Folded Reload
	sd	a0, 160(sp)
	ld	a0, -744(s0)                    # 8-byte Folded Reload
	sd	a0, 152(sp)
	ld	a0, -736(s0)                    # 8-byte Folded Reload
	sd	a0, 144(sp)
	ld	a0, -728(s0)                    # 8-byte Folded Reload
	sd	a0, 136(sp)
	ld	a0, -720(s0)                    # 8-byte Folded Reload
	sd	a0, 128(sp)
	ld	a0, -712(s0)                    # 8-byte Folded Reload
	sd	a0, 120(sp)
	ld	a0, -704(s0)                    # 8-byte Folded Reload
	sd	a0, 112(sp)
	ld	a0, -696(s0)                    # 8-byte Folded Reload
	sd	a0, 104(sp)
	ld	a0, -688(s0)                    # 8-byte Folded Reload
	sd	a0, 96(sp)
	ld	a0, -680(s0)                    # 8-byte Folded Reload
	sd	a0, 88(sp)
	ld	a0, -672(s0)                    # 8-byte Folded Reload
	sd	a0, 80(sp)
	ld	a0, -664(s0)                    # 8-byte Folded Reload
	sd	a0, 72(sp)
	ld	a0, -656(s0)                    # 8-byte Folded Reload
	sd	a0, 64(sp)
	ld	a0, -648(s0)                    # 8-byte Folded Reload
	sd	a0, 56(sp)
	ld	a0, -640(s0)                    # 8-byte Folded Reload
	sd	a0, 48(sp)
	ld	a0, -632(s0)                    # 8-byte Folded Reload
	sd	a0, 40(sp)
	ld	a0, -624(s0)                    # 8-byte Folded Reload
	sd	a0, 32(sp)
	ld	a0, -616(s0)                    # 8-byte Folded Reload
	sd	a0, 24(sp)
	ld	a0, -608(s0)                    # 8-byte Folded Reload
	sd	a0, 16(sp)
	ld	a0, -600(s0)                    # 8-byte Folded Reload
	sd	a0, 8(sp)
	ld	a0, -592(s0)                    # 8-byte Folded Reload
	sd	a0, 0(sp)
	ld	a0, -584(s0)                    # 8-byte Folded Reload
	ld	a1, -576(s0)                    # 8-byte Folded Reload
	ld	a2, -568(s0)                    # 8-byte Folded Reload
	ld	a3, -560(s0)                    # 8-byte Folded Reload
	ld	a4, -552(s0)                    # 8-byte Folded Reload
	ld	a5, -544(s0)                    # 8-byte Folded Reload
	ld	a6, -536(s0)                    # 8-byte Folded Reload
	ld	a7, -528(s0)                    # 8-byte Folded Reload
	call	quicksort@plt
	addi	sp, sp, 752
	sw	zero, -520(s0)
	addi	s2, s0, -512
	lui	a0, %hi(.L__unnamed_3)
	addi	s1, a0, %lo(.L__unnamed_3)
.LBB1_4:                                # %WhileCond1
                                        # =>This Inner Loop Header: Depth=1
	lw	a0, -520(s0)
	lw	a1, -516(s0)
	bge	a0, a1, .LBB1_6
# %bb.5:                                # %WhileLoop2
                                        #   in Loop: Header=BB1_4 Depth=1
	lw	a0, -520(s0)
	slli	a0, a0, 2
	add	a0, s2, a0
	lw	a1, 0(a0)
	mv	a0, s1
	call	printf@plt
	lw	a0, -520(s0)
	addiw	a0, a0, 1
	sw	a0, -520(s0)
	j	.LBB1_4
.LBB1_6:                                # %WhileEnd3
	li	a0, 0
	addi	sp, s0, -1152
	ld	ra, 1144(sp)                    # 8-byte Folded Reload
	ld	s0, 1136(sp)                    # 8-byte Folded Reload
	ld	s1, 1128(sp)                    # 8-byte Folded Reload
	ld	s2, 1120(sp)                    # 8-byte Folded Reload
	ld	s3, 1112(sp)                    # 8-byte Folded Reload
	ld	s4, 1104(sp)                    # 8-byte Folded Reload
	ld	s5, 1096(sp)                    # 8-byte Folded Reload
	ld	s6, 1088(sp)                    # 8-byte Folded Reload
	ld	s7, 1080(sp)                    # 8-byte Folded Reload
	ld	s8, 1072(sp)                    # 8-byte Folded Reload
	ld	s9, 1064(sp)                    # 8-byte Folded Reload
	ld	s10, 1056(sp)                   # 8-byte Folded Reload
	ld	s11, 1048(sp)                   # 8-byte Folded Reload
	addi	sp, sp, 1152
	ret
.Lfunc_end1:
	.size	main, .Lfunc_end1-main
	.cfi_endproc
                                        # -- End function
	.type	.L__unnamed_1,@object           # @0
	.section	.rodata.str1.1,"aMS",@progbits,1
.L__unnamed_1:
	.asciz	"\"%d\""
	.size	.L__unnamed_1, 5

	.type	.L__unnamed_2,@object           # @1
.L__unnamed_2:
	.asciz	"\"%d\""
	.size	.L__unnamed_2, 5

	.type	.L__unnamed_3,@object           # @2
.L__unnamed_3:
	.asciz	"\"%d\\n\""
	.size	.L__unnamed_3, 7

	.section	".note.GNU-stack","",@progbits
