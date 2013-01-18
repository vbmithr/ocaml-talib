/*
 * Copyright (c) 2012 Vincent Bernardoff <vb@luminar.eu.org>
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
#include <caml/alloc.h>
#include <caml/memory.h>
#include <caml/fail.h>
#include <caml/bigarray.h>

#include <sys/param.h>
#include <ta-lib/ta_func.h>

void raise_exn_on_error(TA_RetCode ret)
{
  if (ret != TA_SUCCESS)
    {
      TA_RetCodeInfo info;
      TA_SetRetCodeInfo(ret, &info);
      caml_failwith(info.infoStr);
    }
}

int alloc_size (int lookback, int startidx, int endidx)
{
  int max_value = MAX(lookback, startidx);
  return max_value > endidx ? 0 : endidx-max_value+1;
}

CAMLprim value stub_accbands (value start, value end, value inhigh, value inlow,
                              value inclose, value period)
{
  CAMLparam5(start, end, inhigh, inlow, inclose);
  CAMLxparam1(period);
  CAMLlocal1(result);

  int beg_idx, nb_elems;
  int start_ = Int_val(start), end_ = Int_val(end), period_ = Int_val(period);
  int lookback = TA_ACCBANDS_Lookback(period_);
  int output_size = alloc_size(lookback, start_, end_);
  double *output0 = calloc(output_size, sizeof(double));
  double *output1 = calloc(output_size, sizeof(double));
  double *output2 = calloc(output_size, sizeof(double));
  if (output0 == NULL || output1 == NULL || output2 == NULL)
    caml_failwith("Unable to allocate memory");

  raise_exn_on_error(TA_ACCBANDS(start_, end_,
                                 (const double *)Data_bigarray_val(inhigh),
                                 (const double *)Data_bigarray_val(inlow),
                                 (const double *)Data_bigarray_val(inclose),
                                 period_, &beg_idx, &nb_elems,
                                 output0, output1, output2));

  result = caml_alloc_tuple(5);
  Store_field(result, 0, Val_int(beg_idx));
  Store_field(result, 1, Val_int(nb_elems));
  Store_field(result, 2, alloc_bigarray_dims(BIGARRAY_FLOAT64|BIGARRAY_C_LAYOUT,
                                             1, output0, output_size));
  Store_field(result, 3, alloc_bigarray_dims(BIGARRAY_FLOAT64|BIGARRAY_C_LAYOUT,
                                             1, output1, output_size));
  Store_field(result, 4, alloc_bigarray_dims(BIGARRAY_FLOAT64|BIGARRAY_C_LAYOUT,
                                             1, output2, output_size));

  CAMLreturn(result);

}

CAMLprim value stub_accbands_byte(value *argv, int argn)
{
  return stub_accbands(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

CAMLprim value stub_ad(value start, value end, value inhigh, value inlow,
                       value inclose, value involume)
{
  CAMLparam5(start, end, inhigh, inlow, inclose);
  CAMLxparam1(involume);
  CAMLlocal1(result);

  int beg_idx, nb_elems;
  int start_ = Int_val(start), end_ = Int_val(end);
  int lookback = TA_AD_Lookback();
  int output_size = alloc_size(lookback, start_, end_);
  double *output = calloc(output_size, sizeof(double));
  if (output == NULL)
    caml_failwith("Unable to allocate memory");

  raise_exn_on_error(TA_AD(start_, end_,
                           (const double *)Data_bigarray_val(inhigh),
                           (const double *)Data_bigarray_val(inlow),
                           (const double *)Data_bigarray_val(inclose),
                           (const double *)Data_bigarray_val(involume),
                           &beg_idx, &nb_elems, output));

  result = caml_alloc_tuple(3);
  Store_field(result, 0, Val_int(beg_idx));
  Store_field(result, 1, Val_int(nb_elems));
  Store_field(result, 2, alloc_bigarray_dims(BIGARRAY_FLOAT64|BIGARRAY_C_LAYOUT,
                                             1, output, output_size));

  CAMLreturn(result);
}

CAMLprim value stub_ad_byte(value *argv, int argn)
{
  return stub_ad(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

CAMLprim value stub_adosc(value start, value end, value inhigh, value inlow,
                          value inclose, value involume, value fast, value slow)
{
  CAMLparam5(start, end, inhigh, inlow, inclose);
  CAMLxparam3(involume, fast, slow);
  CAMLlocal1(result);

  int beg_idx, nb_elems;
  int start_ = Int_val(start), end_ = Int_val(end);
  int fast_ = Int_val(fast), slow_ = Int_val(slow);
  int lookback = TA_ADOSC_Lookback(fast_, slow_);
  int output_size = alloc_size(lookback, start_, end_);
  double *output = calloc(output_size, sizeof(double));
  if (output == NULL)
    caml_failwith("Unable to allocate memory");

  raise_exn_on_error(TA_ADOSC(start_, end_,
                              (const double *)Data_bigarray_val(inhigh),
                              (const double *)Data_bigarray_val(inlow),
                              (const double *)Data_bigarray_val(inclose),
                              (const double *)Data_bigarray_val(involume),
                              fast_, slow_, &beg_idx, &nb_elems, output));

  result = caml_alloc_tuple(3);
  Store_field(result, 0, Val_int(beg_idx));
  Store_field(result, 1, Val_int(nb_elems));
  Store_field(result, 2, alloc_bigarray_dims(BIGARRAY_FLOAT64|BIGARRAY_C_LAYOUT,
                                             1, output, output_size));

  CAMLreturn(result);
}

CAMLprim value stub_adosc_byte(value *argv, int argn)
{
  return stub_adosc(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7]);
}

CAMLprim value stub_aroon(value start, value end, value inhigh, value inlow, value period)
{
  CAMLparam5(start, end, inhigh, inlow, period);
  CAMLlocal1(result);

  int beg_idx, nb_elems;
  int start_ = Int_val(start), end_ = Int_val(end), period_ = Int_val(period);
  int lookback = TA_AROON_Lookback(period_);
  int output_size = alloc_size(lookback, start_, end_);
  double *output0 = calloc(output_size, sizeof(double));
  double *output1 = calloc(output_size, sizeof(double));

  if (output0 == NULL || output1 == NULL)
    caml_failwith("Unable to allocate memory");

  raise_exn_on_error(TA_AROON(start_, end_,
                              (const double *)Data_bigarray_val(inhigh),
                              (const double *)Data_bigarray_val(inlow),
                              period_, &beg_idx, &nb_elems, output0, output1));

  result = caml_alloc_tuple(4);
  Store_field(result, 0, Val_int(beg_idx));
  Store_field(result, 1, Val_int(nb_elems));
  Store_field(result, 2, alloc_bigarray_dims(BIGARRAY_FLOAT64|BIGARRAY_C_LAYOUT,
                                             1, output0, output_size));
  Store_field(result, 3, alloc_bigarray_dims(BIGARRAY_FLOAT64|BIGARRAY_C_LAYOUT,
                                             1, output1, output_size));

  CAMLreturn (result);
}

CAMLprim value stub_aroonosc(value start, value end, value inhigh, value inlow, value period)
{
  CAMLparam5(start, end, inhigh, inlow, period);
  CAMLlocal1(result);

  int beg_idx, nb_elems;
  int start_ = Int_val(start), end_ = Int_val(end), period_ = Int_val(period);
  int lookback = TA_AROONOSC_Lookback(period_);
  int output_size = alloc_size(lookback, start_, end_);
  double *output = calloc(output_size, sizeof(double));

  if (output == NULL)
    caml_failwith("Unable to allocate memory");

  raise_exn_on_error(TA_AROONOSC(start_, end_,
                                 (const double *)Data_bigarray_val(inhigh),
                                 (const double *)Data_bigarray_val(inlow),
                                 period_, &beg_idx, &nb_elems, output));

  result = caml_alloc_tuple(3);
  Store_field(result, 0, Val_int(beg_idx));
  Store_field(result, 1, Val_int(nb_elems));
  Store_field(result, 2, alloc_bigarray_dims(BIGARRAY_FLOAT64|BIGARRAY_C_LAYOUT,
                                             1, output, output_size));

  CAMLreturn (result);
}

CAMLprim value stub_atr(value start, value end, value inhigh, value inlow,
                       value inclose, value period)
{
  CAMLparam5(start, end, inhigh, inlow, inclose);
  CAMLxparam1(period);
  CAMLlocal1(result);

  int beg_idx, nb_elems;
  int start_ = Int_val(start), end_ = Int_val(end), period_ = Int_val(period);
  int lookback = TA_ATR_Lookback(period_);
  int output_size = alloc_size(lookback, start_, end_);
  double *output = calloc(output_size, sizeof(double));
  if (output == NULL)
    caml_failwith("Unable to allocate memory");

  raise_exn_on_error(TA_ATR(start_, end_,
                            (const double *)Data_bigarray_val(inhigh),
                            (const double *)Data_bigarray_val(inlow),
                            (const double *)Data_bigarray_val(inclose),
                            period_, &beg_idx, &nb_elems, output));

  result = caml_alloc_tuple(3);
  Store_field(result, 0, Val_int(beg_idx));
  Store_field(result, 1, Val_int(nb_elems));
  Store_field(result, 2, alloc_bigarray_dims(BIGARRAY_FLOAT64|BIGARRAY_C_LAYOUT,
                                             1, output, output_size));

  CAMLreturn(result);
}

CAMLprim value stub_atr_byte(value *argv, int argn)
{
  return stub_atr(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}


CAMLprim value stub_bbands(value start, value end, value input, value period,
                           value devup, value devdown, value ma_type)
{
  CAMLparam5(start, end, input, period, devup);
  CAMLxparam2(devdown, ma_type);
  CAMLlocal1(result);

  int beg_idx, nb_elems;
  int start_ = Int_val(start), end_ = Int_val(end), period_ = Int_val(period),
    devup_ = Int_val(devup), devdown_ = Int_val(devdown), ma_type_ = Int_val(ma_type);

  int lookback = TA_BBANDS_Lookback(period_, devup_, devdown_, (TA_MAType)ma_type_);
  int output_size = alloc_size(lookback, start_, end_);
  double *output0 = calloc(output_size, sizeof(double));
  double *output1 = calloc(output_size, sizeof(double));
  double *output2 = calloc(output_size, sizeof(double));

  if (output0 == NULL || output1 == NULL || output2 == NULL)
    caml_failwith("Unable to allocate memory");

  raise_exn_on_error(TA_BBANDS(start_, end_,
                              (const double *)Data_bigarray_val(input),
                               period_, devup_, devdown_, (TA_MAType)ma_type_,
                               &beg_idx, &nb_elems, output0, output1, output2));

  result = caml_alloc_tuple(5);
  Store_field(result, 0, Val_int(beg_idx));
  Store_field(result, 1, Val_int(nb_elems));
  Store_field(result, 2, alloc_bigarray_dims(BIGARRAY_FLOAT64|BIGARRAY_C_LAYOUT,
                                             1, output0, output_size));
  Store_field(result, 3, alloc_bigarray_dims(BIGARRAY_FLOAT64|BIGARRAY_C_LAYOUT,
                                             1, output1, output_size));
  Store_field(result, 4, alloc_bigarray_dims(BIGARRAY_FLOAT64|BIGARRAY_C_LAYOUT,
                                             1, output2, output_size));

  CAMLreturn (result);
}

CAMLprim value stub_bbands_byte(value *argv, int argn)
{
  return stub_bbands(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

CAMLprim value stub_minmax(value start, value end, value input, value period)
{
  CAMLparam4(start, end, input, period);
  CAMLlocal1(result);

  int beg_idx, nb_elems;
  int start_ = Int_val(start), end_ = Int_val(end), period_ = Int_val(period);
  int lookback = TA_MINMAX_Lookback(period_);
  int output_size = alloc_size(lookback, start_, end_);
  double *output0 = calloc(output_size, sizeof(double));
  double *output1 = calloc(output_size, sizeof(double));

  if (output0 == NULL || output1 == NULL)
    caml_failwith("Unable to allocate memory");

  raise_exn_on_error(TA_MINMAX(start_, end_,
                               (const double *)Data_bigarray_val(input),
                               period_, &beg_idx, &nb_elems, output0, output1));

  result = caml_alloc_tuple(4);
  Store_field(result, 0, Val_int(beg_idx));
  Store_field(result, 1, Val_int(nb_elems));
  Store_field(result, 2, alloc_bigarray_dims(BIGARRAY_FLOAT64|BIGARRAY_C_LAYOUT,
                                             1, output0, output_size));
  Store_field(result, 3, alloc_bigarray_dims(BIGARRAY_FLOAT64|BIGARRAY_C_LAYOUT,
                                             1, output1, output_size));

  CAMLreturn (result);
}

CAMLprim value stub_beta (value start, value end, value price, value index,
                          value period)
{
  CAMLparam5(start, end, price, index, period);
  CAMLlocal1(result);

  int beg_idx, nb_elems;
  int start_ = Int_val(start), end_ = Int_val(end), period_ = Int_val(period);
  int lookback = TA_BETA_Lookback(period_);
  int output_size = alloc_size(lookback, start_, end_);
  double *output = calloc(output_size, sizeof(double));
  if (output == NULL)
    caml_failwith("Unable to allocate memory");

  raise_exn_on_error(TA_BETA(start_, end_,
                             (const double *) Data_bigarray_val(price),
                             (const double *) Data_bigarray_val(index),
                             period_, &beg_idx, &nb_elems, output));

  result = caml_alloc_tuple(3);
  Store_field(result, 0, Val_int(beg_idx));
  Store_field(result, 1, Val_int(nb_elems));
  Store_field(result, 2, alloc_bigarray_dims(BIGARRAY_FLOAT64|BIGARRAY_C_LAYOUT,
                                             1, output, output_size));

  CAMLreturn (result);
}

CAMLprim value stub_cci(value start, value end, value inhigh, value inlow,
                          value inclose, value period)
{
  CAMLparam5(start, end, inhigh, inlow, inclose);
  CAMLxparam1(period);
  CAMLlocal1(result);

  int beg_idx, nb_elems;
  int start_ = Int_val(start), end_ = Int_val(end), period_ = Int_val(period);
  int lookback = TA_CCI_Lookback(period_);
  int output_size = alloc_size(lookback, start_, end_);
  double *output = calloc(output_size, sizeof(double));
  if (output == NULL)
    caml_failwith("Unable to allocate memory");

  raise_exn_on_error(TA_CCI(start_, end_,
                               (const double *)Data_bigarray_val(inhigh),
                               (const double *)Data_bigarray_val(inlow),
                               (const double *)Data_bigarray_val(inclose),
                               period_, &beg_idx, &nb_elems, output));

  result = caml_alloc_tuple(3);
  Store_field(result, 0, Val_int(beg_idx));
  Store_field(result, 1, Val_int(nb_elems));
  Store_field(result, 2, alloc_bigarray_dims(BIGARRAY_FLOAT64|BIGARRAY_C_LAYOUT,
                                             1, output, output_size));

  CAMLreturn(result);
}

CAMLprim value stub_cci_byte(value *argv, int argn)
{
  return stub_cci(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

CAMLprim value stub_ma (value start, value end, value input, value period, value ma_type)
{
  CAMLparam5(start, end, input, period, ma_type);
  CAMLlocal1(result);

  int beg_idx, nb_elems;
  int start_ = Int_val(start), end_ = Int_val(end), period_ = Int_val(period),
    ma_type_ = Int_val(ma_type);
  int lookback = TA_MA_Lookback(period_, (TA_MAType) ma_type_);
  int output_size = alloc_size(lookback, start_, end_);
  double *output = calloc(output_size, sizeof(double));
  if (output == NULL)
    caml_failwith("Unable to allocate memory");

  raise_exn_on_error(TA_MA(start_, end_, (const double *) Data_bigarray_val(input),
                           period_, (TA_MAType) ma_type_, &beg_idx, &nb_elems, output));

  result = caml_alloc_tuple(3);
  Store_field(result, 0, Val_int(beg_idx));
  Store_field(result, 1, Val_int(nb_elems));
  Store_field(result, 2, alloc_bigarray_dims(BIGARRAY_FLOAT64|BIGARRAY_C_LAYOUT,
                                             1, output, output_size));

  CAMLreturn (result);
}

CAMLprim value stub_macd(value start, value end, value input,
                         value fast, value slow, value signal)
{
  CAMLparam5(start, end, input, fast, slow);
  CAMLxparam1(signal);
  CAMLlocal1(result);

  int beg_idx, nb_elems;
  int start_ = Int_val(start), end_ = Int_val(end),
    fast_ = Int_val(fast), slow_ = Int_val(slow), signal_ = Int_val(signal);
  int lookback = TA_MACD_Lookback(fast_, slow_, signal_);
  int output_size = alloc_size(lookback, start_, end_);
  double *output0 = calloc(output_size, sizeof(double));
  double *output1 = calloc(output_size, sizeof(double));
  double *output2 = calloc(output_size, sizeof(double));
  if (output0 == NULL || output1 == NULL || output2 == NULL)
    caml_failwith("Unable to allocate memory");

  raise_exn_on_error(TA_MACD(start_, end_,
                             (const double *)Data_bigarray_val(input),
                             fast_, slow_, signal_,
                             &beg_idx, &nb_elems, output0, output1, output2));

  result = caml_alloc_tuple(5);
  Store_field(result, 0, Val_int(beg_idx));
  Store_field(result, 1, Val_int(nb_elems));
  Store_field(result, 2, alloc_bigarray_dims(BIGARRAY_FLOAT64|BIGARRAY_C_LAYOUT,
                                             1, output0, output_size));
  Store_field(result, 3, alloc_bigarray_dims(BIGARRAY_FLOAT64|BIGARRAY_C_LAYOUT,
                                             1, output1, output_size));
  Store_field(result, 4, alloc_bigarray_dims(BIGARRAY_FLOAT64|BIGARRAY_C_LAYOUT,
                                             1, output2, output_size));

  CAMLreturn(result);
}

CAMLprim value stub_macd_byte(value *argv, int argn)
{
  return stub_macd(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

CAMLprim value stub_macdext(value start, value end, value input,
                             value fast, value fast_matype,
                             value slow, value slow_matype,
                             value signal, value signal_matype)
{
  CAMLparam5(start, end, input, fast, fast_matype);
  CAMLxparam4(slow, slow_matype, signal, signal_matype);
  CAMLlocal1(result);

  int beg_idx, nb_elems;
  int start_ = Int_val(start), end_ = Int_val(end),
    fast_ = Int_val(fast), slow_ = Int_val(slow), signal_ = Int_val(signal),
    fast_matype_ = Int_val(fast_matype),
    slow_matype_ = Int_val(slow_matype),
    signal_matype_ = Int_val(signal_matype);
  int lookback = TA_MACDEXT_Lookback(fast_, fast_matype_, slow_, slow_matype_,
                                     signal_, signal_matype_);
  int output_size = alloc_size(lookback, start_, end_);
  double *output0 = calloc(output_size, sizeof(double));
  double *output1 = calloc(output_size, sizeof(double));
  double *output2 = calloc(output_size, sizeof(double));
  if (output0 == NULL || output1 == NULL || output2 == NULL)
    caml_failwith("Unable to allocate memory");

  raise_exn_on_error(TA_MACDEXT(start_, end_,
                                (const double *)Data_bigarray_val(input),
                                fast_, (TA_MAType) fast_matype_,
                                slow_, (TA_MAType) slow_matype_,
                                signal_,(TA_MAType) signal_matype_,
                                &beg_idx, &nb_elems, output0, output1, output2));

  result = caml_alloc_tuple(5);
  Store_field(result, 0, Val_int(beg_idx));
  Store_field(result, 1, Val_int(nb_elems));
  Store_field(result, 2, alloc_bigarray_dims(BIGARRAY_FLOAT64|BIGARRAY_C_LAYOUT,
                                             1, output0, output_size));
  Store_field(result, 3, alloc_bigarray_dims(BIGARRAY_FLOAT64|BIGARRAY_C_LAYOUT,
                                             1, output1, output_size));
  Store_field(result, 4, alloc_bigarray_dims(BIGARRAY_FLOAT64|BIGARRAY_C_LAYOUT,
                                             1, output2, output_size));

  CAMLreturn(result);
}

CAMLprim value stub_macdext_byte(value *argv, int argn)
{
  return stub_macdext(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5],
                      argv[6], argv[7], argv[8]);
}

CAMLprim value stub_minus_dm (value start, value end, value inhigh, value inlow, value period)
{
  CAMLparam5(start, end, inhigh, inlow, period);
  CAMLlocal1(result);

  int beg_idx, nb_elems;
  int start_ = Int_val(start), end_ = Int_val(end), period_ = Int_val(period);
  int lookback = TA_MINUS_DM_Lookback(period_);
  int output_size = alloc_size(lookback, start_, end_);
  double *output = calloc(output_size, sizeof(double));
  if (output == NULL)
    caml_failwith("Unable to allocate memory");

  raise_exn_on_error(TA_MINUS_DM(start_, end_,
                            (const double *)Data_bigarray_val(inhigh),
                            (const double *)Data_bigarray_val(inlow),
                            period_, &beg_idx, &nb_elems, output));

  result = caml_alloc_tuple(3);
  Store_field(result, 0, Val_int(beg_idx));
  Store_field(result, 1, Val_int(nb_elems));
  Store_field(result, 2, alloc_bigarray_dims(BIGARRAY_FLOAT64|BIGARRAY_C_LAYOUT,
                                             1, output, output_size));

  CAMLreturn (result);
}

CAMLprim value stub_plus_dm (value start, value end, value inhigh, value inlow, value period)
{
  CAMLparam5(start, end, inhigh, inlow, period);
  CAMLlocal1(result);

  int beg_idx, nb_elems;
  int start_ = Int_val(start), end_ = Int_val(end), period_ = Int_val(period);
  int lookback = TA_PLUS_DM_Lookback(period_);
  int output_size = alloc_size(lookback, start_, end_);
  double *output = calloc(output_size, sizeof(double));
  if (output == NULL)
    caml_failwith("Unable to allocate memory");

  raise_exn_on_error(TA_PLUS_DM(start_, end_,
                            (const double *)Data_bigarray_val(inhigh),
                            (const double *)Data_bigarray_val(inlow),
                            period_, &beg_idx, &nb_elems, output));

  result = caml_alloc_tuple(3);
  Store_field(result, 0, Val_int(beg_idx));
  Store_field(result, 1, Val_int(nb_elems));
  Store_field(result, 2, alloc_bigarray_dims(BIGARRAY_FLOAT64|BIGARRAY_C_LAYOUT,
                                             1, output, output_size));

  CAMLreturn (result);
}

CAMLprim value stub_mom (value start, value end, value input, value period)
{
  CAMLparam4(start, end, input, period);
  CAMLlocal1(result);

  int beg_idx, nb_elems;
  int start_ = Int_val(start), end_ = Int_val(end), period_ = Int_val(period);
  int lookback = TA_MOM_Lookback(period_);
  int output_size = alloc_size(lookback, start_, end_);
  double *output = calloc(output_size, sizeof(double));
  if (output == NULL)
    caml_failwith("Unable to allocate memory");

  raise_exn_on_error(TA_MOM(start_, end_,
                            (const double *)Data_bigarray_val(input),
                            period_, &beg_idx, &nb_elems, output));

  result = caml_alloc_tuple(3);
  Store_field(result, 0, Val_int(beg_idx));
  Store_field(result, 1, Val_int(nb_elems));
  Store_field(result, 2, alloc_bigarray_dims(BIGARRAY_FLOAT64|BIGARRAY_C_LAYOUT,
                                             1, output, output_size));

  CAMLreturn (result);
}


CAMLprim value stub_natr(value start, value end, value inhigh, value inlow,
                       value inclose, value period)
{
  CAMLparam5(start, end, inhigh, inlow, inclose);
  CAMLxparam1(period);
  CAMLlocal1(result);

  int beg_idx, nb_elems;
  int start_ = Int_val(start), end_ = Int_val(end), period_ = Int_val(period);
  int lookback = TA_NATR_Lookback(period_);
  int output_size = alloc_size(lookback, start_, end_);
  double *output = calloc(output_size, sizeof(double));
  if (output == NULL)
    caml_failwith("Unable to allocate memory");

  raise_exn_on_error(TA_NATR(start_, end_,
                            (const double *)Data_bigarray_val(inhigh),
                            (const double *)Data_bigarray_val(inlow),
                            (const double *)Data_bigarray_val(inclose),
                            period_, &beg_idx, &nb_elems, output));

  result = caml_alloc_tuple(3);
  Store_field(result, 0, Val_int(beg_idx));
  Store_field(result, 1, Val_int(nb_elems));
  Store_field(result, 2, alloc_bigarray_dims(BIGARRAY_FLOAT64|BIGARRAY_C_LAYOUT,
                                             1, output, output_size));

  CAMLreturn(result);
}

CAMLprim value stub_natr_byte(value *argv, int argn)
{
  return stub_natr(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

CAMLprim value stub_minus_di(value start, value end, value inhigh, value inlow,
                       value inclose, value period)
{
  CAMLparam5(start, end, inhigh, inlow, inclose);
  CAMLxparam1(period);
  CAMLlocal1(result);

  int beg_idx, nb_elems;
  int start_ = Int_val(start), end_ = Int_val(end), period_ = Int_val(period);
  int lookback = TA_MINUS_DI_Lookback(period_);
  int output_size = alloc_size(lookback, start_, end_);
  double *output = calloc(output_size, sizeof(double));
  if (output == NULL)
    caml_failwith("Unable to allocate memory");

  raise_exn_on_error(TA_NATR(start_, end_,
                            (const double *)Data_bigarray_val(inhigh),
                            (const double *)Data_bigarray_val(inlow),
                            (const double *)Data_bigarray_val(inclose),
                            period_, &beg_idx, &nb_elems, output));

  result = caml_alloc_tuple(3);
  Store_field(result, 0, Val_int(beg_idx));
  Store_field(result, 1, Val_int(nb_elems));
  Store_field(result, 2, alloc_bigarray_dims(BIGARRAY_FLOAT64|BIGARRAY_C_LAYOUT,
                                             1, output, output_size));

  CAMLreturn(result);
}

CAMLprim value stub_minus_di_byte(value *argv, int argn)
{
  return stub_minus_di(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

CAMLprim value stub_plus_di(value start, value end, value inhigh, value inlow,
                       value inclose, value period)
{
  CAMLparam5(start, end, inhigh, inlow, inclose);
  CAMLxparam1(period);
  CAMLlocal1(result);

  int beg_idx, nb_elems;
  int start_ = Int_val(start), end_ = Int_val(end), period_ = Int_val(period);
  int lookback = TA_PLUS_DI_Lookback(period_);
  int output_size = alloc_size(lookback, start_, end_);
  double *output = calloc(output_size, sizeof(double));
  if (output == NULL)
    caml_failwith("Unable to allocate memory");

  raise_exn_on_error(TA_PLUS_DI(start_, end_,
                                (const double *)Data_bigarray_val(inhigh),
                                (const double *)Data_bigarray_val(inlow),
                                (const double *)Data_bigarray_val(inclose),
                                period_, &beg_idx, &nb_elems, output));

  result = caml_alloc_tuple(3);
  Store_field(result, 0, Val_int(beg_idx));
  Store_field(result, 1, Val_int(nb_elems));
  Store_field(result, 2, alloc_bigarray_dims(BIGARRAY_FLOAT64|BIGARRAY_C_LAYOUT,
                                             1, output, output_size));

  CAMLreturn(result);
}

CAMLprim value stub_plus_di_byte(value *argv, int argn)
{
  return stub_plus_di(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

CAMLprim value stub_dx(value start, value end, value inhigh, value inlow,
                       value inclose, value period)
{
  CAMLparam5(start, end, inhigh, inlow, inclose);
  CAMLxparam1(period);
  CAMLlocal1(result);

  int beg_idx, nb_elems;
  int start_ = Int_val(start), end_ = Int_val(end), period_ = Int_val(period);
  int lookback = TA_DX_Lookback(period_);
  int output_size = alloc_size(lookback, start_, end_);
  double *output = calloc(output_size, sizeof(double));
  if (output == NULL)
    caml_failwith("Unable to allocate memory");

  raise_exn_on_error(TA_DX(start_, end_,
                                (const double *)Data_bigarray_val(inhigh),
                                (const double *)Data_bigarray_val(inlow),
                                (const double *)Data_bigarray_val(inclose),
                                period_, &beg_idx, &nb_elems, output));

  result = caml_alloc_tuple(3);
  Store_field(result, 0, Val_int(beg_idx));
  Store_field(result, 1, Val_int(nb_elems));
  Store_field(result, 2, alloc_bigarray_dims(BIGARRAY_FLOAT64|BIGARRAY_C_LAYOUT,
                                             1, output, output_size));

  CAMLreturn(result);
}

CAMLprim value stub_dx_byte(value *argv, int argn)
{
  return stub_dx(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

CAMLprim value stub_adx(value start, value end, value inhigh, value inlow,
                       value inclose, value period)
{
  CAMLparam5(start, end, inhigh, inlow, inclose);
  CAMLxparam1(period);
  CAMLlocal1(result);

  int beg_idx, nb_elems;
  int start_ = Int_val(start), end_ = Int_val(end), period_ = Int_val(period);
  int lookback = TA_ADX_Lookback(period_);
  int output_size = alloc_size(lookback, start_, end_);
  double *output = calloc(output_size, sizeof(double));
  if (output == NULL)
    caml_failwith("Unable to allocate memory");

  raise_exn_on_error(TA_ADX(start_, end_,
                                (const double *)Data_bigarray_val(inhigh),
                                (const double *)Data_bigarray_val(inlow),
                                (const double *)Data_bigarray_val(inclose),
                                period_, &beg_idx, &nb_elems, output));

  result = caml_alloc_tuple(3);
  Store_field(result, 0, Val_int(beg_idx));
  Store_field(result, 1, Val_int(nb_elems));
  Store_field(result, 2, alloc_bigarray_dims(BIGARRAY_FLOAT64|BIGARRAY_C_LAYOUT,
                                             1, output, output_size));

  CAMLreturn(result);
}

CAMLprim value stub_adx_byte(value *argv, int argn)
{
  return stub_adx(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

CAMLprim value stub_adxr(value start, value end, value inhigh, value inlow,
                       value inclose, value period)
{
  CAMLparam5(start, end, inhigh, inlow, inclose);
  CAMLxparam1(period);
  CAMLlocal1(result);

  int beg_idx, nb_elems;
  int start_ = Int_val(start), end_ = Int_val(end), period_ = Int_val(period);
  int lookback = TA_ADXR_Lookback(period_);
  int output_size = alloc_size(lookback, start_, end_);
  double *output = calloc(output_size, sizeof(double));
  if (output == NULL)
    caml_failwith("Unable to allocate memory");

  raise_exn_on_error(TA_ADXR(start_, end_,
                                (const double *)Data_bigarray_val(inhigh),
                                (const double *)Data_bigarray_val(inlow),
                                (const double *)Data_bigarray_val(inclose),
                                period_, &beg_idx, &nb_elems, output));

  result = caml_alloc_tuple(3);
  Store_field(result, 0, Val_int(beg_idx));
  Store_field(result, 1, Val_int(nb_elems));
  Store_field(result, 2, alloc_bigarray_dims(BIGARRAY_FLOAT64|BIGARRAY_C_LAYOUT,
                                             1, output, output_size));

  CAMLreturn(result);
}

CAMLprim value stub_adxr_byte(value *argv, int argn)
{
  return stub_adxr(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

CAMLprim value stub_obv (value start, value end, value inprice, value involume)
{
  CAMLparam4(start, end, inprice, involume);
  CAMLlocal1(result);

  int beg_idx, nb_elems;
  int start_ = Int_val(start), end_ = Int_val(end);
  int lookback = TA_OBV_Lookback();
  int output_size = alloc_size(lookback, start_, end_);
  double *output = calloc(output_size, sizeof(double));
  if (output == NULL)
    caml_failwith("Unable to allocate memory");

  raise_exn_on_error(TA_OBV(start_, end_,
                            (const double *)Data_bigarray_val(inprice),
                            (const double *)Data_bigarray_val(involume),
                            &beg_idx, &nb_elems, output));

  result = caml_alloc_tuple(3);
  Store_field(result, 0, Val_int(beg_idx));
  Store_field(result, 1, Val_int(nb_elems));
  Store_field(result, 2, alloc_bigarray_dims(BIGARRAY_FLOAT64|BIGARRAY_C_LAYOUT,
                                             1, output, output_size));

  CAMLreturn (result);
}

CAMLprim value stub_roc (value start, value end, value input, value period, value kind)
{
  CAMLparam5(start, end, input, period, kind);
  CAMLlocal1(result);

  int beg_idx, nb_elems;
  int start_ = Int_val(start), end_ = Int_val(end),
    period_ = Int_val(period), kind_ = Int_val(kind);

  TA_RetCode (*roc_fun[4])(int, int, const double*, int, int*, int*, double*);
  int (*roc_lookback[4])(int);
  roc_fun[0] = TA_ROC; roc_lookback[0] = TA_ROC_Lookback;
  roc_fun[1] = TA_ROCP; roc_lookback[1] = TA_ROCP_Lookback;
  roc_fun[2] = TA_ROCR; roc_lookback[2] = TA_ROCR_Lookback;
  roc_fun[3] = TA_ROCR100; roc_lookback[3] = TA_ROCR100_Lookback;

  int lookback = (*roc_lookback[kind_])(period_);
  int output_size = alloc_size(lookback, start_, end_);
  double *output = calloc(output_size, sizeof(double));
  if (output == NULL)
    caml_failwith("Unable to allocate memory");

  raise_exn_on_error((*roc_fun[kind_])(start_, end_,
                                       (const double *)Data_bigarray_val(input),
                                       period_, &beg_idx, &nb_elems, output));

  result = caml_alloc_tuple(3);
  Store_field(result, 0, Val_int(beg_idx));
  Store_field(result, 1, Val_int(nb_elems));
  Store_field(result, 2, alloc_bigarray_dims(BIGARRAY_FLOAT64|BIGARRAY_C_LAYOUT,
                                             1, output, output_size));

  CAMLreturn (result);
}

CAMLprim value stub_rsi (value start, value end, value input, value period)
{
  CAMLparam4(start, end, input, period);
  CAMLlocal1(result);

  int beg_idx, nb_elems;
  int start_ = Int_val(start), end_ = Int_val(end), period_ = Int_val(period);
  int lookback = TA_RSI_Lookback(period_);
  int output_size = alloc_size(lookback, start_, end_);
  double *output = calloc(output_size, sizeof(double));
  if (output == NULL)
    caml_failwith("Unable to allocate memory");

  raise_exn_on_error(TA_RSI(start_, end_,
                            (const double *)Data_bigarray_val(input),
                            period_, &beg_idx, &nb_elems, output));

  result = caml_alloc_tuple(3);
  Store_field(result, 0, Val_int(beg_idx));
  Store_field(result, 1, Val_int(nb_elems));
  Store_field(result, 2, alloc_bigarray_dims(BIGARRAY_FLOAT64|BIGARRAY_C_LAYOUT,
                                             1, output, output_size));

  CAMLreturn (result);
}


CAMLprim value stub_stddev (value start, value end, value input,
                            value period, value nb_dev)
{
  CAMLparam5(start, end, input, period, nb_dev);
  CAMLlocal1(result);

  int beg_idx, nb_elems;
  int start_ = Int_val(start), end_ = Int_val(end), period_ = Int_val(period),
    nb_dev_ = Int_val(nb_dev);
  int lookback = TA_STDDEV_Lookback(period_, nb_dev_);
  int output_size = alloc_size(lookback, start_, end_);
  double *output = calloc(output_size, sizeof(double));
  if (output == NULL)
    caml_failwith("Unable to allocate memory");

  raise_exn_on_error(TA_STDDEV(start_, end_,
                               (const double *) Data_bigarray_val(input),
                               period_, nb_dev_, &beg_idx, &nb_elems, output));

  result = caml_alloc_tuple(3);
  Store_field(result, 0, Val_int(beg_idx));
  Store_field(result, 1, Val_int(nb_elems));
  Store_field(result, 2, alloc_bigarray_dims(BIGARRAY_FLOAT64|BIGARRAY_C_LAYOUT,
                                             1, output, output_size));

  CAMLreturn (result);
}

CAMLprim value stub_stoch(value start, value end, value inhigh, value inlow,
                          value inclose, value fastk, value slowk, value slowk_ma,
                          value slowd, value slowd_ma)
{
  CAMLparam5(start, end, inhigh, inlow, inclose);
  CAMLxparam5(fastk, slowk, slowk_ma, slowd, slowd_ma);
  CAMLlocal1(result);

  int beg_idx, nb_elems;
  int start_ = Int_val(start), end_ = Int_val(end),
    fastk_ = Int_val(fastk), slowk_ = Int_val(slowk), slowk_ma_ = Int_val(slowk_ma),
    slowd_ = Int_val(slowd), slowd_ma_ = Int_val(slowd_ma);
  int lookback = TA_STOCH_Lookback(fastk_, slowk_, (TA_MAType) slowk_ma_,
                                   slowd_, (TA_MAType) slowd_ma_);
  int output_size = alloc_size(lookback, start_, end_);
  double *output0 = calloc(output_size, sizeof(double));
  double *output1 = calloc(output_size, sizeof(double));
  if (output0 == NULL || output1 == NULL)
    caml_failwith("Unable to allocate memory");

  raise_exn_on_error(TA_STOCH(start_, end_,
                             (const double *)Data_bigarray_val(inhigh),
                             (const double *)Data_bigarray_val(inlow),
                             (const double *)Data_bigarray_val(inclose),
                              fastk_, slowk_, (TA_MAType)slowk_ma_,
                              slowd_, (TA_MAType)slowd_ma_,
                              &beg_idx, &nb_elems, output0, output1));

  result = caml_alloc_tuple(4);
  Store_field(result, 0, Val_int(beg_idx));
  Store_field(result, 1, Val_int(nb_elems));
  Store_field(result, 2, alloc_bigarray_dims(BIGARRAY_FLOAT64|BIGARRAY_C_LAYOUT,
                                             1, output0, output_size));
  Store_field(result, 3, alloc_bigarray_dims(BIGARRAY_FLOAT64|BIGARRAY_C_LAYOUT,
                                             1, output1, output_size));

  CAMLreturn(result);
}

CAMLprim value stub_stoch_byte(value *argv, int argn)
{
  return stub_stoch(argv[0], argv[1], argv[2], argv[3], argv[4],
                    argv[5], argv[6], argv[7], argv[8], argv[9]);
}

CAMLprim value stub_stochf(value start, value end, value inhigh, value inlow,
                          value inclose, value fastk, value fastd, value fastd_ma)
{
  CAMLparam5(start, end, inhigh, inlow, inclose);
  CAMLxparam3(fastk, fastd, fastd_ma);
  CAMLlocal1(result);

  int beg_idx, nb_elems;
  int start_ = Int_val(start), end_ = Int_val(end),
    fastk_ = Int_val(fastk), fastd_ = Int_val(fastd), fastd_ma_ = Int_val(fastd_ma);
  int lookback = TA_STOCHF_Lookback(fastk_, fastd_, (TA_MAType) fastd_ma_);
  int output_size = alloc_size(lookback, start_, end_);
  double *output0 = calloc(output_size, sizeof(double));
  double *output1 = calloc(output_size, sizeof(double));
  if (output0 == NULL || output1 == NULL)
    caml_failwith("Unable to allocate memory");

  raise_exn_on_error(TA_STOCHF(start_, end_,
                               (const double *)Data_bigarray_val(inhigh),
                               (const double *)Data_bigarray_val(inlow),
                               (const double *)Data_bigarray_val(inclose),
                               fastk_, fastd_, (TA_MAType)fastd_ma_,
                               &beg_idx, &nb_elems, output0, output1));

  result = caml_alloc_tuple(4);
  Store_field(result, 0, Val_int(beg_idx));
  Store_field(result, 1, Val_int(nb_elems));
  Store_field(result, 2, alloc_bigarray_dims(BIGARRAY_FLOAT64|BIGARRAY_C_LAYOUT,
                                             1, output0, output_size));
  Store_field(result, 3, alloc_bigarray_dims(BIGARRAY_FLOAT64|BIGARRAY_C_LAYOUT,
                                             1, output1, output_size));

  CAMLreturn(result);
}

CAMLprim value stub_stochf_byte(value *argv, int argn)
{
  return stub_stochf(argv[0], argv[1], argv[2], argv[3], argv[4],
                    argv[5], argv[6], argv[7]);
}

CAMLprim value stub_trange (value start, value end, value inhigh, value inlow, value inclose)
{
  CAMLparam5(start, end, inhigh, inlow, inclose);
  CAMLlocal1(result);

  int beg_idx, nb_elems;
  int start_ = Int_val(start), end_ = Int_val(end);
  int lookback = TA_TRANGE_Lookback();
  int output_size = alloc_size(lookback, start_, end_);
  double *output = calloc(output_size, sizeof(double));
  if (output == NULL)
    caml_failwith("Unable to allocate memory");

  raise_exn_on_error(TA_TRANGE(start_, end_,
                               (const double *) Data_bigarray_val(inhigh),
                               (const double *) Data_bigarray_val(inlow),
                               (const double *) Data_bigarray_val(inclose),
                               &beg_idx, &nb_elems, output));

  result = caml_alloc_tuple(3);
  Store_field(result, 0, Val_int(beg_idx));
  Store_field(result, 1, Val_int(nb_elems));
  Store_field(result, 2, alloc_bigarray_dims(BIGARRAY_FLOAT64|BIGARRAY_C_LAYOUT,
                                             1, output, output_size));

  CAMLreturn (result);
}

CAMLprim value stub_willr(value start, value end, value inhigh, value inlow,
                          value inclose, value period)
{
  CAMLparam5(start, end, inhigh, inlow, inclose);
  CAMLxparam1(period);
  CAMLlocal1(result);

  int beg_idx, nb_elems;
  int start_ = Int_val(start), end_ = Int_val(end), period_ = Int_val(period);
  int lookback = TA_WILLR_Lookback(period_);
  int output_size = alloc_size(lookback, start_, end_);
  double *output = calloc(output_size, sizeof(double));
  if (output == NULL)
    caml_failwith("Unable to allocate memory");

  raise_exn_on_error(TA_WILLR(start_, end_,
                               (const double *)Data_bigarray_val(inhigh),
                               (const double *)Data_bigarray_val(inlow),
                               (const double *)Data_bigarray_val(inclose),
                               period_, &beg_idx, &nb_elems, output));

  result = caml_alloc_tuple(3);
  Store_field(result, 0, Val_int(beg_idx));
  Store_field(result, 1, Val_int(nb_elems));
  Store_field(result, 2, alloc_bigarray_dims(BIGARRAY_FLOAT64|BIGARRAY_C_LAYOUT,
                                             1, output, output_size));

  CAMLreturn(result);
}

CAMLprim value stub_willr_byte(value *argv, int argn)
{
  return stub_willr(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

CAMLprim value stub_apo(value start, value end, value input, value fast,
                          value slow, value ma_type)
{
  CAMLparam5(start, end, input, fast, slow);
  CAMLxparam1(ma_type);
  CAMLlocal1(result);

  int beg_idx, nb_elems;
  int start_ = Int_val(start), end_ = Int_val(end), fast_ = Int_val(fast),
    slow_ = Int_val(slow), ma_type_ = Int_val(ma_type);
  int lookback = TA_APO_Lookback(fast_, slow_, (TA_MAType)ma_type_);
  int output_size = alloc_size(lookback, start_, end_);
  double *output = calloc(output_size, sizeof(double));
  if (output == NULL)
    caml_failwith("Unable to allocate memory");

  raise_exn_on_error(TA_APO(start_, end_,
                              (const double *)Data_bigarray_val(input),
                              fast_, slow_, (TA_MAType)ma_type_,
                              &beg_idx, &nb_elems, output));

  result = caml_alloc_tuple(3);
  Store_field(result, 0, Val_int(beg_idx));
  Store_field(result, 1, Val_int(nb_elems));
  Store_field(result, 2, alloc_bigarray_dims(BIGARRAY_FLOAT64|BIGARRAY_C_LAYOUT,
                                             1, output, output_size));

  CAMLreturn(result);
}

CAMLprim value stub_apo_byte(value *argv, int argn)
{
  return stub_apo(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}
CAMLprim value stub_ppo(value start, value end, value input, value fast,
                          value slow, value ma_type)
{
  CAMLparam5(start, end, input, fast, slow);
  CAMLxparam1(ma_type);
  CAMLlocal1(result);

  int beg_idx, nb_elems;
  int start_ = Int_val(start), end_ = Int_val(end), fast_ = Int_val(fast),
    slow_ = Int_val(slow), ma_type_ = Int_val(ma_type);
  int lookback = TA_PPO_Lookback(fast_, slow_, (TA_MAType)ma_type_);
  int output_size = alloc_size(lookback, start_, end_);
  double *output = calloc(output_size, sizeof(double));
  if (output == NULL)
    caml_failwith("Unable to allocate memory");

  raise_exn_on_error(TA_PPO(start_, end_,
                              (const double *)Data_bigarray_val(input),
                              fast_, slow_, (TA_MAType)ma_type_,
                              &beg_idx, &nb_elems, output));

  result = caml_alloc_tuple(3);
  Store_field(result, 0, Val_int(beg_idx));
  Store_field(result, 1, Val_int(nb_elems));
  Store_field(result, 2, alloc_bigarray_dims(BIGARRAY_FLOAT64|BIGARRAY_C_LAYOUT,
                                             1, output, output_size));

  CAMLreturn(result);
}

CAMLprim value stub_ppo_byte(value *argv, int argn)
{
  return stub_ppo(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

CAMLprim value stub_ultosc(value start, value end, value inhigh, value inlow,
                           value inclose, value p1, value p2, value p3)
{
  CAMLparam5(start, end, inhigh, inlow, inclose);
  CAMLxparam3(p1, p2, p3);
  CAMLlocal1(result);

  int beg_idx, nb_elems;
  int start_ = Int_val(start), end_ = Int_val(end), p1_ = Int_val(p1),
    p2_ = Int_val(p2), p3_ = Int_val(p3);
  int lookback = TA_ULTOSC_Lookback(p1, p2, p3);
  int output_size = alloc_size(lookback, start_, end_);
  double *output = calloc(output_size, sizeof(double));
  if (output == NULL)
    caml_failwith("Unable to allocate memory");

  raise_exn_on_error(TA_ULTOSC(start_, end_,
                               (const double *)Data_bigarray_val(inhigh),
                               (const double *)Data_bigarray_val(inlow),
                               (const double *)Data_bigarray_val(inclose),
                               p1_, p2_, p3_, &beg_idx, &nb_elems, output));

  result = caml_alloc_tuple(3);
  Store_field(result, 0, Val_int(beg_idx));
  Store_field(result, 1, Val_int(nb_elems));
  Store_field(result, 2, alloc_bigarray_dims(BIGARRAY_FLOAT64|BIGARRAY_C_LAYOUT,
                                             1, output, output_size));

  CAMLreturn(result);
}

CAMLprim value stub_ultosc_byte(value *argv, int argn)
{
  return stub_ultosc(argv[0], argv[1], argv[2], argv[3],
                     argv[4], argv[5], argv[6], argv[7]);
}

CAMLprim value stub_sar(value start, value end, value inhigh, value inlow,
                          value accel, value maximum)
{
  CAMLparam5(start, end, inhigh, inlow, accel);
  CAMLxparam1(maximum);
  CAMLlocal1(result);

  int beg_idx, nb_elems;
  int start_ = Int_val(start), end_ = Int_val(end);
  double accel_ = Double_val(accel), maximum_ = Double_val(maximum);
  int lookback = TA_SAR_Lookback(accel_, maximum_);
  int output_size = alloc_size(lookback, start_, end_);
  double *output = calloc(output_size, sizeof(double));
  if (output == NULL)
    caml_failwith("Unable to allocate memory");

  raise_exn_on_error(TA_SAR(start_, end_,
                            (const double *)Data_bigarray_val(inhigh),
                            (const double *)Data_bigarray_val(inlow),
                            accel_, maximum_, &beg_idx, &nb_elems, output));

  result = caml_alloc_tuple(3);
  Store_field(result, 0, Val_int(beg_idx));
  Store_field(result, 1, Val_int(nb_elems));
  Store_field(result, 2, alloc_bigarray_dims(BIGARRAY_FLOAT64|BIGARRAY_C_LAYOUT,
                                             1, output, output_size));

  CAMLreturn(result);
}

CAMLprim value stub_sar_byte(value *argv, int argn)
{
  return stub_sar(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}
