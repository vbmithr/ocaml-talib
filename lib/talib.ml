open Bigarray

type ma_type = SMA | EMA | WMA | DEMA | TEMA | TRIMA | KAMA | MAMA | T3

external ma : int -> int -> (float, float64_elt, c_layout) Array1.t
  -> int -> ma_type -> int * int * (float, float64_elt, c_layout) Array1.t = "stub_ma"
