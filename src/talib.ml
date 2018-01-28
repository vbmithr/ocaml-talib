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

module MA = struct
  type kind = SMA | EMA | WMA | DEMA | TEMA | TRIMA | KAMA | MAMA | T3

  external ma :
    float array -> float array -> int -> kind -> int = "stub_ma" [@@noalloc]

  let compute ~period ~kind ~outbuf ~inbuf =
    ma outbuf inbuf period kind
end

module WellesWilder = struct
  external plus_dm :
    float array -> float array -> float array -> int -> int = "stub_plus_dm" [@@noalloc]
  external minus_dm :
    float array -> float array -> float array -> int -> int = "stub_minus_dm" [@@noalloc]

  let plus_dm ?(period=1) ~out ~high ~low () =
    plus_dm out high low period
  let minus_dm ?(period=1) ~out ~high ~low () =
    minus_dm out high low period

  external tr :
    float array -> float array -> float array -> float array -> int = "stub_trange" [@@noalloc]

  let tr ~out ~high ~low ~close =
    tr out high low close

  external atr :
    float array -> float array -> float array -> float array -> int -> int = "stub_atr" [@@noalloc]
  external natr :
    float array -> float array -> float array -> float array -> int -> int = "stub_natr" [@@noalloc]

  let atr ?(period=1) ~out ~high ~low ~close () =
    atr out high low close period
  let natr ?(period=1) ~out ~high ~low ~close () =
    natr out high low close period

  external minus_di :
    float array -> float array -> float array -> float array -> int -> int
    = "stub_minus_di" [@@noalloc]

  external plus_di :
    float array -> float array -> float array -> float array -> int -> int
    = "stub_plus_di" [@@noalloc]

  let plus_di ?(period=14) ~out ~high ~low ~close () =
    plus_di out high low close period
  let minus_di ?(period=14) ~out ~high ~low ~close () =
    minus_di out high low close period

  external dx :
    float array -> float array -> float array -> float array -> int -> int =
    "stub_dx" [@@noalloc]
  external adx :
    float array -> float array -> float array -> float array -> int -> int =
    "stub_adx" [@@noalloc]
  external adxr :
    float array -> float array -> float array -> float array -> int -> int =
    "stub_adxr" [@@noalloc]

  let dx ?(period=14) ~out ~high ~low ~close () =
    dx out high low close period
  let adx ?(period=14) ~out ~high ~low ~close () =
    adx out high low close period
  let adxr ?(period=14) ~out ~high ~low ~close () =
    adxr out high low close period
end

module BigTrends = struct
  external accbands :
    float array -> float array -> float array ->
    float array -> float array -> float array -> int -> int =
    "stub_accbands_byte" "stub_accbands" [@@noalloc]

  let accbands ?(period=20) ~upper ~middle ~lower ~high ~low ~close () =
    accbands upper middle lower high low close period
end
