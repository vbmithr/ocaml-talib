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

  val compute :
    period:int -> kind:kind -> outbuf:float array -> inbuf:float array -> int
    (** [compute ~period ~kind ~outbuf ~inbuf] compute a moving
        average of type [kind], write the result in [outbuf], and
        return the index from where outbuf contains meaningful data. *)
end

module WellesWilder : sig
  val plus_dm :
    ?period:int -> out:float array -> high:float array ->
    low:float array -> unit -> int
  val minus_dm :
    ?period:int -> out:float array -> high:float array ->
    low:float array -> unit -> int
    (** UpMove = today's high − yesterday's high
        DownMove = yesterday's low − today's low
        if UpMove > DownMove and UpMove > 0, then +DM = UpMove, else +DM = 0
        if DownMove > UpMove and DownMove > 0, then −DM = DownMove, else −DM = 0 *)

  val tr :
    out:float array -> high:float array ->
    low:float array -> close:float array -> int
    (** The true range is the largest of the:

        * Most recent period's high minus the most recent period's low

        * Absolute value of the most recent period's high minus the
        previous close

        * Absolute value of the most recent period's low minus the
        previous close
    *)

  val atr :
    ?period:int -> out:float array -> high:float array ->
    low:float array -> close:float array -> unit -> int
    (** ATR_0 = 1/n * sum(TR)
        ATR_n = 1/n * [ATR_n-1 * (n-1) + TR_t] *)

  val natr :
    ?period:int -> out:float array -> high:float array ->
    low:float array -> close:float array -> unit -> int

  val plus_di :
    ?period:int -> out:float array -> high:float array ->
    low:float array -> close:float array -> unit -> int
  val minus_di :
    ?period:int -> out:float array -> high:float array ->
    low:float array -> close:float array -> unit -> int
    (** After selecting the number of periods (Wilder used 14 days
        originally), +DI and −DI are:

        +DI = 100 times the smoothed moving average of (+DM) divided
        by average true range

        −DI = 100 times the smoothed moving average of (−DM) divided
        by average true range *)

  val dx :
    ?period:int -> out:float array -> high:float array ->
    low:float array -> close:float array -> unit -> int
  (** (+DI − −DI) divided by (+DI + −DI) *)

  val adx :
    ?period:int -> out:float array -> high:float array ->
    low:float array -> close:float array -> unit -> int
  (** A.D.X. = 100 times the smoothed moving average of the absolute
      value of (+DI − −DI) divided by (+DI + −DI) *)

  val adxr :
    ?period:int -> out:float array -> high:float array ->
    low:float array -> close:float array -> unit -> int
  (** Average Directional Movement Rating quantifies momentum change in
      the ADX. It is calculated by adding two values of ADX (the current
      value and a value n periods back), then dividing by two. *)
end

module BigTrends : sig
  val accbands :
    ?period:int ->
    upper:float array -> middle:float array -> lower:float array ->
    high:float array -> low:float array -> close:float array -> unit -> int
    (** https://www.bigtrends.com/education/catching-big-trends-with-acceleration-bands/ *)
end
