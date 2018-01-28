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

(** Bigarrays of float64 *)
module FA : sig
  open Bigarray
  type t = (float, float64_elt, c_layout) Array1.t

  val create : int -> t
  (** [create 10] is a bigarray of float64 of size 10, containing
      garbage. *)

  val fill : t -> float -> unit
  (** [fill t v] writes [v] in each cell of [t]. *)

  val length : t -> int
end

(** Moving Averages *)
module MA : sig
  type kind =
    | SMA (** Simple Moving Average *)
    | EMA (** Exponential Moving Average *)
    | WMA (** Weighted Moving Average *)
    | DEMA (** Double Exponential Moving Average *)
    | TEMA (** Triple Exponential Moving Average *)
    | TRIMA (** Triangular Moving Average *)
    | KAMA (** Kaufman Adaptive Moving Average *)
    | MAMA (** MESA Adaptive Moving Average *)
    | T3 (** Triple Moving Average (T3) *)

  val compute : ?pos:int -> ?len:int -> src:FA.t -> dst:FA.t ->
    period:int -> kind:kind -> unit -> int * int
  (** [(pos, len) = compute ~pos ~len ~src ~dst ~period ~kind ()]
      compute a moving average of type [kind], write the result in
      [~dst], and return the pos and len where the result were stored.

      {b Raises.} [Invalid_argument] if the the size of [~dst] is
      insufficient to store the result and [Failure] in case of a
      TA-Lib error. *)
end
