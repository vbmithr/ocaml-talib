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

CAMLprim value stub_ma (value start, value end, value input, value period, value ma_type)
{
  CAMLparam5(start, end, input, period, ma_type);
  CAMLlocal1(result);

  int beg_idx, nb_elems;
  int start_ = Int_val(start), end_ = Int_val(end), period_ = Int_val(period),
    ma_type_ = Int_val(ma_type);
  int lookback = TA_MA_Lookback(period_, (TA_MAType) ma_type_);

  TA_RetCode ret;

  int output_size = alloc_size(lookback, start_, end_);
  double *output = calloc(output_size, sizeof(double));
  if (output == NULL)
    caml_failwith("Unable to allocate memory");


  ret = TA_MA(start_, end_, (const double *) Data_bigarray_val(input),
              period_, (TA_MAType) ma_type_, &beg_idx, &nb_elems, output);

  raise_exn_on_error(ret);

  result = caml_alloc_tuple(3);
  Store_field(result, 0, Val_int(beg_idx));
  Store_field(result, 1, Val_int(nb_elems));
  Store_field(result, 2, alloc_bigarray_dims(BIGARRAY_FLOAT64|BIGARRAY_C_LAYOUT,
                                             1, output, output_size));

  CAMLreturn (result);
}
