/* This file was generated automatically by the Snowball to ISO C compiler */
/* http://snowballstem.org/ */

#include "../runtime/header.h"

#ifdef __cplusplus
extern "C" {
#endif
extern int german2_UTF_8_stem(struct SN_env * z);
#ifdef __cplusplus
}
#endif
static int r_standard_suffix(struct SN_env * z);
static int r_R2(struct SN_env * z);
static int r_R1(struct SN_env * z);
static int r_mark_regions(struct SN_env * z);
static int r_postlude(struct SN_env * z);
static int r_prelude(struct SN_env * z);
#ifdef __cplusplus
extern "C" {
#endif


extern struct SN_env * german2_UTF_8_create_env(void);
extern void german2_UTF_8_close_env(struct SN_env * z);


#ifdef __cplusplus
}
#endif
static const symbol s_0_1[2] = { 'a', 'e' };
static const symbol s_0_2[2] = { 'o', 'e' };
static const symbol s_0_3[2] = { 'q', 'u' };
static const symbol s_0_4[2] = { 'u', 'e' };
static const symbol s_0_5[2] = { 0xC3, 0x9F };

static const struct among a_0[6] =
{
/*  0 */ { 0, 0, -1, 6, 0},
/*  1 */ { 2, s_0_1, 0, 2, 0},
/*  2 */ { 2, s_0_2, 0, 3, 0},
/*  3 */ { 2, s_0_3, 0, 5, 0},
/*  4 */ { 2, s_0_4, 0, 4, 0},
/*  5 */ { 2, s_0_5, 0, 1, 0}
};

static const symbol s_1_1[1] = { 'U' };
static const symbol s_1_2[1] = { 'Y' };
static const symbol s_1_3[2] = { 0xC3, 0xA4 };
static const symbol s_1_4[2] = { 0xC3, 0xB6 };
static const symbol s_1_5[2] = { 0xC3, 0xBC };

static const struct among a_1[6] =
{
/*  0 */ { 0, 0, -1, 5, 0},
/*  1 */ { 1, s_1_1, 0, 2, 0},
/*  2 */ { 1, s_1_2, 0, 1, 0},
/*  3 */ { 2, s_1_3, 0, 3, 0},
/*  4 */ { 2, s_1_4, 0, 4, 0},
/*  5 */ { 2, s_1_5, 0, 2, 0}
};

static const symbol s_2_0[1] = { 'e' };
static const symbol s_2_1[2] = { 'e', 'm' };
static const symbol s_2_2[2] = { 'e', 'n' };
static const symbol s_2_3[3] = { 'e', 'r', 'n' };
static const symbol s_2_4[2] = { 'e', 'r' };
static const symbol s_2_5[1] = { 's' };
static const symbol s_2_6[2] = { 'e', 's' };

static const struct among a_2[7] =
{
/*  0 */ { 1, s_2_0, -1, 2, 0},
/*  1 */ { 2, s_2_1, -1, 1, 0},
/*  2 */ { 2, s_2_2, -1, 2, 0},
/*  3 */ { 3, s_2_3, -1, 1, 0},
/*  4 */ { 2, s_2_4, -1, 1, 0},
/*  5 */ { 1, s_2_5, -1, 3, 0},
/*  6 */ { 2, s_2_6, 5, 2, 0}
};

static const symbol s_3_0[2] = { 'e', 'n' };
static const symbol s_3_1[2] = { 'e', 'r' };
static const symbol s_3_2[2] = { 's', 't' };
static const symbol s_3_3[3] = { 'e', 's', 't' };

static const struct among a_3[4] =
{
/*  0 */ { 2, s_3_0, -1, 1, 0},
/*  1 */ { 2, s_3_1, -1, 1, 0},
/*  2 */ { 2, s_3_2, -1, 2, 0},
/*  3 */ { 3, s_3_3, 2, 1, 0}
};

static const symbol s_4_0[2] = { 'i', 'g' };
static const symbol s_4_1[4] = { 'l', 'i', 'c', 'h' };

static const struct among a_4[2] =
{
/*  0 */ { 2, s_4_0, -1, 1, 0},
/*  1 */ { 4, s_4_1, -1, 1, 0}
};

