open Bigarray
open Talib

let input = Array1.create float64 c_layout 100

let _ = Array1.fill input 100.

let start, nb_elts, output = ma 0 99 input 16 SMA


let _ =
  Printf.printf "start = %d, nb_elts = %d\n" start nb_elts;
  for i = 0 to nb_elts-1 do
    Printf.printf "%.2f " output.{i}
  done;
  print_endline ""
