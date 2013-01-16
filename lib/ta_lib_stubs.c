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