static const symbol s_5_0[3] = { 'e', 'n', 'd' };
static const symbol s_5_1[2] = { 'i', 'g' };
static const symbol s_5_2[3] = { 'u', 'n', 'g' };
static const symbol s_5_3[4] = { 'l', 'i', 'c', 'h' };
static const symbol s_5_4[4] = { 'i', 's', 'c', 'h' };
static const symbol s_5_5[2] = { 'i', 'k' };
static const symbol s_5_6[4] = { 'h', 'e', 'i', 't' };
static const symbol s_5_7[4] = { 'k', 'e', 'i', 't' };

static const struct among a_5[8] =
{
/*  0 */ { 3, s_5_0, -1, 1, 0},
/*  1 */ { 2, s_5_1, -1, 2, 0},
/*  2 */ { 3, s_5_2, -1, 1, 0},
/*  3 */ { 4, s_5_3, -1, 3, 0},
/*  4 */ { 4, s_5_4, -1, 2, 0},
/*  5 */ { 2, s_5_5, -1, 2, 0},
/*  6 */ { 4, s_5_6, -1, 3, 0},
/*  7 */ { 4, s_5_7, -1, 4, 0}
};

static const unsigned char g_v[] = { 17, 65, 16, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 32, 8 };

static const unsigned char g_s_ending[] = { 117, 30, 5 };

static const unsigned char g_st_ending[] = { 117, 30, 4 };

static const symbol s_0[] = { 'U' };
static const symbol s_1[] = { 'Y' };
static const symbol s_2[] = { 's', 's' };
static const symbol s_3[] = { 0xC3, 0xA4 };
static const symbol s_4[] = { 0xC3, 0xB6 };
static const symbol s_5[] = { 0xC3, 0xBC };
static const symbol s_6[] = { 'y' };
static const symbol s_7[] = { 'u' };
static const symbol s_8[] = { 'a' };
static const symbol s_9[] = { 'o' };
static const symbol s_10[] = { 'n', 'i', 's' };
static const symbol s_11[] = { 'i', 'g' };
static const symbol s_12[] = { 'e', 'r' };
static const symbol s_13[] = { 'e', 'n' };

static int r_prelude(struct SN_env * z) { /* forwardmode */
    int among_var;
    {   int c_test1 = z->c; /* test, line 35 */
        while(1) { /* repeat, line 35 */
            int c2 = z->c;
            while(1) { /* goto, line 35 */
                int c3 = z->c;
                if (in_grouping_U(z, g_v, 97, 252, 0)) goto lab1; /* grouping v, line 36 */
                z->bra = z->c; /* [, line 36 */
                {   int c4 = z->c; /* or, line 36 */
                    if (z->c == z->l || z->p[z->c] != 'u') goto lab3; /* literal, line 36 */
                    z->c++;
                    z->ket = z->c; /* ], line 36 */
                    if (in_grouping_U(z, g_v, 97, 252, 0)) goto lab3; /* grouping v, line 36 */
                    {   int ret = slice_from_s(z, 1, s_0); /* <-, line 36 */
                        if (ret < 0) return ret;
                    }
                    goto lab2;
                lab3:
                    z->c = c4;
                    if (z->c == z->l || z->p[z->c] != 'y') goto lab1; /* literal, line 37 */
                    z->c++;
                    z->ket = z->c; /* ], line 37 */
                    if (in_grouping_U(z, g_v, 97, 252, 0)) goto lab1; /* grouping v, line 37 */
                    {   int ret = slice_from_s(z, 1, s_1); /* <-, line 37 */
                        if (ret < 0) return ret;
                    }
                }
            lab2:
                z->c = c3;
                break;
            lab1:
                z->c = c3;
                {   int ret = skip_utf8(z->p, z->c, 0, z->l, 1);
                    if (ret < 0) goto lab0;
                    z->c = ret; /* goto, line 35 */
                }
            }
            continue;
        lab0:
            z->c = c2;
            break;
        }
        z->c = c_test1;
    }
    while(1) { /* repeat, line 40 */
        int c5 = z->c;
        z->bra = z->c; /* [, line 41 */
        among_var = find_among(z, a_0, 6); /* substring, line 41 */
        if (!(among_var)) goto lab4;
        z->ket = z->c; /* ], line 41 */
        switch (among_var) { /* among, line 41 */
            case 1:
                {   int ret = slice_from_s(z, 2, s_2); /* <-, line 42 */
                    if (ret < 0) return ret;
                }
                break;
            case 2:
                {   int ret = slice_from_s(z, 2, s_3); /* <-, line 43 */
                    if (ret < 0) return ret;
                }
                break;
            case 3:
                {   int ret = slice_from_s(z, 2, s_4); /* <-, line 44 */
                    if (ret < 0) return ret;
                }
                break;
            case 4:
                {   int ret = slice_from_s(z, 2, s_5); /* <-, line 45 */
                    if (ret < 0) return ret;
                }
                break;
            case 5:
                {   int ret = skip_utf8(z->p, z->c, 0, z->l, + 2); /* hop, line 46 */
                    if (ret < 0) goto lab4;
                    z->c = ret;
                }
                break;
            case 6:
                {   int ret = skip_utf8(z->p, z->c, 0, z->l, 1);
                    if (ret < 0) goto lab4;
                    z->c = ret; /* next, line 47 */
                }
                break;
        }
        continue;
    lab4:
        z->c = c5;
        break;
    }
    return 1;
}

