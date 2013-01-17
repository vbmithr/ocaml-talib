(*
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
 *)

open Bigarray

type array_real = (float, float64_elt, c_layout) Array1.t

type ma_type = SMA | EMA | WMA | DEMA | TEMA | TRIMA | KAMA | MAMA | T3

type roc_type = ROC | ROCP | ROCR | ROCR100

external accbands : int -> int -> array_real -> array_real -> array_real
  -> int -> int * int * array_real * array_real * array_real =
    "stub_accbands_byte" "stub_accbands"

external ad : int -> int -> array_real -> array_real -> array_real
  -> array_real -> int * int * array_real = "stub_ad_byte" "stub_ad"

external adosc : int -> int -> array_real -> array_real
  -> array_real -> array_real -> int -> int
    -> int * int * array_real = "stub_adosc_byte" "stub_adosc"

external aroon : int -> int -> array_real -> array_real -> int
  -> int * int * array_real * array_real = "stub_aroon"

external atr : int -> int -> array_real -> array_real -> array_real
  -> int -> int * int * array_real = "stub_atr_byte" "stub_atr"

external bbands : int -> int -> array_real -> int -> float -> float
  -> ma_type -> int * int * array_real * array_real * array_real = "stub_bbands_byte" "stub_bbands"

external beta : int -> int -> array_real -> array_real -> int
  -> int * int * array_real = "stub_beta"

external cci : int -> int -> array_real -> array_real -> array_real -> int
  -> int * int * array_real = "stub_cci_byte" "stub_cci"

external ma : int -> int -> array_real
  -> int -> ma_type -> int * int * array_real = "stub_ma"

external macd : int -> int -> array_real -> int -> int -> int
  -> int * int * array_real * array_real * array_real = "stub_macd_byte" "stub_macd"

external macdext : int -> int -> array_real ->
  int -> ma_type -> int -> ma_type -> int -> ma_type
    -> int * int * array_real * array_real * array_real = "stub_macdext_byte" "stub_macd"

external minus_dm : int -> int -> array_real -> array_real -> int
  -> int * int * array_real = "stub_minus_dm"

external plus_dm : int -> int -> array_real -> array_real -> int
  -> int * int * array_real = "stub_plus_dm"

external minus_di : int -> int -> array_real -> array_real -> array_real -> int
  -> int * int * array_real = "stub_minus_di_byte" "stub_minus_di"

external plus_di : int -> int -> array_real -> array_real -> array_real -> int
  -> int * int * array_real = "stub_plus_di_byte" "stub_plus_di"

external dx : int -> int -> array_real -> array_real -> array_real -> int
  -> int * int * array_real = "stub_dx_byte" "stub_dx"

external adx : int -> int -> array_real -> array_real -> array_real -> int
  -> int * int * array_real = "stub_adx_byte" "stub_adx"

external adxr : int -> int -> array_real -> array_real -> array_real -> int
  -> int * int * array_real = "stub_adxr_byte" "stub_adxr"

external mom : int -> int -> array_real -> int
  -> int * int * array_real = "stub_mom"

external natr : int -> int -> array_real -> array_real -> array_real
  -> int -> int * int * array_real = "stub_natr_byte" "stub_natr"

external obv : int -> int -> array_real -> array_real -> int * int * array_real = "stub_obv"

external roc : int -> int -> array_real -> int -> roc_type
  -> int * int * array_real = "stub_roc"

external rsi : int -> int -> array_real -> int
  -> int * int * array_real = "stub_rsi"

external stddev : int -> int -> array_real -> int -> float
  -> int * int * array_real = "stub_stddev"

external stoch : int -> int -> array_real -> array_real -> array_real
  -> int -> int -> ma_type -> int -> ma_type
    -> int * int * array_real * array_real = "stub_stoch_byte" "stub_stoch"

external stochf : int -> int -> array_real -> array_real -> array_real
  -> int -> int -> ma_type ->
    int * int * array_real * array_real = "stub_stochf_byte" "stub_stochf"

external trange : int -> int -> array_real -> array_real -> array_real
  -> int * int * array_real = "stub_trange"

external willr : int -> int -> array_real -> array_real -> array_real -> int
  -> int * int * array_real = "stub_willr_byte" "stub_willr"
