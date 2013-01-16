open Bigarray

type array_real = (float, float64_elt, c_layout) Array1.t

type ma_type = SMA | EMA | WMA | DEMA | TEMA | TRIMA | KAMA | MAMA | T3

external accbands : int -> int -> array_real -> array_real -> array_real
  -> int -> int * int * array_real * array_real * array_real =
    "stub_accbands_byte" "stub_accbands"

external ma : int -> int -> array_real
  -> int -> ma_type -> int * int * array_real = "stub_ma"