static int r_mark_regions(struct SN_env * z) { /* forwardmode */
    z->I[0] = z->l; /* $p1 = <integer expression>, line 55 */
    z->I[1] = z->l; /* $p2 = <integer expression>, line 56 */
    {   int c_test1 = z->c; /* test, line 58 */
        {   int ret = skip_utf8(z->p, z->c, 0, z->l, + 3); /* hop, line 58 */
            if (ret < 0) return 0;
            z->c = ret;
        }
        z->I[2] = z->c; /* setmark x, line 58 */
        z->c = c_test1;
    }
    {    /* gopast */ /* grouping v, line 60 */
        int ret = out_grouping_U(z, g_v, 97, 252, 1);
        if (ret < 0) return 0;
        z->c += ret;
    }
    {    /* gopast */ /* non v, line 60 */
        int ret = in_grouping_U(z, g_v, 97, 252, 1);
        if (ret < 0) return 0;
        z->c += ret;
    }
    z->I[0] = z->c; /* setmark p1, line 60 */
    /* try, line 61 */
    if (!(z->I[0] < z->I[2])) goto lab0; /* $(<integer expression> < <integer expression>), line 61 */
    z->I[0] = z->I[2]; /* $p1 = <integer expression>, line 61 */
lab0:
    {    /* gopast */ /* grouping v, line 62 */
        int ret = out_grouping_U(z, g_v, 97, 252, 1);
        if (ret < 0) return 0;
        z->c += ret;
    }
    {    /* gopast */ /* non v, line 62 */
        int ret = in_grouping_U(z, g_v, 97, 252, 1);
        if (ret < 0) return 0;
        z->c += ret;
    }
    z->I[1] = z->c; /* setmark p2, line 62 */
    return 1;
}

static int r_postlude(struct SN_env * z) { /* forwardmode */
    int among_var;
    while(1) { /* repeat, line 66 */
        int c1 = z->c;
        z->bra = z->c; /* [, line 68 */
        among_var = find_among(z, a_1, 6); /* substring, line 68 */
        if (!(among_var)) goto lab0;
        z->ket = z->c; /* ], line 68 */
        switch (among_var) { /* among, line 68 */
            case 1:
                {   int ret = slice_from_s(z, 1, s_6); /* <-, line 69 */
                    if (ret < 0) return ret;
                }
                break;
            case 2:
                {   int ret = slice_from_s(z, 1, s_7); /* <-, line 70 */
                    if (ret < 0) return ret;
                }
                break;
            case 3:
                {   int ret = slice_from_s(z, 1, s_8); /* <-, line 71 */
                    if (ret < 0) return ret;
                }
                break;
            case 4:
                {   int ret = slice_from_s(z, 1, s_9); /* <-, line 72 */
                    if (ret < 0) return ret;
                }
                break;
            case 5:
                {   int ret = skip_utf8(z->p, z->c, 0, z->l, 1);
                    if (ret < 0) goto lab0;
                    z->c = ret; /* next, line 74 */
                }
                break;
        }
        continue;
    lab0:
        z->c = c1;
        break;
    }
    return 1;
}

static int r_R1(struct SN_env * z) { /* backwardmode */
    if (!(z->I[0] <= z->c)) return 0; /* $(<integer expression> <= <integer expression>), line 81 */
    return 1;
}

static int r_R2(struct SN_env * z) { /* backwardmode */
    if (!(z->I[1] <= z->c)) return 0; /* $(<integer expression> <= <integer expression>), line 82 */
    return 1;
}

