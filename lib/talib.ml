(*
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
 *)

module FA = struct
  open Bigarray
  type t = (float, float64_elt, c_layout) Array1.t

  let create = Array1.create float64 c_layout
  let fill = Array1.fill
  let length = Array1.dim
end

module Opt = struct
  let default d = function
    | Some v -> v
    | None -> d
end

(** Moving Averages *)
module MA = struct
  type kind = SMA | EMA | WMA | DEMA | TEMA | TRIMA | KAMA | MAMA | T3

  external ma : FA.t -> FA.t -> (int * int * int * kind) -> int * int = "stub_ma"

  let compute ?(pos=0) ?len ~src ~dst ~period ~kind () =
    let len = Opt.default (FA.length src - 1) len in
    ma src dst (pos, len, period, kind)
end

type roc_type = ROC | ROCP | ROCR | ROCR100

(** Trend spotting *)

(** Directional movement and related indicators *)

(** DM+ *)
external minus_dm : int -> int -> FA.t -> FA.t -> int
  -> int * int * FA.t = "stub_minus_dm"

(** DM- *)
external plus_dm : int -> int -> FA.t -> FA.t -> int
  -> int * int * FA.t = "stub_plus_dm"

(** DMI+ *)
external minus_di : int -> int -> FA.t -> FA.t -> FA.t -> int
  -> int * int * FA.t = "stub_minus_di_byte" "stub_minus_di"

(** DMI- *)
external plus_di : int -> int -> FA.t -> FA.t -> FA.t -> int
  -> int * int * FA.t = "stub_plus_di_byte" "stub_plus_di"

(** Directional Movement Index *)
external dx : int -> int -> FA.t -> FA.t -> FA.t -> int
  -> int * int * FA.t = "stub_dx_byte" "stub_dx"

(** Average Directional Movement Index *)
external adx : int -> int -> FA.t -> FA.t -> FA.t -> int
  -> int * int * FA.t = "stub_adx_byte" "stub_adx"

(** Average Directional Movement Index Rating *)
external adxr : int -> int -> FA.t -> FA.t -> FA.t -> int
  -> int * int * FA.t = "stub_adxr_byte" "stub_adxr"

(** Parabolic SAR *)
external sar : int -> int -> FA.t -> FA.t -> float -> float
  -> int * int * FA.t = "stub_sar_byte" "stub_sar"

(** Aroon Index *)
external aroon : int -> int -> FA.t -> FA.t -> int
  -> int * int * FA.t * FA.t = "stub_aroon"

(** Aroon Oscillator *)
external aroonosc : int -> int -> FA.t -> FA.t -> int
  -> int * int * FA.t = "stub_aroonosc"

(** Measure of volatility and enveloppes *)

external beta : int -> int -> FA.t -> FA.t -> int
  -> int * int * FA.t = "stub_beta"

external stddev : int -> int -> FA.t -> int -> float
  -> int * int * FA.t = "stub_stddev"

(** True Range *)
external trange : int -> int -> FA.t -> FA.t -> FA.t
  -> int * int * FA.t = "stub_trange"

(** Average True Range *)
external atr : int -> int -> FA.t -> FA.t -> FA.t
  -> int -> int * int * FA.t = "stub_atr_byte" "stub_atr"

(** Normalized Average True Range *)
external natr : int -> int -> FA.t -> FA.t -> FA.t
  -> int -> int * int * FA.t = "stub_natr_byte" "stub_natr"

(** Accerelation Bands *)
external accbands : int -> int -> FA.t -> FA.t -> FA.t
  -> int -> int * int * FA.t * FA.t * FA.t =
    "stub_accbands_byte" "stub_accbands"

(** Bollinger Bands *)
external bbands : int -> int -> FA.t -> int -> float -> float
  -> MA.kind -> int * int * FA.t * FA.t * FA.t = "stub_bbands_byte" "stub_bbands"

(** Donchian channel *)
external minmax : int -> int -> FA.t -> int
  -> int * int * FA.t * FA.t = "stub_minmax"

(** Volume indexes *)

(** On Balance Volume *)
external obv : int -> int -> FA.t -> FA.t ->
  int * int * FA.t = "stub_obv"

(** Volume oscillators *)

(** Accumulation Distribution (AD) *)
external ad : int -> int -> FA.t -> FA.t -> FA.t
  -> FA.t -> int * int * FA.t = "stub_ad_byte" "stub_ad"

(** AD Oscillator *)
external adosc : int -> int -> FA.t -> FA.t
  -> FA.t -> FA.t -> int -> int
    -> int * int * FA.t = "stub_adosc_byte" "stub_adosc"

(** Momentum indexes and oscillators *)

(** Moving Averages Convergence Divergence *)
external macd : int -> int -> FA.t -> int -> int -> int
  -> int * int * FA.t * FA.t * FA.t = "stub_macd_byte" "stub_macd"

external macdext : int -> int -> FA.t ->
  int -> MA.kind -> int -> MA.kind -> int -> MA.kind
    -> int * int * FA.t * FA.t * FA.t = "stub_macdext_byte" "stub_macd"

(** Absolute Price Oscillator *)
external apo : int -> int -> FA.t -> int -> int -> MA.kind
  -> int * int * FA.t = "stub_apo_byte" "stub_apo"

(** Percentage Price Oscillator *)
external ppo : int -> int -> FA.t -> int -> int -> MA.kind
  -> int * int * FA.t = "stub_ppo_byte" "stub_ppo"

(** Momentum *)
external mom : int -> int -> FA.t -> int
  -> int * int * FA.t = "stub_mom"

(** Rate of Change *)
external roc : int -> int -> FA.t -> int -> roc_type
  -> int * int * FA.t = "stub_roc"

(** Relative Strengh Index *)
external rsi : int -> int -> FA.t -> int
  -> int * int * FA.t = "stub_rsi"

(** Slow Stochastic Oscillator *)
external stoch : int -> int -> FA.t -> FA.t -> FA.t
  -> int -> int -> MA.kind -> int -> MA.kind
    -> int * int * FA.t * FA.t = "stub_stoch_byte" "stub_stoch"

(** Fast Stochastic Oscillator *)
external stochf : int -> int -> FA.t -> FA.t -> FA.t
  -> int -> int -> MA.kind ->
    int * int * FA.t * FA.t = "stub_stochf_byte" "stub_stochf"

(** William’s %R *)
external willr : int -> int -> FA.t -> FA.t -> FA.t -> int
  -> int * int * FA.t = "stub_willr_byte" "stub_willr"

(** Commodity Channel Index *)
external cci : int -> int -> FA.t -> FA.t -> FA.t -> int
  -> int * int * FA.t = "stub_cci_byte" "stub_cci"

(** Ultimate oscillator *)
external ultosc : int -> int -> FA.t -> FA.t -> FA.t
  -> int -> int -> int -> int * int * FA.t = "stub_ultosc_byte" "stub_ultosc"
