/*---------------------------------------------------------------------------*
  Project:  TwlBrom - libraries - GCD
  File:     gcdfirm_blowfish_table.c

  Copyright 2007 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: $
  $NoKeywords: $
 *---------------------------------------------------------------------------*/
#include <firm/gcd/blowfish.h>


const BLOWFISH_CTX  GCDi_BlowfishInitTableGCDFIRM = {

        0x7595a8ee, 0x84fff32d, 0x58f8aec6, 0x6f6444c2, 
        0x10a6cfbc, 0xbee1b813, 0x88efabc3, 0xc72026cd, 
        0xc00b913a, 0x9fb074c0, 0x56d4830f, 0x69abdee5, 
        0xcf6e5ff2, 0xd7febe2f, 0x84f5d5e2, 0x73a1ccda, 
        0x44205999, 0x74278f63, 

        0xf0907253, 0x1c95d48f, 0x7cdbce99, 0xa8b9508a, 
        0x79379f9e, 0x129144fe, 0xd2b3554d, 0x72d702c6, 
        0xce058143, 0x72b411b8, 0x9acf2ae7, 0x62c0d195, 
        0x7d0861e5, 0x333ac8f6, 0xafc17b59, 0x7fabab12, 
        0x5a20b8df, 0x43c908e1, 0xdf057b54, 0x65237d17, 
        0x8988581c, 0x1d02cad9, 0xdde63c8a, 0x302fee12, 
        0x0abedd9d, 0x586fb574, 0x10130aad, 0x0a1ead35, 
        0xfe6f0870, 0x8cac4f02, 0x9c56ef2c, 0xc0ab9bcd, 
        0x7faf9a52, 0xef822dcd, 0x2bc0fdc2, 0xde22a557, 
        0xccf82867, 0x582a9d19, 0xd2790715, 0xdc8df689, 
        0x250ca6e2, 0xfe35236d, 0x8648e2d6, 0xaa0bf6e7, 
        0xd1240620, 0x413a5ea7, 0x4cf59143, 0x4f4f5472, 
        0xa5f29a08, 0x1fff4e8f, 0x14f0ec2d, 0x47d6f42a, 
        0x85b021f0, 0x7836f20a, 0xd908d0d7, 0xbdcc9dd5, 
        0xa6ac0bfb, 0x96fb7daf, 0xb65476ff, 0xbde99b51, 
        0xe8c84b8e, 0x72c88630, 0x3f8d0979, 0x5c1e45dc, 
        0x7555b1db, 0x3edb5a90, 0xb07fac66, 0xf7316aba, 
        0x84a088bd, 0xf0b2fb9d, 0x014b48e1, 0x6d0967e3, 
        0xa38d60e4, 0x148eedf2, 0x81898864, 0xfe0d73aa, 
        0x58c37bd5, 0x8ce2c345, 0x82951de7, 0x17be1aa6, 
        0xbfe8ad1b, 0x4d6b4176, 0x3a0da43d, 0x50a4dcac, 
        0x69f1282e, 0x16b49576, 0x6b521ffe, 0x67588174, 
        0xb3de1d28, 0x06198cbd, 0xeea240ea, 0xd13e358e, 
        0x3664b06c, 0x59f4e227, 0xb54122d3, 0x94bb71e3, 
        0x0315fb94, 0x647301d6, 0x943f1f0d, 0x7a2aaec4, 
        0x51bf88f7, 0x712c091a, 0x6d3b6e3e, 0x6eb24d52, 
        0x9fc82ca4, 0x8ffc188e, 0xbe31140a, 0x1d3e5756, 
        0xc574e16e, 0xb105a793, 0x94f658ec, 0x6ed4864c, 
        0xb2bae3cf, 0xe342cf15, 0xf2bc4d27, 0x090334b1, 
        0xc2632a42, 0x884f0092, 0xa59abd51, 0xe9d203f9, 
        0x7d122257, 0x02a709aa, 0xac9fc39b, 0x4840beed, 
        0x74be37a4, 0x24b9a4d3, 0x8178bca7, 0x606b85e5, 
        0x1dcb46b2, 0xe6112060, 0xbd44008a, 0xd1be2964, 
        0xcfcc5032, 0x74e10e43, 0x53fac5ab, 0x84a6e0a4, 
        0x9080997a, 0xa31a0100, 0xcee21c1c, 0xebcee973, 
        0x77e9a4c7, 0x3a261b9b, 0xce49ca16, 0xec3a432d, 
        0x1410c1bf, 0x8d22c824, 0xb0018266, 0x7964e2e2, 
        0xfcc6eb14, 0x12e6e035, 0xca689d0a, 0x5f9f39fc, 
        0xbf14f7e9, 0x5d7813f2, 0x87347401, 0x1a107660, 
        0xfeaa1bb7, 0x53ebb1a2, 0xfc47a457, 0xf71cde17, 
        0x25379a36, 0xb2ed205d, 0x1225bf36, 0x14536bd4, 
        0x31138cdf, 0xeeecb7f4, 0xbb6e5b19, 0x39877d0f, 
        0x4366ac24, 0xfb13893c, 0x3a7039b2, 0x3a1b8037, 
        0xfc668634, 0x0a3fb783, 0x50380526, 0x9c0e4b1a, 
        0x462b9398, 0x0e6c7d2d, 0x689a929e, 0x715701e6, 
        0x2e61d17d, 0x09da9145, 0xfb143ba1, 0x5b199259, 
        0xc4e3a5ee, 0x0b4bda9a, 0xe18c526c, 0x73171c1a, 
        0x1572a94b, 0x6d15b729, 0x71509e91, 0x571bc76e, 
        0x8c721018, 0x1fcc1742, 0xa6602c75, 0x787f88a9, 
        0x0598f9c4, 0x5addc61b, 0x8e9b7b41, 0x2f4daf72, 
        0xd9f09e2a, 0xe76054ca, 0x28bc0b4e, 0x4a320c32, 
        0xdf2b687e, 0x2cdffbcc, 0x77f16b69, 0x5d425665, 
        0xcf207fd9, 0x2e4d166d, 0x46e57957, 0x37f50f39, 
        0x6742b74a, 0xbb21df47, 0xe2df0964, 0x0dd6d989, 
        0x6f635a6e, 0x8f05a457, 0x6e5dc010, 0xeae76f43, 
        0x135c206a, 0x876bd938, 0x1ccbc607, 0xaf600e28, 
        0x0daa4fe0, 0x95e0fe33, 0x093e44b1, 0x1d16b2ad, 
        0x8d710ba2, 0x3ca3c1d9, 0x8f54a8e1, 0x7eb11ec8, 
        0xcdb82a0e, 0xde1aff6d, 0x68ae2ce2, 0x80e1ca3e, 
        0x67d60c2c, 0xac6ad1da, 0x5330c802, 0x5f67a04d, 
        0x5d6f3c9d, 0x1f4725b0, 0x094a4c69, 0x4c1dea21, 
        0xfd09ced5, 0x270fc341, 0xf16081f5, 0x54dcbdb4, 
        0x72a36bf5, 0xbeabc16a, 0xdd82bb02, 0xf0e75d20, 
        0xea6a64b0, 0x85cb5c2c, 0xd53a5aaa, 0x400f91d1, 

        0xc020695e, 0xa3d05c76, 0x8ac00446, 0xe0ebe1ce, 
        0x7ed2ca13, 0x7f41bbca, 0x09daffc0, 0x16d39c09, 
        0xd417fe9e, 0x11fc4b36, 0x87b92111, 0x581cea89, 
        0x6a51516d, 0xa691f994, 0x06e5c6ab, 0x81200780, 
        0xe6ea60b7, 0x8d0967af, 0x32f81d79, 0x1bf63b78, 
        0xeefe70bb, 0x74123b42, 0xf7345b16, 0x7aaa1388, 
        0x0152a394, 0xb5463ea1, 0xe7968633, 0xf6b00f17, 
        0xfee65926, 0xfac95f88, 0xf7788838, 0x404d27c8, 
        0x0a40725a, 0xac948618, 0xb2fb966f, 0x730b40c3, 
        0x3fa5b3a0, 0x2a4a7b57, 0xe2ee0994, 0xe2662b03, 
        0xa517c253, 0x5fcd9ac2, 0x7cf1861a, 0xfb9c6d92, 
        0x726cfcf6, 0x6bc20855, 0xe03c7757, 0x15f7aefc, 
        0x0490f4b2, 0xc5c49d9e, 0xd91bc403, 0x84799016, 
        0x5e8b5d2f, 0xdd8aef68, 0x4225b87a, 0xd3912770, 
        0x56f84df2, 0xe191d469, 0xb6306514, 0xf66b7461, 
        0xaa528b42, 0xd7d8d211, 0x0409e809, 0x3e995489, 
        0x984e2cd0, 0x21da8726, 0xa901dcce, 0xc59ed627, 
        0xa508a395, 0xe67e1c10, 0x7786c594, 0x7db49c12, 
        0xf3a048fa, 0x6c03c939, 0x5fe538b2, 0xe68d94f1, 
        0x74116818, 0xbc041b38, 0x37e9f59f, 0xd5f0d6b4, 
        0x3abedc09, 0xf2277fcf, 0xb1c090ca, 0x179fbeaf, 
        0x6799f269, 0x4ef2e1ba, 0x9a8530fe, 0xe629bad3, 
        0xef2d1806, 0xefe0d41a, 0x8fbd8038, 0xae93b3b8, 
        0xb96af69a, 0xe976f30a, 0x3735edf2, 0xa10aab80, 
        0x572bc346, 0xd9d352e5, 0xa88382fb, 0xc36d9a6a, 
        0x622169f5, 0x2b668147, 0xc68d8e94, 0xd83725df, 
        0x75ca8dc0, 0xe0fef07d, 0x3020348f, 0xd7e941c5, 
        0x0f18da00, 0x9909caca, 0x1b5f4c03, 0x611ba66e, 
        0xe3c25c8d, 0x87fe1654, 0x20ed099e, 0x2eef6251, 
        0xf8b62747, 0xa8863716, 0x2e654e0a, 0x17985515, 
        0xd121a7f0, 0xf0545a5b, 0xed9f9da3, 0xfe607b10, 
        0x3afc599b, 0xa3c13305, 0x9667a20a, 0xbd639f0c, 
        0xe647e3a0, 0x0e1304b2, 0x26a31cec, 0xd1435273, 
        0x33845341, 0xbe3383f5, 0x22e5e07f, 0xb516aed2, 
        0xe7dad3c1, 0x7e0b2eec, 0x7709d235, 0x48923397, 
        0x086b62a6, 0x05270843, 0x48073d32, 0x3e22db8e, 
        0x7b0fd2eb, 0x9199531d, 0xa47e9efc, 0x76b1bf31, 
        0xee7b6f31, 0xdc6de2c0, 0x120d4d2c, 0x1c7d1a8b, 
        0xd9192142, 0x5251ce66, 0x26dd0acf, 0x18073f04, 
        0x5901f0a3, 0xfc24fea0, 0xe9d4474b, 0xbbda7bdd, 
        0x66cb45f6, 0x66137a90, 0xa010a036, 0xa3fff96c, 
        0x61c8194f, 0x553e0b2b, 0x72b54de2, 0x59aeefe9, 
        0xda01dab4, 0xdac48b91, 0xbba66e7a, 0xa3819de2, 
        0x1f950fce, 0xa3c4d697, 0xc4e28dce, 0x530179ee, 
        0xaa7cc068, 0x1b44146a, 0xb267d209, 0x984ff1be, 
        0x90fd796b, 0xe0e42a5f, 0x36d033fb, 0x13c2f482, 
        0x3b19a86d, 0xff0ad256, 0xf06acb47, 0x0d4fbfa0, 
        0x53246fd3, 0xf9296dd5, 0x42bb5d4a, 0xd4d86e75, 
        0x96442650, 0x0bdebc51, 0xb3cee98d, 0x188c83e2, 
        0xbe632850, 0x9a0ce659, 0xc51250cd, 0x141b9f77, 
        0x292844d4, 0xa8ce50d4, 0xe6f471a3, 0xe51b7ef9, 
        0xece33b79, 0x1ec17a6a, 0x01a0125e, 0x09071e04, 
        0xbfe72df4, 0x170ed1cf, 0x2fa259ac, 0x4821704f, 
        0x95b82704, 0xcd1e0c6a, 0xb57a33ce, 0x057204fe, 
        0x7617de6b, 0xaa72f1d5, 0x4b46d61a, 0xac797378, 
        0x4984d9cf, 0x40726022, 0x2b425b5c, 0x4ca25dab, 
        0xa0e23aa3, 0x4fe1527a, 0x6fd3b7ac, 0xeb47ba60, 
        0xcde7c8b7, 0x9aef5d0f, 0x821674cd, 0xc258ea7d, 
        0xa6a813a5, 0x93e88a84, 0x8f32d2e3, 0x58ae440d, 
        0xc5799715, 0x425284d0, 0x1b696e64, 0x7d3ce93a, 
        0xdad0f25c, 0xc4b0dd14, 0x7079e2e5, 0xa9e8e61d, 
        0xfaf686b7, 0x1cf1b87b, 0x31ab43c7, 0xdc45d1bb, 
        0x386cb6ec, 0xcad283f2, 0x4dccbfaf, 0x4934f28b, 
        0x2fbc3dd4, 0x789b64f7, 0xb2e8918f, 0x506acbf7, 

        0x50a13360, 0xd128d4d3, 0xba687526, 0xc5474940, 
        0x6bb5dfc7, 0xef9bdf1f, 0x92cc643b, 0xfb2ad4f0, 
        0x4ff9410b, 0xb013c81e, 0x9fe69574, 0x5fed0d88, 
        0xcfe87720, 0x09cddf06, 0x9e57696f, 0xc429dfb9, 
        0x460c5dd2, 0x9b9e505b, 0xc012bcf6, 0xd955bdda, 
        0x7310ed31, 0xcdaaebe2, 0xc9761ff6, 0x5de00f45, 
        0x66a5e949, 0x45c5df1d, 0x96a38fab, 0x18939d5b, 
        0x94015083, 0xd27b1379, 0xe10107e7, 0xdaef6ef8, 
        0xaf8f83b3, 0xafd37029, 0x7d6803e0, 0x3a545055, 
        0xfd419925, 0xb49fa25f, 0x533ad3f4, 0xc49f3fe4, 
        0x9b9eb196, 0x2015408e, 0xd6f46485, 0xa8e66479, 
        0x5b8866e1, 0xc97d478d, 0xb7fcb30a, 0xddefdff0, 
        0x34afb94c, 0xa155d92f, 0xf53979b1, 0xf0cdd075, 
        0xf25accae, 0xe4208afd, 0x5b11bb77, 0x37b337e4, 
        0xa69da8be, 0x28a9ee86, 0xb284b30e, 0xc3527598, 
        0xf423936e, 0x7e2e1d51, 0xcaf2613d, 0x7505391e, 
        0x252d3dd5, 0x00d18203, 0x7ef4577e, 0x244e98a9, 
        0xb73b5840, 0xb0f9c9ed, 0xa8d4bc23, 0xb7228243, 
        0x241418d3, 0x39fd4429, 0xe8ab9b37, 0x3a74ecdf, 
        0xbf99499c, 0x70c3eb26, 0xc6ac5d10, 0x7085410a, 
        0x9bc5ca24, 0x37cf4d32, 0x5a407af1, 0x7f38c2af, 
        0x6cf95726, 0x2934cce9, 0x478e4a5e, 0x86bccd71, 
        0x46673804, 0x5cd7e9da, 0x601c0e47, 0x32f3c95c, 
        0x98f3b207, 0x2a9f09f2, 0xa68e3b9b, 0xe0a67f44, 
        0x8d4801eb, 0x0d650900, 0x2dbd9d8f, 0x9113fe47, 
        0x5a317b0e, 0x3d5a8d71, 0xfbd60e45, 0x86f6eedc, 
        0x3f77fec6, 0xe56a0bb2, 0x32ab5ef7, 0x2262c429, 
        0x7ed387c6, 0x0087c87e, 0x6570e4b7, 0x648d80e1, 
        0xc3bd761a, 0x5c3c0c47, 0x9ac5b07c, 0x6ecb158f, 
        0x73e2d323, 0x5095435e, 0x21a97ee4, 0x0c599519, 
        0x1f6c6441, 0xee52efd7, 0xbd886ee2, 0x66ec3c66, 
        0x0e42820c, 0xb4f244cb, 0xa56f2efc, 0xc0302f16, 
        0xf9b795aa, 0x60a00f3f, 0xa83fb0a9, 0xe9b2f724, 
        0xa3c3b44f, 0x8151cc80, 0x2ae0e99c, 0x0cb0ff00, 
        0x2e9a646d, 0x991d2cd6, 0xef2bf16b, 0x0a610ad2, 
        0x1674ea07, 0x567fcfe7, 0xf05ef5af, 0xdfdf47cb, 
        0x6c3ebb59, 0x2f052cad, 0x4701ca04, 0x0c65164a, 
        0xa285ecb3, 0x348fd20a, 0x7915f8ff, 0xdc269d33, 
        0x74578f72, 0x763ced80, 0x53275951, 0x8c51eebd, 
        0x6d8b4452, 0x5267c34e, 0xe9b7197b, 0x912800ab, 
        0x10d207a4, 0x4238eaf7, 0x2171bd12, 0x9c7eff0b, 
        0x251b79ff, 0x41bb7753, 0xecea6583, 0x031393e5, 
        0x49a58fe9, 0x83bb7587, 0x4a2a3156, 0xa3ab8da7, 
        0x38f774aa, 0xd3844d4e, 0x7cc81418, 0x894ca09d, 
        0x341ade56, 0x9574d6a5, 0xd2299751, 0xdbd43293, 
        0x253d53e8, 0x64005cc4, 0x813de56f, 0x631c3cda, 
        0x931681bd, 0x77dd0ab8, 0x15d6b56f, 0x2a3106b1, 
        0x603102bf, 0xfef29a3d, 0x648baa38, 0x470ae791, 
        0x02e625ab, 0x04904d5d, 0x3b31cea4, 0xa9a2126d, 
        0x76814575, 0x4c6a5511, 0xe2d7c619, 0x840d8ca5, 
        0x4d15e8f8, 0x59256a95, 0xf1ed6a56, 0xb996efab, 
        0x5da9c913, 0x7652bed8, 0xedbda0be, 0x59f81908, 
        0xd1d45ed7, 0x00b5f876, 0x986b97e4, 0x0bf99862, 
        0xf3a448c6, 0x05f92573, 0x9ab2c7c4, 0xbf92bbf2, 
        0xa8e5e036, 0x3030a02b, 0xab1e833b, 0x5190d039, 
        0x3d31eec2, 0x4eadf427, 0xea65d217, 0xafac4dd3, 
        0xdf5ef6fe, 0xe88cdd6c, 0xab55d1df, 0x77689e8b, 
        0x3ba6b081, 0x9ed37908, 0x42383678, 0xf9f221a6, 
        0xb6cf355d, 0x1c10aa09, 0x38645486, 0xab46320e, 
        0x6c01bdce, 0xaa9b77bf, 0xdc8a7085, 0x843c40c0, 
        0x35218b12, 0x57c15a35, 0x37a879d4, 0x41fa8671, 
        0xe9bae4f3, 0x9521c923, 0x2a32bab3, 0x5415b46b, 
        0xcb7245dd, 0x6e6407bd, 0x88477782, 0x18424ea6, 
        0x48214427, 0xd266b8b8, 0x70b796d4, 0xe4e48223, 

        0xf6a5bf45, 0xa34cc400, 0x0b62f21c, 0xf0eb6ca7, 
        0x4f8566a3, 0xd23e5904, 0x86eac0fd, 0x95080a7d, 
        0xe2926a24, 0x9983c4a1, 0x7e398b84, 0x9fccb2f1, 
        0xff70696b, 0xccb47af7, 0x61d3bf96, 0xf4170385, 
        0x0bc86fef, 0x06fb5c90, 0xce92d9fe, 0x120ca3cf, 
        0xdcde2f59, 0xd6fd2b38, 0x4258d974, 0x4b2c0a3c, 
        0x1f0967ec, 0x25987e51, 0x4e7acfc7, 0x1f7f9694, 
        0x18de3230, 0x85d9095d, 0x54737616, 0x6ec26956, 
        0x9eb3637b, 0x908a5192, 0x839fb43e, 0xefe70f2a, 
        0x42e168a5, 0x776e5c22, 0x736be3a9, 0xb72d66ed, 
        0xa4f94794, 0xb414bd55, 0x5de623d3, 0x9cd1e1a9, 
        0x42957f7e, 0x381cf593, 0x678a7d07, 0x158bb604, 
        0xe64926bd, 0x5a047438, 0x360d68cb, 0xab487a8e, 
        0x0d769a0b, 0xde3fc939, 0xf33ea9c0, 0x28b87455, 
        0xd5f6c00c, 0x853f8ffe, 0xc8d238c3, 0x3bb5473e, 
        0xc9779097, 0xc4af3a0c, 0x899098c0, 0x3c51c0e4, 
        0x7e02214e, 0xe65f85a4, 0xe7c4a857, 0x6096179e, 
        0x9c9eb559, 0x709a5f7d, 0x548f6fd5, 0xf1ad58cb, 
        0xe4bce783, 0x43ca2b6c, 0x6f43de8f, 0xa60a02f9, 
        0xbcdd0f35, 0x58f582b3, 0x30633b0d, 0xf17c7d49, 
        0x35f809f7, 0x9ee90417, 0x6360674f, 0x44375b7b, 
        0x72949c97, 0xff78dcd2, 0x08bff59a, 0x00b14d4e, 
        0xf37ef8c1, 0x6760a010, 0x87dd4dee, 0x31f5208a, 
        0x721c3add, 0x6eb9ab46, 0x29250341, 0x2fdcc721, 
        0x9d812ebb, 0x60a078a0, 0x20fcdc2d, 0xe8c594f9, 
        0x4956e488, 0x81873803, 0xf51a953d, 0x9b43c7e1, 
        0xdfd95440, 0x8dbdb07e, 0x1ecaf22f, 0xb14dceca, 
        0xc4c8003d, 0xdc26051b, 0x8bdc1011, 0x6df204db, 
        0xc72491cf, 0x9fd74623, 0xa663c57f, 0xd0f6f96d, 
        0x60f5d249, 0x10b66b81, 0xeeb26437, 0xe739332c, 
        0xeb94bdfd, 0xbfc4e0e3, 0x5d8ee7a8, 0xf676c5c3, 
        0x38357061, 0x8d3e4d68, 0xd560280b, 0x7a85b438, 
        0x00e7da19, 0x44e3021b, 0xb22bee73, 0x7af11114, 
        0x9a4aacd3, 0xbb5ea97a, 0x7993ac0b, 0x3dc12ed7, 
        0x7ac7eda8, 0x26528e57, 0xb15b78c9, 0xeae2b177, 
        0xa9bd7a3c, 0x03812180, 0x0ed1451f, 0x9ab1c57d, 
        0xa0acc3c5, 0xbf0b533d, 0x017f8413, 0x3228452a, 
        0x86eb48e1, 0x379cbcff, 0x3b200f75, 0x0cbbb62b, 
        0x7467627f, 0xc782b5e3, 0xd402c537, 0x026be842, 
        0x41a32d7a, 0x5910b6ff, 0x909926b4, 0x05bd811e, 
        0x92fd98c8, 0xcf66e980, 0x1f5eb79c, 0x4e2c31e4, 
        0x5f9b7f0c, 0x91972e91, 0xf70f2e5a, 0xd5b6b627, 
        0x3b1f243a, 0xf404cb7b, 0xe6232ec3, 0x22da8906, 
        0x0cb348ff, 0x0da6349d, 0x7c858b98, 0xd9b258f1, 
        0x623c9dd4, 0x8493c626, 0x91551f3b, 0x6ed97a53, 
        0xb5a10c32, 0x23d39f3e, 0x57e7da04, 0x8f0b2689, 
        0xebb54529, 0x0f015572, 0x2f4db833, 0x407e1d2b, 
        0xfd815f1a, 0xdeacbb64, 0xe8c38859, 0xde04110b, 
        0xb6c901ab, 0x153aee1a, 0x6b5af720, 0xc3bfe796, 
        0x8b412bc7, 0xe8cbe167, 0x60d83df2, 0x35506981, 
        0x2b8f1fc7, 0x311029cf, 0xf46fad6e, 0x7440056b, 
        0x61df9779, 0x693d02da, 0xe7d93ccc, 0x861bd3d3, 
        0xad0b85a0, 0x8bcd277a, 0xb72fceb7, 0x8ca5d84f, 
        0xc0847150, 0x1bd88428, 0x4673ca0d, 0xb030dbe5, 
        0xb51c06c1, 0x642baffb, 0xccb5043b, 0xb84aebcb, 
        0xbcd80352, 0x385520d6, 0x3b4518aa, 0xfed91bbe, 
        0x95f68932, 0x3a10ae0e, 0xd733aeaf, 0xf9f85ba7, 
        0x978ac3d1, 0x6a64540c, 0xc5a1575c, 0xc2adcd2b, 
        0xc3d45465, 0x47671f05, 0x8542fff3, 0x0f528f92, 
        0x3da8b9cd, 0x13e96928, 0x0ae5cb86, 0x55602423, 
        0x1acfb022, 0x68c9f16b, 0xbebc28a5, 0xb1d1d15e, 
        0xa9f54130, 0x0ebb0b93, 0xaf3ffdb9, 0x52078aad, 
        0xb3bf2160, 0xfb4d9d05, 0xe32785a3, 0xd05a87e5, 
        0x688e68a5, 0x38840376, 0x9b46ac8d, 0x23f286fd, 

};

