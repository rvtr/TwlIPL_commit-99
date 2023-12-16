■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
■　Readme-NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp.txt 　　　　　　■
■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　  　　　■
■　NITRO-System for TWL 080408 ( TWL-SDK5.0 FC plus5 対応版 )　　 　 　　　■
■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■
■　Jul. 1, 2008  　　　　　　　　　　  　　　　　　　　　　　　　　　　　　■
■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■
■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■


目次
==============================================================================
　　1. はじめに
　　2. ファイルリスト


1. はじめに
==============================================================================
　　このパッチは、NITRO-System for TWL 2008/04/08版をTWL-SDK5.0 FC plus5に
　　対応させるためのものです。NITRO-System for TWLのライブラリをTWL-SDK5.0 FC plus5
　　を用いてビルドしたものに差し替えます。

　　このパッチをインストールするためには、同梱されているファイルをNITRO-System
　　 for TWL 2008/04/08版がインストールされているディレクトリに上書きコ
　　ピーしてください。


2. 修正内容
===============================================================================
    (1) snd: driverInfoサンプルデモの不具合修正

        ・sndライブラリのdriverInfoサンプルデモに問題があり、
          TWL-SDK5.0 FC plus5では動作しませんでしたが、これを修正しました。

3. ファイルリスト
===============================================================================

　　■ライブラリ
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Debug/libnnsfnd.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Debug/libnnsfnd.thumb.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Debug/libnnsfnd.TWL.HYB.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Debug/libnnsfnd.TWL.HYB.thumb.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Debug/libnnsfnd.TWL.LTD.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Debug/libnnsfnd.TWL.LTD.thumb.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Debug/libnnsg2d.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Debug/libnnsg2d.thumb.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Debug/libnnsg2d.TWL.HYB.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Debug/libnnsg2d.TWL.HYB.thumb.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Debug/libnnsg2d.TWL.LTD.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Debug/libnnsg2d.TWL.LTD.thumb.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Debug/libnnsg3d.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Debug/libnnsg3d.thumb.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Debug/libnnsg3d.TWL.HYB.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Debug/libnnsg3d.TWL.HYB.thumb.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Debug/libnnsg3d.TWL.LTD.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Debug/libnnsg3d.TWL.LTD.thumb.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Debug/libnnsgfd.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Debug/libnnsgfd.thumb.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Debug/libnnsgfd.TWL.HYB.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Debug/libnnsgfd.TWL.HYB.thumb.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Debug/libnnsgfd.TWL.LTD.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Debug/libnnsgfd.TWL.LTD.thumb.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Debug/libnnsmcs.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Debug/libnnsmcs.thumb.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Debug/libnnsmcs.TWL.HYB.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Debug/libnnsmcs.TWL.HYB.thumb.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Debug/libnnsmcs.TWL.LTD.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Debug/libnnsmcs.TWL.LTD.thumb.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Debug/libnnssnd.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Debug/libnnssnd.thumb.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Debug/libnnssnd.TWL.HYB.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Debug/libnnssnd.TWL.HYB.thumb.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Debug/libnnssnd.TWL.LTD.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Debug/libnnssnd.TWL.LTD.thumb.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Release/libnnsfnd.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Release/libnnsfnd.thumb.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Release/libnnsfnd.TWL.HYB.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Release/libnnsfnd.TWL.HYB.thumb.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Release/libnnsfnd.TWL.LTD.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Release/libnnsfnd.TWL.LTD.thumb.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Release/libnnsg2d.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Release/libnnsg2d.thumb.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Release/libnnsg2d.TWL.HYB.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Release/libnnsg2d.TWL.HYB.thumb.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Release/libnnsg2d.TWL.LTD.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Release/libnnsg2d.TWL.LTD.thumb.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Release/libnnsg3d.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Release/libnnsg3d.thumb.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Release/libnnsg3d.TWL.HYB.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Release/libnnsg3d.TWL.HYB.thumb.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Release/libnnsg3d.TWL.LTD.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Release/libnnsg3d.TWL.LTD.thumb.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Release/libnnsgfd.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Release/libnnsgfd.thumb.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Release/libnnsgfd.TWL.HYB.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Release/libnnsgfd.TWL.HYB.thumb.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Release/libnnsgfd.TWL.LTD.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Release/libnnsgfd.TWL.LTD.thumb.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Release/libnnsmcs.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Release/libnnsmcs.thumb.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Release/libnnsmcs.TWL.HYB.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Release/libnnsmcs.TWL.HYB.thumb.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Release/libnnsmcs.TWL.LTD.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Release/libnnsmcs.TWL.LTD.thumb.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Release/libnnssnd.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Release/libnnssnd.thumb.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Release/libnnssnd.TWL.HYB.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Release/libnnssnd.TWL.HYB.thumb.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Release/libnnssnd.TWL.LTD.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Release/libnnssnd.TWL.LTD.thumb.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Rom/libnnsfnd.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Rom/libnnsfnd.thumb.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Rom/libnnsfnd.TWL.HYB.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Rom/libnnsfnd.TWL.HYB.thumb.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Rom/libnnsfnd.TWL.LTD.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Rom/libnnsfnd.TWL.LTD.thumb.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Rom/libnnsg2d.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Rom/libnnsg2d.thumb.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Rom/libnnsg2d.TWL.HYB.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Rom/libnnsg2d.TWL.HYB.thumb.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Rom/libnnsg2d.TWL.LTD.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Rom/libnnsg2d.TWL.LTD.thumb.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Rom/libnnsg3d.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Rom/libnnsg3d.thumb.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Rom/libnnsg3d.TWL.HYB.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Rom/libnnsg3d.TWL.HYB.thumb.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Rom/libnnsg3d.TWL.LTD.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Rom/libnnsg3d.TWL.LTD.thumb.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Rom/libnnsgfd.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Rom/libnnsgfd.thumb.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Rom/libnnsgfd.TWL.HYB.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Rom/libnnsgfd.TWL.HYB.thumb.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Rom/libnnsgfd.TWL.LTD.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Rom/libnnsgfd.TWL.LTD.thumb.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Rom/libnnsmcs.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Rom/libnnsmcs.thumb.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Rom/libnnsmcs.TWL.HYB.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Rom/libnnsmcs.TWL.HYB.thumb.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Rom/libnnsmcs.TWL.LTD.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Rom/libnnsmcs.TWL.LTD.thumb.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Rom/libnnssnd.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Rom/libnnssnd.thumb.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Rom/libnnssnd.TWL.HYB.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Rom/libnnssnd.TWL.HYB.thumb.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Rom/libnnssnd.TWL.LTD.a
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/lib/ARM9-TS/Rom/libnnssnd.TWL.LTD.thumb.a

　　■サンプルデモ
      NitroSystem_forTWL-080408-SDK5_0FCplus5-patch-jp/NitroSystem/build/demos/snd/driverInfo/src/main.c