static int r_standard_suffix(struct SN_env * z) { /* backwardmode */
    int among_var;
    {   int m1 = z->l - z->c; (void)m1; /* do, line 85 */
        z->ket = z->c; /* [, line 86 */
        if (z->c <= z->lb || z->p[z->c - 1] >> 5 != 3 || !((811040 >> (z->p[z->c - 1] & 0x1f)) & 1)) goto lab0; /* substring, line 86 */
        among_var = find_among_b(z, a_2, 7);
        if (!(among_var)) goto lab0;
        z->bra = z->c; /* ], line 86 */
        {   int ret = r_R1(z); /* call R1, line 86 */
            if (ret == 0) goto lab0;
            if (ret < 0) return ret;
        }
        switch (among_var) { /* among, line 86 */
            case 1:
                {   int ret = slice_del(z); /* delete, line 88 */
                    if (ret < 0) return ret;
                }
                break;
            case 2:
                {   int ret = slice_del(z); /* delete, line 91 */
                    if (ret < 0) return ret;
                }
                {   int m2 = z->l - z->c; (void)m2; /* try, line 92 */
                    z->ket = z->c; /* [, line 92 */
                    if (z->c <= z->lb || z->p[z->c - 1] != 's') { z->c = z->l - m2; goto lab1; } /* literal, line 92 */
                    z->c--;
                    z->bra = z->c; /* ], line 92 */
                    if (!(eq_s_b(z, 3, s_10))) { z->c = z->l - m2; goto lab1; } /* literal, line 92 */
                    {   int ret = slice_del(z); /* delete, line 92 */
                        if (ret < 0) return ret;
                    }
                lab1:
                    ;
                }
                break;
            case 3:
                if (in_grouping_b_U(z, g_s_ending, 98, 116, 0)) goto lab0; /* grouping s_ending, line 95 */
                {   int ret = slice_del(z); /* delete, line 95 */
                    if (ret < 0) return ret;
                }
                break;
        }
    lab0:
        z->c = z->l - m1;
    }
    {   int m3 = z->l - z->c; (void)m3; /* do, line 99 */
        z->ket = z->c; /* [, line 100 */
        if (z->c - 1 <= z->lb || z->p[z->c - 1] >> 5 != 3 || !((1327104 >> (z->p[z->c - 1] & 0x1f)) & 1)) goto lab2; /* substring, line 100 */
        among_var = find_among_b(z, a_3, 4);
        if (!(among_var)) goto lab2;
        z->bra = z->c; /* ], line 100 */
        {   int ret = r_R1(z); /* call R1, line 100 */
            if (ret == 0) goto lab2;
            if (ret < 0) return ret;
        }
        switch (among_var) { /* among, line 100 */
            case 1:
                {   int ret = slice_del(z); /* delete, line 102 */
                    if (ret < 0) return ret;
                }
                break;
            case 2:
                if (in_grouping_b_U(z, g_st_ending, 98, 116, 0)) goto lab2; /* grouping st_ending, line 105 */
                {   int ret = skip_utf8(z->p, z->c, z->lb, z->l, - 3); /* hop, line 105 */
                    if (ret < 0) goto lab2;
                    z->c = ret;
                }
                {   int ret = slice_del(z); /* delete, line 105 */
                    if (ret < 0) return ret;
                }
                break;
        }
    lab2:
        z->c = z->l - m3;
    }
    {   int m4 = z->l - z->c; (void)m4; /* do, line 109 */
        z->ket = z->c; /* [, line 110 */
        if (z->c - 1 <= z->lb || z->p[z->c - 1] >> 5 != 3 || !((1051024 >> (z->p[z->c - 1] & 0x1f)) & 1)) goto lab3; /* substring, line 110 */
        among_var = find_among_b(z, a_5, 8);
        if (!(among_var)) goto lab3;
        z->bra = z->c; /* ], line 110 */
        {   int ret = r_R2(z); /* call R2, line 110 */
            if (ret == 0) goto lab3;
            if (ret < 0) return ret;
        }
        switch (among_var) { /* among, line 110 */
            case 1:
                {   int ret = slice_del(z); /* delete, line 112 */
                    if (ret < 0) return ret;
                }
                {   int m5 = z->l - z->c; (void)m5; /* try, line 113 */
                    z->ket = z->c; /* [, line 113 */
                    if (!(eq_s_b(z, 2, s_11))) { z->c = z->l - m5; goto lab4; } /* literal, line 113 */
                    z->bra = z->c; /* ], line 113 */
                    {   int m6 = z->l - z->c; (void)m6; /* not, line 113 */
                        if (z->c <= z->lb || z->p[z->c - 1] != 'e') goto lab5; /* literal, line 113 */
                        z->c--;
                        { z->c = z->l - m5; goto lab4; }
                    lab5:
                        z->c = z->l - m6;
                    }
                    {   int ret = r_R2(z); /* call R2, line 113 */
                        if (ret == 0) { z->c = z->l - m5; goto lab4; }
                        if (ret < 0) return ret;
                    }
                    {   int ret = slice_del(z); /* delete, line 113 */
                        if (ret < 0) return ret;
                    }
                lab4:
                    ;
                }
                break;
            case 2:
                {   int m7 = z->l - z->c; (void)m7; /* not, line 116 */
                    if (z->c <= z->lb || z->p[z->c - 1] != 'e') goto lab6; /* literal, line 116 */
                    z->c--;
                    goto lab3;
                lab6:
                    z->c = z->l - m7;
                }
                {   int ret = slice_del(z); /* delete, line 116 */
                    if (ret < 0) return ret;
                }
                break;
            case 3:
                {   int ret = slice_del(z); /* delete, line 119 */
                    if (ret < 0) return ret;
                }
                {   int m8 = z->l - z->c; (void)m8; /* try, line 120 */
                    z->ket = z->c; /* [, line 121 */
                    {   int m9 = z->l - z->c; (void)m9; /* or, line 121 */
                        if (!(eq_s_b(z, 2, s_12))) goto lab9; /* literal, line 121 */
                        goto lab8;
                    lab9:
                        z->c = z->l - m9;
                        if (!(eq_s_b(z, 2, s_13))) { z->c = z->l - m8; goto lab7; } /* literal, line 121 */
                    }
                lab8:
                    z->bra = z->c; /* ], line 121 */
                    {   int ret = r_R1(z); /* call R1, line 121 */
                        if (ret == 0) { z->c = z->l - m8; goto lab7; }
                        if (ret < 0) return ret;
                    }
                    {   int ret = slice_del(z); /* delete, line 121 */
                        if (ret < 0) return ret;
                    }
                lab7:
                    ;
                }
                break;
            case 4:
                {   int ret = slice_del(z); /* delete, line 125 */
                    if (ret < 0) return ret;
                }
                {   int m10 = z->l - z->c; (void)m10; /* try, line 126 */
                    z->ket = z->c; /* [, line 127 */
                    if (z->c - 1 <= z->lb || (z->p[z->c - 1] != 103 && z->p[z->c - 1] != 104)) { z->c = z->l - m10; goto lab10; } /* substring, line 127 */
                    if (!(find_among_b(z, a_4, 2))) { z->c = z->l - m10; goto lab10; }
                    z->bra = z->c; /* ], line 127 */
                    {   int ret = r_R2(z); /* call R2, line 127 */
                        if (ret == 0) { z->c = z->l - m10; goto lab10; }
                        if (ret < 0) return ret;
                    }
                    {   int ret = slice_del(z); /* delete, line 129 */
                        if (ret < 0) return ret;
                    }
                lab10:
                    ;
                }
                break;
        }
    lab3:
        z->c = z->l - m4;
    }
    return 1;
}

