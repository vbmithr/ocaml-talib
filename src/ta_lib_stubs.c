/*
 * Copyright (c) 2012-2014 Vincent Bernardoff <vb@luminar.eu.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

#include <caml/mlvalues.h>
#include <ta-lib/ta_func.h>

#define ARRSIZE(v) (sizeof(int) == 32 ? Wosize_val(v) / 2 : Wosize_val(v))
#define BEGIDX_OR_FAIL(ret, BegIdx) (((ret == TA_SUCCESS) ? Val_int(BegIdx) : Val_int(-1)));

CAMLprim value stub_accbands (value upper, value middle, value lower,
                              value high, value low, value close, value period)
{
    int BegIdx, NBElement;
    TA_RetCode ret;

    ret = TA_ACCBANDS(0, ARRSIZE(high),
                      Data_custom_val(high),
                      Data_custom_val(low),
                      Data_custom_val(close),
                      Int_val(period), &BegIdx, &NBElement,
                      Data_custom_val(upper),
                      Data_custom_val(middle),
                      Data_custom_val(lower));

    return BEGIDX_OR_FAIL(ret, BegIdx);
}

CAMLprim value stub_accbands_byte(value *argv, int argn)
{
  return stub_accbands(argv[0], argv[1], argv[2], argv[3],
                       argv[4], argv[5], argv[6]);
}

CAMLprim value stub_atr(value out, value high, value low, value close, value period)
{
    TA_RetCode ret;
    int BegIdx, NBElement;
    ret = TA_ATR(0, ARRSIZE(high),
                 Data_custom_val(high),
                 Data_custom_val(low),
                 Data_custom_val(close),
                 Val_int(period), &BegIdx, &NBElement,
                 Data_custom_val(out));

    BEGIDX_OR_FAIL(ret, BegIdx);
}

CAMLprim value stub_natr(value out, value high, value low, value close, value period)
{
    TA_RetCode ret;
    int BegIdx, NBElement;
    ret = TA_NATR(0, ARRSIZE(high),
                 Data_custom_val(high),
                 Data_custom_val(low),
                 Data_custom_val(close),
                 Val_int(period), &BegIdx, &NBElement,
                 Data_custom_val(out));

    BEGIDX_OR_FAIL(ret, BegIdx);
}

CAMLprim value stub_ma (value out, value in, value period, value kind)
{
    int BegIdx, NBElement;
    TA_RetCode ret;

    ret = TA_MA(0, ARRSIZE(in),
                Data_custom_val(in),
                Int_val(period),
                Int_val(kind), &BegIdx, &NBElement,
                Data_custom_val(out));

    return ((ret == TA_SUCCESS) ? Val_int(BegIdx) : Val_int(-1));
}

CAMLprim value stub_minus_dm (value out, value inhigh, value inlow, value period)
{
    int BegIdx, NBElement;
    TA_RetCode ret;
    ret = TA_MINUS_DM(0, ARRSIZE(inhigh),
                      Data_custom_val(inhigh),
                      Data_custom_val(inlow),
                      Int_val(period), &BegIdx, &NBElement,
                      Data_custom_val(out));

    return BEGIDX_OR_FAIL(ret, BegIdx);
}

CAMLprim value stub_plus_dm (value out, value inhigh, value inlow, value period)
{
    int BegIdx, NBElement;
    TA_RetCode ret;
    ret = TA_PLUS_DM(0, ARRSIZE(inhigh),
                      Data_custom_val(inhigh),
                      Data_custom_val(inlow),
                      Int_val(period), &BegIdx, &NBElement,
                      Data_custom_val(out));

    return BEGIDX_OR_FAIL(ret, BegIdx);
}

CAMLprim value stub_minus_di(value out, value high, value low,  value close, value period)
{
    TA_RetCode ret;
    int BegIdx, NBElement;
    ret = TA_MINUS_DI(0, ARRSIZE(high),
                      Data_custom_val(high),
                      Data_custom_val(low),
                      Data_custom_val(close),
                      Int_val(period), &BegIdx, &NBElement,
                      Data_custom_val(out));

    return BEGIDX_OR_FAIL(ret, BegIdx);
}

CAMLprim value stub_plus_di(value out, value high, value low,  value close, value period)
{
    TA_RetCode ret;
    int BegIdx, NBElement;
    ret = TA_PLUS_DI(0, ARRSIZE(high),
                      Data_custom_val(high),
                      Data_custom_val(low),
                      Data_custom_val(close),
                      Int_val(period), &BegIdx, &NBElement,
                      Data_custom_val(out));

    return BEGIDX_OR_FAIL(ret, BegIdx);
}

CAMLprim value stub_dx(value out, value high, value low, value close, value period)
{
    TA_RetCode ret;
    int BegIdx, NBElement;
    ret = TA_DX(0, ARRSIZE(high),
                 Data_custom_val(high),
                 Data_custom_val(low),
                 Data_custom_val(close),
                 Int_val(period), &BegIdx, &NBElement,
                 Data_custom_val(out));

    return BEGIDX_OR_FAIL(ret, BegIdx);
}

CAMLprim value stub_adx(value out, value high, value low, value close, value period)
{
    TA_RetCode ret;
    int BegIdx, NBElement;
    ret = TA_ADX(0, ARRSIZE(high),
                 Data_custom_val(high),
                 Data_custom_val(low),
                 Data_custom_val(close),
                 Int_val(period), &BegIdx, &NBElement,
                 Data_custom_val(out));

    return BEGIDX_OR_FAIL(ret, BegIdx);
}

CAMLprim value stub_adxr(value out, value high, value low, value close, value period)
{
    TA_RetCode ret;
    int BegIdx, NBElement;
    ret = TA_ADXR(0, ARRSIZE(high),
                 Data_custom_val(high),
                 Data_custom_val(low),
                 Data_custom_val(close),
                 Int_val(period), &BegIdx, &NBElement,
                 Data_custom_val(out));

    return BEGIDX_OR_FAIL(ret, BegIdx);
}

CAMLprim value stub_trange (value out, value high, value low, value close)
{
    TA_RetCode ret;
    int BegIdx, NBElement;
    ret = TA_TRANGE(0, ARRSIZE(high),
                    Data_custom_val(high),
                    Data_custom_val(low),
                    Data_custom_val(close),
                    &BegIdx, &NBElement,
                    Data_custom_val(out));

    return BEGIDX_OR_FAIL(ret, BegIdx);
}