extern int german2_UTF_8_stem(struct SN_env * z) { /* forwardmode */
    {   int c1 = z->c; /* do, line 140 */
        {   int ret = r_prelude(z); /* call prelude, line 140 */
            if (ret == 0) goto lab0;
            if (ret < 0) return ret;
        }
    lab0:
        z->c = c1;
    }
    {   int c2 = z->c; /* do, line 141 */
        {   int ret = r_mark_regions(z); /* call mark_regions, line 141 */
            if (ret == 0) goto lab1;
            if (ret < 0) return ret;
        }
    lab1:
        z->c = c2;
    }
    z->lb = z->c; z->c = z->l; /* backwards, line 142 */

    /* do, line 143 */
    {   int ret = r_standard_suffix(z); /* call standard_suffix, line 143 */
        if (ret == 0) goto lab2;
        if (ret < 0) return ret;
    }
lab2:
    z->c = z->lb;
    {   int c3 = z->c; /* do, line 144 */
        {   int ret = r_postlude(z); /* call postlude, line 144 */
            if (ret == 0) goto lab3;
            if (ret < 0) return ret;
        }
    lab3:
        z->c = c3;
    }
    return 1;
}

extern struct SN_env * german2_UTF_8_create_env(void) { return SN_create_env(0, 3, 0); }

extern void german2_UTF_8_close_env(struct SN_env * z) { SN_close_env(z, 0); }

